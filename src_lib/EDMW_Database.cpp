/*
 * Copyright (c) 2017-2025 Amir Czwink (amir130@hotmail.de)
 *
 * This file is part of EDMW-Modding-Tools.
 *
 * EDMW-Modding-Tools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EDMW-Modding-Tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EDMW-Modding-Tools.  If not, see <http://www.gnu.org/licenses/>.
 */
//Class header
#include <EDMW_Database.hpp>
//Namespaces
using namespace StdXX;

//Class functions
UniquePointer<EDMW_Database> EDMW_Database::Load(InputStream &inputStream, UniquePointer<EDMW_ObjectSchema>&& schema)
{
	UniquePointer<EDMW_Database> db = new EDMW_Database(Move(schema));
	db->LoadObjects(inputStream);

	return db;
}

//Private methods
UniquePointer<EDMW_DBObject> EDMW_Database::LoadObject(DataReader& dataReader)
{
	TextReader textReader = TextReader(dataReader.InputStream(), TextCodecType::Latin1);

	UniquePointer<EDMW_DBObject> object = new EDMW_DBObject;

	for(const auto& prop : this->schema->Properties())
	{
		if(prop.isList)
		{
			switch(prop.type)
			{
				case EDMW_SchemaPropertyType::Char:
					object->Add(textReader.ReadZeroTerminatedStringBySize(prop.count));
					break;
				case EDMW_SchemaPropertyType::Float32:
				{
					DynamicArray<EDMW_DBObjectValue> values;
					for(uint32 j = 0; j < prop.count; j++)
					{
						EDMW_DBObjectValue v;
						v.f32Value = dataReader.ReadFloat32();
						values.Push(v);
					}
					object->Add(Move(values));
				}
					break;
				case EDMW_SchemaPropertyType::UInt32:
				{
					uint32 count = (prop.count == 0) ? dataReader.ReadUInt32() : prop.count;
					DynamicArray<EDMW_DBObjectValue> values;
					for(uint32 j = 0; j < count; j++)
					{
						EDMW_DBObjectValue v;
						v.u32Value = dataReader.ReadUInt32();
						values.Push(v);
					}
					object->Add(Move(values));
				}
					break;
				default:
					NOT_IMPLEMENTED_ERROR; //TODO: implement me
			}
		}
		else
		{
			switch(prop.type)
			{
				case EDMW_SchemaPropertyType::Bool:
					object->Add(dataReader.ReadByte() != 0);
					break;
				case EDMW_SchemaPropertyType::Float32:
					object->Add(dataReader.ReadFloat32());
					break;
				case EDMW_SchemaPropertyType::Int32:
					object->Add(dataReader.ReadInt32());
					break;
				case EDMW_SchemaPropertyType::UInt32:
					object->Add(dataReader.ReadUInt32());
					break;
				default:
					NOT_IMPLEMENTED_ERROR; //TODO: implement me
			}
		}
	}

	return object;
}

void EDMW_Database::LoadObjects(InputStream& inputStream)
{
	DataReader dataReader(false, inputStream);

	if(this->schema->IsTechtree())
	{
		while(!inputStream.IsAtEnd())
		{
			uint32 nTechsInEpoch = dataReader.ReadUInt32();
			auto epoch = this->LoadObject(dataReader);

			for(uint32 i = 0; i < nTechsInEpoch; i++)
			{
				auto tech = this->LoadObject(dataReader);
				epoch->AddChild(Move(tech));
			}

			this->objects.Push(Move(epoch));
		}
	}
	else
	{
		uint32 nObjects = dataReader.ReadUInt32();
		for(uint32 i = 0; i < nObjects; i++)
		{
			auto object = this->LoadObject(dataReader);
			this->objects.Push(Move(object));
		}
	}
}