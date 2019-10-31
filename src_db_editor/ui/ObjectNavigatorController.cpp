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
#include "ObjectNavigatorController.hpp"
//Local
#include "MainWindow.hpp"
#include "../db/Object.hpp"
#include "UIController.hpp"

//Public methods
ControllerIndex ObjectNavigatorController::GetChildIndex(uint32 row, uint32 column, const ControllerIndex &parent) const
{
	DB *db = UIController::Get().GetActiveDB();
	
	if(parent == ControllerIndex())
		return this->CreateIndex(row, column, &db->GetObject(row));

	const Object* obj = (const Object*)parent.GetNode();
	return this->CreateIndex(row, column, &obj->GetChild(row));
}

String ObjectNavigatorController::GetColumnText(uint32 column) const
{
	return u8"Items";
}

uint32 ObjectNavigatorController::GetNumberOfChildren(const ControllerIndex &parent) const
{
	DB *db = UIController::Get().GetActiveDB();

	if(db == nullptr)
		return 0;
	if (parent == ControllerIndex())
		return db->GetNumberOfObjects();

	const Object* obj = (const Object*)parent.GetNode();
	return obj->GetNumberOfChildren();
}

uint32 ObjectNavigatorController::GetNumberOfColumns() const
{
	return 1;
}

ControllerIndex ObjectNavigatorController::GetParentIndex(const ControllerIndex &index) const
{
	//TODO:!
	return ControllerIndex();
}

String ObjectNavigatorController::GetText(const ControllerIndex &index) const
{
	DB *db = UIController::Get().GetActiveDB();
	
	const Object *object = (const Object*)index.GetNode();
	return object->GetProperty(UIController::Get().GetActiveFilterFieldIndex()).ToString();
}

//Private methods
void ObjectNavigatorController::OnSelectionChanged() const
{
	if(!this->view->GetSelectionController().GetSelectedIndexes().IsEmpty())
	{
		Object* object = (Object*)this->view->GetSelectionController().GetSelectedIndexes().GetFront().GetNode();
		UIController::Get().SetActiveObject(object);
	}
}