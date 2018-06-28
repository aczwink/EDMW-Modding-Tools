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
#include "../db/DB.hpp"
#include "../db/DBManager.hpp"
#include "../MainWindow.hpp"
#include "../db/Object.hpp"
#include "UIController.hpp"

//Constructor
ItemFieldsController::ItemFieldsController(const MainWindow &mainWindow) : mainWindow(mainWindow)
{
	this->activeItemIndex = this->CreateIndex(0, 0, nullptr);
}

//Public methods
ControllerIndex ItemFieldsController::GetChildIndex(uint32 row, uint32 column, const ControllerIndex &parent) const
{
	return this->CreateIndex(row, column, nullptr);
}

String ItemFieldsController::GetColumnText(uint32 column) const
{
	static const char *columns[] = {u8"Field name", u8"Value", u8"Associated value", u8"Comment"};

	return columns[column];
}

uint32 ItemFieldsController::GetNumberOfColumns() const
{
	return 4;
}

uint32 ItemFieldsController::GetNumberOfChildren(const ControllerIndex &parent) const
{
	DB *db = UIController::Get().GetActiveDB();

	if(parent.HasParent())
		return 0;

	if(db)
		return db->GetFields().GetNumberOfElements();
}

ControllerIndex ItemFieldsController::GetParentIndex(const ControllerIndex &index) const
{
	return ControllerIndex();
}

String ItemFieldsController::GetText(const ControllerIndex &index) const
{
	return u8"TODO";
	/*
	DB *db = UIController::Get().GetActiveDB();
	const FixedArray<DBField> &entries = db->GetFields();
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
	 */
}