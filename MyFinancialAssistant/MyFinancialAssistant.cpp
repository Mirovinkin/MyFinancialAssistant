// MyFinancialAssistant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <math.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#include <typeinfo>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
//#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <map>
#include <vector>


using namespace std;
class DebitCard
{
private:
	int _id;
	double _balance;
	map<int,vector<double>> _expenses;
public:
	DebitCard() {};
	DebitCard(const int& Id, const double& Balance) : _id(Id), _balance(Balance) {};

	int GetId()
	{
		return _id;
	}

	double GetBalance()
	{
		return _balance;
	}

	void AddBalance(const double& Add)
	{
		_balance += Add;
	}


	void DeductBalance(const double& Deduct)
	{
		
		if (_balance >= Deduct) {
			vector<double> Num;
			Num.push_back(Deduct);
			AddToExpenses(Num);
			_balance -= Deduct;
		}
		else
		{
			throw exception("На балансе не хватает средств");
		}
	}

	void AddToExpenses(const vector<double> Num)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		_expenses.insert(pair<int, vector<double>>(1 + ltm->tm_mon, Num));
	}

	map<int, vector<double>> GetExpenses()
	{
		return _expenses;
	}

};

class CreditCard
{
private:
	int _id;
	double _balance;
	double _limit;
	map<int,vector<double>> _expenses;

public:
	CreditCard() {};
	CreditCard(const int& Id, const double& Balance) : _id(Id), _balance(Balance) {};

	int GetId()
	{
		return _id;
	}

	double GetBalance()
	{
		return _balance;
	}

	void AddBalance(const double& Add)
	{
		_balance += Add;
	}
	void DeductBalance(const double& Deduct)
	{

		if (_balance >= Deduct) {
			vector<double> Num;
			Num.push_back(Deduct);
			AddToExpenses(Num);
			_balance -= Deduct;
		}
		else
		{
			throw exception("На балансе не хватает средств");
		}
	}

	void AddToExpenses(const vector<double> Num)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		_expenses.insert(pair<int, vector<double>>(1 + ltm->tm_mon, Num));
	}

	map<int, vector<double>> GetExpenses()
	{
		return _expenses;
	}
};

class Account
{
private:
	vector<DebitCard> _debitCards;
	vector<CreditCard> _creditCards;
	int _id;
public:
	Account() {};
	Account(const DebitCard& DebitCardN, const CreditCard& CreditCardN, const int& Id)
	{
		srand(time(NULL));
		_debitCards.push_back(DebitCardN);
		_creditCards.push_back(CreditCardN);
		_id = 10000000 + rand() % 9999999;
	}

	vector<DebitCard> GetDebitCard()
	{
		return _debitCards.size()!=0?_debitCards:throw exception("У Вас нет Дубетовой карты");
	}

	vector<CreditCard> CreditCard()
	{
		return _creditCards.size() != 0 ? _creditCards : throw exception("У Вас нет Дубетовой карты");
	}

	int GetId()
	{
		return _id;
	}

	void SetDebitCard(const DebitCard& DebitCardN)
	{
		_debitCards.push_back(DebitCardN);

	}
	void SetCreditCard(const class CreditCard& CreditCardN)
	{
		_creditCards.push_back(CreditCardN);
	}
};
class FinancialManager
{
private:
	string _name;
	map<string, Account> _customer;
	
public:
	FinancialManager() {};
	FinancialManager(const map<string,Account> Customer)
	{
		_customer = Customer;
	};
	FinancialManager(const string& Name, const Account AccountN)
	{
		_customer.insert(pair<string, Account>(Name, AccountN));
	}

	void PrintTopThreeExpenses()
	{
		int count = 3;
		for(auto item : _customer)
		{
			cout << "Имя клиента: " << item.first << endl;
			cout << "Топ 3 затраты: " << item.first << endl;
			do
			{
				for(auto item2 : item.second.GetDebitCard())
				{
					for(auto item3 : item2.GetExpenses())
					{
						cout << "Дата затраты: " << item3.first << endl;
						cout << "Сумма затраты: " << *min_element(item3.second.begin(), item3.second.end());
					}
				}
			} while (count != 0);
		}
	}
};

int main()
{

}
