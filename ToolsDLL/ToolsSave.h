#ifndef ToolsSave_h__
#define ToolsSave_h__
#include "../Library/BaseSave.h"

class ToolsSave : public BaseSave
{
public:
	ToolsSave();
	virtual ~ToolsSave();
	void Save(std::vector<Product*> & produts);
protected:
private:
};
#endif // ToolsSave_h__
