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
#include <StdXX.hpp>

enum class EDMW_SchemaPropertyType
{
	Bool,
	Char,
	Float32,
	Int32,
	UInt32
};

class EDMW_ObjectSchema
{
	struct PropertyDefinition
	{
		EDMW_SchemaPropertyType type;
		bool isList;
		uint32 count; //if isList = true and count = 0 => variable length list. Actual count is read from stream
		StdXX::String name;
	};
public:
	//Constructor
	inline EDMW_ObjectSchema()
	{
		this->isTechtree = false;
	}

	//Properties
	inline uint8 IdPropertyIndex() const
	{
		return this->idPropertyIndex;
	}

	inline bool IsTechtree() const
	{
		return this->isTechtree;
	}

	inline const StdXX::DynamicArray<PropertyDefinition>& Properties() const
	{
		return this->properties;
	}

	//Functions
	static StdXX::UniquePointer<EDMW_ObjectSchema> Load(StdXX::InputStream& inputStream);

private:
	//State
	bool isTechtree;
	uint8 idPropertyIndex;
	StdXX::DynamicArray<PropertyDefinition> properties;

	//Methods
	void LoadXMLSchema(StdXX::Serialization::XMLDeserializer& deserializer);
};