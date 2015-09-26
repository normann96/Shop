#ifndef AliveFactory_h__
#define AliveFactory_h__

#include "../Library/BaseFactory.h"

class AliveFactory : public BaseFactory
{
public:
	AliveFactory();
	virtual ~AliveFactory();

	virtual BaseInput	* CreateBaseInput();
	virtual BaseOutput	* CreateBaseOutput();
	virtual BaseSave	* CreateBaseSave();
	virtual BaseLoad	* CreateBaseLoad();
	
protected:
private:
	BaseInput *m_pInputAlive;
	BaseOutput *m_pOutputAlive;
	BaseLoad *m_pLoadAlive;
	BaseSave *m_pSaveAlive;
};

#endif // AliveFactory_h__
