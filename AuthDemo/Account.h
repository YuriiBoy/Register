#pragma once


class Account
{
	int id;
	TCHAR login[100];
	TCHAR pasww[100];
	TCHAR name[100];
	TCHAR surname[100];
	TCHAR registry[100];
	TCHAR role[100];
	TCHAR status[100];
public:
	Account();
	Account(int id, TCHAR login[100], TCHAR pasww[100], TCHAR name[100],
	TCHAR surname[100], TCHAR registry[100], TCHAR role[100], TCHAR status[100]);
	int getId();
	TCHAR* getLogin();
	TCHAR* getPasww();
	TCHAR* gretName();
	TCHAR* getSurname();
	TCHAR* getRegistry();
	TCHAR* getRole();
	TCHAR* getStatus();
};
