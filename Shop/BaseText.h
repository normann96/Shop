#ifndef _BASETEXT_H
#define _BASETEXT_H

class BaseText
{
private:
protected:
	virtual int ChooseMenu();
public:
	BaseText();
	virtual ~BaseText();

	virtual void Info();

};

#endif // _BASETEXT_H