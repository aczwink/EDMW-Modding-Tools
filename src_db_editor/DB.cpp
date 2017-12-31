/*
 * Copyright (c) 2017 Amir Czwink (amir130@hotmail.de)
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

//Constructor
DB::DB(const String &name, const XML::Element &element) :isLoaded(false),
														 name(name),
														 entries(element.GetChildren().GetNumberOfElements())
{
	uint32 index = 0, offset = 0;
	for(const XML::Node *const& field : element)
	{
		ASSERT(field->GetType() == XML::NodeType::Element);
		XML::Element const& fieldElement = *(XML::Element *)field;
		ASSERT(fieldElement.GetName() == "field");

		DBField &dbEntry = this->entries[index++];

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
			dbEntry.count = static_cast<uint32>(StringToUInt64(fieldElement.GetAttribute("count")));
		else
			dbEntry.count = 1;

		//comment
		if(fieldElement.HasAttribute("comment"))
			dbEntry.comment = fieldElement.GetAttribute("comment");

		//offset
		dbEntry.offset = offset;

		offset += dbEntry.GetSize();
	}

	this->objectSize = offset;
}