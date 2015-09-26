#include "stdafx.h"
#include "ToolsInput.h"

ToolsInput::ToolsInput() : BaseInput(), m_ppToolsArray(nullptr), m_numberTools(0)
{
	
#ifdef test_cout_toolsinput
	std::cout << "I'm Constructor by ToolsInput\t  " << this << std::endl;
#endif
}

ToolsInput::~ToolsInput()
{
	if (m_ppToolsArray != NULL)
	{
		for (int i = 0; i < m_numberTools; i++)
			delete m_ppToolsArray[i];
		delete [] m_ppToolsArray;
	}

#ifdef test_cout_toolsinput
	std::cout << "I'm Destructor  by ToolsInput\t  " << this << std::endl;
#endif
}

Product * ToolsInput::CreateProduct()
{
	if(!m_ppToolsArray)
		m_ppToolsArray = new Tools *[NUMBER_TOOLS];

	if (m_numberTools < NUMBER_TOOLS )
	{
		m_ppToolsArray[m_numberTools++] = new Tools;
		return m_ppToolsArray[m_numberTools-1];
	}

	return nullptr;
}

void ToolsInput::EditDataOfProduct(Product * product)
{
	Tools * pTools = (Tools*)product;
	std::cout << "Enter name of Tools: ";
	pTools->m_name_product = SecurityInput::inputAnyString();
	std::cout << "Enter countity of Tools: ";
	pTools->m_quantity_product = SecurityInput::inputAnyInteger();
	std::cout << "Enter price of Tools: ";
	pTools->m_price_product = SecurityInput::inputFloat();
	std::cout << "Enter weight of Tools: ";
	pTools->m_weight = SecurityInput::inputFloat();
	std::cout << "Enter type of Tools: ";
	pTools->m_type = SecurityInput::inputAnyString();
}

void ToolsInput::BuyExistProd( Product * product, unsigned int quanity, double & pBalance )
{
	Tools * pTools = (Tools*)product;
	if (pBalance >= quanity * pTools->m_price_product)
	{
		pTools->m_quantity_product += quanity;
		pBalance -= (pTools->m_price_product * quanity);

	}
	else if (pBalance/pTools->m_price_product > 0)
	{
		int num = pBalance/pTools->m_price_product;
		std::cout << "Do you buy " << num << " " 
			<< pTools->m_name_product << "?\n1. - Yes\n2. = No\n";
		switch(SecurityInput::inputAnyInteger(2))
		{
		case 1:
			{
				pTools->m_quantity_product += num;
				pBalance -= (pTools->m_price_product * num);
			}
		case 2: break;
		default: break;
		}
	}
	else
	{
		std::cout << "You don't have enough money!\n";
		Sleep(1200);
	}
}

void ToolsInput::SellProd( Product * product, unsigned int quanity, double & pBalance )
{
	Tools * pTools = (Tools*)product;
	if (quanity <= pTools->m_quantity_product)
	{
		pTools->m_quantity_product -= quanity;
		pBalance += (pTools->m_price_product * quanity);
	}
	else if (pTools->m_quantity_product > 0 )
	{
		std::cout << "Do you sell " << pTools->m_quantity_product << " " 
			<< pTools->m_name_product << "?\n1. - Yes\n2. = No\n";
		switch(SecurityInput::inputAnyInteger(2))
		{
		case 1:
			{
				quanity = pTools->m_quantity_product;
				pTools->m_quantity_product = 0;
				if (pBalance >= (pTools->m_price_product * quanity))
					pBalance += (pTools->m_price_product * quanity);
				else
				{
					std::cout << "You don't have enough money!\n";
					Sleep(2000);
				}
				break;
			}
		case 2:	break;
		default: break;
		}
	}
	else
	{
		std::cout << "We don't have " << quanity << " " 
			<< pTools->m_type << " " << pTools->m_name_product << std::endl;
		Sleep(1200);
	}
}

void ToolsInput::BuyNewProd( Product * product, double & pBalance )
{
	Tools * pTools = (Tools*)product;
	std::cout << "Enter name: ";
	pTools->m_name_product = SecurityInput::inputAnyString();
	std::cout << "Enter quantity: ";
	pTools->m_quantity_product = SecurityInput::inputAnyInteger();
	std::cout << "Enter price: ";
	
	double temp;
	std::cin >> temp;
	pTools->m_price_product = temp;/*SecurityInput::inputFloat();*/

	if (pBalance >= pTools->m_quantity_product * pTools->m_price_product)
	{
		pBalance -= (pTools->m_price_product * pTools->m_quantity_product);
	}
	else if (pBalance/pTools->m_price_product > 0)
	{
		int num = pBalance/pTools->m_price_product;
		std::cout << "Do you buy " << num << " " 
			<< pTools->m_name_product << "?\n1. - Yes\n2. = No\n";
		switch(SecurityInput::inputAnyInteger(2))
		{
		case 1:
			{
				pTools->m_quantity_product = 0;
				pTools->m_quantity_product += num;
				pBalance -= (pTools->m_price_product * num);
			}
		case 2: break;
		default: break;
		}
	}
	else
	{
		std::cout << "You don't have enough money!\n";
		Sleep(1200);
	}

	pTools->m_price_product *= PROFITS;

	std::cout << "Enter type: ";
	pTools->m_type = SecurityInput::inputAnyString();
	std::cout << "Enter weight: ";
	pTools->m_weight = SecurityInput::inputAnyInteger();
}
