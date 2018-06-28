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
#include "MainWindow.hpp"
#include "db/DBManager.hpp"
#include "ui/UIController.hpp"

//Constructor
MainWindow::MainWindow() : itemFieldsController(*this)
{
	this->SetTitle(u8"EDMW DB Editor");
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

	//TableView *editTable = new TableView(groupBox);
	TreeView *editTable = new TreeView(groupBox);
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
			return DBManager::Get().GetDatabases()[index]->GetName().SubString(2);
		}

	private:
		//Members
		MainWindow *mainWindow;

		void OnSelectionChanged() const
		{
			uint32 index = this->view->GetSelectionController().GetSelectedIndexes()[0].GetRow();
			UIController::Get().SetActiveDBIndex(index);

			mainWindow->filterMethodSelect->SetEnabled(true);
			mainWindow->filterMethodSelect->GetController()->ModelChanged();
			mainWindow->filterMethodSelect->Select(0);
		}
	} dbController(this);
	dbFileSelect->SetController(dbController);
	dbFileSelect->SetHint(u8"Select File");

	//filter method
	static class FilterMethodController : public ListController
	{
	public:
		//Constructor
		inline FilterMethodController(MainWindow *mainWindow) : mainWindow(mainWindow)
		{
		}

		//Event handlers
		uint32 GetNumberOfItems() const
		{
			DB *db = UIController::Get().GetActiveDB();
			if(db)
				return db->GetFilterableFields().GetNumberOfElements();
			return 0;
		}

		String GetText(uint32 index) const
		{
			DB *db = UIController::Get().GetActiveDB();

			return db->GetFields()[db->GetFilterableFields()[index]].name;
		}

	private:
		//Members
		MainWindow *mainWindow;

		//Event handlers
		void OnSelectionChanged() const
		{
			uint32 index = this->view->GetSelectionController().GetSelectedIndexes()[0].GetRow();
			UIController::Get().SetActiveFilterMethodIndex(index);
			this->mainWindow->itemsView->GetController()->ModelChanged();
		}
	} filterMethodController(this);
	this->filterMethodSelect = new ComboBox(subContainer);
	this->filterMethodSelect->SetController(filterMethodController);
	this->filterMethodSelect->SetEnabled(false);
	this->filterMethodSelect->SetHint(u8"Filter method");

	//save button
	PushButton *saveButton = new PushButton(container);
	saveButton->sizingPolicy.SetVerticalPolicy(SizingPolicy::Policy::Preferred);
	saveButton->SetEnabled(false);
	saveButton->SetText("Save");

	//second row
	SearchBox *filterEdit = new SearchBox(groupBox);
	filterEdit->SetEnabled(false);
	filterEdit->SetHint(u8"Filter text");

	//third row
	this->itemsView = new TreeView(groupBox);
	this->itemsView->SetController(this->itemsController);
}