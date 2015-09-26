#include "stdafx.h"
#include "BaseSave.h"

BaseSave::BaseSave()
{
#ifdef test_cout_baseSave
	std::cout << "I'm Constructor by BaseSave\t  " << this << std::endl;
#endif
}

BaseSave::~BaseSave()
{
#ifdef test_cout_baseSave
	std::cout << "I'm Destructor  by BaseSave\t  " << this << std::endl;
#endif
}