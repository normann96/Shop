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
	try
	{
		std::ofstream fout(ALIVEDATABASE, std::ios_base::out | std::ios_base::trunc);
		fout.exceptions(std::ofstream::failbit);
		if(produts.size() && fout.is_open())
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
			std::cout << "Alive saved successfully!\n";
		}
		fout.close();
	}
	catch(std::ios_base::failure &fail)
	{
		std::cout << "Exception opening/writing file: " << fail.what() << std::endl;
		_getch();
	}
}