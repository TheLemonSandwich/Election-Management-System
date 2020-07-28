#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include "VoterLogin.h"
#include "PoliticalParty.h"
#include "ElelctionCommision.h"


using namespace std;

void ElectionCommision::EC_Login()
{
	system("cls");
	cin.ignore();
	cout << "Password: ";
	getline(cin, pass);
	if (pass == "NustSucks69")
	{
		cout << "\nSuccessfully Logged In!\n";
		system("pause");
		EC_Interface();
	}
	else cout << "\nInvalid Password!\n";
}

void EC_Interface()
{
	
	char op;
	do
	{
		system("cls");
		cout << "1. Register a National Assembly Constituency\n";
		cout << "\n2. List all Constituencies\n";
		cout << "\n3. Delete Constituencies\n";
		cout << "\n4. Register Political Party\n";
		cout << "\n5. Register a Candidate\n";
		cout << "\n6. Register a voter\n";
		cout << "\n7. Exit\n";
		cout << "\nChoose: ";
		cin >> op;
		switch (op)
		{
		case '1':
			RegisterConstituency();
			break;
		case '2':
			DisplayConstituencies();
			break;
		case '3':
			Delete();
			break;
		case '4':
			RegisterPP();
			break;
		case '5':
			RegisterCandidate();
			break;
		case '6':
			RegisterVoter();
			break;
		case '7':
			exit(1);
		default:
			cout << "Choose from the following\n";
			system("pause");
		}
	} while (true);
}

void RegisterCandidate()
{
	cin.ignore();
	string dir = Filename();
	bool invalid;
	string line, constituency, name;
	int search, counter = 0, choice, c2 = 0;
	do
	{
		invalid = false;
		cout << "Name of the candidate: ";
		getline(cin, name);
		if (name.length() != 0)
			for (int i = 0; i < name.length(); i++)
			{
				if (name.at(i) > 47 && name.at(i) < 58)
				{
					cout << "\nInvalid Name!\n";
					invalid = true;
				}
			}
		else 
		{
			cout << "\nInvalid Name!\n";
			invalid = true;
		}
	} while (invalid);
	cout << "\n1. Independent Candidate\n";
	cout << "\n2. Political Candidate\n";
	char op;
	cout << "\nChoose: ";
	cin >> op;
	cin.ignore();
	bool exist = false;
	cout << "Constituency: ";
	getline(cin, constituency);
	ifstream cons(dir + "Election Commision/Constituencies.txt");
	while (!cons.eof())
	{
		getline(cons, line);
		if (search = line.find("Name: " + constituency) != string::npos)
			exist = true;
	}
	if (exist)
	{
		if (op == '2')
		{
			ifstream registered(dir + "Political Parties/Registered Parties.txt");
			while (!registered.eof())
			{
				getline(registered, line);
				cout << ++counter << ": " << line << endl;
			}
			registered.close();
			cout << "Choose: ";
			cin >> choice;
			if (choice > 0 && choice <= counter)
			{
				registered.open(dir + "Political Parties/Registered Parties.txt");
				while (++c2 < choice) getline(registered, line);
				getline(registered, line);
				registered.close();
				ofstream request(dir + "Political Parties/" + line + "/Requested Candidates.txt", ios::out | ios::app);
				request << "Name: " << name << endl;
				request << "Constituency: " << constituency << endl << endl;
				cout << "\nCandidate Up for Approval!\n\n";
				request.close();
			}
		}
		else if (op == '1')
		{
			int choice2;
			int c1 = 1;
			cin.ignore();
			ifstream symbols(dir + "Political Parties/Available Symbols.txt");
			ofstream tsymbols(dir + "Political Parties/Stemp.txt");
			while (!symbols.eof())
			{
				getline(symbols, line);
				if (line.length() != 0)
					cout << c1++ << ": " << line << endl;
			}
			symbols.close();
			cout << "Choose: ";
			cin >> choice2;
			if (choice2 > 0 && choice2 <= c1)
			{
				symbols.open(dir + "Political Parties/Available Symbols.txt");
				while (c2++ < choice2)
				{
					getline(symbols, line);
					tsymbols << line << endl;
				}
				getline(symbols, line);
				string sym = line;
				while (!symbols.eof())
				{
					getline(symbols, line);
					tsymbols << line << endl;
				}
				symbols.close();
				tsymbols.close();
				string name1 = dir + "Political Parties/Available Symbols.txt";
				string tname = dir + "Political Parties/Stemp.txt";
				remove(name1.c_str());
				rename(tname.c_str(), name1.c_str());

				ofstream independent(dir + "Political Parties/Independent Candidates/Approved Candidates.txt", ios::out | ios::app);
				independent << "Name: " << name << endl;
				independent << "Constituency: " << constituency << endl << endl;
				independent << "Symbol: " << sym << endl;
				cout << "\nCandidate Registered!\n\n";
				independent.close();
				ofstream candi(dir + "Election Commision/Candidates.txt", ios::out | ios::app);
				candi << "Name: " << name << endl;
				candi << "Constituency: " << constituency << endl;
				candi << "Party Status: Independent\n\n";
				candi.close();
			}
		}
	}
	else cout << "Constituency doesn't exist\n";
	system("pause");
}

void RegisterPP()
{
	string dir = Filename();
	string line;
	int search;
	int count = 1,choice;
		system("cls");
		cout << "Available Names for Political Parties\n";
		ifstream names(dir + "Political Parties/Available Names.txt");
		ofstream Ntemp(dir + "Political Parties/Ntemp.txt");
		while (!names.eof())
		{
			getline(names, line);
			if (line.length() != 0)
			cout << count++ << ": " << line << endl;
		}
		names.close();
		cout << "Choose: ";
		cin >> choice;
		if (choice > 0 && choice <= count)
		{
			names.open(dir + "Political Parties/Available Names.txt");
			int count2 = 1;
			while (count2++ < choice)
			{
				getline(names, line);
				Ntemp << line << endl;
			}
			getline(names, line);
			string newdir = dir + "Political Parties/" + line;
			string partyname = line;
			ofstream taken(dir + "Political Parties/Registered Parties.txt", ios::out | ios::app);
			taken << line << endl;
			taken.close();
			_mkdir(newdir.c_str());
			ofstream Info(newdir + "/Information.txt");
			Info << "Name: " << line << endl;
			while (!names.eof())
			{
				getline(names, line);
				Ntemp << line << endl;
			}
			names.close();
			Ntemp.close();
			string name = dir + "Political Parties/Available Names.txt";
			string tname = dir + "Political Parties/Ntemp.txt";
			remove(name.c_str());
			rename(tname.c_str(), name.c_str());

			system("cls");
			cout << "Available Symbols\n";
			int c1 = 1, c2 = 1, choice2;
			ifstream symbols(dir + "Political Parties/Available Symbols.txt");
			ofstream tsymbols(dir + "Political Parties/Stemp.txt");
			while (!symbols.eof())
			{
				getline(symbols, line);
				if (line.length() != 0)
				cout << c1++ << ": " << line << endl;
			}
			symbols.close();
			cout << "Choose: ";
			cin >> choice2;
			if (choice2 > 0 && choice2 <= c1)
			{
				symbols.open(dir + "Political Parties/Available Symbols.txt");
				while (c2++ < choice2)
				{
					getline(symbols, line);
					tsymbols << line << endl;
				}
				getline(symbols, line);
				Info << "Symbol: " << line << endl;
				while (!symbols.eof())
				{
					getline(symbols, line);
					tsymbols << line << endl;
				}
				symbols.close();
				tsymbols.close();
				Info.close();
				name = dir + "Political Parties/Available Symbols.txt";
				tname = dir + "Political Parties/Stemp.txt";
				remove(name.c_str());
				rename(tname.c_str(), name.c_str());
				cin.ignore();
				string username, pass,pass2;
				cout << "\nUsername and password for Party\n";
				cout << "\nUsername: ";
				getline(cin, username);
				if (UsernameCheck(username))
				{
					cout << "Password: ";
					getline(cin, pass);
					if (PasswordCheck(pass))
					{
						cout << "Re-Enter Password: ";
						getline(cin, pass2);
						if (PassCrossCheck(pass, pass2))
						{
							ofstream Login(newdir + "/Information.txt", ios::out | ios::app);
							Login << "Username: " << username << endl;
							Login << "Password: " << pass << endl;
							Login.close();
							ofstream PPInfo(dir + "Political Parties/Parties Info.txt", ios::out | ios::app);
							PPInfo << "Username: " << username << endl;
							PPInfo << "Password: " << pass << endl;
							PPInfo << "Name: " << partyname << endl << endl;
							PPInfo.close();
						}
						else cout << "\nPasswords Don't Match!\n";
					}
				}
			}
		}
}

void Delete()
{
	cin.ignore();
	string dir = Filename();
	string district, province, name, name2;
	bool exist = false;
	bool exist1 = false;
	string line;
	int search,search2;
	cout << "Name of the Constituency: ";
	getline(cin, name);
	ifstream edit(dir + "Election Commision/Constituencies.txt");
	while (!edit.eof())
	{
		getline(edit, line);
		if(!exist)
		if (search = line.find("Name: ") != string::npos)
		{
			search = line.find(": ");
			search += 2;
			name2 = line.substr(search, line.length());
			if (name2 == name)
				exist = true;
		}
		if (exist && !exist1)
		{
			if (search = line.find("District: ") != string::npos)
			{
				search = line.find(": ");
				search += 2;
				search2 = line.find("/");
				district = line.substr(search, search2 - search);
				search2++;
				province = line.substr(search2, line.length());
				cout << "District: " << district << endl;
				cout << "Province: " << province << endl;
				exist1 = true;
			}
		}
	}
	edit.close();
	char op;
	if (exist1)
	{
		cout << "\nAre you sure you want to delete " << name << "?" << endl;
		cout << "Choose: ";
		cin >> op;
	}
	else op = 'n';
	if (op == 'y' || op == 'Y')
	{
		ifstream file(dir + "Election Commision/Constituencies.txt");
		ofstream temp(dir + "Election Commision/temp.txt");
		while (!file.eof())
		{
			getline(file, line);
			cout << "Election Commision Constiuencies line: " << line << endl;
			if (search = line.find("Name: " + name) != string::npos) do getline(file, line); while (search = line.find("Name: ") == string::npos && !file.eof());
			else temp << line << endl;
			temp << line << endl;
		}
		file.close();
		temp.close();
		string ecfile = dir + "Election Commision/Constituencies.txt";
		string tempname = dir + "Election Commision/temp.txt";
		remove(ecfile.c_str());
		rename(tempname.c_str(), ecfile.c_str());
		ifstream c(dir + "Constituencies/" + province + "/" + district + ".txt");
	ofstream tempo(dir + "Constituencies/" + province + "/ctemp.txt");
		while (!c.eof())
		{
			getline(c, line);
			if (search = line.find("Name: " + name) != string::npos) do getline(c, line); while (search = line.find("Name: ") == string::npos && !c.eof());
			else tempo << line << endl;
			tempo << line << endl;
		}
		c.close();
		tempo.close();
		string Fname = dir + "Constituencies/" + province + "/" + district + ".txt";
		string Tname = dir + "Constituencies/" + province + "/ctemp.txt";
		remove(Fname.c_str());
		rename(Tname.c_str(), Fname.c_str());
		system("pause");
	}
}

void RegisterConstituency()
{
	cin.ignore();
	string line;
	int search;
	bool exist = false;
	string dir = Filename();
	string constituency, district, province;
	system("cls");
	cout << "Name of the Constituency: ";
	getline(cin, constituency);
	cout << "Province: ";
	getline(cin, province);
	ifstream provinces(dir + "Constituencies/Provinces.txt");
	while (!provinces.eof())
	{
		getline(provinces, line);
		if (line == province)
			exist = true;
	}
	provinces.close();
	if (exist)
	{
		exist = false;
		cout << "District: ";
		getline(cin, district);
		ifstream districts(dir + "Constituencies/" + province + "/Districts.txt");
		while (!districts.eof())
		{
			getline(districts, line);
			if (line == district)
				exist = true;
		}
		districts.close();
		if (exist)
		{
			exist = false;
			string newdir = dir + "Constituencies/" + province + "/" + district;
			fstream C(newdir + ".txt");
			if (C.is_open())
			{
				while (!C.eof())
				{
					getline(C, line);
					if (search = line.find("Name: ") != string::npos)
					{
						search = line.find(": ");
						search += 2;
						if (constituency == line.substr(search, line.length()))
						{
							cout << "Already Exists\n";
							exist = true;
							system("pause");
						}
					}
				}
				C.close();
			}
			if (!exist)
			{
				ofstream c(newdir + ".txt", ios::out | ios::app);
				c << "Name: " << constituency << endl;
				c << "District: " << district + "/" + province << endl << endl;
				c.close();
				ifstream cons(dir + "Election Commision/Constituencies.txt");
				if (cons.is_open())
				{
					while (!cons.eof())
					{
						getline(cons, line);
						if (search = line.find("Name: ") != string::npos)
						{
							search = line.find(": ");
							search += 2;
							if (constituency == line.substr(search, line.length()))
							{
								cout << "Already Created\n";
								exist = true;
								system("pause");
							}
						}
					}
					cons.close();
				}
				if (!exist)
				{
					ofstream con(dir + "Election Commision/Constituencies.txt", ios::out | ios::app);
					con << "Name: " << constituency << endl;
					con << "District: " << district << "/" << province << endl << endl;
					con.close();
					cout << "\nConstituency Created!\n";
					system("pause");
				}
			}
		}

	}
}

void DisplayConstituencies()
{
	bool open = true;
	string line;
	string dir = Filename();
	ifstream c(dir + "Election Commision/Constituencies.txt");
	if (c.is_open())
	{
		while (!c.eof())
		{
			getline(c, line);
			cout << line << endl;
		}
		c.close();
	}
	else cout << "\nNo constituencies yet listed\n";
	system("pause");
}

void RegisterVoter()
{
	string province, district;
	bool exist = false;
	string line;
	int search;
	string cnic, pass, pass2;
	string dir = Filename();
	cin.ignore();
	cout << "CNIC: ";
	getline(cin, cnic);
	if (CNICcheck(cnic))
	{
		cout << "Password: ";
		getline(cin, pass);
		if (PasswordCheck(pass))
		{
			cout << "Re-enter Password: ";
			getline(cin, pass2);
			if (PassCrossCheck(pass, pass2))
			{
				cout << "Province: ";
				getline(cin, province);
				ifstream prov(dir + "Constituencies/Provinces.txt");
				while (!prov.eof())
				{
					getline(prov, line);
					if (line == province)
						exist = true;
				}
				prov.close();
				if (exist)
				{
					exist = false;
					cout << "District: ";
					getline(cin, district);
					ifstream dist(dir + "Constituencies/" + province + "/Districts.txt");
					while (!dist.eof())
					{
						getline(dist, line);
						if (line == district)
							exist = true;
					}
					if (exist)
					{
						ofstream userfile(dir + "Election Commision/Voters/" + cnic + ".txt");
						userfile << "CNIC: " << cnic << endl;
						userfile << "Password: " << pass << endl;
						userfile << "District: " << district + "/" << province << endl;
						userfile << "Vote Casted: No\n";
						cout << "Voter Registered!\n\n";
						system("pause");
						userfile.close();
					}
				}
			} 
		}
	}
}

bool CNICcheck(string cnic)
{
	// 33100-0235986-7
	if (cnic.at(5) == '-' && cnic.at(13) == '-' && cnic.length() == 15)
		return true;
	cout << "Invalid CNIC!\n";
	return false;
}
