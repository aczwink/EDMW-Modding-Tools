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
#include "UnknownCountDB.hpp"

//Public methods
void UnknownCountDB::Load()
{
	FileInputStream file(this->GetPath());
	DataReader reader(false, file);

	this->nObjects = static_cast<uint32>(file.GetSize() / this->GetObjectSize());
	uint32 totalSize = this->nObjects * this->GetObjectSize();
	ASSERT(file.GetRemainingBytes() == totalSize);
	this->objects = MemAlloc(totalSize);
	file.ReadBytes(this->objects, totalSize);

	this->isLoaded = true;
}