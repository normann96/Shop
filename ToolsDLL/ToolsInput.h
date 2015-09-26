#ifndef ToolsInput_h__
#define ToolsInput_h__
#include "../Library/BaseInput.h"
#include "../Library/SecurityInput.h"
#include "ToolsDLL.h"

class ToolsInput : public BaseInput
{
public:
	friend class ToolsLoad;

	ToolsInput();
	virtual ~ToolsInput();

protected:
	virtual Product * CreateProduct();
	virtual void EditDataOfProduct(Product * product);
	virtual void BuyNewProd(Product * product, double & pBalance);
	virtual void BuyExistProd(Product * product, unsigned int quanity, double & pBalance);
	virtual void SellProd(Product * product, unsigned int quanity, double & pBalance);
	
private:
	Tools ** m_ppToolsArray;
	int m_numberTools;
};
#endif // ToolsInput_h__
