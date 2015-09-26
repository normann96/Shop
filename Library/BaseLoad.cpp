#include "stdafx.h"
#include "BaseLoad.h"

BaseLoad::BaseLoad()
{
#ifdef test_cout_baseLoad
	std::cout << "I'm Constructor by BaseLoad\t  " << this << std::endl;
#endif
}

BaseLoad::~BaseLoad()
{
#ifdef test_cout_baseLoad
	std::cout << "I'm Destructor  by BaseLoad\t  " << this << std::endl;
#endif
}