#include "stdafx.h"
#include "ConsoleText.h"

ConsoleText::ConsoleText()
{
#ifdef test_cout_console_text
	std::cout << "I'm Constructor by ConsoleText\t  " << this << std::endl;
#endif
}

ConsoleText::~ConsoleText()
{
#ifdef test_cout_console_text
	std::cout << "I'm Destructor by ConsoleText\t  " << this << std::endl;
#endif
}

void ConsoleText::Info()
{
	con_color(14);
	std::cout << "Choose menu:\n";
	std::cout << "1 - Sell a product\n";
	std::cout << "2 - Buy a product\n";
	std::cout << "3 - Show products\n";
	std::cout << "4 - Set balance\n";
	std::cout << "5 - Refresh\n";
// 	std::cout << "6 - Create new product\n";
// 	std::cout << "7 - Change the product\n";
	std::cout << "0 - Save and Exit\n";
	con_color(15);
}

int ConsoleText::ChooseMenu()
{
	char numberArr[1];
	int a = 5;
	while(true)
	{
		a = _getch();
		if (a > 48 && a < 57)
		{
			numberArr[0] = a;
			std::cout << char(a);
			std::cout << '\b';
		}
		if (a == 8)
		{
			std::cout << ' ';
			std::cout << '\b';
			numberArr[0] = 0;
		}
		if(a == 27 || a == 13)
			break;
	}
	//	cout << endl;
	return  atoi(numberArr);
}
