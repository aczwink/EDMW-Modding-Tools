//Local
#include "IDbManager.h"

class CDbAnimalsManager : public IDbManager
{
	struct SAnimal
	{
		char identifier[100];
		uint32 unknown1[14];
		float32 unknownFloat1;
		uint32 unknown2[8];
		float32 unknownFloat2;
		float32 unknownFloat3;
		uint32 unknown3[4];
		float32 unknownFloat4;
		uint32 unknownrest[13];
	};
private:
	//Members
	uint32 nAnimals;
	SAnimal *pAnimals;
public:
	//Constructor
	CDbAnimalsManager();
	//Destructor
	~CDbAnimalsManager();
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