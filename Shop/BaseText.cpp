#include "stdafx.h"
#include "BaseText.h"

BaseText::BaseText()
{
#ifdef test_cout_base_text
	std::cout << "I'm Constructor by BaseText\t  " << this << std::endl;
#endif
}

BaseText::~BaseText()
{
#ifdef test_cout_base_text
	std::cout << "I'm Destructor  by BaseText\t  " << this << std::endl;
#endif
}

int BaseText::ChooseMenu()
{
	return  0;
}

void BaseText::Info()
{

}

