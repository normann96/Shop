#ifndef BaseOutput_h__
#define BaseOutput_h__

#include "Product.h"

class BaseOutput
{
private:
protected:
	
public:
	BaseOutput();
	virtual ~BaseOutput();
	virtual void ShowProduct(Product * product) = 0;
	virtual void ShowAllProducts(std::vector<Product*> &productsArray) = 0;
};
#endif // BaseOutput_h__
