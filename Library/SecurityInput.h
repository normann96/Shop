#ifndef SecurityInput_h__
#define SecurityInput_h__
#include <string>

class SecurityInput
{
public:
	static char * inputAnyChar();
	static std::string inputAnyString();
	static char inputOneSymbol();
	static char inputOneChar();
	static int inputOneInteger(char num);
	static int inputAnyInteger();
	static int inputAnyInteger(int max);
	static double InputAnyDouble();
	static float inputFloat();
	static bool inputBool();
	static std::string inputString();
	static void waitForInput();
	static void clearScreen();
};

#endif // SecurityInput_h__
