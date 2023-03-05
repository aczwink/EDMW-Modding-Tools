//Class Header
#include "CItemTable.h"
//Local
#include "CDbObjectsManager.h"
#include "DbManager.h"
#include "Globals.h"

//Internal Functions
bool OnEditObjectResourceType(SItemTableData *pItd, CWindow *pWnd)
{
	CSelectDialog dlg;
	
	dlg.Create("Select Resource type", *pWnd);
	dlg.AddSelection(CDbObjectsManager::GetResourceTypeString(RESOURCETYPE_NONE));
	dlg.AddSelection(CDbObjectsManager::GetResourceTypeString(RESOURCETYPE_UNKNOWNRESOURCE));
	dlg.AddSelection(CDbObjectsManager::GetResourceTypeString(RESOURCETYPE_FOOD));
	dlg.AddSelection(CDbObjectsManager::GetResourceTypeString(RESOURCETYPE_WOOD));
	dlg.AddSelection(CDbObjectsManager::GetResourceTypeString(RESOURCETYPE_STONE));
	dlg.AddSelection(CDbObjectsManager::GetResourceTypeString(RESOURCETYPE_GOLD));
	dlg.PreSelect(*(uint32 *)pItd->pBuffer);
	
	if(dlg.Run() == IDOK)
	{
		*((uint32 *)pItd->pBuffer) = dlg.GetSelection();
		g_MainWindow.buttonSave.Enable(true);
		return true;
	}
	return false;
}

//Message-callbacks
uint16 CItemTable::OnCustomDraw(uint32 itemIndex, LPARAM lParam, uint32 drawStage, CColor &textColor, CColor &textBackgroundColor)
{
	switch(drawStage)
	{
	case CDDS_PREPAINT:
		return CDRF_NOTIFYITEMDRAW;
	case CDDS_ITEMPREPAINT:
		{
			const SItemTableData &refItemData = DbManager::Get().GetItemData(itemIndex);

			switch(refItemData.state)
			{
			case 0:
				{
					textColor.Set(0, 0, 0);
					textBackgroundColor.Set(255, 255, 255);
				}
				break;
			case 1: //constant
				{
					textColor.Set(255, 255, 255);
					textBackgroundColor.Set(255, 128, 128);
				}
				break;
			case 2: //unknown
				{
					textColor.Set(255, 255, 255);
					textBackgroundColor.Set(255, 0, 255);
				}
				break;
			}
		}
		return CDRF_NEWFONT;
	}
	return CDRF_DODEFAULT;
}

void CItemTable::OnDoubleClick(int32 index)
{
	SItemTableData *pItd = &DbManager::Get().data[(uint32)this->GetItemData(index)];
	CPromptDialog dlg;
	bool accepted = false;

	if(!pItd->isEditable)
	{
		((CPopupWindow *)this->GetParent())->MessageBox(L"This Item is not editable", L"Uneditable Item selected");
		return;
	}
	
	switch(pItd->type)
	{
	case ITEMDATATYPE_BOOL:
		{
			*(bool *)pItd->pBuffer = !*(bool *)pItd->pBuffer;
			g_MainWindow.buttonSave.Enable(true);
			accepted = true;
		}
		break;
	case ITEMDATATYPE_CHARARRAY:
		{
			dlg.Create("Enter text (max. " + CString(pItd->bufferSize) + " chars)", CString((char *)pItd->pBuffer, pItd->bufferSize), this->GetParent());
			dlg.SetTextLimit(pItd->bufferSize);
			
			if(dlg.Run() == IDOK)
			{
				CString text = dlg.GetValue();
				
				MemZero(pItd->pBuffer, pItd->bufferSize);
				MemCopy(pItd->pBuffer, text.GetC_Str(), text.GetLength());
				
				g_MainWindow.buttonSave.Enable(true);
				accepted = true;
			}
		}
		break;
	case ITEMDATATYPE_INT32:
		{
			dlg.Create("Enter integer", CString(*(int32 *)pItd->pBuffer), this->GetParent());

			while(!accepted)
			{
				if(dlg.Run() == IDOK)
				{
					CString text = dlg.GetValue();

					if(!text.IsInteger())
					{
						((CPopupWindow *)this->GetParent())->MessageBox(L"You have to enter an integer", L"Warning", MB_ICONWARNING);
						accepted = false;
					}
					else
					{
						*((int32 *)pItd->pBuffer) = (int32)text.ToInt64();
						accepted = true;
						g_MainWindow.buttonSave.Enable(true);
					}
				}
				else
				{
					accepted = true;
				}
			}
		}
		break;
	case ITEMDATATYPE_STRING:
		{
			dlg.Create("Enter text", *(CString *)pItd->pBuffer, this->GetParent());
			
			if(dlg.Run() == IDOK)
			{
				*(CString *)pItd->pBuffer = dlg.GetValue();
				
				g_MainWindow.buttonSave.Enable(true);
				accepted = true;
			}
		}
		break;
	case ITEMDATATYPE_UINT32:
		dlg.Create("Enter positive integer", CString(*(uint32 *)pItd->pBuffer), this->GetParent());
		
		while(!accepted)
		{
			if(dlg.Run() == IDOK)
			{
				CString text = dlg.GetValue();
				
				if(!text.IsInteger())
				{
failuint32:;
					((CPopupWindow *)this->GetParent())->MessageBox(L"You have to enter a positive integer", L"Warning", MB_ICONWARNING);
					accepted = false;
				}
				else
				{
					if(!text.IsEmpty() && text[0] == '-')
						goto failuint32;
					
					*((uint32 *)pItd->pBuffer) = (uint32)text.ToUInt64();
					accepted = true;
					g_MainWindow.buttonSave.Enable(true);
				}
			}
			else
			{
				accepted = true;
			}
		}
		break;
	case ITEMDATATYPE_FLOAT:
		dlg.Create("Enter a decimal number", CString(*(float *)pItd->pBuffer), this->GetParent());
		while(!accepted)
		{
			if(dlg.Run() == IDOK)
			{
				CString text = dlg.GetValue();
				
				if(!text.IsFloat())
				{
					((CPopupWindow *)this->GetParent())->MessageBox(L"You have to enter a decimal number", L"Warning", MB_ICONWARNING);
					accepted = false;
				}
				else
				{
					*((float *)pItd->pBuffer) = (float32)text.ToFloat();
					accepted = true;
					g_MainWindow.buttonSave.Enable(true);
				}
			}
			else
			{
				accepted = true;
			}
		}
		break;
	/*case ITEMDATATYPE_OBJECT_TARGETMODE:
		accepted = OnEditObjectTargetMode(pItd, this->GetParent());
		break;*/
	case ITEMDATATYPE_OBJECT_RESOURCETYPE:
		accepted = OnEditObjectResourceType(pItd, this->GetParent());
		break;
	}
	
	if(accepted)
	{
		DbManager::Get().SetItem(pItd->itemIndex);
		this->EnsureVisible(index);
	}
}

/*//SJC Lib
#include <SJCLibString.h>
//Local
#include "globals.h"
#include "DbManager.h"

//Namespaces
using namespace SJCLibString;

static uint targetModes[] = {0, 2, 4, 5, 6, 7, 9, 18, 24, 31, 32, 34, 37, 38, 41, 55, 57, 59};

bool OnEditObjectTargetMode(ItemTableData *pItd, CWindow *pWnd)
{
	CSelectDialog dlg;
	
	dlg.Init("Select Target Mode", pWnd, &g_Module);
	repeat(sizeof(targetModes)/sizeof(targetModes[0]), i)
	{
		dlg.AddSelection(CString::FromUInt(targetModes[i]));
	}
	
	if(dlg.Run() == IDOK)
	{
		*((ulong *)pItd->ptr) = targetModes[dlg.GetSelection()];
		g_MainWindow.buttonSave.Enable(true);
		return true;
	}
	return false;
}

*/