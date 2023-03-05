//Local
#include "IDbManager.h"

class CDbSoundsManager : public IDbManager
{
	class CSound
	{
	public:
		CString fileName;
		char identifier[100];
		char identifier2[100];
		uint32 unknownRest[8];
	};
private:
	//Members
	uint32 nSounds;
	CSound *pSounds;
public:
	//Constructor
	CDbSoundsManager();
	//Destructor
	~CDbSoundsManager();
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