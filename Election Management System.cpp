#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include "ElelctionCommision.h"
#include "PoliticalParty.h"
#include "VoterLogin.h"

using namespace std;

int main()
{
	VoterLogin v;
	PoliticalParty p;
	ElectionCommision ec;
	system("cls");
	char op;
	do
	{
		system("cls");
		cout << "1. Election Commision Login\n";
		cout << "\n2. Political Paty Login\n";
		cout << "\n3. Voter Login\n";
		cout << "\n4. Exit\n";
		cin >> op;
		switch (op)
		{
		case '1':
			ec.EC_Login();
			break;
		case '2':
			p.Login();
			break;
		case '3':
			v.Login();
			break;
		case '4':
			exit(1);
		default:
			cout << "Choose from the following\n";
			system("pause");
		}
	} while (true);
}
