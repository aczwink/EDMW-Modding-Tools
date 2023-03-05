//Local
#include "IDbManager.h"

class CDbPhoenixCivTableManager : public IDbManager
{
	struct SPhoenixCivTable
	{
		uint32 unknown1[2];
		char identifier[100];
		uint32 unknown2[25];
		uint32 nameStringId;
		uint32 unknown4[25];
		float32 unknownFloat2;
		float32 unknownFloat3;
		float32 unknownFloat4;
		uint32 unknown3;
		float32 unknownFloat1;
		uint32 unknownRest[3];
	};
private:
	//Members
	uint32 nTables;
	SPhoenixCivTable *pTables;
public:
	//Constructor
	CDbPhoenixCivTableManager();
	//Destructor
	~CDbPhoenixCivTableManager();
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