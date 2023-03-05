//Local
#include "IDbManager.h"

class CDbTechtreeManager : public IDbManager
{
	struct STech
	{
		char identifier[100];
		uint32 id1;
		uint32 techId;
		uint32 startEpochId;
		uint32 endEpochId;
		uint32 unknown1[2];
		uint32 costWood;
		uint32 costStone;
		uint32 costGold;
		uint32 costUnknown;
		uint32 costFood;
		uint32 buildSpeed;
		uint32 unknown3[5];
		uint32 buttonId;
		uint32 unknown4;
		uint32 stringId;
		uint32 unknown5[6];
		uint32 phoenixCivTableId;
		uint32 unknown8;
		uint32 amount;
		uint32 unknown6[4];
		uint32 prerequisiteStringId1;
		uint32 prerequisiteStringId2;
		uint32 toolTipStringId;
		float32 unknownFloat30;
		float32 unknownFloat31;
		float32 unknownFloat32;
		float32 unknownFloat33;
		bool unknownBool1;
		bool editorOnly;
		bool unknownBool3;
		bool unknownBool4;
		uint32 unknown[40];
		uint32 unknown7;
		uint32 unknown_rest[2];
		uint32 nUnknownAdditionals1;
		uint32 *pUnknownAdditionals1;
		uint32 nUnknownAdditionals2;
		uint32 *pUnknownAdditionals2;
	};
	
	struct STechtree
	{
		uint32 nTechs;
		STech epoch;
		STech *pTechs;
	};
private:
	//Members
	CArray<STechtree> techtrees;
	//Methods
	void ReadTech(STech &refTech, AInputStream &refInput);
	void WriteTech(const STech &refTech, AOutputStream &refOutput) const;
public:
	//Constructor
	CDbTechtreeManager();
	//Destructor
	~CDbTechtreeManager();
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