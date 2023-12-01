#include "framework.h"
#include "Account.h"


Account::Account() : id(0)
{
	lstrcpy(this->login, L"-");
	lstrcpy(this->pasww, L"-");
	lstrcpy(this->name, L"-");
	lstrcpy(this->surname, L"-");
	lstrcpy(this->registry, L"-");
	lstrcpy(this->role, L"-");
	lstrcpy(this->status, L"-");
}

Account::Account(int id, TCHAR login[100], TCHAR pasww[100], TCHAR name[100], TCHAR surname[100], TCHAR registry[100], TCHAR role[100], TCHAR status[100])
{
	lstrcpy(this->login, login);
	lstrcpy(this->pasww, pasww);
	lstrcpy(this->name, name);
	lstrcpy(this->surname, surname);
	lstrcpy(this->registry, registry);
	lstrcpy(this->role, role);
	lstrcpy(this->status, status);
}

int Account::getId()
{
	return id;
}

TCHAR* Account::getLogin()
{
	return login;
}

TCHAR* Account::getPasww()
{
	return pasww;
}

TCHAR* Account::gretName()
{
	return name;
}

TCHAR* Account::getSurname()
{
	return surname;
}

TCHAR* Account::getRegistry()
{
	return registry;
}

TCHAR* Account::getRole()
{
	return role;
}

TCHAR* Account::getStatus()
{
	return status;
}
