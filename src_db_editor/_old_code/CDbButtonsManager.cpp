//Class Header
#include "CDbButtonsManager.h"
//Global
#include <iostream>
//Local
#include "DbManager.h"

//Constructor
CDbButtonsManager::CDbButtonsManager()
{
	this->pButtons = NULL;
}

//Destructor
CDbButtonsManager::~CDbButtonsManager()
{
	memfreesafe(this->pButtons);
}

//Public methods
void CDbButtonsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nButtons; i++)
	{
		const CString &refCurrentName = this->pButtons[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbButtonsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
}

CString CDbButtonsManager::GetFileTitle() const
{
	return "dbbuttons";
}

void CDbButtonsManager::Init()
{
}

void CDbButtonsManager::ReadInput(AInputStream &refInput)
{
	CString buffer;
	
	refInput.ReadUInt32(this->nButtons);
	this->pButtons = (SDbButton *)malloc(this->nButtons * sizeof(*this->pButtons));
	refInput.ReadBytes(this->pButtons, this->nButtons * sizeof(*this->pButtons));

	//finding out values
	/*for(uint32 i = 0; i < this->nButtons; i++)
	{
		if(this->pButtons[i].unknownLong4)
		{
			stdOut << this->pButtons[i].identifier << endl;
		}
	}*/
}

void CDbButtonsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nButtons);
	refOutput.WriteBytes(this->pButtons, this->nButtons * sizeof(*this->pButtons));
}

CString CDbButtonsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SDbButton &refButton = this->pButtons[index];
	
	APPENDCHARARRAY("Identifier", refButton.identifier, "", false);
	APPENDCHARARRAY("Texture name", refButton.textureName, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 1", refButton.unknownLong1, "", true);
		APPENDUINT32("Unknown Long 2", refButton.unknownLong2, "this is somehow related to objects and techtrees button id... above figure could also be an id...", true);
	}
	
	APPENDUINT32("Button position", refButton.buttonPosition, "row-wise left to right (1-10 = first row)", true);
	
	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 4", refButton.unknownLong4, "", true);
	}
	
	return refButton.identifier;
}

bool CDbButtonsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbButtonsManager::Uninit()
{
}