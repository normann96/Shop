#ifndef ToolsFactory_h__
#define ToolsFactory_h__
#include "../Library/BaseFactory.h"

class ToolsFactory : public BaseFactory
{
public:
	ToolsFactory();
	virtual ~ToolsFactory();

	virtual BaseInput	* CreateBaseInput();
	virtual BaseOutput	* CreateBaseOutput();
	virtual BaseSave	* CreateBaseSave();
	virtual BaseLoad	* CreateBaseLoad();
protected:
private:
	BaseInput *m_pInputTools;
	BaseOutput *m_pOutputTools;
	BaseLoad *m_pLoadTools;
	BaseSave *m_pSaveTools;
};
#endif // ToolsFactory_h__
