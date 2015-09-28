#include "stdafx.h"
#include "SecurityInput.h"
#include <conio.h>
#include <iostream>
#include <string>

#include "boost/smart_ptr.hpp"

static const unsigned int size = 64;
static char buffer[size];
static int a = 0;

#define MAX_PATH 260

// Enter string, input first symbol
char * SecurityInput::inputAnyChar()
{
	char cSimbol[MAX_PATH];
	int iCurIndex = 0;

	while(true)
	{
		a = _getch();
		if (((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || a == 32) && (iCurIndex < MAX_PATH-1))
		{
			cSimbol[iCurIndex++] = a;
			cSimbol[iCurIndex] = '\0';
			std::cout << char(a);
		} 
		else if (a == 8)
		{
			std::cout << '\b';
			std::cout << ' ';
			std::cout << '\b';
			cSimbol[iCurIndex--] = NULL;
			cSimbol[iCurIndex] = '\0';
		}
		else if(a == 13)			// 13 asci = enter
			break;
	}
	std::cout << std::endl;
	return cSimbol;
}

char SecurityInput::inputOneSymbol()
{
	char cSimbol = NULL;
	int iCurIndex = 0;

	while(true)
	{
		a = _getch();
		if (a != 13 && a != 8)
		{
			cSimbol = a;
			std::cout << '\b';
			std::cout << char(a);
		} 
		if (a == 8)
		{
			std::cout << '\b';
			std::cout << ' ';
			cSimbol = NULL;
		}
		else if(a == 27 || a == 13)			// 13 asci = enter  27 == ESC
			break;
	}
	std::cout << std::endl;
	return cSimbol;
}

char SecurityInput::inputOneChar()
{
	char cSimbol;
	int iCurIndex = 0;

	while(true)
	{
		a = _getch();
		if((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'))
		{
			cSimbol = a;
			std::cout << '\b';
			std::cout << char(a);
		} 
		if (a == 8)
		{
			std::cout << '\b';
			std::cout << ' ';
			cSimbol = NULL;
		}
		else if(a == 27 || a == 13)			// 13 asci = enter  27 == ESC
			break;
	}
	std::cout << std::endl;
	return cSimbol;
}

// Input any string or number: return 0 if was input string, return max of integer (2147483647), if enter number more than max integer
int SecurityInput::inputOneInteger(char num)
{
	ZeroMemory(buffer, sizeof(buffer));
	while(true)
	{
		a = _getch();
		if (a >= '0' && a <= num)
		{
			buffer[0] = a;
			std::cout << char(a);
			std::cout << '\b';
		}
		if (a == 8)
		{
			std::cout << ' ';
			std::cout << '\b';
			ZeroMemory(buffer, sizeof(buffer));
		}
		if(a == 13)
		{
			std::cout << '\b';
			break;
		}
		if (a == 27)
		{
			exit(1);
		}
	}
//	std::cout << std::endl;
	return  atoi(buffer);
}

int SecurityInput::inputAnyInteger()
{
	char numberCharAr[11];
	int a = 5;
	int iCurIndex = 0;

	while(true)
	{
		a = _getch();								// press any key
		if (a >= '0' && a <= '9' && iCurIndex < 10)
		{
			numberCharAr[iCurIndex++] = a;			// int max = 2 147 483 647

			if (atoi(numberCharAr) < 2147483647)
			{
				numberCharAr[iCurIndex] = 0;
				std::cout << (char)a;
			}
			else
			{
				numberCharAr[iCurIndex-1] = 0;
				iCurIndex = 9;
			}
		}
		if (a == 8)
		{
			numberCharAr[--iCurIndex] = 0;
			std::cout << '\b';
			std::cout << ' ';
			std::cout << '\b';

		}
		else if (a == 13 && iCurIndex > 0)		// 13 - enter

				break;
	}

	std::cout << std::endl;
	return atoi(numberCharAr);
}

int SecurityInput::inputAnyInteger( int max )
{
	std::cin.sync();
	char numberCharAr[11];
	int a = 5;
	unsigned int iCurIndex = 0;

	char b = '9';
	if (max < b)
		b = max + '0';

	while(true)
	{
		a = _getch();								// press any key
		
		if (a >= '0' && a <= b && iCurIndex < 10)
		{
			numberCharAr[iCurIndex++] = a;			// int max = 2 147 483 647

			if (atoi(numberCharAr) <= max)
			{
				numberCharAr[iCurIndex] = 0;
				std::cout << (char)a;
			}
			else
			{
				numberCharAr[iCurIndex-1] = 0;
				--iCurIndex;
			}
		}
		if (a == 8 && iCurIndex)
		{
			numberCharAr[--iCurIndex] = 0;
			std::cout << '\b' << ' ' << '\b';
		}
		else if (a == 13 && iCurIndex > 0)		// 13 - enter
				break;
		if (a == 27)
		{
			std::cout << "Exit...\n";
			Sleep(1000);
			exit(1);
		}
	}

	std::cout << std::endl;
	return atoi(numberCharAr);
}

double SecurityInput::InputAnyDouble()
{
	char numberCharAr[21];
	int a = 5;
	unsigned int iCurIndex = 0;
	int dot = 0;
	bool flagDot = true;
	while(true)
	{
		a = _getch();														// press any key

		if (a == '.' && flagDot && iCurIndex < 20)
		{
			dot = iCurIndex;
			flagDot = false;
			numberCharAr[iCurIndex++] = a;	
			numberCharAr[iCurIndex] = 0;
			std::cout << (char)a;
		}
		
		if ((a >= '0' && a <= '9') && iCurIndex < 20)
		{
			numberCharAr[iCurIndex++] = a;									// double  max = 1.79769e+308

			if (atof(numberCharAr) <= 1.79769e+308)
			{
				numberCharAr[iCurIndex] = 0;
				std::cout << (char)a;
			}
			else
			{
				numberCharAr[iCurIndex-1] = 0;
				--iCurIndex;
			}
		}
		if (a == 8 && iCurIndex)
		{
			numberCharAr[--iCurIndex] = 0;
			if (iCurIndex == dot)
				flagDot = true;
			std::cout << '\b' << ' ' << '\b';
		}
		else if (a == 13 && iCurIndex > 0)		// 13 - enter
			break;
		if (a == 27)
		{
			std::cout << "Exit...\n";
			Sleep(1000);
			exit(1);
		}
	}

	std::cout << std::endl;
	return atof(numberCharAr);
}

float SecurityInput::inputFloat()
{
	std::cin.getline(buffer, size);
	return (float)atof(buffer);
}

bool SecurityInput::inputBool()
{
	std::cin.getline(buffer, size);
	return buffer[0] == 'y';
}

std::string SecurityInput::inputString()
{
	std::cin.getline(buffer, size);
	return buffer;
}

void SecurityInput::waitForInput()
{
	system("pause");
}

void SecurityInput::clearScreen()
{
	system("cls");
}

std::string SecurityInput::inputAnyString()
{
	char cSimbol[MAX_PATH];
	int iCurIndex = 0;

	while(true)
	{
		a = _getch();
		if (((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || a == 32) && (iCurIndex < MAX_PATH-1))
		{
			cSimbol[iCurIndex++] = a;
			cSimbol[iCurIndex] = '\0';
			std::cout << char(a);
		} 
		else if (a == 8)
		{
			std::cout << '\b';
			std::cout << ' ';
			std::cout << '\b';
			cSimbol[iCurIndex--] = 0;
			cSimbol[iCurIndex] = '\0';
		}
		else if(a == 13 && iCurIndex)			// 13 asci = enter
		{
			cSimbol[iCurIndex] = '\0';
			break;
		}
	}
	std::cout << std::endl;
	return cSimbol;
}


