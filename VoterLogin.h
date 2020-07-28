#ifndef VOTER_LOGIN
#define VOTER_LOGIN

using namespace std;
string Filename();
class VoterLogin
{
public:
	VoterLogin();
	void Login();
protected:
	string cnic, pass, date_of_birth, pass2, province, district, fname, lname;
	int search2;
	string dir = Filename();
	string line;
	int search;
	char op;
	bool exist;
private:
	
	

};

void CandidatesList(char);
bool UsernameCheck(string);
bool PasswordCheck(string);
bool PassCrossCheck(string, string);
void LoginInterface(string,string,string);
void CastVote(string,string,string);
//void CandidatesList(char);
#endif // !VOTER_LOGIN

#pragma once
