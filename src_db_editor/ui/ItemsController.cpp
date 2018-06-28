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
#include "ItemsController.hpp"
//Local
#include "../MainWindow.hpp"
#include "../db/Object.hpp"
#include "UIController.hpp"

extern MainWindow *g_mainWindow;

//Public methods
ControllerIndex ItemsController::GetChildIndex(uint32 row, uint32 column, const ControllerIndex &parent) const
{
	DB *db = UIController::Get().GetActiveDB();

	if(parent == ControllerIndex())
		return this->CreateIndex(row, column, db->GetObjects()[row]);

	stdOut << "TODO: GetChildIndex" << endl;
	NOT_IMPLEMENTED_ERROR;
	return ControllerIndex();
}

String ItemsController::GetColumnText(uint32 column) const
{
	return u8"Items";
}

uint32 ItemsController::GetNumberOfChildren(const ControllerIndex &parent) const
{
	DB *db = UIController::Get().GetActiveDB();

	if(db == nullptr)
		return 0;
	if(parent == ControllerIndex())
		return db->GetObjects().GetNumberOfElements();

	return 0;
}

uint32 ItemsController::GetNumberOfColumns() const
{
	return 1;
}

ControllerIndex ItemsController::GetParentIndex(const ControllerIndex &index) const
{
	return ControllerIndex();
}

String ItemsController::GetText(const ControllerIndex &index) const
{
	DB *db = UIController::Get().GetActiveDB();
	Object *object;
	if(index.GetParent() == ControllerIndex())
		object = db->GetObjects()[index.GetRow()];
	else
	NOT_IMPLEMENTED_ERROR

	return object->GetValue(UIController::Get().GetActiveFilterFieldIndex()).string;
}

//Private methods
void ItemsController::OnSelectionChanged() const
{
	if(!this->view->GetSelectionController().GetSelectedIndexes().IsEmpty())
	{
		uint32 selectedRow = this->view->GetSelectionController().GetSelectedIndexes()[0].GetRow();

		g_mainWindow->SetCurrentItem(this->CreateIndex(selectedRow, 0, nullptr));
	}
}