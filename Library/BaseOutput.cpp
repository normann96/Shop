#include "stdafx.h"
#include "BaseOutput.h"

BaseOutput::BaseOutput()
{
#ifdef test_cout_baseOutput
	std::cout << "I'm Constructor by BaseOutput\t  " << this << std::endl;
#endif
}

BaseOutput::~BaseOutput()
{
#ifdef test_cout_baseOutput
	std::cout << "I'm Destructor  by BaseOutput\t  " << this << std::endl;
#endif
}