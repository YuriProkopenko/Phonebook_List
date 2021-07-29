#pragma once
#include "DList.h"

struct Subscriber
{
	char Name[30]{};
	char Phone[30]{};
	char Start_license[30]{};
	int License_duration = 0;
	bool operator == (Subscriber sub);
	bool operator != (Subscriber sub);
	Subscriber operator = (Subscriber sub);
	Subscriber operator = (char* word);
	bool operator < (Subscriber sub);
	bool operator > (Subscriber sub);
};

istream& operator >> (istream& cin, Subscriber& sub);

ostream& operator << (ostream& cout, Subscriber& sub);

class Phonebook
{
	List <Subscriber> List;
public:
	Phonebook() {}
	Phonebook(const Phonebook& book);
	~Phonebook() {}
	void AddSubscriber(const Subscriber sub);
	void DelSubscriber(Subscriber sub);
	void ModSubscriber(Subscriber past, Subscriber future);
	Subscriber Search(Subscriber sub);
	void Sort();
	void Print();
	Phonebook& operator = (const Phonebook& book);
	void Save();
	void Load();
};