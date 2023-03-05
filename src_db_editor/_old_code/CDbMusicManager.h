//Local
#include "IDbManager.h"

class CDbMusicManager : public IDbManager
{
	struct SMusic
	{
		uint32 unknown[2];
		char identifier[100];
		char sptFileName[100];
	};
private:
	//Members
	uint32 nMusic;
	SMusic *pMusic;
public:
	//Constructor
	CDbMusicManager();
	//Destructor
	~CDbMusicManager();
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