#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <vector>
#include <iterator>

class Product
{
private:
protected:
	std::string m_name_product;
	unsigned int m_quantity_product;
	double m_price_product;

public:
	Product();
	virtual ~Product();
	virtual void SetName(std::string name);
	virtual void SetCountity(unsigned int countity);
	virtual void SetPrice(double price);

	virtual const std::string &GetName();
	virtual unsigned int GetQuantity();
	virtual double GetPrice();

};

#endif