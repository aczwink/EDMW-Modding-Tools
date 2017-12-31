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
#include "MainWindow.hpp"
#include "DBManager.hpp"

//Constructor
MainWindow::MainWindow() : itemFieldsController(*this)
{
	this->activeDBIndex = Natural<uint32>::Max();

	this->SetTitle("EDMW DB Editor");
	this->SetupChildren();
}

//Private methods
void MainWindow::SetupChildren()
{
	this->SetLayout(new HorizontalLayout);
	this->SetupSelectionPanel();

	//right panel
	GroupBox *groupBox = new GroupBox(this);
	groupBox->sizingPolicy.horzScale = 5;

	TableView *editTable = new TableView(groupBox);
	editTable->SetController(this->itemFieldsController);
}

void MainWindow::SetupSelectionPanel()
{

	GroupBox *groupBox = new GroupBox(this);
	groupBox->SetLayout(new VerticalLayout);

	//first row
	WidgetContainer *container = new WidgetContainer(groupBox);
	container->SetLayout(new HorizontalLayout);

	//sub container
	WidgetContainer *subContainer = new WidgetContainer(container);
	subContainer->sizingPolicy.horzScale = 2;
	subContainer->SetLayout(new VerticalLayout);

	//db file selections
	ComboBox *dbFileSelect = new ComboBox(subContainer);
	static class DBController : public ListController
	{
	public:
		//Constructor
		inline DBController(MainWindow *mainWindow) : mainWindow(mainWindow)
		{
		}
		//Methods
		uint32 GetNumberOfItems() const
		{
			return DBManager::Get().GetDatabases().GetNumberOfElements();
		}

		String GetText(uint32 index) const
		{
			return DBManager::Get().GetDatabases()[index]->GetName();
		}

	private:
		//Members
		MainWindow *mainWindow;

		void OnSelectionChanged() const
		{
			mainWindow->activeDBIndex = this->view->GetSelectionController().GetSelectedIndexes()[0].GetRow();
			DBManager::Get().LoadDB(mainWindow->activeDBIndex);
			mainWindow->itemView->SetController(DBManager::Get().GetDatabase(mainWindow->activeDBIndex)->GetItemController());
		}
	} dbController(this);
	dbFileSelect->SetController(dbController);
	//dbFileSelect->SetHint("Select File");

	//filter method
	ComboBox *filterMethodSelect = new ComboBox(subContainer);
	filterMethodSelect->SetEnabled(false);
	//filterMethodSelect->SetHint("Filter by");

	//save button
	PushButton *saveButton = new PushButton(container);
	saveButton->sizingPolicy.SetVerticalPolicy(SizingPolicy::Policy::Preferred);
	saveButton->SetEnabled(false);
	saveButton->SetText("Save");

	//second row
	SearchBox *filterEdit = new SearchBox(groupBox);
	filterEdit->SetEnabled(false);

	//third row
	this->itemView = new TreeView(groupBox);
}