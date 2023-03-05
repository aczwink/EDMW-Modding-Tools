//Class Header
#include "CDbTechtreeManager.h"
//Local
#include "DbManager.h"
#include "debug.h"
#include "Globals.h"

//Constructor
CDbTechtreeManager::CDbTechtreeManager()
{
}

//Destructor
CDbTechtreeManager::~CDbTechtreeManager()
{
	uint32 i;
	
	foreach(it, this->techtrees)
	{
		free((*it).epoch.pUnknownAdditionals1);
		free((*it).epoch.pUnknownAdditionals2);

		for(i = 0; i < (*it).nTechs; i++)
		{
			free((*it).pTechs[i].pUnknownAdditionals1);
			free((*it).pTechs[i].pUnknownAdditionals2);
		}
		free((*it).pTechs);
	}
}

//Private methods
void CDbTechtreeManager::ReadTech(STech &refTech, AInputStream &refInput)
{
	uint32 i;
	
	refInput.ReadBytes(refTech.identifier, sizeof(refTech.identifier));
	refInput.ReadUInt32(refTech.id1);
	refInput.ReadUInt32(refTech.techId);
	refInput.ReadUInt32(refTech.startEpochId);
	refInput.ReadUInt32(refTech.endEpochId);
	refInput.ReadBytes(refTech.unknown1, sizeof(refTech.unknown1));
	refInput.ReadUInt32(refTech.costWood);
	refInput.ReadUInt32(refTech.costStone);
	refInput.ReadUInt32(refTech.costGold);
	refInput.ReadUInt32(refTech.costUnknown);
	refInput.ReadUInt32(refTech.costFood);
	refInput.ReadUInt32(refTech.buildSpeed);
	refInput.ReadBytes(refTech.unknown3, sizeof(refTech.unknown3));
	refInput.ReadUInt32(refTech.buttonId);
	refInput.ReadUInt32(refTech.unknown4);
	refInput.ReadUInt32(refTech.stringId);
	refInput.ReadBytes(refTech.unknown5, sizeof(refTech.unknown5));
	refInput.ReadUInt32(refTech.phoenixCivTableId);
	refInput.ReadUInt32(refTech.unknown8);
	refInput.ReadUInt32(refTech.amount);
	refInput.ReadBytes(refTech.unknown6, sizeof(refTech.unknown6));
	refInput.ReadUInt32(refTech.prerequisiteStringId1);
	refInput.ReadUInt32(refTech.prerequisiteStringId2);
	refInput.ReadUInt32(refTech.toolTipStringId);
	refInput.ReadFloat32(refTech.unknownFloat30);
	refInput.ReadFloat32(refTech.unknownFloat31);
	refInput.ReadFloat32(refTech.unknownFloat32);
	refInput.ReadFloat32(refTech.unknownFloat33);
	refTech.unknownBool1 = refInput.ReadBool();
	refTech.editorOnly = refInput.ReadBool();
	refTech.unknownBool3 = refInput.ReadBool();
	refTech.unknownBool4 = refInput.ReadBool();
	refInput.ReadBytes(refTech.unknown, sizeof(refTech.unknown));
	refInput.ReadUInt32(refTech.unknown7);
	refInput.ReadBytes(refTech.unknown_rest, sizeof(refTech.unknown_rest));
	refInput.ReadUInt32(refTech.nUnknownAdditionals1);

	refTech.pUnknownAdditionals1 = (uint32 *)malloc(refTech.nUnknownAdditionals1 * sizeof(*refTech.pUnknownAdditionals1));
	for(i = 0; i < refTech.nUnknownAdditionals1; i++)
	{
		refInput.ReadUInt32(refTech.pUnknownAdditionals1[i]);
	}

	refInput.ReadUInt32(refTech.nUnknownAdditionals2);
	refTech.pUnknownAdditionals2 = (uint32 *)malloc(refTech.nUnknownAdditionals2 * sizeof(*refTech.pUnknownAdditionals2));
	for(i = 0; i < refTech.nUnknownAdditionals2; i++)
	{
		refInput.ReadUInt32(refTech.pUnknownAdditionals2[i]);
	}
}

void CDbTechtreeManager::WriteTech(const STech &refTech, AOutputStream &refOutput) const
{
	refOutput.WriteBytes(refTech.identifier, sizeof(refTech.identifier));
	refOutput.WriteUInt32(refTech.id1);
	refOutput.WriteUInt32(refTech.techId);
	refOutput.WriteUInt32(refTech.startEpochId);
	refOutput.WriteUInt32(refTech.endEpochId);
	refOutput.WriteBytes(refTech.unknown1, sizeof(refTech.unknown1));
	refOutput.WriteUInt32(refTech.costWood);
	refOutput.WriteUInt32(refTech.costStone);
	refOutput.WriteUInt32(refTech.costGold);
	refOutput.WriteUInt32(refTech.costUnknown);
	refOutput.WriteUInt32(refTech.costFood);
	refOutput.WriteUInt32(refTech.buildSpeed);
	refOutput.WriteBytes(refTech.unknown3, sizeof(refTech.unknown3));
	refOutput.WriteUInt32(refTech.buttonId);
	refOutput.WriteUInt32(refTech.unknown4);
	refOutput.WriteUInt32(refTech.stringId);
	refOutput.WriteBytes(refTech.unknown5, sizeof(refTech.unknown5));
	refOutput.WriteUInt32(refTech.phoenixCivTableId);
	refOutput.WriteUInt32(refTech.unknown8);
	refOutput.WriteUInt32(refTech.amount);
	refOutput.WriteBytes(refTech.unknown6, sizeof(refTech.unknown6));
	refOutput.WriteUInt32(refTech.prerequisiteStringId1);
	refOutput.WriteUInt32(refTech.prerequisiteStringId2);
	refOutput.WriteUInt32(refTech.toolTipStringId);
	refOutput.WriteFloat32(refTech.unknownFloat30);
	refOutput.WriteFloat32(refTech.unknownFloat31);
	refOutput.WriteFloat32(refTech.unknownFloat32);
	refOutput.WriteFloat32(refTech.unknownFloat33);
	refOutput.WriteByte(refTech.unknownBool1);
	refOutput.WriteByte(refTech.editorOnly);
	refOutput.WriteByte(refTech.unknownBool3);
	refOutput.WriteByte(refTech.unknownBool4);
	refOutput.WriteBytes(refTech.unknown, sizeof(refTech.unknown));
	refOutput.WriteUInt32(refTech.unknown7);
	refOutput.WriteBytes(refTech.unknown_rest, sizeof(refTech.unknown_rest));
	
	refOutput.WriteUInt32(refTech.nUnknownAdditionals1);
	repeat(refTech.nUnknownAdditionals1, j)
	{
		refOutput.WriteUInt32(refTech.pUnknownAdditionals1[j]);
	}

	refOutput.WriteUInt32(refTech.nUnknownAdditionals2);
	repeat(refTech.nUnknownAdditionals2, j)
	{
		refOutput.WriteUInt32(refTech.pUnknownAdditionals2[j]);
	}
}

//Public methods
void CDbTechtreeManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 groupId, index, i;
	
	foreach(it, this->techtrees)
	{
		const CString &refCurrentEpochName = (*it).epoch.identifier;
		const CString &refCurrentEpochLowerCase = refCurrentEpochName.ToLowercase();
		
		groupId = refItemList.InsertGroup(refCurrentEpochName);
		if(refCurrentEpochLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem(groupId);
			refItemList.SetItemText(refCurrentEpochName, index, 0);
			refItemList.SetItemData(index, MAKE32(it.GetIndex(), 0));
		}

		for(i = 0; i < (*it).nTechs; i++)
		{
			const CString &refCurrentName = (*it).pTechs[i].identifier;
			const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
			
			if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
			{
				index = refItemList.InsertItem(groupId);
				refItemList.SetItemText(refCurrentName, index, 0);
				refItemList.SetItemData(index, MAKE32(it.GetIndex(), i+1));
			}
		}
	}
}

void CDbTechtreeManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 groupId, index, i;
	
	foreach(it, this->techtrees)
	{
		const CString &refCurrentEpochName = DbManager::Get().GetLanguageString((*it).epoch.stringId, true).ToCString();
		const CString &refCurrentEpochLowerCase = refCurrentEpochName.ToLowercase();
		
		groupId = refItemList.InsertGroup(refCurrentEpochName);
		if(refCurrentEpochLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem(groupId);
			refItemList.SetItemText(refCurrentEpochName, index, 0);
			refItemList.SetItemData(index, MAKE32(it.GetIndex(), 0));
		}

		for(i = 0; i < (*it).nTechs; i++)
		{
			const CString &refCurrentName = DbManager::Get().GetLanguageString((*it).pTechs[i].stringId, true).ToCString();
			const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
			
			if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
			{
				index = refItemList.InsertItem(groupId);
				refItemList.SetItemText(refCurrentName, index, 0);
				refItemList.SetItemData(index, MAKE32(it.GetIndex(), i+1));
			}
		}
	}
}

CString CDbTechtreeManager::GetFileTitle() const
{
	return "dbtechtree";
}

void CDbTechtreeManager::Init()
{
	g_MainWindow.GetItemList().EnableGroupView();
}

void CDbTechtreeManager::ReadInput(AInputStream &refInput)
{
	uint32 i;
	STechtree currentTree;
	
	while(refInput.GetRemainingBytes())
	{
		refInput.ReadUInt32(currentTree.nTechs);
		this->ReadTech(currentTree.epoch, refInput);

		currentTree.pTechs = (STech *)malloc(currentTree.nTechs * sizeof(*currentTree.pTechs));
		for(i = 0; i < currentTree.nTechs; i++)
		{
			this->ReadTech(currentTree.pTechs[i], refInput);
		}
		
		this->techtrees.Push(currentTree);
	}

	//finding out values
	foreach(it, this->techtrees)
	{
		/*if((*it).epoch.blabla[j] > 1)
		{
			stdOut << (*it).epoch.identifier << endl;
		}*/
		
		/*for(i = 0; i < (*it).nTechs; i++)
		{
			if((*it).pTechs[i].techId == 9311)
			{
				stdOut << (*it).pTechs[i].identifier << endl;
			}
		}*/
	}
}

void CDbTechtreeManager::Save(AOutputStream &refOutput) const
{
	uint32 i;
	
	foreach(it, this->techtrees)
	{
		refOutput.WriteUInt32((*it).nTechs);
		this->WriteTech((*it).epoch, refOutput);

		for(i = 0; i < (*it).nTechs; i++)
		{
			this->WriteTech((*it).pTechs[i], refOutput);
		}
	}
}

CString CDbTechtreeManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	uint32 i;
	STech *pCurrentTech;
	
	if(HIGH16(index) == 0)
		pCurrentTech = (STech *)&this->techtrees[LOW16(index)].epoch;
	else
		pCurrentTech = (STech *)&this->techtrees[LOW16(index)].pTechs[HIGH16(index)-1];
	
	APPENDCHARARRAY("Identifier", pCurrentTech->identifier, "", false);
	APPENDUINT32("Unknown (Unique)", pCurrentTech->id1, "", false);
	APPENDUINT32("Tech ID", pCurrentTech->techId, "", false);
	APPENDUINT32("Start Epoch Id", pCurrentTech->startEpochId, "", false);
	APPENDUINT32("End Epoch Id", pCurrentTech->endEpochId, "", false);

	debugout(pCurrentTech->unknown1, sizeof(pCurrentTech->unknown1), index);

	APPENDUINT32("Wood cost", pCurrentTech->costWood, "", true);
	APPENDUINT32("Stone cost", pCurrentTech->costStone, "", true);
	APPENDUINT32("Gold cost", pCurrentTech->costGold, "", true);
#ifdef _DEBUG
	APPENDUINT32("Unknown cost (Might be iron from Empire Earth?!)", pCurrentTech->costUnknown, "", false);
#endif
	APPENDUINT32("Food cost", pCurrentTech->costFood, "", true);

	APPENDUINT32("Build Speed (Slow Ingame Speed)", pCurrentTech->buildSpeed, "Real Build Speed = Build Speed x Coef.; Coef: 1 Slow, ? Normal, ? Fast, 0.4 Very Fast ingame speed", true);

	debugout(pCurrentTech->unknown3, sizeof(pCurrentTech->unknown3), index);
	
	APPENDUINT32("Button Id", pCurrentTech->buttonId, "", false);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long x", pCurrentTech->unknown4, "", false);
	}

	APPENDUINT32("String Id", pCurrentTech->stringId, DbManager::Get().GetLanguageString(pCurrentTech->stringId, true).ToCString(), false);

	debugout(pCurrentTech->unknown5, sizeof(pCurrentTech->unknown5), index);

	APPENDUINT32("Phoenix-civilization-table Id", pCurrentTech->phoenixCivTableId, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 8", pCurrentTech->unknown8, "", true);
		SETUNKNOWN;
	}

	APPENDUINT32("Amount", pCurrentTech->amount, "How many techs you get when purchasing this", true);

	debugout(pCurrentTech->unknown6, sizeof(pCurrentTech->unknown6), index);

	APPENDUINT32("Prerequisite String Id 1", pCurrentTech->prerequisiteStringId1, DbManager::Get().GetLanguageString(pCurrentTech->prerequisiteStringId1).ToCString(), false);
	APPENDUINT32("Prerequisite String Id 2", pCurrentTech->prerequisiteStringId2, DbManager::Get().GetLanguageString(pCurrentTech->prerequisiteStringId2).ToCString(), false);
	APPENDUINT32("Tooltip String Id", pCurrentTech->toolTipStringId, DbManager::Get().GetLanguageString(pCurrentTech->toolTipStringId).ToCString(), false);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 30", pCurrentTech->unknownFloat30, "", true);
		APPENDFLOAT("Unknown Float 31", pCurrentTech->unknownFloat31, "", true);
		APPENDFLOAT("Unknown Float 32", pCurrentTech->unknownFloat32, "", true);
		APPENDFLOAT("Unknown Float 33", pCurrentTech->unknownFloat33, "", true);
		
		APPENDBOOL("Unknown Bool 1", pCurrentTech->unknownBool1, "", true);
	}

	APPENDBOOL("Editor-only", pCurrentTech->editorOnly, "false means that unit is buildable", true);

	if(showUnknownValues)
	{
		APPENDBOOL("Unknown Bool 3", pCurrentTech->unknownBool3, "", true);
		APPENDBOOL("Unknown Bool 4", pCurrentTech->unknownBool4, "", true);
	}
	
	debugout(pCurrentTech->unknown, sizeof(pCurrentTech->unknown), index);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 7", pCurrentTech->unknown7, "there seems to be a link between this value and unknown long 4 in dbobjects", true);
	}

	debugout(pCurrentTech->unknown_rest, sizeof(pCurrentTech->unknown_rest), index);

#ifdef _DEBUG
	APPENDUINT32("Unknown Additionals 1", pCurrentTech->nUnknownAdditionals1, "", NULL);
	for(i = 0; i < pCurrentTech->nUnknownAdditionals1; i++)
	{
		APPENDUINT32("Unknown Additionals 1 - " + CString(i), pCurrentTech->pUnknownAdditionals1[i], "could be a building id (like unknown7)", false);
	}
	APPENDUINT32("Unknown Additionals 2", pCurrentTech->nUnknownAdditionals2, "", NULL);
	for(i = 0; i < pCurrentTech->nUnknownAdditionals2; i++)
	{
		APPENDUINT32("Unknown Additionals 2 - " + CString(i), pCurrentTech->pUnknownAdditionals1[i], "when is unknown additionals 2 needed?", false);
	}
#endif
	
	return DbManager::Get().GetLanguageString(pCurrentTech->stringId, true).ToCString();
}

bool CDbTechtreeManager::SupportsFilterByDisplayString() const
{
	return true;
}

void CDbTechtreeManager::Uninit()
{
	g_MainWindow.GetItemList().EnableGroupView(false);
}