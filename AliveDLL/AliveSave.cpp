#include "stdafx.h"
#include "AliveSave.h"
#include "AliveDLL.h"

AliveSave::AliveSave()
{

#ifdef test_cout_aliveSave
	std::cout << "I'm Constructor by AliveSave\t  " << this << std::endl;
#endif
}

AliveSave::~AliveSave()
{
#ifdef test_cout_aliveSave
	std::cout << "I'm Destructor  by AliveSave\t  " << this << std::endl;
#endif
}

void AliveSave::Save( std::vector<Product*> & produts )
{
// 	con_color(11);
// 	std::cout << "Enter filename that you want save \"Alive\":\n";
// 	con_color(15);
// 	char nameFile[80];
// 	std::cin >> nameFile;
	std::ofstream fout(ALIVEDATABASE, std::ios_base::out | std::ios_base::trunc);
	
	if (!fout.is_open())
		std::cout << "Error opening file!\n";
	else
	{
		for (unsigned int i = 0; i < produts.size(); i++)
		{
			fout << dynamic_cast<Alive*>(produts[i])->m_name_product << " ";
			fout << dynamic_cast<Alive*>(produts[i])->m_quantity_product << " ";
			fout << dynamic_cast<Alive*>(produts[i])->m_price_product << " ";
			fout << dynamic_cast<Alive*>(produts[i])->m_color << " ";
			fout << dynamic_cast<Alive*>(produts[i])->m_lifetime_day;
			if (i != produts.size()-1)
				fout << '\n';
		}
		fout.close();
//		con_color(11);
//		std::cout << "Your successfully saved " << produts.size() << " alive\n";
//		con_color(15);
	}
}
