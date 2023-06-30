#include <iostream>
#include <malloc.h>
using namespace std;

// https://github.com/memr5/Data-Structures/blob/master/Linked-List/Circular-Doubly-List.c
// https://github.com/BaseMax/CircularDoublyLinkedListC/blob/main/CircularDoublyLinkedList.c

struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node* head=NULL;

struct node* createNewNode(int data) {
    struct node *n = nullptr;
    n = (struct node*) malloc(sizeof(node));
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/*
 * Insert a new node at the end of the list
 */
void insertAtEnd(int value) {
    struct node* new_node = createNewNode(value);
    new_node->data = value;
    if(head == NULL) {
        new_node->next = new_node;
        head = new_node;
        new_node->prev = new_node;
    } else {
        struct node *temp = head->prev;
        head->prev = new_node;
        new_node->prev = temp;
        new_node->next = head;
        temp->next = new_node;
    }
}

/*
 * Insert a new node at the beginning of the list
 */
void insertAtBeginning(int value) {
    struct node* new_node = createNewNode(value);
    if(!head) { // if list is empty
        head = new_node;
        new_node->next = head;
        new_node->prev = head;
        return;
    }
    struct node *temp = head->prev;
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
    temp->next = new_node;
    new_node->prev = temp;
}

/*
 * Insert after a given element after the key
*/
void insertAfter(int key, int element) {
    if(head == NULL) {
        cout << "\nEmpty list\n";
        return;
    }
    else {
        struct node* temp = head->next;
        if(head->data == key) {
            struct node* new_node = createNewNode(element);
            new_node->next = head->next;
            head->next = new_node;
            new_node->prev = head;
            new_node->next->prev = new_node;
            return;
        }
        while(temp != head && temp->data != key) {
            temp = temp->next;
        }

        if(temp == head) {
            cout << "\nKey not found in the list!\n";
        }
        else {
            struct node* new_node = createNewNode(element);
            new_node->next = temp->next;
            temp->next = new_node;
            new_node->prev = temp;
            new_node->next->prev = new_node;
        }
    }
}

/*
 * Delete a node
 */

void deleteNode(int value) {
    if(head==NULL){
		cout << "\nList is Empty!\n";
		return;
	}
    else{
        if(head->data==value) {
            if(head->next==head) {
                head=NULL;
            }
            else{
                struct node* temp = head->prev;
                head=head->next;
                head->prev=temp;
                temp->next=head;
            }
            return;
        }

        struct node* temp=head->next;
        while(temp!=head && temp->data!=value) {
            temp=temp->next;
        }

        if(temp==head) {
            cout << "Value not in the list\n";
        }
        else {
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
        }
    }
}

/*
 * Display list elements
 */
void displayList() {
    if(head == NULL) {
        cout << "\nEmpty list!\n";
        return;
    }
    else {
        struct node *temp = head->next;
        cout << "\t" << head->data;
        while(temp != head) {
            cout << "\t" << temp->data;
            temp = temp->next;
        }
    }
}

int main() {

    int option;
    int value;
    do {
        cout << "\n*****MAIN MENU*****";
        cout << "\n 1. Insert at end";
        cout << "\n 2. Insert at the beginning";
        cout << "\n 3. Insert after an element";
        cout << "\n 4. Display the list";
        cout << "\n 5. Delete an element";
        cout << "\n 6. EXIT";

        cout << "\n Enter your choice : ";
        cin >> option;

        switch(option) {
            case 1:
                cout << "Enter the value : ";
                cin >> value;
                insertAtEnd(value);
                break;
            case 2:
                cout << "Enter the value : ";
                cin >> value;
                insertAtBeginning(value);
                break;
            case 3:
                int key;
                cout << "Enter the value after which you want to insert new node : ";
                cin >> key;
                cout << "Enter the value you want to insert : ";
                cin >> value;
                insertAfter(key, value);
                break;
            case 4:
                displayList();
                break;
            case 5:
                cout << "Enter the value you want to delete : ";
                cin >> value;
                deleteNode(value);
                break;
        }
    } while(option != 6);

    return 0;
}
