#include <iostream>
#include "Phonebook.h"
using namespace std;

bool Subscriber::operator < (Subscriber sub)
{
	if (strcmp(this->Name, sub.Name) < 0)
		return true;
	else
		return false;
}

bool Subscriber::operator > (Subscriber sub)
{
	if (strcmp(this->Name, sub.Name) >= 0)
		return false;
	else
		return true;
}

Subscriber Subscriber::operator = (Subscriber sub)
{
	strcpy_s(this->Name , sub.Name );
	strcpy_s(this->Phone, sub.Phone );
	strcpy_s(this->Start_license, sub.Start_license );
	this->License_duration = sub.License_duration;
	return *this;
}

Subscriber Subscriber::operator = (char* word)
{
	strcpy_s(this->Name, word );
	strcpy_s(this->Phone, word );
	strcpy_s(this->Start_license, word );
	return *this;
}


bool Subscriber::operator == (Subscriber sub)
{
	if ((strcmp(this->Name, sub.Name)) == 0 || (strcmp(this->Phone, sub.Phone)) == 0)
		return true;
	else
		return false;
}

bool Subscriber::operator != (Subscriber sub)
{
	if ((strcmp(this->Name, sub.Name)) != 0)
		return true;
	else
		return false;
}

istream& operator >> (istream& is, Subscriber& sub)
{
	cout << "Name : ";
	if (cin.peek() == '\n')
		cin.get();
	is.getline(sub.Name, 30);
	cout << "Phone : ";
	is >> sub.Phone;
	cout << "Start_license : ";
	is >> sub.Start_license;
	cout << "License_duration : ";
	is >> sub.License_duration;
	return is;
}

ostream& operator << (ostream& os, Subscriber& sub)
{
	os << "\t\t\t\t" << sub.Phone << '\t' << sub.Start_license << '\t' << sub.License_duration << '\r' << sub.Name << endl;
	return os;
}

Phonebook::Phonebook(const Phonebook& book)
{
	this->List = book.List;
}

void Phonebook::AddSubscriber(const Subscriber sub)
{
	List.AddTail(sub);
}

void Phonebook::DelSubscriber(Subscriber sub)
{
	Subscriber search_sub = Search(sub);
	List.DelElementByKey(search_sub);
}

void Phonebook::ModSubscriber(Subscriber past, Subscriber future)
{
	int checker = List.Find(past);
	List.Replace(future, checker);
}

Subscriber Phonebook::Search(Subscriber sub)
{
	int checker = List.Find(sub);
	Subscriber s_sub;
	if (checker > 0)
	{
		s_sub = List.operator[](checker - 1);
		return s_sub;
	}
	else
		return s_sub;
}

void Phonebook::Sort()
{
	List.Sort();
}

void Phonebook::Print()
{
	List.PrintHead();
}

Phonebook& Phonebook::operator = (const Phonebook& book)
{
	this->List = book.List;
	return *this;
}

void Phonebook::Save()
{
	char filename[100];
	cout << "Enter file path : ";
	cin >> filename;
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");
	if (file == nullptr)
	{
		perror(NULL);
		system("pause>>NUL");
		return;
	}
	int size_GC = List.GetCount();
	fwrite(&size_GC, sizeof(int), 1, file);
	for (int i = 0; i < List.GetCount(); i++)
	{
		Elem<Subscriber>* s_elem = List.GetElem(i + 1);
		int size_n = size(s_elem->data.Name) + 1;
		fwrite(&size_n, sizeof(int), 1, file);
		fwrite(&s_elem->data.Name, sizeof(char), size_n, file);
		int size_Ph = size(s_elem->data.Phone) + 1;
		fwrite(&size_Ph, sizeof(int), 1, file);
		fwrite(&s_elem->data.Phone, sizeof(char), size_Ph, file);
		int size_Sl = size(s_elem->data.Start_license) + 1;
		fwrite(&size_Sl, sizeof(int), 1, file);
		fwrite(&s_elem->data.Start_license, sizeof(char), size_Sl, file);
		int size_Ld = s_elem->data.License_duration;
		fwrite(&size_Ld, sizeof(int), 1, file);
	}
	fclose(file);
}

void Phonebook::Load()
{
		char filename[100];
		cout << "Enter file path : ";
		cin >> filename;
		FILE* file = nullptr;
		fopen_s(&file, filename, "rb");
		if (file == nullptr)
		{
			perror(NULL);
			system("pause>>NUL");
			return;
		}
		List.DelAll();
		Subscriber l_subs;
		int size_GC;
		fread(&size_GC, sizeof(int), 1, file);
		for (int i = 0; i < size_GC; i++)
		{
			int size_ln;
			fread(&size_ln, sizeof(int), 1, file);
			fread(&l_subs.Name, sizeof(char), size_ln, file);
			int size_lPh;
			fread(&size_lPh, sizeof(int), 1, file);
			fread(&l_subs.Phone, sizeof(char), size_lPh, file);
			int size_lln;
			fread(&size_lln, sizeof(int), 1, file);
			fread(&l_subs.Start_license, sizeof(char), size_lln, file);
			fread(&l_subs.License_duration, sizeof(int), 1, file);
			List.AddHead(l_subs);
		}
		fclose(file);
}