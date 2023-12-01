#pragma once
#include "Account.h"
#include <xkeycheck.h>

class AccountsRep
{
	std::vector<Account> accounts;
	TCHAR userName[100];
	TCHAR userSurname[100];
public:
	void loadData();
	bool authCheck(TCHAR login[], TCHAR pasww[]);
	void registry();
	TCHAR* getUserName();
	TCHAR* getUserSurname();
};

