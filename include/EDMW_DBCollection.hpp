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
//Local
#include "EDMW_Database.hpp"

class EDMW_DBCollection
{
public:
	//Inline
	inline const EDMW_Database& LoadDatabase(const FileSystem::Path& dbPath, const FileSystem::Path& schemaPath)
	{
		FileInputStream fileInputStream(schemaPath);
		BufferedInputStream bufferedInputStream(fileInputStream);
		UniquePointer<EDMW_ObjectSchema> schema = EDMW_ObjectSchema::Load(bufferedInputStream);

		FileInputStream fileInputStream2(dbPath);
		BufferedInputStream bufferedInputStream2(fileInputStream2);

		this->databases[dbPath.GetTitle()] = EDMW_Database::Load(bufferedInputStream2, Move(schema));

		if(bufferedInputStream2.GetBytesAvailable() || fileInputStream2.QueryRemainingBytes())
			NOT_IMPLEMENTED_ERROR; //TODO: implement me

		return *this->databases[dbPath.GetTitle()];
	}

private:
	//State
	BinaryTreeMap<String, UniquePointer<EDMW_Database>> databases;
};