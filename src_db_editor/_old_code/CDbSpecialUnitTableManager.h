//Local
#include "IDbManager.h"

class CDbSpecialUnitTableManager : public IDbManager
{
	class SSpecialUnitTable
	{
	public:
		char identifier[100];
		uint32 unknown1;
		uint32 unknown2;
		float32 unknown3;
		float32 unknown4;
		uint32 unknownRest[8];
	};
private:
	//Members
	uint32 nTables;
	SSpecialUnitTable *pTables;
public:
	//Constructor
	CDbSpecialUnitTableManager();
	//Destructor
	~CDbSpecialUnitTableManager();
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