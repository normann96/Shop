#include "stdafx.h"
#include "ToolsLoad.h"

ToolsLoad::ToolsLoad() : m_pTI(nullptr), m_pT(nullptr)
{
	m_pTI = new ToolsInput;
//	m_pT = new Tools[NUMBER_TOOLS];

#ifdef test_cout_toolsLoad
	std::cout << "I'm Constructor by ToolsLoad\t  " << this << std::endl;
#endif
}

ToolsLoad::~ToolsLoad()
{

	if (m_pTI)
		delete m_pTI;

	if (m_pT)
		delete [] m_pT;


#ifdef test_cout_toolsLoad
	std::cout << "I'm Destructor by ToolsLoad\t  " << this << std::endl;
#endif
}

void ToolsLoad::Load( std::vector<Product*> & produts )
{
	try
	{
		std::ifstream fin(TOOLSDATABASE, std::ios::in);
		fin.exceptions(std::ifstream::failbit);
		if (!fin.is_open())
			std::cout << "Error opening file tools load!\n";
		else
		{
			fin.seekg (0, fin.end);
			int length = (int)fin.tellg();
			fin.seekg (0, fin.beg);

			produts.clear();
			int i = 0;
			if (length)
			{
				m_pT = new Tools[NUMBER_TOOLS];
				while (!fin.eof() && length)
				{
					if (i < NUMBER_TOOLS )
					{
						produts.push_back(&m_pT[i]);
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
			}
		}
		fin.close();
	}
	catch(std::ios_base::failure &fail)
	{
		std::cout << "Exception opening/reading file: " << fail.what() << std::endl;
	}
}