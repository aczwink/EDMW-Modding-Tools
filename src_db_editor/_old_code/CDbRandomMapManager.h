//Local
#include "IDbManager.h"

class CDbRandomMapManager : public IDbManager
{
	struct SRandomMap
	{
		uint32 unknown1[2];
		char identifier[100];
		uint32 unknownRest[6];
	};
private:
	//Members
	uint32 nTables;
	SRandomMap *pTables;
public:
	//Constructor
	CDbRandomMapManager();
	//Destructor
	~CDbRandomMapManager();
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