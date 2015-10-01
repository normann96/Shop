#ifndef _SHOP_H
#define _SHOP_H

#include "Category.h"
#include "BaseText.h"
#include "ConsoleText.h"
#include "Balance.h"
#include "../Library/BaseFactory.h"
#include "../Library/SecurityInput.h"

#define BALANCE "balance.db"


class Shop
{
private:
	Category *m_pCategory;
	BaseText *m_pBaseTxt;
	Balance *m_pBalance;

	std::vector<std::string> m_pPathNameDLL;
	std::string sCurPathToDLL();
	unsigned int m_nCountLibrary;
	HMODULE *m_pHmod;

	bool Run();
	void OpenDLL();
	
	void DeleteProduct(unsigned int numCategory, unsigned int numProduct);	// undef

	double GetBalance();
	void SaveBalance();
	void LoadBalance();
	void SetBalance(double balance);

	void CreateNewProduct(unsigned int numCategory);
	void ShowAllProduct(unsigned int numCategory);
	void ShowProduct(unsigned int numCategory, unsigned int numProduct);	// unused
	void EditProduct(unsigned int numCategory, unsigned int numProduct);

	void ShowCategory();
	int GetNumberCategory();
	int GetCountProducts(unsigned int numCategory);

	void BuyNewProduct(unsigned int numCategory);
	void BuyExistProduct(unsigned int numCategory, unsigned int numProduct, unsigned int quantityProd);
	void SellProduct(unsigned int numCategory, unsigned int numProduct, unsigned int quantityProd);

	void Save(unsigned int numCategory);
	void Load(unsigned int numCategory);

public:
	Shop();
	~Shop();

	void ShowBalance(); 
	void SetBalance();

	void Menu();

	void ExitAndSave();
	void Sell();
	void Buy();
	void New();
	void Edit();
	void ShowProducts();
	void Refresh();
	void Save();
	void Load();
};



#endif // _SHOP_H