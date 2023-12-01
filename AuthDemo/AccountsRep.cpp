#include "framework.h"
#include "AccountsRep.h"

void AccountsRep::loadData()
{
	// 1
	int id;
	TCHAR login[100];
	TCHAR pasww[100];
	TCHAR name[100];
	TCHAR surname[100];
	TCHAR registry[100];
	TCHAR role[100];
	TCHAR status[100];
	char buff[100];
	// 2
	std::ifstream fin;
	fin.open("Accounts.txt");

	while (!fin.eof())	{
		fin >> buff;
		if (strlen(buff) > 0) {
			id = atoi(buff);
			//
			fin >> buff;
			mbstowcs_s(NULL, login, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, pasww, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, name, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, surname, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, registry, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, role, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, status, 100, buff, 100);
			//
			Account a(id, login, pasww, name, surname, registry, role, status);
			accounts.push_back(a);
		}
	}

	// 3
	fin.close();
}

bool AccountsRep::authCheck(TCHAR login[], TCHAR pasww[])
{
	auto iter = std::find_if(accounts.begin(), accounts.end(),
		[login, pasww](Account& a) { 
			return (lstrcmp(a.getLogin(), login) == 0 && 
				lstrcmp(a.getPasww(), pasww) == 0);
		});
	bool temp = (iter != accounts.end());
	if (temp == true) {
		lstrcpy(userName, iter->gretName());
		lstrcpy(userSurname, iter->getSurname());
	}
	return (temp);
}

void AccountsRep::registry()
{
}

TCHAR* AccountsRep::getUserName()
{
	return userName;
}

TCHAR* AccountsRep::getUserSurname()
{
	return userSurname;
}
