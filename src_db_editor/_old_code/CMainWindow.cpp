//Class Header
#include "CMainWindow.h"
//Global
#include <CommCtrl.h>
#include <ShlObj.h>
//Local
#include "CEDMWFolderDialog.h"
#include "DbManager.h"
#include "definitions.h"
#include "globals.h"
#include "resource.h"
//Namespaces
using namespace SJCLib;
//Definitions
#define STYLE_LEFTCONTROLS_RIGHT 200

//Message-callbacks
bool CMainWindow::OnCreate()
{
	CMenu menu, subMenu;

	//Menu
	menu.Create();
	subMenu.CreatePopup();
	subMenu.AppendItem("Exit", IDM_FILE_EXIT);
	menu.AppendSubMenu("File", subMenu);

	subMenu.CreatePopup();
	subMenu.AppendItem("Show unknown values", IDM_EXTRAS_SHOWUNKNOWNVALUES);
	subMenu.AppendItem("Show constant values", IDM_EXTRAS_SHOWCONSTANTVALUES);
	subMenu.AppendSeperator();
	subMenu.AppendItem("About", IDM_EXTRAS_ABOUT);
	menu.AppendSubMenu("Extras", subMenu);

	this->SetMenu(menu);

	//Controls
	this->editFilter.SetCueBanner(L"Filter");
	
	this->itemList.CreateReportView(WS_BORDER | LVS_SHOWSELALWAYS, *this);
	this->itemList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	this->itemList.AddColumn(L"Items");
	
	this->table.CreateReportView(WS_BORDER | LVS_SHOWSELALWAYS, *this);
	this->table.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	this->table.Show(SW_HIDE);
	this->table.AddColumn(L"Description");
	this->table.AddColumn(L"Value");
	this->table.AddColumn(L"Associations/Comments");
	
	this->PostMessageA(WM_USER_ONINIT, 0, 0);
	
	return true;
}

void CMainWindow::OnMenuCommand(uint16 menuItemId)
{
	switch(menuItemId)
	{
	case IDM_FILE_EXIT:
		this->PostMessageA(MsgClose());
		break;
	case IDM_EXTRAS_SHOWUNKNOWNVALUES:
		{
			CMenu &menu = this->GetMenu();
			bool isChecked;
			
			isChecked = menu.IsItemChecked(menuItemId);
			menu.CheckItem(menuItemId, !isChecked);
			g_Settings.SetValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWUNKNOWNVALUES, !isChecked);
			DbManager::Get().SetItem((uint32)this->itemList.GetItemData(this->itemList.GetCurrentSelection()));
		}
		break;
	case IDM_EXTRAS_SHOWCONSTANTVALUES:
		{
			CMenu &menu = this->GetMenu();
			bool isChecked;
			
			isChecked = menu.IsItemChecked(menuItemId);
			menu.CheckItem(menuItemId, !isChecked);
			g_Settings.SetValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWCONSTANTVALUES, !isChecked);
			DbManager::Get().SetItem((uint32)this->itemList.GetItemData(this->itemList.GetCurrentSelection()));
		}
		break;
	case IDM_EXTRAS_ABOUT:
		this->MessageBox((CWString)"Programmed by SoulJammingCurse\nVersion: " + (CWString)APPLICATION_VERSION_STRING + L"\nContact: souljammingcurse.de\n\nCredits:\nThanks to my best friend for helping me out with associating values.", L"About");
		break;
	}
}

void CMainWindow::OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight)
{
	CRect rcClient;
	CRect rcComboBoxDbFile;
	CRect rcComboBoxFilterBy;
	CRect rcButtonSave;
	CRect rcEditFilter;
	CRect rcItemList;
	CRect rcTitle;
	CRect rcTable;

	this->GetClientRect(rcClient);
	
	rcComboBoxDbFile.left = 5;
	rcComboBoxDbFile.top = 5;
	rcComboBoxDbFile.right = 120;
	rcComboBoxDbFile.bottom = 20;

	rcComboBoxFilterBy.left = rcComboBoxDbFile.left;
	rcComboBoxFilterBy.top = rcComboBoxDbFile.top + rcComboBoxDbFile.GetHeight() + 10;
	rcComboBoxFilterBy.right = rcComboBoxDbFile.right;
	rcComboBoxFilterBy.bottom = rcComboBoxFilterBy.top + rcComboBoxDbFile.bottom;

	rcButtonSave.left = rcComboBoxDbFile.left + rcComboBoxDbFile.right;
	rcButtonSave.top = rcComboBoxDbFile.top;
	rcButtonSave.right = STYLE_LEFTCONTROLS_RIGHT;
	rcButtonSave.bottom = rcComboBoxFilterBy.bottom;

	rcEditFilter.left = rcComboBoxDbFile.left;
	rcEditFilter.top = rcComboBoxFilterBy.top + rcComboBoxFilterBy.GetHeight() + 5;
	rcEditFilter.right = STYLE_LEFTCONTROLS_RIGHT;
	rcEditFilter.bottom = rcEditFilter.top + 20;

	rcItemList.left = rcComboBoxDbFile.left;
	rcItemList.top = rcEditFilter.bottom + 5;
	rcItemList.right = rcEditFilter.right;
	rcItemList.bottom = rcClient.bottom - 5;

	rcTitle.left = rcEditFilter.left + rcEditFilter.right + 10;
	rcTitle.top = rcClient.top + 5;
	rcTitle.right = rcClient.right - rcTitle.left;
	rcTitle.bottom = 20;
	
	rcTable.left = rcTitle.left;
	rcTable.top = rcTitle.top + rcTitle.bottom;
	rcTable.right = rcClient.right - 5;
	rcTable.bottom = rcClient.bottom - 5;
	
	this->comboBoxDbFile.SetPos(rcComboBoxDbFile, SWP_NOZORDER);
	this->comboBoxFilterBy.SetPos(rcComboBoxFilterBy, SWP_NOZORDER);
	this->buttonSave.SetPos(rcButtonSave, SWP_NOZORDER);
	this->editFilter.SetPos(rcEditFilter, SWP_NOZORDER);
	this->itemList.SetPos(rcItemList, SWP_NOZORDER);
	this->title.SetPos(rcTitle, SWP_NOZORDER);
	this->table.SetPos(rcTable, SWP_NOZORDER);
	
	this->itemList.SetColumnWidth(0, (uint16)rcItemList.right-5);
	
	this->table.SetColumnWidth(0, ((uint16)rcTable.GetWidth() - 20) / 3);
	this->table.SetColumnWidth(1, ((uint16)rcTable.GetWidth() - 20) / 5);
	this->table.SetColumnWidth(2, ((uint16)rcTable.GetWidth() - 20) * 47 / 100);
}

void CMainWindow::OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_USER_ONINIT:
		if(g_Settings.GetBoolValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWUNKNOWNVALUES))
			this->OnMenuCommand(IDM_EXTRAS_SHOWUNKNOWNVALUES);
		if(g_Settings.GetBoolValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWCONSTANTVALUES))
			this->OnMenuCommand(IDM_EXTRAS_SHOWCONSTANTVALUES);

		DbManager::Get().Init();
		break;
	}
}