#ifndef ELECTION_COMMISION
#define ELECTION_COMMISION

using namespace std;

#endif // !ELECTION_COMMISION

class ElectionCommision
{
public:
	void EC_Login();
protected:
	
private:
	string pass;
};
void RegisterPP();
void RegisterCandidate();
void RegisterConstituency();
void RegisterVoter();
void EC_Interface();
void DisplayConstituencies();
void Delete();
bool CNICcheck(string cnic);
#pragma once
