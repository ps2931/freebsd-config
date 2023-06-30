#include<iostream>
using namespace std;

class Node
{
private:
	int data;
	Node* prev;
	Node* next;

	Node(int data_)
	{
		data=data_;
		prev=NULL;
		next=NULL;
	}

};

//Time: O(1)
//Space: O(1)
Node* insertAtHead(Node* head, int key)
{
	Node* n = new Node(key);

	if(head == NULL)
	{
		return n;
	}

	n->next = head;
	head->prev = n;

	return n;
}

//Time: O(N)
//Space: O(1)
Node* insertAtTail(Node* head,int key)
{
	Node* n = new Node(key);

	if(head == NULL)
	{
		return n;
	}

	//traverse to last node
	Node* curr = head;
	while(curr->next)
	{
		curr=curr->next;
	}

	curr->next = n;
	n->prev = curr;

	return head;
}

//Time: O(N)
//Space: O(1)
Node* reverse(Node* &head)
{
	if(head==NULL or head->next==NULL)
	{
		return head;
	}

	Node* temp=NULL;
	Node* curr=head;

	while(curr)
	{
		temp=curr->prev;
		curr->prev=curr->next;
		curr->next=temp;
		curr=curr->prev;
	}

	return temp->prev;
}

//Time: O(1)
//Space: O(1)
Node* deleteAtHead(Node* &head)
{
	if(head==NULL)
	{
		return NULL;
	}

	if(head->next==NULL)
	{
		delete head;
		return NULL;
	}

	Node* curr=head;
	head=head->next;
	head->prev=NULL;
	delete curr;

	return head;
}

//Time: O(N)
//Space: O(1)
Node* deleteAtTail(Node* &head)
{
	if(head==NULL)
	{
		return NULL;
	}

	if(head->next==NULL)
	{
		delete head;
		return NULL;
	}

	//traverse to second last node
	Node* curr=head;
	while(curr->next->next)
	{
		curr=curr->next;
	}

	delete curr->next;
	curr->next=NULL;

	return head;
}

//Time: O(N)
//Space: O(1)
void print(Node* head)
{
	while(head)
	{
		cout<<head->data<<" ";
		head=head->next;
	}
	cout<<endl;
}

int main()
{
	Node* head=new Node(10);
	Node* node2=new Node(20);
	Node* node3=new Node(30);

	head->next=node2;
	node2->next=node3;

	node2->prev=head;
	node3->prev=node2;

	print(head);
	return 0;
}
