#include "stdafx.h"
#include "BaseFactory.h"

BaseFactory::BaseFactory()
{
#ifdef test_cout_baseFactory
	std::cout << "I'm Constructor by BaseFactory\t  " << this << std::endl;
#endif
}

BaseFactory::~BaseFactory()
{
#ifdef test_cout_baseFactory
	std::cout << "I'm Destructor  by BaseFactory\t  " << this << std::endl;
#endif
}