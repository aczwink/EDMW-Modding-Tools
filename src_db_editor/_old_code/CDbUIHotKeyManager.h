//Local
#include "IDbManager.h"

class CDbUIHotKeyManager : public IDbManager
{
	struct SHotKey
	{
		uint32 unknown1;
		uint32 unknown2;
		char identifier[100];
		uint32 unknown3;
		uint32 unknown4;
		uint32 unknown5;
		uint32 unknown6;
		uint32 stringId;
		uint32 unknown8;
		uint32 unknown9;
	};
private:
	//Members
	uint32 nHotKeys;
	SHotKey *pHotKeys;
public:
	//Constructor
	CDbUIHotKeyManager();
	//Destructor
	~CDbUIHotKeyManager();
	//Methods
	void Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const;
	void FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const;
	CString GetFileTitle() const;
	void Init();
	void ReadInput(AInputStream &refInput);
	void Save(AOutputStream &refOutput) const;
	CString SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const;
	bool SupportsFilterByDisplayString() const;
	void Uninit();
};