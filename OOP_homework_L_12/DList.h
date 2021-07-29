#pragma once;
#include <iostream>
using namespace std;

template <class T>
struct Elem
{
	T data;
	Elem* next, * prev;
	Elem operator = (Elem elem)
	{
		this->data = elem.data;
		return *this;
	}
};

template <class T>
class List
{
	Elem<T>* Head, * Tail;
	int Count;
public:
	List();
	List(const List&);
	~List();
	int GetCount();
	Elem<T>* GetElem(int);
	void DelAll();
	void Del(int pos);
	void Insert(T data, int pos);
	void AddTail(T data);
	void AddHead(T data);
	void DelHead();
	void DelTail();
	void PrintHead();
	void PrintTail();
	List& operator = (const List&);
	int Find(T key);
	void Replace(T value, int position);
	void DelElementByKey(T key);
	T& operator[](int position);
	void Sort();
};

template <class T>
List<T>::List()
{
	Head = Tail = nullptr;
	Count = 0;
}

template <class T>
List<T>::List(const List<T>& L)
{
	Head = Tail = nullptr;
	Count = 0;
	Elem<T>* temp = L.Head;
	while (temp != nullptr)
	{
		AddTail(temp->data);
		temp = temp->next;
	}
}

template <class T>
List<T>::~List()
{
	DelAll();
}

template <class T>
void List<T>::AddHead(T data)
{
	Elem<T>* temp = new Elem<T>;
	temp->prev = nullptr;
	temp->data = data;
	temp->next = Head;
	if (Head != nullptr)
		Head->prev = temp;
	Head = temp;
	if (Tail == nullptr)
		Tail = temp;
	Count++;
}

template <class T>
void List<T>::AddTail(T data)
{
	Elem<T>* temp = new Elem<T>;
	temp->next = nullptr;
	temp->data = data;
	temp->prev = Tail;
	if (Tail != nullptr)
		Tail->next = temp;
	Tail = temp;
	if (Head == nullptr)
		Head = temp;
	Count++;
}

template <class T>
void List<T>::DelHead()
{
	if (Head != nullptr)
	{
		Elem<T>* temp = Head;
		Head = Head->next;
		if (Head != nullptr)
			Head->prev = nullptr;
		else
			Tail = nullptr;
		delete temp;
		Count--;
	}
}

template <class T>
void List<T>::DelTail()
{
	if (Tail != nullptr)
	{
		Elem<T>* temp = Tail;
		Tail = Tail->prev;
		if (Tail != nullptr)
			Tail->next = nullptr;
		else
			Head = nullptr;
		delete temp;
		Count--;
	}
}

template <class T>
void List<T>::Insert(T data, int pos)
{
	if (pos < 0 || pos > Count)
		return;
	if (pos == 0)
	{
		AddHead(data);
		return;
	}
	if (pos == Count)
	{
		AddTail(data);
		return;
	}
	Elem<T>* current = nullptr;
	if (pos < Count / 2)
	{
		current = Head;
		int i = 0;
		while (i < pos)
		{
			current = current->next;
			i++;
		}
	}
	else
	{
		current = Tail;
		int i = Count - 1;
		while (i > pos)
		{
			current = current->prev;
			i--;
		}
	}
	Elem<T>* temp = new Elem<T>;
	temp->data = data;
	temp->prev = current->prev;
	temp->next = current;
	current->prev->next = temp;
	current->prev = temp;
	Count++;
}

template <class T>
void List<T>::Del(int pos)
{
	if (pos < 0 || pos >= Count)
		return;
	if (pos == 0)
	{
		DelHead();
		return;
	}
	if (pos == Count - 1)
	{
		DelTail();
		return;
	}
	Elem<T>* delElement = nullptr;
	if (pos < Count / 2)
	{
		delElement = Head;
		int i = 0;
		while (i < pos)
		{
			delElement = delElement->next;
			i++;
		}
	}
	else
	{
		delElement = Tail;
		int i = Count - 1;
		while (i > pos)
		{
			delElement = delElement->prev;
			i--;
		}
	}
	delElement->prev->next = delElement->next;
	delElement->next->prev = delElement->prev;
	delete delElement;
	Count--;
}

template <class T>
void List<T>::PrintHead()
{
	Elem<T>* current = Head;
	while (current != nullptr)
	{
		cout << current->data;
		current = current->next;
	}
}

template <class T>
void List<T>::PrintTail()
{
	Elem<T>* current = Tail;
	while (current != nullptr)
	{
		cout << current->data;
		current = current->prev;
	}
}

template <class T>
void List<T>::DelAll()
{
	while (Head != nullptr)
		DelHead();
}

template <class T>
int List<T>::GetCount()
{
	return Count;
}

template <class T>
Elem<T>* List<T>::GetElem(int pos)
{
	Elem<T>* temp = Head;
	if (pos < 0 || pos > Count)
		return nullptr;
	int i = 1;
	while (i < pos)
	{
		temp = temp->next;
		i++;
	}
	return temp;
}

template <class T>
List<T>& List<T>::operator = (const List<T>& L)
{
	if (this == &L)
		return *this;
	DelAll();
	Elem<T>* temp = L.Head;
	while (temp != nullptr)
	{
		AddTail(temp->data);
		temp = temp->next;
	}
	return *this;
}

template <class T>
int List<T>::Find(T key)
{
	if (Head)
	{
		Elem<T>* temp = Head;
		int count = 1;
		for (int i = 0; i < Count; i++)
		{
			if (temp->data == key)
				return count;
			temp = temp->next;
			count++;
		}
		return -1;
	}
	else
		return -1;

}

template <class T>
void List<T>::Replace(T value, int position)
{
	if (position <= Count / 2 && Head)
	{
		Elem<T>* temp = Head;
		for (int i = 0; i < position - 1; i++)
		{
			temp = temp->next;
		}
		temp->data = value;
	}
	else if (position > Count / 2 && Tail)
	{
		Elem<T>* temp = Tail;
		for (int i = Count; i > position; i--)
		{
			temp = temp->prev;
		}
		temp->data = value;
	}
}

template <class T>
void List<T>::DelElementByKey(T key)
{
	if (Head)
	{
		Elem<T>* temp_h = Head;
		while (temp_h != nullptr)
		{
			if (temp_h->next == 0 && temp_h->data != key)
				Tail = temp_h;
			else if(temp_h->next == 0 && temp_h->data == key)
				Tail = temp_h->prev;
			if (Head->prev == nullptr && Head->data == key)
			{
				temp_h = temp_h->next;
				DelHead();
			}
			else if (temp_h->data == key)
			{
				temp_h->prev->next = temp_h->next;
				if (temp_h->next != nullptr)
					temp_h->next->prev = temp_h->prev;
				Elem<T>* temp_del = temp_h;
				temp_h = temp_h->next;
				delete temp_del;
				Count--;
			}
			else
				temp_h = temp_h->next;
		}
	}
	else
		return;
}

template <class T>
T& List<T>::operator [](int position)
{
	Elem<T>* temp = GetElem(position + 1);
	return temp->data;
}

template <class T>
void List<T>::Sort()
{
	if (Head)
	{
		Elem<T>* temp = Head;
		Elem<T>* temper = Head->next;
		T trial;
		int count = 0;
		for (int i = 0; i < Count - 1; i++)
		{
			for (int j = count; j < Count - 1; j++)
			{
				if (temper->data < temp->data)
				{
					trial = temp->data;
					temp->data = temper->data;
					temper->data = trial;
				}
				temper = temper->next;
			}
			temp = temp->next;
			temper = temp->next;
			count++;
		}
	}
	else
		return;
}