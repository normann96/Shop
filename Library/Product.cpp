#include "stdafx.h"
#include "Product.h"

Product::Product() : m_name_product("..."), m_quantity_product(0), m_price_product(0)
{
#ifdef test_cout_product
	std::cout << "I'm Constructor by Product\t  " << this << std::endl;
#endif
}

Product::~Product()
{
#ifdef test_cout_product
	std::cout << "I'm Destructor  by Product\t  " << this << std::endl;
#endif
}

void Product::SetName( std::string name )
{
	m_name_product = name;
}

void Product::SetCountity( unsigned int countity )
{
	m_quantity_product = countity;
}

void Product::SetPrice( double price )
{
	m_price_product = price;
}

const std::string & Product::GetName()
{
	return m_name_product;
}

unsigned int Product::GetQuantity()
{
	return m_quantity_product;
}

double Product::GetPrice()
{
	return m_price_product;
}
