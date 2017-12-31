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
#include "ItemFieldsController.hpp"
//Local
#include "DB.hpp"
#include "DBManager.hpp"
#include "MainWindow.hpp"

//Constructor
ItemFieldsController::ItemFieldsController(const MainWindow &mainWindow) : mainWindow(mainWindow)
{
	this->activeItemIndex = this->CreateIndex(0, 0, nullptr);
}

//Public methods
String ItemFieldsController::GetColumnText(uint32 column) const
{
	static const char *columns[] = {"Field name", "Value", "Associated value", "Comment"};

	return columns[column];
}

uint32 ItemFieldsController::GetNumberOfRows() const
{
	DB *db = this->GetActiveDB();

	if(db)
		return db->GetEntries().GetNumberOfElements();
	return 0;
}

String ItemFieldsController::GetText(uint32 row, uint32 column) const
{
	DB *db = DBManager::Get().GetDatabase(this->mainWindow.GetActiveDBIndex());
	DBManager::Get().LoadDB(this->mainWindow.GetActiveDBIndex()); //TODO
	const FixedArray<DBField> &entries = db->GetEntries();
	const DBField &entry = entries[row];
	const void *objectPtr = db->GetObjectPointer(this->activeItemIndex);
	const void *fieldPtr = ((byte *)objectPtr) + entry.offset;

	switch(column)
	{
		case 0:
			return entry.name;
		case 1:
			return entry.ValueToString(fieldPtr);
		case 2:
			return "TODO: COL2";
		case 3:
			return entry.comment;
	}

	return String();
}

//Private methods
DB *ItemFieldsController::GetActiveDB() const
{
	if(this->mainWindow.GetActiveDBIndex() == Natural<uint32>::Max())
		return nullptr;

	return DBManager::Get().GetDatabase(this->mainWindow.GetActiveDBIndex());
}