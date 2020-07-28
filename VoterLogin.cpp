#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include "ElelctionCommision.h"
#include "VoterLogin.h"

using namespace std;

void VoterLogin::Login()
{
	cin.ignore();
	cout << "CNIC: ";
	getline(cin, cnic);
	cout << "Password: ";
	getline(cin, pass);
	ifstream userfile(dir + "Election Commision/Voters/" + cnic + ".txt");
	if (userfile.is_open())
	{
		while (!userfile.eof())
		{
			getline(userfile, line);
			if (search = line.find("Password: ") != string::npos)
			{
				search = line.find(": ");
				search += 2;
				if (pass == line.substr(search, line.length()))
				{
					getline(userfile, line);
					search = line.find(": ");
					search += 2;
					search2 = line.find("/");
					district = line.substr(search, search2 - search);
					search2++;
					province = line.substr(search2, line.length());
					LoginInterface(cnic, district,province);
				}
					
			}
		}
	}
	else cout << "\nInvalid CNIC!\n";
	system("pause");
}

void LoginInterface(string cnic, string district,string province)
{
	char op;
	do
	{
		system("cls");
		cout << "1. Show all candidates with symbols\n";
		cout << "\n2. Cast Vote\n";
		cout << "\nChoose: ";
		cin >> op;
		switch (op)
		{
		case'1':
			system("cls");
			cout << "1. Sort by symbol id\n";
			cout << "\n2. Sort by symbol name\n";
			cin >> op;
			CandidatesList(op);
			system("pause");
			break;
		case '2':
			CastVote(cnic,district,province);
			break;
		default:
			cout << "Choose from the following\n";
			system("pause");
		}
	} while (true);
}

bool UsernameCheck(string username)
{
	if (username.length() <= 4)
	{
		cout << "Username must be more than 4 letters\n";
		return false;
	}
	if (username.length() > 25)
	{
		cout << "Username is too long\n";
		return false;
	}
	for (int i = 0; i < username.length(); i++)
	{
		if (username.at(i) == 32)
		{
			cout << "Spaces are not allowed in usernames\n";
			return false;
		}
	}
	return true;
}

bool PasswordCheck(string pass)
{
	if (pass.length() <= 4)
	{
		cout << "Password must be greater than 4 letters\n";
		return false;
	}
	return true;
}

bool PassCrossCheck(string pass, string pass2)
{
	return pass == pass2;
}

string Filename()
{
	string filename = __FILE__;
	string file2;
	for (int i = 0; i < filename.length(); i++)
	{
		if (filename.at(i) == '\\')
			file2 += "/";
		else
			file2 += filename.at(i);

	}
	int search = file2.find("System/");
	if (search != string::npos)
	{
		search += 7;
		file2 = file2.substr(0, search);
	}
	file2;
	return file2;
}

VoterLogin::VoterLogin()
{
	exist = false;
}

void CastVote(string cnic,string district,string province)
{
	string line, party;
	int search;
	string cons,constituencies[5];
	string dir = Filename();
	int choice, c1 = 1, c2 = 1;
	bool casted = false;
	ifstream ifcasted(dir + "Election Commision/Voters/" + cnic + ".txt");
	while (!ifcasted.eof())
	{
		getline(ifcasted, line);
		if (line == "Vote Casted: Yes")
			casted = true;
	}
	if (!casted)
	{
		ifstream parties(dir + "Political Parties/Registered Parties.txt");
		while (!parties.eof())
		{
			getline(parties, line);
			cout << c1++ << ": " << line << endl;
		}
		parties.close();

		cout << "\nChoose Party: ";
		cin >> choice;
		if (choice > 0 && choice <= c1)
		{
			parties.open(dir + "Political Parties/Registered Parties.txt");
			while (c2++ < choice)
				getline(parties, line);
			getline(parties, line);
			party = line;
			parties.close();
			int count = 0;
			ifstream cons(dir + "Constituencies/" + province + "/" + district + ".txt");
			while (!cons.eof())
			{
				getline(cons, line);
				if (search = line.find("Name: ") != string::npos)
				{
					search = line.find(": ");
					search += 2;
					constituencies[count++] = line.substr(search, line.length());
				}
			}
			string name;
			cons.close();
			ifstream candi(dir + "Political Parties/" + party + "/Approved Candidates.txt");
			while (!candi.eof())
			{
				getline(candi, line);
				if (search = line.find("Name: ") != string::npos)
				{
					search = line.find(": ");
					search += 2;
					name = line.substr(search, line.length());
				}
				if (search = line.find("Constituency: ") != string::npos)
				{
					search = line.find(": ");
					search += 2;
					for (int i = 0; i < count; i++)
					{
						if (constituencies[i] == line.substr(search, line.length()))
							cout << name << endl;
					}
				}
			}
			bool done = false;
			candi.close();
			string choose;
			cin.ignore();
			cout << "\nChoose a Candidate (Name): ";
			getline(cin, choose);
			int vote;
			candi.open(dir + "Political Parties/" + party + "/Approved Candidates.txt");
			ofstream temp(dir + "Political Parties/" + party + "/temp.txt");
			while (!candi.eof())
			{
				getline(candi, line);
				if (line == "Name: " + name)
				{
					done = true;
					temp << line << endl;
					getline(candi, line);
					temp << line << endl;
					getline(candi, line);
					search = line.find(": ");
					search += 2;
					vote = stoi(line.substr(search, line.length()));
					vote++;
					temp << "Votes: " << vote << endl;
				}
				else temp << line << endl;
			}
			candi.close();
			temp.close();
			string Bchange = dir + "Political Parties/" + party + "/Approved Candidates.txt";
			string Achange = dir + "Political Parties/" + party + "/temp.txt";
			remove(Bchange.c_str());
			rename(Achange.c_str(), Bchange.c_str());

			if (done)
			{
				ifstream votecasted(dir + "Election Commision/Voters/" + cnic + ".txt");
				ofstream tempcasted(dir + "Election Commision/Voters/temp.txt");
				while (!votecasted.eof())
				{
					getline(votecasted, line);
					if (search = line.find("Vote Casted: ") != string::npos)
						temp << "Vote Casted: Yes\n";
					else temp << line << endl;
				}
				votecasted.close();
				tempcasted.close();
				Bchange = dir + "Election Commision/Voters/" + cnic + ".txt";
				Achange = dir + "Election Commision/Voters/temp.txt";
				remove(Bchange.c_str());
				rename(Achange.c_str(), Bchange.c_str());
				cout << "Vote Casted!\n";

			}
			else
				cout << "Candidate Not Found!\n";
			
		}

	}
	else cout << "Vote Already Casted!\n";
	system("pause");
}

void CandidatesList(char op)
{
	if (op == '1')
	{


	}
	else if (op == '2')
	{

	}
}