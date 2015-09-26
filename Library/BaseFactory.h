#ifndef BaseFactory_h__
#define BaseFactory_h__

#include "../Library/BaseInput.h"
#include "../Library/BaseOutput.h"
#include "../Library/BaseSave.h"
#include "../Library/BaseLoad.h"

class BaseFactory
{
public:
	BaseFactory();
	virtual ~BaseFactory();
	virtual BaseInput	* CreateBaseInput() = 0;
	virtual BaseOutput	* CreateBaseOutput() = 0;
	virtual BaseSave	* CreateBaseSave() = 0;
	virtual BaseLoad	* CreateBaseLoad() = 0;
protected:

private:
};

#endif // BaseFactory_h__
