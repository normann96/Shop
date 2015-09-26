// AliveDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "AliveDLL.h"
#include "AliveFactory.h"

extern "C" ALIVEDLL_API BaseFactory * GetFactory()
{
	return new AliveFactory;
}

 extern "C" ALIVEDLL_API const char * GetNameDLL()
 {
 	return "Alive";
 }

Alive::Alive() : Product(), m_color("..."), m_lifetime_day(0)
{
	m_name_product = "";
#ifdef test_cout_alive
	std::cout << "I'm Constructor by Alive!\t  " << this << std::endl;
#endif
}

Alive::~Alive()
{
#ifdef test_cout_alive
	std::cout << "I'm Destructor  by Alive\t  " << this << std::endl;
#endif
}

const std::string & Alive::GetColor()
{
	return m_color;
}

unsigned int Alive::GetLifetimeDay()
{
	return m_lifetime_day;
}
