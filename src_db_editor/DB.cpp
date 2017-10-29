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
	for(const XML::Node *const& entry : element)
	{
		ASSERT(entry->GetType() == XML::NodeType::Element);
		XML::Element const& entryElement = *(XML::Element *)entry;
		ASSERT(entryElement.GetName() == "entry");

		DBEntry &dbEntry = this->entries[index++];

		//type
		if(entryElement.GetAttribute("type") == "byte")
			dbEntry.type = DBType::ByteType;
		else if(entryElement.GetAttribute("type") == "char")
			dbEntry.type = DBType::CharType;
		else
		NOT_IMPLEMENTED_ERROR;

		//name
		dbEntry.name = entryElement.GetAttribute("name");

		//count
		dbEntry.count = static_cast<uint32>(StringToUInt64(entryElement.GetAttribute("count")));

		//offset
		dbEntry.offset = offset;

		offset += dbEntry.GetSize();
	}

	this->objectSize = offset;
}