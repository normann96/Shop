#include "stdafx.h"
#include "ToolsOutput.h"

ToolsOutput::ToolsOutput()
{
#ifdef test_cout_toolsoutput
	std::cout << "I'm Constructor by ToolsOutput\t  " << this << std::endl;
#endif
}

ToolsOutput::~ToolsOutput()
{
#ifdef test_cout_toolsoutput
	std::cout << "I'm Destructor  by ToolsOutput\t  " << this << std::endl;
#endif
}

void ToolsOutput::ShowProduct( Product * product )
{
	Tools *pTools = (Tools*)product;

	std::cout << "Name: " << pTools->m_name_product << " " << this << std::endl;
	std::cout << "Quantity: " << pTools->m_quantity_product << std::endl;
	std::cout << "Price: " << pTools->m_price_product << std::endl;
	std::cout << "Weight: " << pTools->m_weight << std::endl;
	std::cout << "Type: " << pTools->m_type << std::endl;
}

void ToolsOutput::ShowAllProducts( std::vector<Product*> &productsArray )
{
	con_color(11);
	std::cout << "\t\t\t\t" <<   " Tools table " << "\n";
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
	std::cout << "   " << std::setw(12) << "Type" << (char)186;
	std::cout << " " << std::setw(14) << "Weight" << (char)186;
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
		std::cout << "  " << std::setw(12) << std::left << dynamic_cast<Tools*>(productsArray[i])->m_name_product << (char)186;
		std::cout << "   " << std::setw(7) << std::left << dynamic_cast<Tools*>(productsArray[i])->m_quantity_product << (char)186;
		std::cout << "   " << std::setw(9) << std::left << dynamic_cast<Tools*>(productsArray[i])->m_price_product << (char)186;
		std::cout << "  "	 << std::setw(13) << std::left << dynamic_cast<Tools*>(productsArray[i])->m_type << (char)186;
		std::cout << "   " << std::setw(12) << std::left << dynamic_cast<Tools*>(productsArray[i])->m_weight;
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