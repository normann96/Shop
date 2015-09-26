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
// 	con_color(11);
// 	std::cout << "Enter filename that you want save \"Tools\":\n";
// 	con_color(15);
// 	char nameFile[80];
// 	std::cin >> nameFile;
	std::ofstream fout(TOOLSDATABASE, std::ios_base::out | std::ios_base::trunc);

	if (!fout.is_open())
		std::cout << "Error opening file!\n";
	else
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
		fout.close();
// 		con_color(11);
// 		std::cout << "Your successfully saved " << produts.size() << " tools\n";
//		con_color(15);
	}
}
