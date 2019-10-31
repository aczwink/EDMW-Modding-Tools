/*
 * Copyright (c) 2017-2018 Amir Czwink (amir130@hotmail.de)
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

//Constructor
DBManager::DBManager()
{
	//TODO
	this->AddDB(OSFileSystem::GetInstance().GetWorkingDirectory() / Path(u8"db/dbobjects.xml"));
	//this->AddDB(OSFileSystem::GetInstance().GetWorkingDirectory() / Path(u8"db/dbtechtree.xml"));
	return;

	Path dirPath = Path(u8"db");
	auto dir = OSFileSystem::GetInstance().GetDirectory(dirPath);
	for (auto& node : *dir)
	{
		if (node.Get<1>().IsInstanceOf<Directory>())
			continue;
		Path fileName = node.Get<0>();
		if(fileName.GetFileExtension() == u8"xml")
			this->AddDB(dirPath / fileName);
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
	for (const DB *const& db : this->databases)
		delete db;
	this->databases.Release();
}

//Private methods
void DBManager::AddDB(const Path &dbDefFilePath)
{
	FileInputStream inputStream(dbDefFilePath);
	XML::Document *doc = XML::Document::Parse(inputStream);

	const XML::Element &root = doc->GetRootElement();
	ASSERT(root.GetName() == u8"Database", u8"The root element must be 'Database'");
	this->databases.Push(new DB(dbDefFilePath.GetTitle(), root));
	delete doc;
}