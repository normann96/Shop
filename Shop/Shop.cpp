#include "stdafx.h"
#include "Shop.h"
#include <wchar.h>

#define PASSWORD "admin"

Shop::Shop() : m_nCountLibrary(0), m_pHmod(nullptr), m_pPathNameDLL(NULL), m_pCategory(nullptr), m_pBaseTxt(nullptr), m_pBalance(nullptr)
{
	if(this->Run())														 //	���� DLL, ���� ������� - ���������, ����� �����
		this->OpenDLL();
	else
		exit(1);

	try
	{
		m_pBaseTxt = new ConsoleText;
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		throw;
	}
	try
	{
		m_pBalance = new Balance;
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}

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

	if(m_pBaseTxt)
		delete m_pBaseTxt;

	if(m_pBalance)
		delete m_pBalance;

	if(m_pCategory)
		delete [] m_pCategory;

	if (m_pHmod)
	{
		for (unsigned int i = 0; i < m_nCountLibrary; i++)
			FreeLibrary(m_pHmod[i]);
		delete m_pHmod;
	}

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

bool Shop::Run()																					// ������� DLL � ��������� ���� � ������ m_pVectPath, ���������� DLL - m_nCountLibrary
{
	m_nCountLibrary = 0;
	WIN32_FIND_DATA f_data;
	ZeroMemory(&f_data, sizeof(WIN32_FIND_DATA));
	HANDLE hFind = NULL;
	m_pPathNameDLL.clear();

#ifdef _DEBUG
	hFind = FindFirstFile("../Debug/*.dll", &f_data);												// ���� dll � ����� Debug �� ����� *.dll
#else 
	hFind = FindFirstFile("../Release/*.dll", &f_data);												// ���� dll � ����� Realese �� ����� *.dll
#endif
	
	if (hFind == INVALID_HANDLE_VALUE)																// ���� dll � ������� ����� � exe
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

void Shop::OpenDLL()																								// ��������� �������� DLL
{
	try
	{
		m_pHmod = new HMODULE[m_nCountLibrary];
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}

	for (unsigned int i = 0; i < m_pPathNameDLL.size(); i++)
	{
		try
		{
			m_pHmod[i] = LoadLibrary(m_pPathNameDLL[i].c_str());
			if (!m_pHmod[i]) throw 1;
		}
		catch(int a)
		{
			std::cout << "DLL not loaded!\n";
			Sleep(2000);
			return;
		}
		//	else
		//	{
		//		con_color(11);
		//		std::cout << "DLL Loaded:  ";
		//		con_color(14);
		//		std::cout << m_pPathNameDLL[i].c_str() << std::endl;
		//		con_color(15);
		//		Sleep(2000);
		//		system("cls");
		//	}
	}
	//--------------------------------------------------------------------------

	typedef const char * (*sNameFactory)();
	typedef BaseFactory * (*GetFactoryT)();

	try
	{
		m_pCategory = new Category[m_nCountLibrary];																// ������� ���������� ��������� �� ���������� DLL	
	}
	catch (std::bad_alloc& ba)
	{
		std::cout << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}	

	for (unsigned int i = 0; i < m_nCountLibrary; i++)
	{
		try
		{
			GetFactoryT pFn = (GetFactoryT)GetProcAddress(m_pHmod[i], "GetFactory");
			sNameFactory name = (sNameFactory)GetProcAddress(m_pHmod[i], "GetNameDLL");
			if (!pFn ) throw 1;
			if (!name ) throw 2;

			m_pCategory[i].m_pBaseFactory = pFn();
			m_pPathNameDLL[i] = name();																				// ��������� �������� �������� � m_pPathNameDLL
		}
		catch(int nError)
		{
			switch(nError)
			{
			case 1:
				{
					std::cout << "GetFactory not found!\n";
					FreeLibrary(m_pHmod[i]);
					return;
					break;
				}
			case 2:
				{
					std::cout << "GetNameDLL not found!\n";
					FreeLibrary(m_pHmod[i]);
					return;
					break;
				}
			}
		}
	}
}

void Shop::Refresh()
{
	this->SaveBalance();
	for (unsigned int i = 0; i < m_nCountLibrary; i++)
		this->Save(i);

	if(this->Run())																	 //	���� DLL, ���� ������� - ���������, ����� �����
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
		this->SetBalance(SecurityInput::InputAnyDouble());
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
	try
	{
		if (numCategory < m_nCountLibrary)
		{
			//		m_pCategory[numCategory].m_pBaseInput = m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput();
			//		Product *pNewProduct = m_pCategory[numCategory].m_pBaseInput->CreateProduct();
			Product *pNewProduct = m_pCategory[numCategory].m_pBaseFactory->CreateBaseInput()->CreateProduct();
			if (pNewProduct)
				m_pCategory[numCategory].m_pvProdCat.push_back(pNewProduct);
			else
				std::cout << "Array " << m_pPathNameDLL[numCategory] << " is fully!\n";
		}
		else
			std::cout << "Category " << numCategory << " is absent.\n";
	}
	catch(std::bad_alloc& ba)
	{
		std::cout << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}
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
	try
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
	catch(std::bad_alloc& ba)
	{
	 	std::cout << "bad_alloc caught: " << ba.what() << '\n';
	 	throw ba;
	}
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
	{
		try
		{
			m_pCategory[numCategory].m_pBaseLoad = m_pCategory[numCategory].m_pBaseFactory->CreateBaseLoad();
			if (!m_pCategory[numCategory].m_pBaseLoad) throw 1;
			m_pCategory[numCategory].m_pBaseLoad->Load((m_pCategory[numCategory].m_pvProdCat));
	//		m_pCategory[numCategory].m_pBaseFactory->CreateBaseLoad()->Load((m_pCategory[numCategory].m_pvProdCat));
		}
		catch (int a)
		{
			std::cout << "Base not created!\n";
		}

	}
	else
		std::cout << "This category is not exist!\n";
}

void Shop::SaveBalance()
{
	try
	{
		std::ofstream fout(BALANCE, std::ios_base::out | std::ios_base::trunc);
		fout.exceptions(std::ofstream::failbit);
		if (fout.is_open())
		{
			fout << m_pBalance->GetBalance();
			con_color(15);
		}
		fout.close();
	}
	catch(std::ios_base::failure &fail)
	{
		std::cout << "Exception opening/writing file: " << fail.what() << std::endl;
	}
}

void Shop::LoadBalance()
{
	try
	{
		std::ifstream fin(BALANCE, std::ios::in);
		fin.exceptions(std::ifstream::failbit);
		if (fin.is_open())
		{
			double balance;
			while (!fin.eof())
			{
				fin >> balance;
				m_pBalance->SetBalance(balance);
			}
			con_color(15);
		}
		fin.close();
	}
	catch(std::ios_base::failure &fail)
	{
		std::cout << "Exception opening/reading file: " << fail.what() << std::endl;
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
	std::cin.sync();
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
			int countProd = SecurityInput::inputAnyInteger(50000);
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
	std::cin.sync();
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
					int countProd = SecurityInput::inputAnyInteger(50000);
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
	std::cin.sync();
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
	if (_CrtDumpMemoryLeaks())
		std::cout << "Memory Leak!\n";
	else
		std::cout << "Memory ok\n";

	Sleep(700);
	exit(1);
}