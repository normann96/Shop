#ifndef BaseSave_h__
#define BaseSave_h__

// #include "BaseFactory.h"
// #include "AliveFactory.h"
// #include "ToolsFactory.h"

#include "../Library/Product.h"

class BaseSave
{
private:
protected:
public:
	BaseSave();
	virtual ~BaseSave();

	virtual void Save(std::vector<Product*> & produts) = 0;
	// 	friend class BaseFactory;
	// 	friend class AliveFactory;
	// 	friend class ToolsFactory;

};
#endif // BaseSave_h__
