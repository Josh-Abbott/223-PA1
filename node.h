#pragma once

#include "functions.h"

template <class T, class T2>
class ListNode
{
public:
	ListNode(string line);
	~ListNode();

	T getName() const;
    T2 getDesc() const;
	ListNode<T, T2>* getNextPtr() const;

	void setName(const T newName);
    void setDesc(const T2 newDesc);
	void setNextPtr(ListNode<T, T2>* const newNext);

private:
	T name;
    T2 desc;
	ListNode<T, T2>* mpNext;
};

template <class T, class T2>
ListNode<T, T2>::ListNode(string line)
{
	string name, input;
	stringstream newLine(line); // ?

	getline(newLine, input, ',');

	if (input != "")
	{
		setName(input);
        getline(newLine, input, ',');
        setDesc(input);
	}
};

template <class T, class T2>
ListNode<T, T2>::~ListNode()
{

};

template <class T, class T2>
T ListNode<T, T2>::getName() const
{
	return name;
};

template <class T, class T2>
T2 ListNode<T, T2>::getDesc() const
{
	return desc;
};

template <class T, class T2>
ListNode<T, T2>* ListNode<T, T2>::getNextPtr() const
{
	return mpNext;
};

template <class T, class T2>
void ListNode<T, T2>::setName(const T newName)
{
	name = newName;
};

template <class T, class T2>
void ListNode<T, T2>::setDesc(const T2 newDesc)
{
	desc = newDesc;
};

template <class T, class T2>
void ListNode<T, T2>::setNextPtr(ListNode<T, T2>* const newNext)
{
	mpNext = newNext;
};