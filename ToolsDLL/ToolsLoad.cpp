#include "stdafx.h"
#include "ToolsLoad.h"

ToolsLoad::ToolsLoad() : m_pTI(nullptr)
{
	m_pTI = new ToolsInput;

	if (!(m_pTI->m_ppToolsArray))
		m_pTI->m_ppToolsArray = new Tools*[NUMBER_TOOLS];

#ifdef test_cout_toolsLoad
	std::cout << "I'm Constructor by ToolsLoad\t  " << this << std::endl;
#endif
}

ToolsLoad::~ToolsLoad()
{
	if (m_pTI)
		delete m_pTI;

#ifdef test_cout_toolsLoad
	std::cout << "I'm Destructor by ToolsLoad\t  " << this << std::endl;
#endif
}

void ToolsLoad::Load( std::vector<Product*> & produts )
{
// 	con_color(11);
// 	std::cout << "Enter filename that you want load \"Tools\":\n";
// 	char nameFile[80];
// 	con_color(15);
// 	std::cin >> nameFile;
	std::ifstream fin(TOOLSDATABASE, std::ios::in);

	if (!fin.is_open())
		std::cout << "Error opening file!\n";
	else
	{
		produts.clear();
		int i = 0;
		while (!fin.eof())
		{
			if (m_pTI->m_numberTools < NUMBER_TOOLS )
			{
				m_pTI->m_ppToolsArray[m_pTI->m_numberTools++] = new Tools;
				produts.push_back(m_pTI->m_ppToolsArray[m_pTI->m_numberTools-1]);
			

				fin >> dynamic_cast<Tools*>(produts[i])->m_name_product;
				fin >> dynamic_cast<Tools*>(produts[i])->m_quantity_product;
				fin >> dynamic_cast<Tools*>(produts[i])->m_price_product;
				fin >> dynamic_cast<Tools*>(produts[i])->m_type;
				fin >> dynamic_cast<Tools*>(produts[i])->m_weight;
				i++;
			}
			else
				break;
		}
			fin.close();
// 		con_color(11);
// 		std::cout << "Your successfully load " << produts.size() << " tools\n";
// 		con_color(15);
	}
}