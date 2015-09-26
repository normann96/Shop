#ifndef ToolsOutput_h__
#define ToolsOutput_h__
#include "../Library/BaseOutput.h"
#include "ToolsInput.h"

class ToolsOutput : public BaseOutput
{
public:
	ToolsOutput();
	virtual ~ToolsOutput();

	virtual void ShowProduct(Product * product);
	void ShowAllProducts(std::vector<Product*> &productsArray);
protected:
private:
};
#endif // ToolsOutput_h__
