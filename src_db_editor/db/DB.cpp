/*
 * Copyright (c) 2017-2018 Amir Czwink (amir130@hotmail.de)
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
#include "DB.hpp"
//Local
#include "Object.hpp"

//Constructor
DB::DB(const String &name, const XML::Element &element) :isLoaded(false),
														 name(name),
														 fields(element.GetChildren().GetNumberOfElements())
{
	uint32 index = 0, offset = 0;
	for(const XML::Node *const& field : element)
	{
		ASSERT(field->GetType() == XML::NodeType::Element, u8"If you see this, please report");
		XML::Element const& fieldElement = *(XML::Element *)field;
		ASSERT(fieldElement.GetName() == "field", u8"If you see this, please report");

		DBField &dbEntry = this->fields[index];

		//type
		if(fieldElement.GetAttribute("type") == "bool")
			dbEntry.type = DBType::Bool;
		else if(fieldElement.GetAttribute("type") == "byte")
			dbEntry.type = DBType::ByteType;
		else if(fieldElement.GetAttribute("type") == "char")
			dbEntry.type = DBType::CharType;
		else if(fieldElement.GetAttribute("type") == "float32")
			dbEntry.type = DBType::Float32;
		else if(fieldElement.GetAttribute("type") == "uint32")
			dbEntry.type = DBType::UInt32;
		else
		NOT_IMPLEMENTED_ERROR;

		//name
		dbEntry.name = fieldElement.GetAttribute("name");

		//count
		if(fieldElement.HasAttribute("count"))
			dbEntry.count = fieldElement.GetAttribute("count").ToUInt32();
		else
			dbEntry.count = 1;

		//comment
		if(fieldElement.HasAttribute("comment"))
			dbEntry.comment = fieldElement.GetAttribute("comment");

		//filterable
		if(fieldElement.HasAttribute("filterable"))
			this->filterableFields.Push(index);

		//offset
		dbEntry.offset = offset;

		offset += dbEntry.GetSize();

		index++;
	}

	this->objectSize = offset;
}

//Destructor
DB::~DB()
{
	for(const auto &object : this->objects)
		delete object;
}

//Protected methods
Object *DB::LoadObject(InputStream &inputStream)
{
	Object *row = new Object(*this);

	uint32 i = 0;
	for(const auto &field : this->fields)
	{
		switch(field.type)
		{
			case DBType::CharType:
			{
				TextReader textReader(inputStream, TextCodecType::ASCII);

				String string = textReader.ReadString(100);
				row->SetValue(i, string);
			}
				break;
			case DBType::Bool:
			NOT_IMPLEMENTED_ERROR;
				break;
			case DBType::ByteType:
			NOT_IMPLEMENTED_ERROR;
				break;
			case DBType::Float32:
			NOT_IMPLEMENTED_ERROR;
				break;
			case DBType::UInt32:
			NOT_IMPLEMENTED_ERROR;
				break;
		}

		i++;
	}

	return row;
}