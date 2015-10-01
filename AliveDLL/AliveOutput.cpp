#include "stdafx.h"
#include "AliveOutput.h"


AliveOutput::AliveOutput()
{

#ifdef test_cout_aliveoutput
	std::cout << "I'm Constructor by AliveOutput\t  " << this << std::endl;
#endif
}

AliveOutput::~AliveOutput()
{
#ifdef test_cout_aliveoutput
	std::cout << "I'm Destructor  by AliveOutput\t  " << this << std::endl;
#endif

}

void AliveOutput::ShowProduct( Product * product )
{
	std::cout << (char)186 << std::right << std::setw(8) << "Name: " << std::setw(14) << "Quantity: "\
		<< std::setw(12) << "Price: " << std::setw(11) << "Color: " << \
		std::setw(18) << "Lifetime day: " << std::setw(4) << (char)186 << std::endl;

	if (product)
	{
		Alive *pAlive = (Alive*)product;

		std::cout << (char)186 << std::right << std::setw(8) << pAlive->m_name_product;
		std::cout << std::setw(14) << pAlive->m_quantity_product;
		std::cout << std::setw(12) << pAlive->m_price_product;
		std::cout << std::setw(11) << pAlive->m_color;
		std::cout << std::setw(18) << pAlive->m_lifetime_day << std::setw(4) << (char)186;
		std::cout << std::endl;
	}
	else
		std::cout << "Alive not exist!\n";
}

void AliveOutput::ShowAllProducts( std::vector<Product*> &productsArray )
{
	con_color(10);
	std::cout << "\t\t\t\t" <<   " Alive table " << "\n";
	con_color(15);
	std::cout << (char)201;
	for (int i = 0; i < 76; ++i) 
	{
		if(i == 5 || i == 20 || i == 31 || i == 44 || i == 60)
			std::cout << (char)203;
		else
			std::cout << (char)205;
	}
	std::cout << (char)187 << std::endl;

	std::cout << (char)186;
	std::cout << " " << std::setw(4) << std::left << "Num." << (char)186;
	std::cout << "  " << std::setw(12) << std::left << "Name" << (char)186;
	std::cout << " " << std::setw(9) << "Quantity" << (char)186;
	std::cout << "  " << std::setw(10) << "Price" << (char)186;
	std::cout << "   " << std::setw(12) << "Color" << (char)186;
	std::cout << " " << std::setw(14) << "Lifetime day" << (char)186;
	std::cout << std::endl;
	
	std::cout << (char)204;
	for (int i = 0; i < 76; ++i) 
	{
		if(i == 5 || i == 20 || i == 31 || i == 44 || i == 60)
			std::cout << (char)206;
		else
			std::cout << (char)205;
	}
	std::cout << (char)185 << std::endl;

	for (unsigned int i = 0; i < productsArray.size(); i++)
	{
		std::cout << (char)186; 
		std::cout << " " << std::setw(4) << std::left << i+1 << (char)186;
		std::cout << "  " << std::setw(12) << std::left << dynamic_cast<Alive*>(productsArray[i])->m_name_product << (char)186;
		std::cout << "   " << std::setw(7) << std::left << dynamic_cast<Alive*>(productsArray[i])->m_quantity_product << (char)186;
		std::cout << "   " << std::setw(9) << std::left << dynamic_cast<Alive*>(productsArray[i])->m_price_product << (char)186;
		std::cout << "   " << std::setw(12) << std::left << dynamic_cast<Alive*>(productsArray[i])->m_color << (char)186;
		std::cout << "   " << std::setw(12) << std::left << dynamic_cast<Alive*>(productsArray[i])->m_lifetime_day;
		std::cout << (char)186;
		std::cout << std::endl;
	}


	std::cout << (char)200;
	for (int i = 0; i < 76; ++i) 
	{
		if( i == 5 || i == 20 || i == 31 || i == 44 || i == 60)
			std::cout << (char)202;
		else
			std::cout << (char)205;
	}
	std::cout << (char)188 << std::endl;
}
