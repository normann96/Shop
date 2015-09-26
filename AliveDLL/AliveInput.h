#ifndef AliveInput_h__
#define AliveInput_h__
#include "../Library/BaseInput.h"
#include "../Library/SecurityInput.h"
#include "AliveDLL.h"

class AliveInput : public BaseInput
{
public:
	friend class AliveLoad;

	AliveInput();
	virtual ~AliveInput();

protected:
	virtual Product * CreateProduct();
	virtual void EditDataOfProduct(Product * product);
	virtual void BuyNewProd(Product * product, double & pBalance);
	virtual void BuyExistProd(Product * product, unsigned int quanity, double & pBalance);
	virtual void SellProd(Product * product, unsigned int quanity, double & pBalance);

private:
	Alive ** m_ppAliveArray;
	int m_numberAlive;
};
#endif // AliveInput_h__
