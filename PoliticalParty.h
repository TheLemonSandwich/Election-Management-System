#ifndef POLITICAL_PARTY
#define POLITICAL_PARTY
#include "VoterLogin.h"
using namespace std;
class PoliticalParty : public VoterLogin
{
public:
	void Login();
protected:
	string partyname;
private:
	string dir = Filename();
	
};
void PartyInterface(string);
void Decide(string);
#endif // !POLITICAL_PARTY

