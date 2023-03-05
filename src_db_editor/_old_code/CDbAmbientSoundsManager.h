//Local
#include "IDbManager.h"

class CDbAmbientSoundsManager : public IDbManager
{
	struct SAmbientSounds
	{
		char identifier[100];
		uint32 unknown1[3];
		float32 unknownFloat1;
		float32 unknownFloat2;
		float32 unknownFloat3;
		float32 unknownFloat4;
		float32 unknownFloat5;
		uint32 unknownrest[5];
	};
private:
	//Members
	uint32 nAmbientSounds;
	SAmbientSounds *pAmbientSounds;
public:
	//Constructor
	CDbAmbientSoundsManager();
	//Destructor
	~CDbAmbientSoundsManager();
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