// Shop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Shop.h"
#include "Category.h"


int _tmain(int argc, _TCHAR* argv[])
{

// 	int temp = SecurityInput::inputAnyInteger(2);
// 	std::cout << temp << std::endl;

//	_getch();

	Shop *pMyShop = new Shop;
	do 
	{
		SecurityInput::clearScreen();
		pMyShop->ShowBalance();
		std::cout << std::endl;
		pMyShop->Menu();

		switch(SecurityInput::inputAnyInteger(5))													// номер 5 - соответсвует количеству выборов меню
		{
			case 0: 
					pMyShop->ExitAndSave();															// Сохранить продукты и выйти
					break;
			case 1:																					
					pMyShop->Sell();																// Продать покупателю
					break;
			case 2:																					
					pMyShop->Buy();																	// Купить у поставщика
					break;
			case 3:																					
					pMyShop->ShowProducts();														// Показать продукты
					break;
			case 4:			
					pMyShop->SetBalance();															// Установить новый баланс
					break;
			case 5:																					
					pMyShop->Refresh();																// Поиск новых категорий и выгрузка продуктов
					break;
			case 6:																					 
					pMyShop->New();																	// Создать новый продукт
					break;
			case 7:																					
					pMyShop->Edit();																// Редактировать продукт
					break;

			default:
					std::cout << "Make you choice.\n";
					break;
		}
	} while (true);

	return 0;
}