// Shop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Shop.h"
#include "Category.h"


int _tmain(int argc, _TCHAR* argv[])
{

	Shop *pMyShop;
	try
	{
		pMyShop = new Shop;
	}
	catch (std::bad_alloc& ba)
	{
		std::cout << "bad_alloc caught: " << ba.what() << '\n';
	}

	do 
	{
		SecurityInput::clearScreen();
		pMyShop->ShowBalance();
		std::cout << std::endl;
		pMyShop->Menu();

		switch(SecurityInput::inputAnyInteger(5))													// ����� 5 - ������������ ���������� ������� ����
		{
			case 0: 
					pMyShop->ExitAndSave();															// ��������� �������� � �����	
					break;
			case 1:																					
					pMyShop->Sell();																// ������� ����������
					break;
			case 2:																					
					pMyShop->Buy();																	// ������ � ����������
					break;
			case 3:																					
					pMyShop->ShowProducts();														// �������� ��������
					break;
			case 4:			
					pMyShop->SetBalance();															// ���������� ����� ������
					break;
			case 5:																					
					pMyShop->Refresh();																// ����� ����� ��������� � �������� ���������
					break;
			case 6:																					 
					pMyShop->New();																	// ������� ����� �������
					break;
			case 7:																					
					pMyShop->Edit();																// ������������� �������
					break;

			default:
					std::cout << "Make you choice.\n";
					break;
		}
	} while (true);

	return 0;
}