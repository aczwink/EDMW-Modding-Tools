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
#include "StandardDB.hpp"
//Local
#include "StandardDBController.hpp"

//Constructor
StandardDB::StandardDB(const String &name, const XML::Element &element) : DB(name, element),
																		  objects(nullptr)
{
	this->controller = new StandardDBController(this);
}

//Destructor
StandardDB::~StandardDB()
{
	if(this->objects)
		MemFree(this->objects);

	delete this->controller;
}

//Public methods
UI::TreeController &StandardDB::GetItemController() const
{
	return *this->controller;
}

const void *StandardDB::GetObjectPointer(const ControllerIndex &index) const
{
	const byte *p = static_cast<const byte *>(this->objects);
	return &p[index.GetRow() * this->GetObjectSize()];
}

void StandardDB::Load()
{
	FileInputStream file(this->GetPath());
	DataReader reader(false, file);

	this->nObjects = reader.ReadUInt32();
	uint32 totalSize = this->nObjects * this->GetObjectSize();
	ASSERT(file.GetRemainingBytes() == totalSize);
	this->objects = MemAlloc(totalSize);
	file.ReadBytes(this->objects, totalSize);

	this->isLoaded = true;
}