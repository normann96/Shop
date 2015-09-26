#include "stdafx.h"
#include "AliveLoad.h"

//#include "AliveDLL.h"

AliveLoad::AliveLoad() : m_pAI(nullptr)
{
	m_pAI = new AliveInput;

	if (!(m_pAI->m_ppAliveArray))
		m_pAI->m_ppAliveArray = new Alive*[NUMBER_ALIVE];

#ifdef test_cout_aliveLoad
	std::cout << "I'm Constructor by AliveLoad\t  " << this << std::endl;
#endif
}

AliveLoad::~AliveLoad()
{
	if (m_pAI)
		delete m_pAI;

#ifdef test_cout_aliveLoad
	std::cout << "I'm Destructor  by AliveLoad\t  " << this << std::endl;
#endif
}

void AliveLoad::Load( std::vector<Product*> & produts )
{
// 	con_color(11);
// 	std::cout << "Enter filename that you want load \"Alive\":\n";
// 	char nameFile[80];
// 	con_color(15);
// 	std::cin >> nameFile;
	std::ifstream fin(ALIVEDATABASE, std::ios::in);

	if (!fin.is_open())
		std::cout << "Error opening file!\n";
	else
	{
		produts.clear();
		int i = 0;
		while (!fin.eof())
		{
			if (m_pAI->m_numberAlive < NUMBER_ALIVE )
			{
				m_pAI->m_ppAliveArray[m_pAI->m_numberAlive++] = new Alive;
				produts.push_back(m_pAI->m_ppAliveArray[m_pAI->m_numberAlive-1]);

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
		fin.close();
// 		con_color(11);
// 		std::cout << "Your successfully load " << produts.size() << " alive\n";
//		con_color(15);
	}
}
