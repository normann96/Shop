#include "stdafx.h"
#include "AliveInput.h"

AliveInput::AliveInput() : BaseInput(), m_ppAliveArray(nullptr), m_numberAlive(0)
{
	
#ifdef test_cout_aliveinput
	std::cout << "I'm Constructor by AliveInput\t  " << this << std::endl;
#endif
}

AliveInput::~AliveInput()
{
	if (m_ppAliveArray != NULL)
	{
		for (int i = 0; i < m_numberAlive; i++)
			delete m_ppAliveArray[i];
		delete [] m_ppAliveArray;
	}

#ifdef test_cout_aliveinput
	std::cout << "I'm Destructor  by AliveInput\t  " << this << std::endl;
#endif
}

Product * AliveInput::CreateProduct()
{
	if (!m_ppAliveArray)
		m_ppAliveArray = new Alive*[NUMBER_ALIVE];
	
	if (m_numberAlive < NUMBER_ALIVE )
	{
		m_ppAliveArray[m_numberAlive++] = new Alive;
		return m_ppAliveArray[m_numberAlive-1];
	}

	return nullptr;
}

void AliveInput::EditDataOfProduct(Product * product)
{
	Alive * pAlive = (Alive*)product;
	std::cout << "Enter name of Alive: ";
	pAlive->m_name_product = SecurityInput::inputAnyString();
	std::cout << "Enter countity of Alive: ";
	pAlive->m_quantity_product = SecurityInput::inputAnyInteger();
	std::cout << "Enter price of Alive: ";
	pAlive->m_price_product = SecurityInput::inputFloat();
	std::cout << "Enter color of Alive: ";
	pAlive->m_color = SecurityInput::inputAnyString();
	std::cout << "Enter lifetime day of Alive: ";
	pAlive->m_lifetime_day = SecurityInput::inputAnyInteger();
}

void AliveInput::BuyExistProd( Product * product, unsigned int quanity, double & pBalance )
{
	Alive * pAlive = (Alive*)product;
	if (pBalance >= (quanity * pAlive->m_price_product))
	{
		pAlive->m_quantity_product += quanity;
		pBalance -= (pAlive->m_price_product * quanity);

	}
	else if (pBalance/pAlive->m_price_product > 0)
	{
		int num = pBalance/pAlive->m_price_product;
		std::cout << "Do you buy " << num << " " 
			<< pAlive->m_name_product << "?\n1. - Yes\n2. = No\n";
//		int choise = 0;
//		std::cin >> choise;
//		choise = SecurityInput::inputAnyInteger(2);
		switch(SecurityInput::inputAnyInteger(2))
		{
			case 1:
				{
					pAlive->m_quantity_product += num;
					pBalance -= (pAlive->m_price_product * num);
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

void AliveInput::SellProd( Product * product, unsigned int quanity, double & pBalance )
{
	Alive * pAlive = (Alive*)product;
	if (quanity <= pAlive->m_quantity_product)
	{
		pAlive->m_quantity_product -= quanity;
		pBalance += (pAlive->m_price_product * quanity);
	}
	else if (pAlive->m_quantity_product > 0 )
	{
		std::cout << "Do you sell " << pAlive->m_quantity_product << " " 
			<< pAlive->m_name_product << "?\n1. - Yes\n2. = No\n";
		switch(SecurityInput::inputAnyInteger(2))
		{
		case 1:
			{
				quanity = pAlive->m_quantity_product;
				pAlive->m_quantity_product = 0;
				if (pBalance >= (pAlive->m_price_product * quanity))
					pBalance += (pAlive->m_price_product * quanity);
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
			<< pAlive->m_color << " " << pAlive->m_name_product << std::endl;
		Sleep(1200);
	}
}

void AliveInput::BuyNewProd( Product * product, double & pBalance )
{
	Alive * pAlive = (Alive*)product;
	std::cout << "Enter name: ";
	pAlive->m_name_product = SecurityInput::inputAnyString();
	std::cout << "Enter quantity: ";
	pAlive->m_quantity_product = SecurityInput::inputAnyInteger();
	std::cout << "Enter price: ";
	double temp;
	std::cin >> temp;
	pAlive->m_price_product = temp;/*SecurityInput::inputFloat();*/

	if (pBalance >= pAlive->m_quantity_product * pAlive->m_price_product)
		pBalance -= (pAlive->m_price_product * pAlive->m_quantity_product);
	else if (pBalance/pAlive->m_price_product > 0)
	{
		int num = pBalance/pAlive->m_price_product;
		std::cout << "Do you buy " << num << " " 
			<< pAlive->m_name_product << "?\n1. - Yes\n2. = No\n";
		switch(SecurityInput::inputAnyInteger(2))
		{
		case 1:
			{
				pAlive->m_quantity_product = 0;
				pAlive->m_quantity_product += num;
				pBalance -= (pAlive->m_price_product * num);
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

	pAlive->m_price_product *= PROFITS;

	std::cout << "Enter color: ";
	pAlive->m_color = SecurityInput::inputAnyString();
	std::cout << "Enter lifetime day: ";
	pAlive->m_lifetime_day = SecurityInput::inputAnyInteger();
}
