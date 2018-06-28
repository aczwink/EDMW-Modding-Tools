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
#include "DBManager.hpp"
//Local
#include "StandardDB.hpp"
#include "UnknownCountDB.hpp"

//Constructor
DBManager::DBManager()
{
	//TODO
	this->AddDB(Path(u8"db/dbtechtree.xml"));
	return;
	for(const Path &path : Path("db"))
	{
		if(!path.IsDirectory() && path.GetFileExtension() == "xml")
			this->AddDB(Path("db") / path);
	}
}

//Destructor
DBManager::~DBManager()
{
	this->ReleaseAll();
}

//Public methods
void DBManager::ReleaseAll()
{
	for(const DB *const& db : this->databases)
		delete db;
	this->databases.Release();
}

//Private methods
void DBManager::AddDB(const Path &dbDefFilePath)
{
	FileInputStream inputStream(dbDefFilePath);
	XML::Document *doc = XML::Document::Parse(inputStream);

	const XML::Element &root = doc->GetRootElement();
	ASSERT(root.GetName() == "Database", u8"The root element must be 'Database'");

	if(root.HasAttribute("type"))
	{
		if(root.GetAttribute("type") == "List_UnknownCount")
		{
			this->databases.Push(new UnknownCountDB(dbDefFilePath.GetTitle(), root));
		}
		else
		{
			NOT_IMPLEMENTED_ERROR;
		}
	}
	else
	{
		this->databases.Push(new StandardDB(dbDefFilePath.GetTitle(), root));
	}

	delete doc;
}