#ifndef AliveLoad_h__
#define AliveLoad_h__
#include "../Library/BaseLoad.h"
#include "AliveInput.h"

class AliveLoad : public BaseLoad
{
public:
	AliveLoad();
	virtual ~AliveLoad();
	void Load(std::vector<Product*> & produts);

protected:
private:
	AliveInput * m_pAI;
	Alive *m_pAl;
};
#endif // AliveLoad_h__
