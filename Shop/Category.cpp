#include "stdafx.h"
#include "Category.h"
#include "../Library/BaseFactory.h"


Category::Category() : m_pBaseFactory(nullptr), m_pBaseOut(nullptr), 
	m_pBaseInput(nullptr), m_pBaseSave(nullptr), m_pBaseLoad(nullptr)
{
	
#ifdef test_cout_category
	con_color(15);
	std::cout << "I'm Constructor by Category\t  " << this << std::endl;
#endif
}

Category::~Category()
{
	if (m_pBaseFactory != NULL)
		delete [] m_pBaseFactory;

// 	if (m_pBaseInput != NULL)
// 		delete m_pBaseInput;

 	if (m_pBaseOut != NULL)
 		delete [] m_pBaseOut;
	
	if (m_pBaseSave != NULL)
		delete [] m_pBaseSave;

	if (m_pBaseLoad != NULL)
		delete [] m_pBaseLoad;

#ifdef test_cout_category
	std::cout << "I'm Destructor  by Category\t  " << this << std::endl;
#endif
}
