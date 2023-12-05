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

void AccountsRep::registry(TCHAR login[], TCHAR pasww[], TCHAR name[],
	TCHAR surname[], TCHAR role[], TCHAR status[])
{

	int id = 0;
	TCHAR registry[100];
	char buff;
	std::ofstream fout;
	fout.open("Accounts.txt", std::ios_base::app);
	
	fout << id;
	//mbstowcs(null, login, 100, buff, 100);
	fout << login << std::endl;
	fout << pasww << std::endl;
	fout << name << std::endl;
	fout << surname << std::endl;
	fout << "date" << std::endl;
	fout << role << std::endl;
	fout << status << std::endl;

	Account a(id, login, pasww, name, surname, registry, role, status);
	accounts.push_back(a);

	fout.close();
	
}


TCHAR* AccountsRep::getUserName()
{
	return userName;
}

TCHAR* AccountsRep::getUserSurname()
{
	return userSurname;
}

TCHAR* AccountsRep::getUserTel()
{
	return userTel;
}

TCHAR* AccountsRep::getUserLog()
{
	return userLog;
}

TCHAR* AccountsRep::getUserPasw()
{
	return userPasw;
}



TCHAR* AccountsRep::getUserRole()
{
	return userRole;
}

TCHAR* AccountsRep::getUserStatus()
{
	return userStatus;
}
