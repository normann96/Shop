#include "stdafx.h"
#include "BaseInput.h"

BaseInput::BaseInput()
{
#ifdef test_cout_baseInput
	std::cout << "I'm Constructor by BaseInput\t  " << this << std::endl;
#endif
}

BaseInput::~BaseInput()
{
#ifdef test_cout_baseInput
	std::cout << "I'm Destructor  by BaseInput\t  " << this << std::endl;
#endif
}