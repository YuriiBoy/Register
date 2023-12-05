#pragma once
#include "Account.h"
#include <xkeycheck.h>

class AccountsRep
{
	std::vector<Account> accounts;
	TCHAR userName[100];
	TCHAR userSurname[100];
	TCHAR userTel[100];
	TCHAR userLog[100];
	TCHAR userPasw[100];
	TCHAR userRole[100];
	TCHAR userStatus[100];
public:
	void loadData();
	bool authCheck(TCHAR login[], TCHAR pasww[]);
	void registry( TCHAR login[], TCHAR pasww[], TCHAR name[], TCHAR surname[],
		TCHAR role[], TCHAR status[]);
	TCHAR* getUserName();
	TCHAR* getUserSurname();
	TCHAR* getUserTel();
	TCHAR* getUserLog();
	TCHAR* getUserPasw();
	TCHAR* getUserRole();
	TCHAR* getUserStatus();
};

