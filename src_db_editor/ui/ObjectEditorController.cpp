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
//Class header
#include "ObjectEditorController.hpp"
//Local
#include "UIController.hpp"

//Constructor
ObjectEditorController::ObjectEditorController(const MainWindow &mainWindow) : mainWindow(mainWindow)
{
	this->activeItemIndex = this->CreateIndex(0, 0, nullptr);
	
	UIController::Get().RegisterForActiveObjChange([this]() {
		this->ModelChanged();
	});
}

//Public methods
ControllerIndex ObjectEditorController::GetChildIndex(uint32 row, uint32 column, const ControllerIndex &parent) const
{
	return this->CreateIndex(row, column, nullptr);
}

String ObjectEditorController::GetColumnText(uint32 column) const
{
	static const char *columns[] = { u8"Property name", u8"Value", u8"Associated value", u8"Comment" };

	return columns[column];
}

uint32 ObjectEditorController::GetNumberOfChildren(const ControllerIndex &parent) const
{
	if (parent.HasParent())
		return 0;
	
	Object* obj = UIController::Get().GetActiveObject();
	if (obj)
	{
		DB* db = UIController::Get().GetActiveDB();
		auto& fields = db->GetFlattenedFields();
		return fields.GetNumberOfElements();
	}
	return 0;
}

uint32 ObjectEditorController::GetNumberOfColumns() const
{
	return 4;
}

ControllerIndex ObjectEditorController::GetParentIndex(const ControllerIndex &index) const
{
	//TODO:!
	return ControllerIndex();
}

String ObjectEditorController::GetText(const ControllerIndex &index) const
{
	DB* db = UIController::Get().GetActiveDB();
	Object* obj = UIController::Get().GetActiveObject();

	auto& fields = db->GetFlattenedFields();
	const DBField& field = *fields[index.GetRow()];
	if (index.GetRow() >= obj->GetNumberOfProperties())
		return u8"TODO";
	const ObjectProperty& prop = obj->GetProperty(index.GetRow());

	switch (index.GetColumn())
	{
	case 0:
		return field.name;
	case 1:
		return prop.ToString();
	case 2:
		if (field.language.HasValue())
			return DB::LoadLanguageString(prop.ui, *field.language);
		break;
	case 3:
		return field.comment;
	}

	return String();
}