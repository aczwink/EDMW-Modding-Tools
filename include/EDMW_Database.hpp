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
//Local
#include "EDMW_ObjectSchema.hpp"
#include "EDMW_DBObject.hpp"

class EDMW_Database
{
public:
	//Constructor
	inline EDMW_Database(StdXX::UniquePointer<EDMW_ObjectSchema> schema) : schema(Move(schema))
	{
	}

	//Properties
	inline const StdXX::DynamicArray<StdXX::UniquePointer<EDMW_DBObject>>& Objects() const
	{
		return this->objects;
	}

	inline const EDMW_ObjectSchema& Schema() const
	{
		return *this->schema;
	}

	//Functions
	static StdXX::UniquePointer<EDMW_Database> Load(StdXX::InputStream& inputStream, StdXX::UniquePointer<EDMW_ObjectSchema>&& schema);

private:
	//State
	StdXX::UniquePointer<EDMW_ObjectSchema> schema;
	StdXX::DynamicArray<StdXX::UniquePointer<EDMW_DBObject>> objects;

	//Methods
	StdXX::UniquePointer<EDMW_DBObject> LoadObject(StdXX::DataReader& dataReader);
	void LoadObjects(StdXX::InputStream& inputStream);
};