#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include "ElelctionCommision.h"
#include "VoterLogin.h"
#include "PoliticalParty.h"

using namespace std;

void PoliticalParty::Login()
{
	cin.ignore();
	string username;
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, pass);
	ifstream party(dir + "Political Parties/Parties Info.txt");
	while (!party.eof())
	{
		getline(party, line);
		if (search = line.find("Username: " + username) != string::npos)
		{
			getline(party, line);
			if (line == "Password: " + pass)
			{
				getline(party, line);
				search = line.find(": ");
				search += 2;
				partyname = line.substr(search, line.length());
				cout << "Logged In!\n";
				system("pause");
				PartyInterface(partyname);
			}
			else cout << "Wrong Password\n";
		}
	}
	party.close();
	
}

void PartyInterface(string partyname)
{
	char op;
	do
	{
		system("cls");
		cout << "1. Approve/Reject request of ticket\n";
		cout << "\n2. Check Results after voting is done (won/lost)\n";
		cout << "\n3. Exit\n";
		cout << "\nChoose: ";
		cin >> op;
		switch (op)
		{
		case '1':
			Decide(partyname);
			break;
		case '2':

			break;
		case '3':
			exit(1);
		default:
			cout << "Choose from the following\n";
			system("pause");
		}
	} while(true);
}

void Decide(string partyname)
{
	string dir = Filename();
	string line, name;
	bool approve = false;
	int search;
	system("cls");
	ifstream candidates(dir + "Political Parties/" + partyname + "/Requested Candidates.txt");
	while (!candidates.eof())
	{
		getline(candidates, line);
		cout << line << endl;
	}
	cin.ignore();

	candidates.close();
	cout << "Name: ";
	getline(cin, name);
	cout << "\n1. Approve\n";
	cout << "\n2. Reject\n";
	cin >> approve;
		candidates.open(dir + "Political Parties/" + partyname + "/Requested Candidates.txt");
		ofstream approved(dir + "Political Parties/" + partyname + "/Approved Candidates.txt", ios::out | ios::app);
		ofstream temp(dir + "Political Parties/" + partyname + "/temp.txt");
		while (!candidates.eof())
		{
			getline(candidates, line);
			if (search = line.find("Name: " + name) != string::npos)
				do
				{
					if (approve) approved << line << endl;
					getline(candidates, line);
				} while (search = line.find("Name: ") == string::npos && !candidates.eof());
			else temp << line << endl;
			temp << line << endl;
		}
		temp.close();
		if (approve) approved << "Votes: 0\n\n";
		approved.close();
		candidates.close();
		string can = dir + "Political Parties/" + partyname + "/Requested Candidates.txt";
		string tcan = dir + "Political Parties/" + partyname + "/temp.txt";
		remove(can.c_str());
		rename(tcan.c_str(), can.c_str());
		cout << "\nCandidate Approved!\n\n";
	system("pause");
}