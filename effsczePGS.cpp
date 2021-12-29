#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Customer {
	string cc;
	string name;
	float payment;
	float balance;
};

class Effscze {
	public :
	Effscze(float& payment, float& balance) {
		payment = rand() % 1000 + 1 + (float) rand()/RAND_MAX;
		balance = rand() % 1000 + 1000 + (float) rand()/RAND_MAX;
	}

	bool askCC(string& cc) {
		bool exitFlag;
		do {
			cout << "\n->\tEnter Credit Card Number (16 Digit) : ";
			cin >> ws;
			getline(cin, cc);

			if (cc == "exit")
				return 1;

			exitFlag = checkCC(cc);
			if (!exitFlag)
				cout << "\n\t-= !! Error : Invalid Credit Card Number !! =-\n";
		} while (!exitFlag);
		return 0;
	}

	bool checkCC(string cc) {
		for (int i = 0; i < cc.length(); i++) {
			if (cc[i] < '0' || cc[i] > '9')
				return 0;
		}

		if (cc.length() != 16)
			return 0;

		return 1;
	}

	bool luhnCalc(string& cc) {
		cout << "\tChecking…\n"
			<< "\t█▒▒▒▒▒▒▒▒▒\n";
		int dbl, dblTotal = 0;
		//123 123 123 123 123 1
		//* *  *  * *  *  * *
		for (int i = cc.length() - 2; i >=  0; i = i - 2) {
			dbl = cc[i] * 2;
			if (dbl > 9)
				dbl = (dbl / 10) + (dbl % 10);
			dblTotal += dbl;
		}
		
		cout << "\t50%\n"
			<< "\t█████▒▒▒▒▒\n";
			
		for (int i = 1; i < cc.length(); i = i + 2) {
			dblTotal += cc[i];
		}
		
		cout << "\t100%\n"
			<< "\t██████████\n";

		if (dblTotal % 10 == 0)
			return true;
		return false;
	}
};

int main() {
	Customer cust;
	Effscze fz(cust.payment, cust.balance);
	bool exitPGS, valid, cont;

	cout << fixed << setprecision(2);
	cout << "\n====================================================  ❤\n"
		<< "\n  -= Welcome to Effscze Payment Gateway System =-\n"
		<< "\n====================================================  ❤\n";

	do {
		exitPGS = fz.askCC(cust.cc);

		if (exitPGS)
			break;

		cout << "->\tEnter Name : ";
		cin >> ws;
		getline(cin, cust.name);
		valid = fz.luhnCalc(cust.cc);

		cout << "\n====================================================  ❤\n";
		if (!valid)
			cout << "\n\t-= !! Invalid Credit Card Number !! =-\n";
		else
			cout << "\n\t-= !! Credit Card Validated !! =-\n";
		cout << "\n====================================================  ❤\n";
	} while (!valid);
	
	if (!exitPGS) {
		cout << "\n\tSummary of Transactions :"
			<< "\n\tNet Charges : MYR " << cust.payment
			<< "\n\tPay To : Herschel Supply Co."
			<< "\n\tFrom Account : " << cust.cc
			<< "\n\tAccount Name : " << cust.name
			<< "\n\tAccount Balance : " << cust.balance
			<< "\n\n->\tPayment Confirmation : "
			<< "\n\t[1] Press 1 to Proceed with Payment : ";
		cin >> cont;
		if (cont) 
			cout << "\n\t-= !! Payment Successful !! =-"
				<< "\n\tYour new balance : " << cust.balance - cust.payment;
		else
			cout << "\n\t-= !! Payment Failed !! =-";
	}
	cout << "\n\n\tThank you for using Effscze Payment Gateway"
		<< "\n\tRedirecting to Official Page...\n"
		<< "\n====================================================  ❤\n";
	return 0;
}
