#pragma once

#include "file.h"
#include "simlink.h"

using namespace std;


class directory : public parent {
	vector <string> inf;
public:
	vector <file*> fil;
	vector <directory*> dir;
	vector <simlink*> sim;

	directory(string, vector<user*>);
	~directory();
	string getname() { return name; };
	void del() { (*this).~directory(); }
	void add_file(user, file*);
	void add_directory(user, directory*);
	void add_simlink(user, simlink*);
	void show();
	void deletedir(string);
	file* findfile(string);
	directory copy(string user);
};

directory::directory(string dname = "default", vector<user*> user) :
	parent(dname, user) {}

directory::~directory() { fil.~vector(); dir.~vector(); sim.~vector(); cout << "dctor directory"; }

void directory::add_file(user us, file* f)
{
	int k = 0;
	while ((k < f->users.size()) && (us.name != f->users[k]->name))
		k++;
	if ((k != f->users.size()) || (us.get_adm == true))
		fil.push_back(f);
	else
		throw "�� ������ �����";
}

void directory::add_simlink(user us, simlink* siml) 
{
	int k = 0;
	while ((k < f->users.size()) && (us.name != f->users[k]->name))
		k++;
	if ((k != f->users.size()) || (us.get_adm == true))
		fil.push_back(f);
	else
		throw 404;
}

void directory::add(string user) {
	char command[10];
	string name;
	string dat;

	cout << "�������� ���� - fil" << endl;
	cout << "�������� ������������� ������ - sim" << endl;
	cout << "�������� ����� - dir" << endl;

	scanf("%s", &command);
	switch (command[0]) {
	case 'f':
	{
		cout << "name of file: ";
		cin >> name;
		cout << "text: ";
		cin >> dat;
		file* f = new file(user, name, dat);
		fil.push_back(f);
	}
	break;

	case 's':
	{
		cout << "name of simlink: ";
		cin >> name;
		cout << "������� ��� ����� �� ������� ������ ���������" << endl;
		string fname;
		cin >> fname;
		file* f = findfile(fname);
		simlink* s = new simlink(user, f, name);
		sim.push_back(s);
	}
	break;

	case 'd':
	{
		cout << "name of directory: ";
		cin >> name;
		directory* d = new directory(user, name);
		dir.push_back(d);
	}
	break;

	default:
		break;
	}
}

void directory::show() {
	cout << "files: " << endl;
	if (fil.size() == 0)
		cout << "empty" << endl;
	else
		for (int i = 0; i < fil.size(); i++) {
			cout << fil[i]->getname() << endl;
		}

	cout << "simlinks: " << endl;
	if (sim.size() == 0)
		cout << "empty" << endl;
	else
		for (int i = 0; i < sim.size(); i++) {
			cout << sim[i]->getname() << endl;
			cout << "����, �� ������� ��������� ������" << endl;
			cout << sim[i]->link->name << endl;
		}

	cout << "directories: " << endl;
	if (dir.size() == 0)
		cout << "empty" << endl;
	else
		for (int i = 0; i < dir.size(); i++) {
			cout << dir[i]->getname() << endl;
		}
}

void directory::deletedir(string name) { //�������� ���������� 

	for (int i = 0; i < fil.size(); i++)
		fil[i]->del();

	for (int i = 0; i < sim.size(); i++)
		sim[i]->del();

	for (int i = 0; i < dir.size(); i++)
		if (dir.size() == 0)
			del();
		else
			deletedir(dir[i]->getname());
}

file* directory::findfile(string name) {  //����� ����� � ����� ���������
	for (int i = 0; i < fil.size(); i++)
		if (fil[i]->name == name) {
			return fil[i];
		}
	for (int i = 0; i < dir.size(); i++)
		if (dir[i]->findfile(name))
			return dir[i]->findfile(name);
	return 0;
}

directory directory::copy(string user) { //����� ����������
	directory d(user);
	for (int i = 0; i < dir.size(); i++) {
		d.dir[i] = dir[i];
	}
	for (int i = 0; i < sim.size(); i++) {
		d.sim[i] = sim[i];
	}
	for (int i = 0; i < fil.size(); i++) {
		d.fil[i] = fil[i];
	}
	return d;
}