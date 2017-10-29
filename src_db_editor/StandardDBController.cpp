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
#include "StandardDBController.hpp"
//Local
#include "MainWindow.hpp"

//Public methods
uint32 StandardDBController::GetNumberOfItems() const
{
	return this->db->nObjects;
}

String StandardDBController::GetText(uint32 index) const
{
	return "TODO: implement me";
}

//Private methods
void StandardDBController::OnSelectionChanged() const
{
	if(!this->view->GetSelectionController().GetSelectedIndexes().IsEmpty())
	{
		uint32 selectedRow = this->view->GetSelectionController().GetSelectedIndexes()[0].GetRow();

		extern MainWindow *g_mainWindow;

		g_mainWindow->SetCurrentItem(this->CreateIndex(selectedRow, 0, nullptr));
	}
}