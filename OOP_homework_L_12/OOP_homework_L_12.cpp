//Create a telephone number based on a doubly linked list
//reference book for the following operations :
//- Adding subscribers to the base.
//- Removing subscribers from the base.
//- Modification of subscriber data.
//- Search for subscribers by phone number or surname.
//- Listing subscribers in alphabetical order.
//- Saving the database to a file.
//- Loading base from file.

#include <iostream>
#include <conio.h>
#include "Phonebook.h"
using namespace std;

int main()
{
	Phonebook book;
	Subscriber sub;
	int input = 0;
	while (input != 6)
	{
		system("cls");
		cout << "1.Check the list " << endl;
		cout << "2.Load the list " << endl;
		cout << "3.Save the list" << endl;
		cout << "4.Add the subscriber" << endl;
		cout << "5.Search the subscriber (del/ mod)" << endl;
		cout << "6.Exit" << endl;
		input = _getch() - 48;
		switch (input)
		{
		case 1:
			system("cls");
			cout << "1.Check the list " << endl;
			book.Sort();
			book.Print();
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "2.Load the list " << endl;
			book.Load();
			cout << "Completed !";
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "3.Save the list" << endl;
			book.Save();
			cout << "Completed !";
			system("pause");
			break;
		case 4:
			system("cls");
			cout << "4.Add the subscriber" << endl;
			cin >> sub;
            book.AddSubscriber(sub);
			cout << "Completed !";
			system("pause");
			break;
		case 5:
			int input_case5 = 0;
			char name_or_phone[30]{};
			Subscriber sub_case5;
			while (input_case5 != 3)
			{
				system("cls");
				cout << "5.Search the subscriber (del/ mod)" << endl << endl;
				cout << "Enter the name or phone : ";
				if (cin.peek() == '\n')
					cin.get();
				cin.getline(name_or_phone, 29);
				sub_case5 = name_or_phone;
				sub = book.Search(sub_case5);
				if ((strcmp(sub_case5.Name, sub.Name)) == 0 || (strcmp(sub_case5.Phone, sub.Phone)) == 0)
				{
					cout << sub << endl << endl;
					cout << "1.Modify the subscriber" << endl;
					cout << "2.Delete the subscriber" << endl;
					int mod_del;
					Subscriber sub_mod;
					mod_del = _getch() - 48;
					switch (mod_del)
					{
					case 1:
						system("cls");
						cout << sub << endl << endl;
						cin >> sub_mod;
						book.ModSubscriber(sub, sub_mod);
						cout << "Completed !";
						system("pause>>NUL");
						break;
					case 2:
						system("cls");
						book.DelSubscriber(sub);
						cout << "Completed !";
						system("pause>>NUL");
						break;
					}
					system("cls");
					break;
				}
				else
				{
					cout << "Subscriber not found !";
					system("pause>>NUL");
					break;
				}
			}

		}
	}
	return 0;
}