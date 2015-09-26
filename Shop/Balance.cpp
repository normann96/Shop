#include "stdafx.h"
#include "Balance.h"

Balance::Balance() : m_nMoney(50000.00)
{
#ifdef test_cout_balance
	std::cout << "I'm Constructor by Balance\t  " << this << std::endl;
#endif
}

Balance::~Balance()
{
#ifdef test_cout_balance
	std::cout << "I'm Destructor  by Balance\t  " << this << std::endl;
#endif
}

void Balance::ShowBalance()
{
	std::cout << "Balance = $" << m_nMoney << std::endl;
}

void Balance::SetBalance( double balance )
{
	m_nMoney = balance;
}

double Balance::GetBalance()
{
	return m_nMoney;
}
