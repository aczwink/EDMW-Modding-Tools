//SJC Libs
#include <SJCLib.h>
#include <SJCWinLib.h>
//Local
#include "CComboBoxDbFile.h"
#include "IDbManager.h"
#include "CItemTable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define APPENDBOOL(description, value, assoc, isEditable) DbManager::Get().InsertTableItem(description, &value, 0, ITEMDATATYPE_BOOL, assoc, index, isEditable);
#define APPENDCHARARRAY(description, array, assoc, isEditable) DbManager::Get().InsertTableItem(description, (char *)&array, sizeof(array), ITEMDATATYPE_CHARARRAY, assoc, index, isEditable);
#define APPENDFLOAT(description, value, assoc, isEditable) DbManager::Get().InsertTableItem(description, &value, 0, ITEMDATATYPE_FLOAT, assoc, index, isEditable);
#define APPENDINT32(description, value, assoc, isEditable) DbManager::Get().InsertTableItem(description, &value, 0, ITEMDATATYPE_INT32, assoc, index, isEditable);
#define APPENDSTRING(description, string, assoc, isEditable) DbManager::Get().InsertTableItem(description, &string, 0, ITEMDATATYPE_STRING, assoc, index, isEditable);
#define APPENDUINT32(description, value, assoc, isEditable) DbManager::Get().InsertTableItem(description, &value, 0, ITEMDATATYPE_UINT32, assoc, index, isEditable);
#define APPENDCUSTOM(description, value, assoc, itemDataType) DbManager::Get().InsertTableItem(description, &value, 0, itemDataType, assoc, index, true);
#define SETCONSTANT DbManager::Get().SetState(1);
#define SETUNKNOWN DbManager::Get().SetState(2);

class DbManager
{
	friend class CItemTable;
	
	enum EDbFileType
	{
		DBFILETYPE_NONE,
		DBFILETYPE_AIUNITTARGETING,
		DBFILETYPE_AMBIENTSOUNDS,
		DBFILETYPE_ANIMALS,
		DBFILETYPE_AREAEFFECTS,
		DBFILETYPE_BUTTONS,
		DBFILETYPE_CALAMITIES,
		DBFILETYPE_CIVSPECAI,
		DBFILETYPE_COLORTABLE,
		DBFILETYPE_FAMILY,
		DBFILETYPE_GFXEFFECTS,
		DBFILETYPE_GRAPHICS,
		DBFILETYPE_MOUSEPOINTERS,
		DBFILETYPE_MUSIC,
		DBFILETYPE_OBJECTS,
		DBFILETYPE_PHOENIXCIVTABLES,
		DBFILETYPE_PREMADECIVS,
		DBFILETYPE_RANDOMMAP,
		DBFILETYPE_SOUNDS,
		DBFILETYPE_SPECIALUNITTABLE,
		DBFILETYPE_TECHTREES,
		DBFILETYPE_UICONTROLS,
		DBFILETYPE_UIFONTS,
		DBFILETYPE_UIHOTKEYS,
		DBFILETYPE_UNITSET,
		DBFILETYPE_WEAPONTOHIT,
	};
private:
	//Variables
	EDbFileType dbType;
	CModule *pLangdll;
	CModule *pLang2dll;
	CMap<uint32, SItemTableData> data;
	bool byIdentifier;
	uint32 lastIdx;
public:
	//Functions
	void Filter(const CString &refText);
	void FilterBy(bool byIdentifier);
	CWString GetLanguageString(uint32 id, bool lang2dll = false);
	void Init();
	void InsertTableItem(CString description, void *pBuffer, uint32 bufferSize, EItemDataType type, CString assoc, uint32 itemListIndex, bool isEditable);
	void Save();
	void SetFile(uint64 itemData);
	void SetItem(uint32 index);

	//Inline
	inline const SItemTableData &GetItemData(uint32 index) const
	{
		return this->data[index];
	}

	inline bool IsFilterByIdentifier() const
	{
		return this->byIdentifier;
	}

	inline void SetState(uint8 state)
	{
		this->data[this->lastIdx].state = state;
	}
};