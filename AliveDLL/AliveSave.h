#ifndef AliveSave_h__
#define AliveSave_h__

#include "../Library/BaseSave.h"

class AliveSave : public BaseSave
{
public:
	AliveSave();
	virtual ~AliveSave();

	void Save(std::vector<Product*> & produts);

protected:
private:
};
#endif // AliveSave_h__
