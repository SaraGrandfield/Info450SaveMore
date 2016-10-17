// BankAccountInfo450.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

//function to return a string with properly formated money $100,000.00 with a $ and , every third digit
string handleMoney(double money)
{
	string lmoney = to_string(money);
	int len = lmoney.size();
	len = len - 4;
	lmoney.resize(len);
	if (len >= 7)
	{
		for (int x = len - 6; x > 0; x = x - 3)
		{
			lmoney.insert(x, ",");
		}
	}
	lmoney.insert(0, "$");
	return lmoney;
}

class bankAccount
{
protected:
	int accountID = 0;
	double interestRate= 0;
	double balence = 0;
public:
	virtual double setRate() = 0;
	virtual bool withdraw()=0;
	virtual void deposit(double amount)=0;
	virtual void display()=0;

};

class savings : public bankAccount
{
public:
	savings(int id, double b)
	{
		accountID = id;
		balence = b;
		interestRate = setRate();
	}
	savings(int id)
	{
		accountID = id;
		balence = 0;
	}
	double setRate() 
	{
	    double oRate = interestRate;
		double newRate;
		if (balence >= 10000)
		{
			newRate = 2;
		}
		else if (balence < 10000)
		{
			newRate = 1;
		}
		else
		{
			cout << "ERROR INTEREST RATE UNCHANGED";
		}
		if (newRate != oRate)
		{
			cout << "Your new Interest rate is " << newRate << "% \n";
			return newRate;
		}
		else
			return oRate;

	}
	bool withdraw()
	{
		double amount;
		double fee = 2;
		cout << "Savings Account #" << accountID;
		cout << "Please enter the amount you would like to withdraw: ";
		cin >> amount;
		if (balence >= amount)
		{
			balence = balence - amount - fee;
			cout << "Savings Account #" << accountID << ":";
			cout << "You've been charged a $2 fee, so your new balence is " << handleMoney(balence) << "." << "\n";
			interestRate = setRate();
			return true;
		}
		else
		cout << "You do not have enough funds in your account to withdraw $" << amount << ".";
		cout << "\n You have " << handleMoney(balence) << " in this account.";
		return false;


	}
	void deposit(double amount)
	{
		balence = balence + amount;
		cout << "Savings Account #" << accountID << ":";
		cout << "Your new balence is " <<  handleMoney(balence) << ".\n";
		interestRate = setRate();
	}
	void display() 
	{
		cout << "Savings Account #" << accountID << ":\n";
		cout << "\tYour current balence is "  << handleMoney(balence) << ".\n";
		cout << "\tInterestRate " << interestRate << "%.\n";
	}

	void monthlyInterest()
	{
		double interestPayment = (interestRate/100) * balence;
		deposit(interestPayment);
		interestRate = setRate();
	}

};

class checkings : public bankAccount
{
	
public:
checkings(int id, double b)
{
accountID = id;
balence = b;
interestRate = setRate();
}
checkings(int id)
{
accountID = id;
}
double setRate()
{
	return 0;
}
bool withdraw()
{
double amount;
cout << "Checking Account #" << accountID;
cout << "Please enter the amount you would like to withdraw: ";
cin >> amount;
if (balence >= amount)
{
balence = balence - amount;
if (balence < 500)
{
	balence = balence - 5;
	cout << "Your account has been charged a $5 fee for falling bellow the $500 limit";
}
cout << "Checking Account #" << accountID << "Your new balence is " << handleMoney(balence) << "." << "\n";
return true;
}
else
cout << "You do not have enough funds in your account to withdraw $" << amount << ".";
cout << "\n You have " << handleMoney(balence) << " in this account.";
return false;


}
void deposit(double amount)
{
balence = balence + amount;
cout << "Checking Account # " << accountID << ":";
cout << "Your new balence is " <<  handleMoney(balence) << ".\n";
}
void display()
{
	cout << "Checking Account # " << accountID << ":\n";
	cout << "\tYour current balence is "  << handleMoney(balence) << ".\n";
}

void orderCheck()
{
	cout << "Checking Account # " << accountID << ":";
	cout << "Thank You for ordering checks. $15 has been deducted from your account. Shipping takes 2 to 3 business days.\n";
	balence = balence - 15;
	cout << "Your new total is " << handleMoney(balence) << ".\n";
}

};

class cd : public bankAccount
{
	int term;
public:
cd(int id, double b, int t)
{
accountID = id;
balence = b;
term = t;
interestRate = setRate();
}
double setRate()
{
double oRate = interestRate;
double newRate;
if (term >= 5)
{
newRate = 10;
}
else if (term < 5)
{
newRate = 5;
}
else
{
cout << "ERROR INTEREST RATE UNCHANGED";
}
if (newRate != oRate)
{
cout << "Your new Interest rate is " << newRate << "% \n";
return newRate;
}
else
return oRate;

}
bool withdraw()
{
double amount;
double fee = .1;
double earlyW;
cout << "CD Account #" << accountID;
cout << "Please enter the amount you would like to withdraw: ";
cin >> amount;
if (balence >= amount)
{
	earlyW = balence * fee;
	balence = balence - amount - earlyW;
cout << "Savings Account #" << accountID << ":";
cout << "You've been charged an early withdraw fee of" << handleMoney(earlyW) << " , so your new balence is " << handleMoney(balence) << "." << "\n";
setRate();
return true;
}
else
cout << "You do not have enough funds in your account to withdraw $" << amount << ".";
cout << "\n You have " << handleMoney(balence) << " in this account.";
return false;


}
void deposit(double amount)
{
balence = balence + amount;
cout << "Savings Account #" << accountID << ":";
cout << "Your new balence is " <<  handleMoney(balence) << ".\n";
interestRate = setRate();
}
void display()
{
cout << "CD Account #" << accountID << ":";
cout << "\tYour current balence is "  << handleMoney(balence) << ".\n";
cout << "\tInterestRate " << interestRate << "%." << "\n";
cout << "\tYour CD has a term of " << term << " years." << "\n";
}

void monthlyInterest()
{
double interestPayment = (interestRate/100) * balence;
deposit(interestPayment);
setRate();
}
};

int main()
{
	savings sara(01);
	checkings sean(02);
	cd mister(03,0,3);
	mister.deposit(10000);
	sara.deposit(10000);
	sara.monthlyInterest();
	sara.display();
	sean.deposit(600);
	sean.display();
	sean.orderCheck();
	mister.monthlyInterest();
	mister.display();
	sara.withdraw();
	sean.withdraw();
	mister.withdraw();
	sean.display();
	sara.display();
	mister.display();

	return 0;
}

