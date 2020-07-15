#ifndef _NODE_H
#define _NODE_H
#pragma warning (disable:4996)
#include <iostream>
using namespace std;
class Node
{
private:
	int m_Data;
	Node* m_Next;

public:
	Node(const int i_Item);
	Node(Node* i_Ptr, const int i_Item);
	~Node();
	int GetData() const;
	Node* GetNext() ;
	void SetNext(Node* i_Ptr);
	void InsertAfter(Node* newnode);
	Node* DeleteAfter();
	friend ostream& operator<<(ostream& i_os, const Node& i_obj);
};

#endif // !_NODE_H