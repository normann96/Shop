#ifndef _BALANCE_H
#define _BALANCE_H

class Balance
{
private:
	double m_nMoney;
protected:
public:
	Balance();
	~Balance();

	void ShowBalance();
	void SetBalance(double balance);
	double GetBalance();
};

#endif // _BALANCE_H
