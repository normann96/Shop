// ToolsDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ToolsDLL.h"
#include "ToolsFactory.h"


extern "C" TOOLSDLL_API BaseFactory * GetFactory()
{
	return new ToolsFactory;
}

 extern "C" TOOLSDLL_API const char * GetNameDLL()
 {
 	return "Tools";
 }

Tools::Tools() : Product(), m_type("handheld"), m_weight(0.0)
{
	m_name_product = "Shovel";
#ifdef test_cout_tools
	std::cout << "I'm Constructor by Tools\t  " << this << std::endl;
#endif
}

Tools::~Tools()
{
#ifdef test_cout_tools
	std::cout << "I'm Destructor  by Tools\t  " << this << std::endl;
#endif
}
