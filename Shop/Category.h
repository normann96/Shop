#ifndef _CATEGORYy_H
#define _CATEGORYy_H

#include <vector>
#include "../Library/Product.h"
#include "../Library/BaseFactory.h"
#include "../Library/BaseOutput.h"
#include "../Library/BaseInput.h"
#include "../Library/BaseSave.h"
#include "../Library/BaseLoad.h"

class Category
{
private:
	friend class Shop;
	std::string m_name;
	std::vector<Product*> m_pvProdCat;
protected:
public:
	Category();
	~Category();
	
	BaseFactory *m_pBaseFactory;
	BaseOutput	*m_pBaseOut;
	BaseInput	*m_pBaseInput;
	BaseSave	*m_pBaseSave;
	BaseLoad	*m_pBaseLoad;
};

#endif // _CATEGORYy_H