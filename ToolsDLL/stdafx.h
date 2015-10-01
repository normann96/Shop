// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include "TaskTools.h"

#define con_color(a) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a)


// TODO: reference additional headers your program requires here
