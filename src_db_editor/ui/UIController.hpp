/*
 * Copyright (c) 2018 Amir Czwink (amir130@hotmail.de)
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
//Local
#include "../db/DB.hpp"
#include "../db/DBManager.hpp"

class UIController
{
public:
	//Inline
	inline DB *GetActiveDB()
	{
		return DBManager::Get().GetDatabase(this->activeDBIndex);
	}

	inline Object* GetActiveObject()
	{
		return this->activeObject;
	}
	
	inline uint32 GetActiveFilterFieldIndex()
	{
		return this->GetActiveDB()->GetFilterableFields()[this->filterMethodIndex];
	}

	inline void RegisterForActiveObjChange(Function<void()>&& callback)
	{
		this->objChangeCallback = Forward<Function<void()>>(callback);
	}

	inline void SetActiveDBIndex(uint32 index)
	{
		this->activeDBIndex = index;
		DBManager::Get().LoadDB(index);
	}

	inline void SetActiveFilterMethodIndex(uint32 index)
	{
		this->filterMethodIndex = index;
	}

	inline void SetActiveObject(Object* object)
	{
		this->activeObject = object;
		this->objChangeCallback();
	}

	//Functions
	inline static UIController &Get()
	{
		static UIController state;

		return state;
	}

private:
	//Members
	uint32 activeDBIndex;
	uint32 filterMethodIndex;
	Object* activeObject;
	Function<void()> objChangeCallback;

	//Constructor
	inline UIController() : activeDBIndex(Unsigned<uint32>::Max()), filterMethodIndex(Unsigned<uint32>::Max()), activeObject(nullptr)
	{
	}
};