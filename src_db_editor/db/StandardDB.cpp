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
#include "StandardDB.hpp"
//Local
#include "../ui/ItemsController.hpp"

//Constructor
StandardDB::StandardDB(const String &name, const XML::Element &element) : DB(name, element)
{
}

//Destructor
StandardDB::~StandardDB()
{
}

//Public methods
const void *StandardDB::GetObjectPointer(const ControllerIndex &index) const
{
	//NOT_IMPLEMENTED_ERROR; //TODO: new implementation
	//const byte *p = static_cast<const byte *>(this->asd);
	//return &p[index.GetRow() * this->GetObjectSize()];
	return nullptr;
}

void StandardDB::Load()
{
	FileInputStream file(this->GetPath());
	DataReader reader(false, file);

	uint32 nObjects = reader.ReadUInt32();
	for(uint32 i = 0; i < nObjects; i++)
	{
		Object *row = this->LoadObject(file);
		this->objects.Push(row);
		break; //TODO
	}
	file.Skip(file.GetRemainingBytes()); //TODO

	ASSERT(file.GetRemainingBytes() == 0, u8"If you see this, please report");
	this->isLoaded = true;
}

