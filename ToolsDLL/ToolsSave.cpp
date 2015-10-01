#include "stdafx.h"
#include "ToolsSave.h"
#include "ToolsDLL.h"

ToolsSave::ToolsSave()
{

#ifdef test_cout_toolsSave
	std::cout << "I'm Constructor by ToolsSave\t  " << this << std::endl;
#endif
}

ToolsSave::~ToolsSave()
{
#ifdef test_cout_toolsSave
	std::cout << "I'm Destructor by ToolsSave\t  " << this << std::endl;
#endif
}

void ToolsSave::Save( std::vector<Product*> & produts )
{
	try
	{
		std::ofstream fout(TOOLSDATABASE, std::ios_base::out | std::ios_base::trunc);
		fout.exceptions(std::ofstream::failbit);
		if(produts.size() && fout.is_open())
		{
			for (unsigned int i = 0; i < produts.size(); i++)
			{
				fout << dynamic_cast<Tools*>(produts[i])->m_name_product << " ";
				fout << dynamic_cast<Tools*>(produts[i])->m_quantity_product << " ";
				fout << dynamic_cast<Tools*>(produts[i])->m_price_product << " ";
				fout << dynamic_cast<Tools*>(produts[i])->m_type << " ";
				fout << dynamic_cast<Tools*>(produts[i])->m_weight;
				if (i != produts.size()-1)
					fout << '\n';
			}
			std::cout << "Tools saved successfully!\n";
		}
		fout.close();
	}
	catch(std::ios_base::failure &fail)
	{
		std::cout << "Exception opening/reading file: " << fail.what() << std::endl;
	}
}