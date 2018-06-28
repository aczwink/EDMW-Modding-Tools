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
#include "DBField.hpp"
#include "../definitions.hpp"
//Namespaces
using namespace ACStdLib;

//Global variables
extern ConfigurationFile g_settings;

//Forward declarations
class Object;

class DB
{
public:
	//Constructor
	DB(const String &name, const XML::Element &element);

	//Destructor
	virtual ~DB();

	//Abstract
	virtual const void *GetObjectPointer(const UI::ControllerIndex &index) const = 0;
	virtual void Load() = 0;

	//Inline
	inline const FixedArray<DBField> &GetFields() const
	{
		return this->fields;
	}

	inline const DynamicArray<uint32> &GetFilterableFields() const
	{
		return this->filterableFields;
	}

	inline const String &GetName() const
	{
		return this->name;
	}

	inline const DynamicArray<Object *> GetObjects() const
	{
		return this->objects;
	}

	inline bool IsLoaded() const
	{
		return this->isLoaded;
	}

protected:
	//Members
	bool isLoaded;
	FixedArray<DBField> fields;
	DynamicArray<uint32> filterableFields;

protected:
	DynamicArray<Object *> objects;

	//Methods
	Object *LoadObject(InputStream &inputStream);

	//Inline
	inline uint32 GetObjectSize() const
	{
		return this->objectSize;
	}

	inline Path GetPath() const
	{
		return Path(g_settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH)) / Path(u8"Data/db") / (this->name + u8".dat");
	}

private:
	//Members
	String name;
	uint32 objectSize;
};