#ifndef BaseLoad_h__
#define BaseLoad_h__

#include "Product.h"

class BaseLoad
{
public:
	BaseLoad();
	virtual ~BaseLoad();
	virtual void Load(std::vector<Product*> & produts) = 0;
protected:
private:
};
#endif // BaseLoad_h__
