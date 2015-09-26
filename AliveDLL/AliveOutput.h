#ifndef AliveOutput_h__
#define AliveOutput_h__
#include "../Library//BaseOutput.h"
#include "AliveInput.h"

class AliveOutput : public BaseOutput
{
public:
	AliveOutput();
	virtual ~AliveOutput();

	void ShowProduct(Product * product);
	void ShowAllProducts(std::vector<Product*> &productsArray);
protected:
private:
};
#endif // AliveOutput_h__
