#pragma once

#include <iostream>
#include <string>

using namespace std;
class user
{
protected:
	bool admin;
public:
	string name;
	user(string name);
	~user(void);
	void set_rignts();     //�������� ����� ��������������
	bool get_adm();        //������� ����� ������������
	user& operator=(user&);//����������
};

user::user(string name)
{
	this->admin = false;
	this->name = name;
}

user::~user(void)
{

}

void user::set_rignts()
{
	this->admin = true;
}

bool user::get_adm()
{
	return this->admin;
}

user& user::operator=(user& us)//���������� ��������� 
{
	name = us.name;
	this->admin = us.admin;
	return *this;//���������� ������ �� ������� ������
}