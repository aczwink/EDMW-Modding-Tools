//Class Header
#include "CDbUIControlsManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbUIControlsManager::CDbUIControlsManager()
{
	this->pUIControls = NULL;
}

//Destructor
CDbUIControlsManager::~CDbUIControlsManager()
{
	memfreesafe(this->pUIControls);
}

//Public methods
void CDbUIControlsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nUIControls; i++)
	{
		const CString &refCurrentName = this->pUIControls[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbUIControlsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nUIControls; i++)
	{
		const CString &refCurrentName = DbManager::Get().GetLanguageString(this->pUIControls[i].stringId).ToCString();
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

CString CDbUIControlsManager::GetFileTitle() const
{
	return "dbuicontrols";
}

void CDbUIControlsManager::Init()
{
}

void CDbUIControlsManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nUIControls);
	this->pUIControls = (SDbUIControl *)malloc(this->nUIControls * sizeof(*this->pUIControls));
	
	refInput.ReadBytes(this->pUIControls, this->nUIControls * sizeof(*this->pUIControls));
	
	/*for(uint32 i = 0; i < this->nUIControls; i++)
	{
	}
	*/
}

void CDbUIControlsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nUIControls);
	refOutput.WriteBytes(this->pUIControls, this->nUIControls * sizeof(*this->pUIControls));
}

CString CDbUIControlsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SDbUIControl &refControl = this->pUIControls[index];
	
	APPENDCHARARRAY("Identifier", refControl.identifier, "", false);
	
	debugout((uint32 *)refControl.unknown1, sizeof(refControl.unknown1), index);

	APPENDFLOAT("Unknown Float 1", refControl.unknownFloat1, "", true);
	APPENDFLOAT("Unknown Float 2", refControl.unknownFloat2, "", true);
	APPENDFLOAT("Unknown Float 3", refControl.unknownFloat3, "", true);
	APPENDFLOAT("Unknown Float 4", refControl.unknownFloat4, "", true);
	APPENDFLOAT("Unknown Float 5", refControl.unknownFloat5, "", true);
	APPENDFLOAT("Unknown Float 6", refControl.unknownFloat6, "", true);
	APPENDFLOAT("Unknown Float 7", refControl.unknownFloat7, "", true);
	APPENDFLOAT("Unknown Float 8", refControl.unknownFloat8, "", true);

	debugout((uint32 *)refControl.unknown2, sizeof(refControl.unknown2), index);	


	APPENDUINT32("String id", refControl.stringId, DbManager::Get().GetLanguageString(refControl.stringId, false).ToCString(), true);


	debugout((uint32 *)refControl.unknownRest, sizeof(refControl.unknownRest), index);
	
	APPENDUINT32("Unknown Flags 1", refControl.unknownFlags1, "a bit field, values are: 0x100 0000, 0x100 0100, 0x101 0000, 0x101 0100, 0x100", true);
	APPENDUINT32("Unknown Long 2", refControl.unknownLong2, "seems to be a bool value... mostly 0, 3 times 1", true);
	
	return refControl.identifier;
}

bool CDbUIControlsManager::SupportsFilterByDisplayString() const
{
	return true;
}

void CDbUIControlsManager::Uninit()
{
}