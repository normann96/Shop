// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ALIVEDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ALIVEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ALIVEDLL_EXPORTS
#define ALIVEDLL_API __declspec(dllexport)
#else
#define ALIVEDLL_API __declspec(dllimport)
#endif

#include "../Library/BaseFactory.h"
#include "../Library/Product.h"

#define NUMBER_ALIVE 100
#define PROFITS 1.2
#define ALIVEDATABASE "alive.db"

class Alive : public Product
{
private:
	friend class AliveOutput;
	friend class AliveInput;
	friend class AliveSave;
	friend class AliveLoad;

	std::string m_color;
	unsigned int m_lifetime_day;

protected:
public:
	Alive();
	virtual ~Alive();

	const std::string &GetColor();
	unsigned int GetLifetimeDay();
};

extern "C" ALIVEDLL_API BaseFactory * GetFactory();
extern "C" ALIVEDLL_API const char * GetNameDLL();