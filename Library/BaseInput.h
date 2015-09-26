#ifndef BaseInput_h__
#define BaseInput_h__

#include "../Library/Product.h"

class BaseInput
{
public:
	BaseInput();
	virtual ~BaseInput();

	virtual Product * CreateProduct() = 0;
	virtual void EditDataOfProduct(Product * product) = 0; 
	virtual void BuyExistProd(Product * product, unsigned int quanity, double & pBalance) = 0;
	virtual void SellProd(Product * product, unsigned int quanity, double & pBalance) = 0;

	virtual void BuyNewProd(Product * product, double & pBalance) = 0;
protected:

private:
};
#endif // BaseInput_h__
