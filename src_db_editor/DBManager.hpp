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
#pragma once
#include <ACStdLib.hpp>
//Local
#include "DB.hpp"
using namespace ACStdLib;

class DBManager
{
public:
	//Destructor
	~DBManager();

	//Methods
	void ReleaseAll();

	//Inline
	inline DB *GetDatabase(uint32 index) const
	{
		return this->databases[index];
	}

	inline DynamicArray<DB *> GetDatabases() const
	{
		return this->databases;
	}

	inline void LoadDB(uint32 index)
	{
		if(!this->databases[index]->IsLoaded())
			this->databases[index]->Load();
	}

	//Functions
	static inline DBManager &Get()
	{
		static DBManager obj;

		return obj;
	}

private:
	//Members
	DynamicArray<DB *> databases;

	//Constructor
	DBManager();

	//Methods
	void AddDB(const Path &dbDefFilePath);
};