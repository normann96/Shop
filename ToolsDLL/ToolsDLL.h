// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TOOLSDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TOOLSDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TOOLSDLL_EXPORTS
#define TOOLSDLL_API __declspec(dllexport)
#else
#define TOOLSDLL_API __declspec(dllimport)
#endif

#include "../Library/BaseFactory.h"
#include "../Library/Product.h"

#define NUMBER_TOOLS 100
#define PROFITS 1.3
#define TOOLSDATABASE "tools.db"

class Tools : public Product
{
private:
	friend class ToolsOutput;
	friend class ToolsInput;
	friend class ToolsSave;
	friend class ToolsLoad;

	std::string m_type;
	double m_weight;
protected:
public:
	Tools();
	virtual ~Tools();
};

extern "C" TOOLSDLL_API BaseFactory * GetFactory();
extern "C" TOOLSDLL_API const char * GetNameDLL();