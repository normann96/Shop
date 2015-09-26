#include "stdafx.h"
#include "Shop.h"
#include <wchar.h>

#define PASSWORD "admin"

Shop::Shop() : m_nCountLibrary(0), m_pHmod(nullptr), m_pPathNameDLL(NULL), m_pCategory(nullptr), m_pBaseTxt(nullptr), m_pBalance(nullptr)
{
	if(this->Run())					 //	ищем DLL, если находим - открывает, инчае выход
		this->OpenDLL();
	else
		exit(1);

 	m_pBaseTxt = new ConsoleText;
 	
	m_pBalance = new Balance;
	this->LoadBalance();

	for (unsigned int i = 0; i < m_nCountLibrary; i++)
		this->Load(i);

#ifdef test_cout_shop
	std::cout << "I'm Constructor by Shop\t\t  " << this << std::endl;
#endif
}

Shop::~Shop()
{
	this->SaveBalance();
 	for (unsigned int i = 0; i < m_nCountLibrary; i++)
 		this->Save(i);

	if (m_pHmod)
		delete [] m_pHmod;

	if(m_pBaseTxt)
		delete m_pBaseTxt;

	if(m_pBalance)
		delete m_pBalance;

	if(m_pCategory)
		delete [] m_pCategory;

	for (unsigned int i = 0; i < m_nCountLibrary; i++)
		FreeLibrary(m_pHmod[i]);

#ifdef test_cout_shop
	std::cout << "I'm Destructor  by Shop\t\t  " << this << std::endl;
#endif
}

void Shop::ShowBalance()
{
	m_pBalance->ShowBalance();
}

std::string Shop::sCurPathToDLL()
{
	char szCurrentPath[260];
	GetCurrentDirectory(sizeof(szCurrentPath), szCurrentPath);
	std::string sStrTemp = szCurrentPath;
	sStrTemp += ("\\*.dll");
	return sStrTemp;
}

bool Shop::Run()																					// находим DLL и сохраняем путь в вектор m_pVectPath, количество DLL - m_nCountLibrary
{
	m_nCountLibrary = 0;
	WIN32_FIND_DATA f_data;
	ZeroMemory(&f_data, sizeof(WIN32_FIND_DATA));
	HANDLE hFind = NULL;
	m_pPathNameDLL.clear();

#ifdef _DEBUG
	hFind = FindFirstFile("../Debug/*.dll", &f_data);												// ищем dll в папке Debug по маске *.dll
#else 
	hFind = FindFirstFile("../Release/*.dll", &f_data);												// ищем dll в папке Realese по маске *.dll
#endif
	
	if (hFind == INVALID_HANDLE_VALUE)																// ищем dll в текущей папке с exe
	{
		char pStr[MAX_PATH];
		strcpy(pStr, sCurPathToDLL().c_str());
		hFind = FindFirstFile(pStr, &f_data);
	}
	
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
 			m_pPathNameDLL.push_back(f_data.cFileName);
			m_nCountLibrary++;
		}while(FindNextFile(hFind, &f_data));
	}
	else															
	{
		con_color(12);
		std::cout << "Can't find any DLL!\n";
		Sleep(3000);
		return false;
	}
	FindClose(hFind);

	return true;
}

void Shop::OpenDLL()																								// отркываем найденые DLL
{
	m_pHmod = new HMODULE[m_nCountLibrary];
	for (unsigned int i = 0; i < m_pPathNameDLL.size(); i++)
	{
		m_pHmod[i] = LoadLibrary(m_pPathNameDLL[i].c_str());
		if (m_pHmod[i] == NULL)
		{
			std::cout << "DLL not loaded!\n";
			Sleep(2000);
			return;
		}
// 		else
// 		{
// 			con_color(11);
// 			std::cout << "DLL Loaded:  ";
// 			con_color(14);
// 			std::cout << m_pPathNameDLL[i].c_str() << std::endl;
// 			con_color(15);
// 		}
//		Sleep(2000);
	}

//	system("cls");
//--------------------------------------------------------------------------

	typedef const char * (*sNameFactory)();
	typedef BaseFactory * (*GetFactoryT)();

	m_pCategory = new Category[m_nCountLibrary];						// создаем количество категорий по количеству DLL											
	for (unsigned int i = 0; i < m_nCountLibrary; i++)
	{
		GetFactoryT pFn = (GetFactoryT)GetProcAddress(m_pHmod[i], "GetFactory");
		sNameFactory name = (sNameFactory)GetProcAddress(m_pHmod[i], "GetNameDLL");
		if (pFn == NULL)
		{
			std::cout << "GetFactory not found!\n";
			FreeLibrary(m_pHmod[i]);
			_getch();
			return;
		}
		m_pCategory[i].m_pBaseFactory = pFn();
		m_pPathNameDLL[i] = name();										// сохраняем название продукта в m_pPathNameDLL
	}
}

void Shop::Refresh()
{
	this->SaveBalance();
	for (unsigned int i = 0; i < m_nCountLibrary; i++)
		this->Save(i);

	if(this->Run())																	 //	ищем DLL, если находим - открывает, инчае выход
	{
		this->OpenDLL();
		for (unsigned int i = 0; i < m_nCountLibrary; i++)
			this->Load(i);
	}
	else
		exit(1);
}

void Shop::ShowProduct(unsigned int numCategory, unsigned int numProduct)
{
	if (numCategory < m_nCountLibrary && numProduct < m_pCategory[numCategory].m_pvProdCat.size())
		m_pCategory[numCategory].m_pBaseFactory->CreateBaseOutput()->ShowProduct(m_pCategory[numCategory].m_pvProdCat[numProduct]);		
	else
		std::cout << "This product is not exist!\n";
}

void Shop::ShowAllProduct( unsigned int numCategory )
{
	if (numCategory < m_nCountLibrary)
		m_pCategory[numCategory].m_pBaseFactory->CreateBaseOutput()->ShowAllProducts((m_pCategory[numCategory].m_pvProdCat));
	else
		std::cout << "This category is not exist!\n";
}

void Shop::ShowCategory()
{
	for (unsigned int i = 0; i < m_nCountLibrary; i++)
		std::cout << i+1 << ". - " << m_pPathNameDLL[i] << " products.\n";
}

int Shop::GetNumberCategory()
{
	return m_nCountLibrary;
}

int Shop::GetCountProducts(unsigned int numCategory)
{
	return m_pCategory[numCategory].m_pvProdCat.size();
}

void Shop::SetBalance( double balance )
{
	if (m_pBalance)
		m_pBalance->SetBalance(balance);
	else
		std::cout << "Balance is undefined\n";
}

void Shop::SetBalance()
{
	std::cout << "Enter password:\n";
	std::string sPass = SecurityInput::inputAnyString();
	if(sPass == PASSWORD)
	{
		std::cout << "Enter new balance!\n";
		double balance;
		std::cin >> balance;
		this->SetBalance(balance);
	}
	else
	{
		std::cout << "Incorrect password !\n";
		Sleep(500);
	}
}

double Shop::GetBalance()
{
	if (m_pBalance)
		return m_pBalance->GetBalance();

	std::cout << "Balance 0\n";
	return 0;
}

void Shop::DeleteProduct( unsigned int numCategory, unsigned int numProduct )
{

}

void Shop::CreateNewProduct(unsigned int numCategory)
{
	if (numCategory < m_nCountLibrary)
	{
		m_pCategory[numCategory].m_pBaseInput = m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput();
		Product *pNewProduct = m_pCategory[numCategory].m_pBaseInput->CreateProduct();
//		Product *pNewProduct = m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput()->CreateProduct();
		if (pNewProduct)
			m_pCategory[numCategory].m_pvProdCat.push_back(pNewProduct);
		else
			std::cout << "Array " << m_pPathNameDLL[numCategory] << " is fully!\n";
	}
	else
		std::cout << "Category " << numCategory << " is absent.\n";
}

void Shop::EditProduct(unsigned int numCategory, unsigned int numProduct)
{
	if (numCategory < m_nCountLibrary && numProduct < m_pCategory[numCategory].m_pvProdCat.size())
		m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput()->EditDataOfProduct(m_pCategory[numCategory].m_pvProdCat[numProduct]);
	else
		std::cout << "This product is not exist!\n";
}

void Shop::SellProduct( unsigned int numCategory, unsigned int numProduct, unsigned int quantityProd )
{
	if (numCategory < m_nCountLibrary && numProduct < m_pCategory[numCategory].m_pvProdCat.size() && m_pBalance)
	{
		double pBal = m_pBalance->GetBalance();
		m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput()->SellProd(m_pCategory[numCategory].m_pvProdCat[numProduct], quantityProd, pBal);
		m_pBalance->SetBalance(pBal);
	}
	else
		std::cout << "This product is not exist!\n";
}

void Shop::BuyNewProduct( unsigned int numCategory )
{
	if (numCategory < m_nCountLibrary)
	{
		Product *pNewProduct = m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput()->CreateProduct();
		if (pNewProduct)
		{
			m_pCategory[numCategory].m_pvProdCat.push_back(pNewProduct);
			std::cout << "Create new product " << m_pCategory[numCategory].m_pvProdCat.size() << ": " << m_pPathNameDLL[numCategory] << std::endl;

			if (numCategory < m_nCountLibrary && m_pBalance)
			{
				double pBal = m_pBalance->GetBalance();
				m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput()->BuyNewProd(pNewProduct, pBal);
				m_pBalance->SetBalance(pBal);
			}
		}
		else
			std::cout << "Array " << m_pPathNameDLL[numCategory] << " is fully!\n";
	}
	else
		std::cout << "This category is not exist!\n";
}

void Shop::BuyExistProduct( unsigned int numCategory, unsigned int numProduct, unsigned int quantityProd )
{
	if (numCategory < m_nCountLibrary && numProduct < m_pCategory[numCategory].m_pvProdCat.size() && m_pBalance)
	{
		double pBal = m_pBalance->GetBalance();
		m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput()->BuyExistProd(m_pCategory[numCategory].m_pvProdCat[numProduct], quantityProd, pBal);
		m_pBalance->SetBalance(pBal);
	}
	else
		std::cout << "This product is not exist!\n";
}

void Shop::Save( unsigned int numCategory )
{
	if (numCategory < m_nCountLibrary)
		m_pCategory[numCategory].m_pBaseFactory->CreateBaseSave()->Save((m_pCategory[numCategory].m_pvProdCat));
	else
		std::cout << "This category is not exist!\n";
}

void Shop::Load( unsigned int numCategory )
{
	if (numCategory < m_nCountLibrary)
		m_pCategory[numCategory].m_pBaseFactory->CreateBaseLoad()->Load((m_pCategory[numCategory].m_pvProdCat));
	else
		std::cout << "This category is not exist!\n";
}

void Shop::SaveBalance()
{
// 	con_color(11);
// 	std::cout << "Enter filename that you want save balance:\n";
// 	con_color(15);
// 	char nameFile[80];
// 	std::cin >> nameFile;
	std::ofstream fout(BALANCE, std::ios_base::out | std::ios_base::trunc);
	if (!fout.is_open())
		std::cout << "Error opening file!\n";
	else
	{
		fout << m_pBalance->GetBalance();
		fout.close();
// 		con_color(11);
// 		std::cout << "Your successfully saved balance!\n";
		con_color(15);
	}
}

void Shop::LoadBalance()
{
// 	con_color(11);
// 	std::cout << "\nEnter filename that you want load balance:\n";
// 	char nameFile[80];
// 	con_color(15);
// 	std::cin >> nameFile;
	std::ifstream fin(BALANCE, std::ios::in);
	if (!fin.is_open())
		std::cout << "Error opening file!\n";
	else
	{
		double balance;
		while (!fin.eof())
		{
			fin >> balance;
			m_pBalance->SetBalance(balance);
		}
		fin.close();
//		con_color(11);
//		std::cout << "Your successfully load $ " << balance << "\n";
		con_color(15);
	}

}

void Shop::Menu()
{
	m_pBaseTxt->Info();
}

void Shop::Sell()
{
	system("cls");
	std::cout << "0. - Back.\n";
	this->ShowCategory();
	int nCountCat = this->GetNumberCategory();
	int chooseCategory = SecurityInput::inputAnyInteger(nCountCat);
	system("cls");
	this->ShowBalance();
	std::cout << std::endl;
	if (chooseCategory)
	{
		this->ShowAllProduct(chooseCategory-1);
		std::cout << "Select the number of products you want to sell:  ";
		int quantityProducts = this->GetCountProducts(chooseCategory - 1);
		int numbProd = SecurityInput::inputAnyInteger(quantityProducts);
		if (numbProd)
		{
			std::cout << "Select quantity of products:  ";
			int countProd = SecurityInput::inputAnyInteger(5000);
			this->SellProduct(chooseCategory-1, numbProd-1, countProd);
		}
	}
}

void Shop::Buy()
{
	system("cls");
	std::cout << "0. - Back.\n";
	this->ShowCategory();
	int nCountCat = this->GetNumberCategory();
	int chooseCategory = SecurityInput::inputAnyInteger(nCountCat);
	system("cls");
	this->ShowBalance();
	std::cout << std::endl;
	if (chooseCategory)
	{
		this->ShowAllProduct(chooseCategory-1);

		std::cout << "Choose menu:\n";
		std::cout << "1 - Buy a new product\n";
		std::cout << "2 - Buy an exist product from table\n";
		std::cout << "0 - Back\n";
		switch(SecurityInput::inputAnyInteger(2))
		{
		case 1:
			{
				system("cls");
				this->ShowBalance();
				std::cout << std::endl;
				this->ShowAllProduct(chooseCategory-1);
				this->BuyNewProduct(chooseCategory-1);
				break;
			}
		case 2:
			{
				system("cls");
				this->ShowBalance();
				std::cout << std::endl;
				this->ShowAllProduct(chooseCategory-1);
				std::cout << "Select the number of products you want to buy:  ";
				int quantityProducts = this->GetCountProducts(chooseCategory - 1);
				int numbProd = SecurityInput::inputAnyInteger(quantityProducts);
				if (numbProd)
				{
					std::cout << "Select quantity of product:  ";
					int countProd = SecurityInput::inputAnyInteger(5000);
					this->BuyExistProduct(chooseCategory-1, numbProd-1, countProd);
				}
				break;
			}
		case 0: break;
		default: break;
		}
	}
}

void Shop::New()
{
	system("cls");
	this->ShowBalance();
	std::cout << std::endl;
	std::cout << "0. - Back.\n";
	this->ShowCategory();
	int nCountCat = this->GetNumberCategory();
	int chooseCategory = SecurityInput::inputAnyInteger(nCountCat);
	if (chooseCategory)
		this->CreateNewProduct(chooseCategory-1);
}

void Shop::Edit()
{
	system("cls");
	std::cout << "0. - Back.\n";
	this->ShowCategory();
	int nCountCat = this->GetNumberCategory();
	int chooseCategory = SecurityInput::inputAnyInteger(nCountCat);
	system("cls");
	if (chooseCategory)
	{
		this->ShowAllProduct(chooseCategory-1);
		std::cout << "Choose number product, what you want to change:  ";
		int quantityProducts = this->GetCountProducts(chooseCategory - 1);
		int numbProd = SecurityInput::inputAnyInteger(quantityProducts);
		this->EditProduct(chooseCategory-1, numbProd-1);
	}
}

void Shop::ShowProducts()
{
	system("cls");
	std::cout << "0. - Back.\n";
	this->ShowCategory();
	int nCountCat = this->GetNumberCategory();
	int choose = SecurityInput::inputAnyInteger(nCountCat);
	system("cls");
	this->ShowBalance();
	std::cout << std::endl;
	if (choose)
	{
		this->ShowAllProduct(choose-1);
		std::cout << std::endl;
		system("pause");
	}
}

void Shop::Save()
{
	system("cls");
	this->ShowBalance();
	std::cout << std::endl;
	this->ShowCategory();
	int nCountCat = this->GetNumberCategory();
	int chooseCategory = SecurityInput::inputAnyInteger(nCountCat);
	if (chooseCategory)
		this->Save(chooseCategory-1);
}

void Shop::Load()
{
	system("cls");
	this->ShowBalance();
	std::cout << std::endl;
	this->ShowCategory();
	int nCountCat = this->GetNumberCategory();
	int chooseCategory = SecurityInput::inputAnyInteger(nCountCat);
	if (chooseCategory)
		this->Load(chooseCategory-1);
}

void Shop::ExitAndSave()
{
	delete this;
	std::cout << "Exit from shop! Bye!\n";
// 	if (_CrtDumpMemoryLeaks())
// 		std::cout << "Memory Leak!\n";

	Sleep(700);
	exit(1);
}