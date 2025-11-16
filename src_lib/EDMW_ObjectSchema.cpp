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
#include <EDMW_ObjectSchema.hpp>
//Namespaces
using namespace StdXX;
using namespace StdXX::Serialization;

//Class functions
UniquePointer<EDMW_ObjectSchema> EDMW_ObjectSchema::Load(InputStream& inputStream)
{
	Serialization::XMLDeserializer deserializer(inputStream);

	deserializer.EnterElement(u8"List");

	UniquePointer<EDMW_ObjectSchema> schema = new EDMW_ObjectSchema;

	deserializer.EnterAttributes();
	if(deserializer.HasAttribute(u8"techtree"))
		schema->isTechtree = true;
	deserializer.LeaveAttributes();

	schema->LoadXMLSchema(deserializer);

	deserializer.LeaveElement();

	return schema;
}

//Private methods
void EDMW_ObjectSchema::LoadXMLSchema(XMLDeserializer& deserializer)
{
	deserializer.EnterElement(u8"Object");

	deserializer.EnterAttributes();
	String idPropName;
	deserializer & Binding(u8"id", idPropName);
	deserializer.LeaveAttributes();

	while(deserializer.HasChildElement(u8"Property"))
	{
		deserializer.EnterElement(u8"Property");

		deserializer.EnterAttributes();

		PropertyDefinition def;

		//type
		String stringType;
		deserializer & Binding(u8"type", stringType);
		if(stringType == u8"bool")
			def.type = EDMW_SchemaPropertyType::Bool;
		else if(stringType == u8"char")
			def.type = EDMW_SchemaPropertyType::Char;
		else if(stringType == u8"float32")
			def.type = EDMW_SchemaPropertyType::Float32;
		else if(stringType == u8"int32")
			def.type = EDMW_SchemaPropertyType::Int32;
		else if(stringType == u8"uint32")
			def.type = EDMW_SchemaPropertyType::UInt32;
		else if(stringType == u8"uint32[]")
		{
			def.type = EDMW_SchemaPropertyType::UInt32;
			def.isList = true;
			def.count = 0;
		}
		else
		{
			NOT_IMPLEMENTED_ERROR; //TODO: implement me
		}

		//count
		if(deserializer.HasAttribute(u8"count"))
		{
			deserializer & Binding(u8"count", def.count);
			def.isList = true;
		}
		else if(stringType != u8"uint32[]")
			def.isList = false;

		if (deserializer.HasAttribute(u8"name"))
			deserializer & Binding(u8"name", def.name);

		uint32 index = this->properties.Push(def);

		deserializer.LeaveAttributes();

		deserializer.LeaveElement();

		if(def.name == idPropName)
			this->idPropertyIndex = static_cast<uint8>(index);
	}

	deserializer.LeaveElement();
}