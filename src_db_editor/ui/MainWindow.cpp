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
#include "MainWindow.hpp"
//Local
#include "../db/DBManager.hpp"
#include "ObjectNavigatorController.hpp"
#include "UIController.hpp"

//Constructor
MainWindow::MainWindow(EventQueue& eventQueue) : MainAppWindow(eventQueue)
{
	this->SetTitle(u8"EDMW DB Editor");
	this->SetupChildren();
}

//Private methods
void MainWindow::SetupChildren()
{
	this->GetContentContainer()->SetLayout(new HorizontalLayout);
	this->SetupSelectionPanel();
	
	//right panel
	GroupBox *groupBox = new GroupBox();
	groupBox->sizingPolicy.horzScale = 5;
	this->AddContentChild(groupBox);

	TableView *objectEditorView = new TableView();
	//TreeView *objectEditorView = new TreeView();
	objectEditorView->SetController(new ObjectEditorController(*this));
	groupBox->AddContentChild(objectEditorView);
}

void MainWindow::SetupSelectionPanel()
{
	GroupBox *groupBox = new GroupBox();
	groupBox->GetContentContainer()->SetLayout(new VerticalLayout);
	this->AddContentChild(groupBox);

	//first row
	CompositeWidget *container = new CompositeWidget();
	container->SetLayout(new HorizontalLayout);
	groupBox->AddContentChild(container);

	//sub container
	CompositeWidget *subContainer = new CompositeWidget();
	subContainer->sizingPolicy.horzScale = 2;
	subContainer->SetLayout(new VerticalLayout);
	container->AddChild(subContainer);

	//db file selections
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
			mainWindow->filterMethodSelect->Select(mainWindow->filterMethodSelect->GetController()->GetChildIndex(0, 0));
		}
	};

	SelectBox *dbFileSelect = new SelectBox();
	dbFileSelect->SetController(new DBController(this));
	dbFileSelect->SetHint(u8"Select File");
	subContainer->AddChild(dbFileSelect);

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
			if (db)
				return db->GetFilterableFields().GetNumberOfElements();
			return 0;
		}

		String GetText(uint32 index) const
		{
			DB *db = UIController::Get().GetActiveDB();

			return db->GetObjectScheme()[db->GetFilterableFields()[index]].name;
		}

	private:
		//Members
		MainWindow *mainWindow;

		//Event handlers
		void OnSelectionChanged() const
		{
			uint32 index = this->view->GetSelectionController().GetSelectedIndexes()[0].GetRow();
			UIController::Get().SetActiveFilterMethodIndex(index);
			this->mainWindow->objectNavigatorView->GetController()->ModelChanged();
			this->mainWindow->filterBox->SetEnabled(true);
		}
	};
	this->filterMethodSelect = new SelectBox();
	this->filterMethodSelect->SetController(new FilterMethodController(this));
	this->filterMethodSelect->SetEnabled(false);
	this->filterMethodSelect->SetHint(u8"Filter method");
	subContainer->AddChild(this->filterMethodSelect);

	//save button
	PushButton *saveButton = new PushButton();
	saveButton->sizingPolicy.SetVerticalPolicy(SizingPolicy::Policy::Preferred);
	saveButton->SetEnabled(false);
	saveButton->SetText("Save");
	container->AddChild(saveButton);

	//second row
	this->filterBox = new SearchBox();
	this->filterBox->SetEnabled(false);
	this->filterBox->SetHint(u8"Filter text");
	groupBox->AddContentChild(this->filterBox);

	//third row
	this->objectNavigatorView = new TreeView();
	this->objectNavigatorView->SetController(new ObjectNavigatorController);
	groupBox->AddContentChild(this->objectNavigatorView);
}