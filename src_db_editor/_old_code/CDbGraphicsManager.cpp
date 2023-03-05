//Class Header
#include "CDbGraphicsManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbGraphicsManager::CDbGraphicsManager()
{
}

//Destructor
CDbGraphicsManager::~CDbGraphicsManager()
{
	HeapDeleteArraySafe(this->pGraphics);
}

//Private methods
void CDbGraphicsManager::ReadGraphic(SGraphic &refGraphic, AInputStream &refInput)
{
	uint32 i;
	
	this->ReadString(refGraphic.identifier, refInput);
	for(i = 0; i < sizeof(refGraphic.textures)/sizeof(refGraphic.textures[0]); i++)
	{
		this->ReadString(refGraphic.textures[i], refInput);
	}
	refInput.ReadBytes(refGraphic.anotherIdentifier, sizeof(refGraphic.anotherIdentifier));
	refInput.ReadBytes(refGraphic.identifier3, sizeof(refGraphic.identifier3));
	refInput.ReadUInt32(refGraphic.unknown2);
	refInput.ReadUInt32(refGraphic.id);
	refInput.ReadBytes(refGraphic.unknown1, sizeof(refGraphic.unknown1));
	refInput.ReadFloat32(refGraphic.unknownFloat1);
	refInput.ReadUInt32(refGraphic.unknownLong1);
	refInput.ReadFloat32(refGraphic.unknownFloat2);
	refInput.ReadBytes(refGraphic.unknownRest, sizeof(refGraphic.unknownRest));
}

void CDbGraphicsManager::ReadString(CString &refString, AInputStream &refInput)
{
	uint32 length, i;

	refInput.ReadUInt32(length);
	for(i = 0; i < length; i++)
		refString += (char)refInput.ReadByte();
}

void CDbGraphicsManager::WriteGraphic(SGraphic &refGraphic, AOutputStream &refOutput) const
{
	uint32 i;
	
	this->WriteString(refGraphic.identifier, refOutput);
	for(i = 0; i < sizeof(refGraphic.textures)/sizeof(refGraphic.textures[0]); i++)
	{
		this->WriteString(refGraphic.textures[i], refOutput);
	}
	refOutput.WriteBytes(refGraphic.anotherIdentifier, sizeof(refGraphic.anotherIdentifier));
	refOutput.WriteBytes(refGraphic.identifier3, sizeof(refGraphic.identifier3));
	refOutput.WriteUInt32(refGraphic.unknown2);
	refOutput.WriteUInt32(refGraphic.id);
	refOutput.WriteBytes(refGraphic.unknown1, sizeof(refGraphic.unknown1));
	refOutput.WriteFloat32(refGraphic.unknownFloat1);
	refOutput.WriteUInt32(refGraphic.unknownLong1);
	refOutput.WriteFloat32(refGraphic.unknownFloat2);
	refOutput.WriteBytes(refGraphic.unknownRest, sizeof(refGraphic.unknownRest));
}

void CDbGraphicsManager::WriteString(CString &refString, AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(refString.GetLength());
	refOutput.WriteString(refString);
}

//Public methods
void CDbGraphicsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;

	for(i = 0; i < this->nGraphics; i++)
	{
		const CString &refCurrentName = this->pGraphics[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbGraphicsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbGraphicsManager::GetFileTitle() const
{
	return "dbgraphics";
}

void CDbGraphicsManager::Init()
{
}

void CDbGraphicsManager::ReadInput(AInputStream &refInput)
{
	uint32 i;
	SGraphic graphic;
	
	refInput.ReadUInt32(this->nGraphics);
	
	this->pGraphics = new SGraphic[this->nGraphics];
	
	for(i = 0; i < this->nGraphics; i++)
	{
		this->ReadGraphic(this->pGraphics[i], refInput);
	}


	/*uint32 max = 0, bla;
	for(i = 0; i < this->nGraphics; i++)
	{
		if(strlen((char *)this->pGraphics[i].identifier3) > max)
		{
			max = strlen(this->pGraphics[i].identifier3);
			bla = i;
		}
	}

	stdOut << max << this->pGraphics[bla].identifier << endl;*/
}

void CDbGraphicsManager::Save(AOutputStream &refOutput) const
{
	uint32 i;
	
	refOutput.WriteUInt32(this->nGraphics);
	
	for(i = 0; i < this->nGraphics; i++)
	{
		this->WriteGraphic(this->pGraphics[i], refOutput);
	}
}

CString CDbGraphicsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	uint32 i;
	SGraphic &refGraphic = this->pGraphics[index];
	
	APPENDSTRING("Identifier", refGraphic.identifier, "", false);

	for(i = 0; i < sizeof(refGraphic.textures) / sizeof(refGraphic.textures[0]); i++)
	{
		APPENDSTRING(CString("Texture ") + CString(i), refGraphic.textures[i], "", true);
	}

	if(showUnknownValues)
	{
		APPENDCHARARRAY("Identifier 2???", refGraphic.anotherIdentifier, "", false);
		APPENDCHARARRAY("Identifier 3???", refGraphic.identifier3, "", false);
		APPENDUINT32("Unknown 2", refGraphic.unknown2, "", true);
	}

	APPENDUINT32("Id", refGraphic.id, "", false);
	
	debugout((uint32 *)refGraphic.unknown1, sizeof(refGraphic.unknown1), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refGraphic.unknownFloat1, "", true);
		APPENDUINT32("Unknown Long 1", refGraphic.unknownLong1, "", true);
		APPENDFLOAT("Unknown Float 2", refGraphic.unknownFloat2, "", true);
	}
	
	debugout((uint32 *)refGraphic.unknownRest, sizeof(refGraphic.unknownRest), index);
	
	return refGraphic.identifier;
}

bool CDbGraphicsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbGraphicsManager::Uninit()
{
}