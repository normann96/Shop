#ifndef ConsoleText_h__
#define ConsoleText_h__
#include "BaseText.h"

class ConsoleText : public BaseText
{
public:
	ConsoleText();
	~ConsoleText();
protected:
	int ChooseMenu();
private:
	virtual void Info();
};

#endif // ConsoleText_h__
