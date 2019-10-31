/*
 * Copyright (c) 2017-2019 Amir Czwink (amir130@hotmail.de)
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
#include <Std++.hpp>
//Local
#include "DBField.hpp"
#include "../definitions.hpp"
#include "Object.hpp"
//Namespaces
using namespace StdXX;

//Global variables
extern ConfigurationFile g_settings;

class DB
{
public:
	//Constructor
	inline DB(const String &name, const XML::Element& dbElement) : repeating(false), isLoaded(false), name(name), objectScheme(nullptr)
	{
		this->ParseXML(dbElement);
	}

	//Methods
	void Load();

	//Inline
	inline const DynamicArray<uint32> &GetFilterableFields() const
	{
		return this->filterableFields;
	}

	inline const DynamicArray<const DBField*>& GetFlattenedFields() const
	{
		return this->flattenedFields;
	}

	inline const String &GetName() const
	{
		return this->name;
	}

	inline uint32 GetNumberOfObjects() const
	{
		return this->root.GetNumberOfChildren();
	}

	inline const Object& GetObject(uint32 index) const
	{
		return this->root.GetChild(index);
	}

	inline const DynamicArray<DBField>& GetObjectScheme() const
	{
		return *this->objectScheme;
	}

	inline bool IsLoaded() const
	{
		return this->isLoaded;
	}

	//Functions
	static String LoadLanguageString(uint32 resourceId, uint8 langDllNumber);

private:
	//Members
	bool repeating;
	bool isLoaded;
	String name;
	DynamicArray<DBField> fields;
	Map<String, DynamicArray<DBField>> types;
	DynamicArray<uint32> filterableFields;
	DynamicArray<DBField>* objectScheme;
	DynamicArray<const DBField*> flattenedFields;
	Object root;

	//Methods
	DynamicArray<const DBField*> FlattenFields(const DynamicArray<DBField>& fields) const;
	void LoadFields(Object& object, const DynamicArray<DBField>& fields, Map<String, uint32>& virtuals, DataReader& reader, TextReader& textReader);
	DynamicArray<DBField> ParseFields(const XML::Element& element);
	void ParseXML(const XML::Element& dbElement);

	//Inline
	inline Path GetPath() const
	{
		return Path(g_settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH)) / Path(u8"Data/db") / (this->name + u8".dat");
	}
};