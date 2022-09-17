#pragma once

#include "node.h"

template <class T, class T2>
class List
{
public:
	List();
	~List();
	ListNode<T, T2>* getHeadPtr() const;
	void setHeadPtr(string newData);
	bool insertAtFront(ListNode<T, T2>* newData);
	bool isEmpty();

	void loadList(ifstream& infile);
    T getnumName(int n);
    T2 getdescName(int n);
    bool searchList(string name);

private:
	ListNode<T, T2>* mpHead;

	ListNode<T, T2>* makeNode(const string newData);
	void destroyList();
	void destroyList(ListNode<T, T2>* const pMem);
};

template <class T, class T2>
List<T, T2>::List()
{
	mpHead = nullptr;
};

template <class T, class T2>
List<T, T2>::~List()
{
	destroyList();
};

template <class T, class T2>
ListNode<T, T2>* List<T, T2>::getHeadPtr() const
{
	return mpHead;
};

template <class T, class T2>
bool List<T, T2>::insertAtFront(ListNode<T, T2>* newData)
{
	bool success = false;

	if (newData != nullptr)
	{
		success = true;
		newData->setNextPtr(mpHead);
		mpHead = newData;
	}

	return success;
};

template <class T, class T2>
bool List<T, T2>::isEmpty()
{
	return (mpHead == nullptr);
};

template <class T, class T2>
void List<T, T2>::setHeadPtr(string newData)
{
	mpHead = makeNode(newData);
};

template <class T, class T2>
ListNode<T, T2>* List<T, T2>::makeNode(const string newData)
{
	ListNode<T, T2>* pMem = new ListNode<T, T2>(newData);
	return pMem;
};

template <class T, class T2>
void List<T, T2>::destroyList(ListNode<T, T2>* const pMem)
{
	if (pMem != nullptr)
	{
		destroyList(pMem->getNextPtr());
		delete pMem;
	}
};

template <class T, class T2>
void List<T, T2>::destroyList()
{
	destroyList(mpHead);
};

template <class T, class T2>
void List<T, T2>::loadList(ifstream& infile)
{
	string line;

	while (!infile.eof())
	{
		getline(infile, line);
		ListNode<T, T2>* pNew = new ListNode<T, T2>(line);
		insertAtFront(pNew);
	}
};

template <class T, class T2>
T List<T, T2>::getnumName(int n)
{
    int counter = 1;
    ListNode<T, T2>* temp = mpHead;
    if (temp != NULL) 
    {
        while (temp != NULL)
        {
            if (counter == n)
            {
                return temp->getName();
            }
            counter += 1;
            temp = temp->getNextPtr();
        }
    }
    return "ERROR";
};

template <class T, class T2>
T2 List<T, T2>::getdescName(int n)
{
    int counter = 1;
    ListNode<T, T2>* temp = mpHead;
    if (temp != NULL) 
    {
        while (temp != NULL)
        {
            if (counter == n)
            {
                return temp->getDesc();
            }
            counter += 1;
            temp = temp->getNextPtr();
        }
    }
    return "ERROR";
};

template <class T, class T2>
bool List<T, T2>::searchList(string name)
{
    ListNode<T, T2>* temp = mpHead;
    while (temp != NULL)
    {
        if (temp->getName() == name)
        {
            return true;
        }
        temp = temp->getNextPtr();
    }
    return false;
};
