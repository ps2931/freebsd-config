#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
};

node* start = NULL;
node* create_cll(node*);
node* display(node*);
node* insert_beg(node*);
node* insert_end(node*);
node* delete_beg(node*);
node* delete_end(node*);
node* delete_after(node*);
node* delete_list(node*);

int main() {
    int option;
    do {
        cout << "\n\n *****MAIN MENU*****";
        cout << "\n 1.  Create a list";
        cout << "\n 2.  Display the list";
        cout << "\n 3.  Add a node at the beginning";
        cout << "\n 4.  Add a node at the end";
        cout << "\n 5.  Delete a node from the beginning";
        cout << "\n 6.  Delete a node from the end";
        cout << "\n 7.  Delete a node after a given node";
        cout << "\n 8.  Delete the entire list";
        cout << "\n 9.  EXIT";

        cout << "\n\n Enter your option : ";
        cin >> option;

        switch(option) {
            case 1:  start = create_cll(start);
                     cout << "\n CIRCULAR LINKED LIST CREATED";
                     break;
            case 2:  start = display(start);
                     break;
            case 3:  start = insert_beg(start);
                     break;
            case 4:  start = insert_end(start);
                     break;
            case 5:  start = delete_beg(start);
                     break;
            case 6:  start = delete_end(start);
                     break;
            case 7:  start = delete_after(start);
                     break;
            case 8:  start = delete_list(start);
                     cout << "\n CIRCULAR LINKED LIST DELETED";
                     break;
        }
    }while(option != 9);
    return 0;
}

node* create_cll(node* start) {
    node* new_node, *ptr;
    int num;
    cout << "\n Enter the data (-1 to end) : ";
    cin >> num;

    while(num != -1) {
        new_node = new node;
        new_node->data = num;
        if(start == NULL) {
            new_node->next = new_node;
            start = new_node;
        } else {
            ptr = start;
            while(ptr->next != start)
                ptr = ptr->next;
            ptr->next = new_node;
            new_node->next = start;
        }
        cout << "\n Enter the data : ";
        cin >> num;
    }
    return start;
}

node* display(node* start) {
    node *ptr;
    ptr = start;
    while(ptr->next != start) {
        cout << "\t" << ptr->data;
        ptr = ptr->next;
    }
    cout << "\t" << ptr->data;
    return start;
}

node* insert_beg(node* start) {
    int num;
    cout << "\n Enter the data : ";
    cin >> num;

    node* new_node = new node;
    new_node->data = num;

    node* ptr = start;
    while(ptr->next != start)
        ptr  = ptr->next;

    ptr->next = new_node;
    new_node->next = start;
    start = new_node;
    return start;
}

node* insert_end(node* start) {
    int num;
    cout << "\n Enter the data : ";
    cin >> num;

    node* new_node = new node;
    new_node->data = num;

    node* ptr = start;
    while(ptr->next != start)
        ptr = ptr->next;

    ptr->next = new_node;
    new_node->next = start;
    return start;
}

node* delete_beg(node* start) {
    node* ptr = start;
    while(ptr->next != start)
        ptr = ptr->next;

    ptr->next = start->next;
    delete start;

    start = ptr->next;
    return start;
}

node* delete_end(node* start) {
    node* ptr = start;
    ptr = start;
    node *preptr = nullptr;
    while(ptr->next != start) {
        preptr = ptr;
        ptr = ptr->next;
    }
    preptr->next = ptr->next;
    delete ptr;
    return start;
}

node* delete_after(node* start) {
    int val;
    cout << "\n Enter the value after which the node has to deleted : ";
    cin >> val;

    node* ptr = start;
    node* preptr = ptr;

    while(preptr->data != val) {
        preptr = ptr;
        ptr = ptr->next;
    }
    preptr->next = ptr->next;

    if(ptr == start)
        start = preptr->next;
    delete ptr;

    return start;
}

node* delete_list(node* start) {
    node* ptr = start;
    while(ptr->next != start)
        start = delete_end(start);
    delete start;

    return start;
}
