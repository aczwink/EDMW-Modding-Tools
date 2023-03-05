//Local
#include "IDbManager.h"

class CDbCalamityManager : public IDbManager
{
	struct SCalamity
	{
		char identifier[100];
		float32 unknownFloat1;
		float32 unknownFloat2;
		float32 unknownFloat3;
		float32 unknownFloat4;
		float32 unknownFloat5;
		float32 unknownFloat6;
		uint32 unknown1[12];
		float32 unknownFloat7;
		uint32 unknown2[8];
		bool unknownBool1;
		bool unknownBool2;
		bool unknownBool3;
		bool unknownBool4;
		uint32 unknownrest[13];
	};
private:
	//Members
	uint32 nCalamities;
	SCalamity *pCalamities;
public:
	//Constructor
	CDbCalamityManager();
	//Destructor
	~CDbCalamityManager();
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