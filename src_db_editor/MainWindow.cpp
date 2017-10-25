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

//Constructor
MainWindow::MainWindow()
{
	this->SetTitle("EDMW DB Editor");

	this->SetLayout(new HorizontalLayout);

	//left panel
	GroupBox *pLeftPanel = new GroupBox(this);
	pLeftPanel->SetText("Left Panel");
	pLeftPanel->SetLayout(new VerticalLayout);

	//first row
	WidgetContainer *pContainer = new WidgetContainer(pLeftPanel);
	pContainer->SetLayout(new HorizontalLayout);

	//sub container
	WidgetContainer *pSubContainer = new WidgetContainer(pContainer);
	pSubContainer->sizingPolicy.horzScale = 2;
	pSubContainer->SetLayout(new VerticalLayout);

	//db file selections
	CDropDown *pDbFileSelect = new CDropDown(pSubContainer);
	pDbFileSelect->SetHint("Select File");

	pDbFileSelect->BindSelectionChanged(
		[this]()
		{
			stdOut << "bla" << endl;
			this->ShowInformationBox("bla", "blu");
		}
	);

	/*
	for(IDbManager *const& refpManager : CDbManager::Get().GetManagers())
	{
		pDbFileSelect->AddItem(refpManager->GetFileTitle());
	}
	 */

	//filter method
	/*
	CDropDown *pFilterMethodSelect = new CDropDown(pSubContainer);
	pFilterMethodSelect->SetEnabled(false);
	pFilterMethodSelect->SetHint("Filter by");
	 */

	//save button
	/*
	PushButton *pSaveButton = new PushButton(pContainer);
	pSaveButton->sizingPolicy.SetVerticalPolicy(SizingPolicy::Policy::Preferred);
	pSaveButton->SetEnabled(false);
	pSaveButton->SetText("Save");
	 */

	//second row
	/*
	CLineEdit *pFilterEdit = new CLineEdit(pLeftPanel);
	pFilterEdit->SetEnabled(false);
	 */

	//third row
	//CTreeView *pItemTree = new CTreeView(pLeftPanel);

	//right panel
	/*
	GroupBox *pRightPanel = new GroupBox(this);
	pRightPanel->sizingPolicy.horzScale = 5;
	pRightPanel->SetText("Right panel");
	 */

	//CTableView *pEditTable = new CTableView(pRightPanel);
}