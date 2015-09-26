#ifndef ToolsLoad_h__
#define ToolsLoad_h__
#include "../Library/BaseLoad.h"
#include "ToolsInput.h"

class ToolsLoad : public BaseLoad
{
public:
	ToolsLoad();
	virtual ~ToolsLoad();
	void Load(std::vector<Product*> & produts);
protected:
private:
	ToolsInput * m_pTI;
};

#endif // ToolsLoad_h__
