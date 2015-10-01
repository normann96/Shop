#include "stdafx.h"
#include "AliveLoad.h"

//#include "AliveDLL.h"

AliveLoad::AliveLoad() : m_pAI(nullptr), m_pAl(nullptr)
{
	m_pAI = new AliveInput;

#ifdef test_cout_aliveLoad
	std::cout << "I'm Constructor by AliveLoad\t  " << this << std::endl;
#endif
}

AliveLoad::~AliveLoad()
{
	if (m_pAI)
		delete m_pAI;

	if (m_pAl)
		delete [] m_pAl;


#ifdef test_cout_aliveLoad
	std::cout << "I'm Destructor  by AliveLoad\t  " << this << std::endl;
#endif
}

void AliveLoad::Load( std::vector<Product*> & produts )
{
	try
	{
		std::ifstream fin(ALIVEDATABASE, std::ios::in );
		fin.exceptions(std::ifstream::failbit);
		if (!fin.is_open())
			std::cout << "Error opening file load alive!\n";
		else
		{
			fin.seekg (0, fin.end);
			int length = (int)fin.tellg();
			fin.seekg (0, fin.beg);

			produts.clear();
			int i = 0;
			if (length)
			{
				m_pAl = new Alive[NUMBER_ALIVE];
				while (!fin.eof())
				{
					if (i < NUMBER_ALIVE )
					{
						produts.push_back(&m_pAl[i]);
						fin >> dynamic_cast<Alive*>(produts[i])->m_name_product;
						fin >> dynamic_cast<Alive*>(produts[i])->m_quantity_product;
						fin >> dynamic_cast<Alive*>(produts[i])->m_price_product;
						fin >> dynamic_cast<Alive*>(produts[i])->m_color;
						fin >> dynamic_cast<Alive*>(produts[i])->m_lifetime_day;
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
		_getch();
	}
}
