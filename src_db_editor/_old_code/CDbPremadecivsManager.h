//Local
#include "IDbManager.h"

class CDbPremadecivsManager : public IDbManager
{
	struct SPremadeciv
	{
		uint32 unknown1[2];
		char identifier[100];
		uint32 unknown2;
		uint32 nameStringId;
		uint32 epochRangeStringId;
		uint32 civilizationTechId;
	};
private:
	//Members
	uint32 nTables;
	SPremadeciv *pTables;
public:
	//Constructor
	CDbPremadecivsManager();
	//Destructor
	~CDbPremadecivsManager();
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