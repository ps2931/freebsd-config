#include <iostream>
using namespace std;

struct node {
    node *prev;
    int data;
    node *next;
};

node* start = NULL;
node* create_ll(node*);
node* display(node*);
node* insert_beg(node*);
node* insert_end(node*);
node* insert_before(node*);
node* insert_after(node*);
node* delete_beg(node*);
node* delete_end(node*);
node* delete_before(node*);
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
        cout << "\n 5.  Add a node before a given node";
        cout << "\n 6.  Add a node after a given node";
        cout << "\n 7.  Delete a node from the beginning";
        cout << "\n 8.  Delete a node from the end";
        cout << "\n 9.  Delete a node before a given node";
        cout << "\n 10. Delete a node after a given node";
        cout << "\n 11. Delete the entire list";
        cout << "\n 12. EXIT";

        cout << "\n\n Enter your option : ";
        cin >> option;

        switch(option) {
            case 1:  start = create_ll(start);
                     cout << "\n DOUBLY LINKED LIST CREATED";
                     break;
            case 2:  start = display(start);
                     break;
            case 3:  start = insert_beg(start);
                     break;
            case 4:  start = insert_end(start);
                     break;
            case 5:  start = insert_before(start);
                     break;
            case 6:  start = insert_after(start);
                     break;
            case 7:  start = delete_beg(start);
                     break;
            case 8:  start = delete_end(start);
                     break;
            case 9:  start = delete_before(start);
                     break;
            case 10: start = delete_after(start);
                     break;
            case 11: start = delete_list(start);
                     cout << "\n DOUBLY LINKED LIST DELETED";
                     break;
        }
    } while(option != 12);
    return 0;
}

node* create_ll(node* start) {
    node* new_node, *ptr;
    int num;
    cout << "\n Enter the data (-1 to end): ";
    cin >> num;
    while(num != -1) {
        if(start == NULL) {
            /* new_node = (node*)malloc(sizeof(node)); */
            new_node = new node; 
            new_node->prev = NULL;
            new_node->data = num;
            new_node->next = NULL;
            start = new_node;
        } else {
            ptr = start;
            /* new_node = (node*)malloc(sizeof(node)); */
            new_node = new node; 
            new_node->data = num;
            while(ptr->next != NULL) ptr = ptr->next;
            ptr->next = new_node;
            new_node->prev = ptr;
            new_node->next = NULL;
        }
        cout << "\n Enter the data : ";
        cin >> num;
    }
    return start;
}

node *display(node *start) {
    node *ptr;
    ptr = start;
    while(ptr != NULL) {
        cout << "\t" << ptr->data;
        ptr = ptr->next;
    }
    return start;
}

node* insert_beg(node *start) {
    node *new_node;
    int num;

    cout << "\n Enter the data : ";
    cin >> num;

    /* new_node = (node*)malloc(sizeof(node)); */
    new_node = new node; 
    new_node->data = num;
    start->prev = new_node;
    new_node->next = start;
    new_node->prev = NULL;
    start = new_node;
    return start;
}

node* insert_end(node* start) {
    int num;
    cout << "\n Enter the data : ";
    cin >> num;

    /* node *new_node = (node*)malloc(sizeof(node)); */
    node* new_node = new node; 
    new_node->data = num;

    node *ptr = start;
    while(ptr->next != NULL) ptr = ptr->next;

    ptr->next = new_node;
    new_node->prev = ptr;
    new_node->next = NULL;
    return start;
}

node* insert_before(node* start) {
    int num, val;
    cout << "\n Enter the data : ";
    cin >> num;
    cout << "\n Enter the value before which the data has to be inserted : ";
    cin >> val;

    // create a new node
    /* node* new_node = (node*)malloc(sizeof(node)); */
    node* new_node = new node; 
    new_node->data = num;

    // go till val
    node* ptr = start;
    while(ptr->data != val) ptr = ptr->next;

    new_node->next = ptr;
    new_node->prev = ptr->prev;
    ptr->prev->next = new_node;
    ptr->prev = new_node;
    return start;
    
}

node* insert_after(node* start) {
    int num, val;
    cout << "\n Enter the data : ";
    cin >> num;
    cout << "\n Enter the value before which the data has to be inserted : ";
    cin >> val;

    // create a new node
    /* node* new_node = (node*)malloc(sizeof(node)); */
    node* new_node = new node; 
    new_node->data = num;

    // go till val
    node* ptr = start;
    while(ptr->data != val) ptr = ptr->next;

    new_node->prev = ptr;
    new_node->next = ptr->next;
    ptr->next->prev = new_node;
    ptr->next = new_node;
    return start;
    
}

node* delete_beg(node* start) {
    node* ptr = start;
    start = start->next;
    start->prev = NULL;
    delete ptr;
    return start;
}

node* delete_end(node* start) {
    node* ptr =  start;
    while(ptr->next != NULL) ptr = ptr->next;
    ptr->prev->next = NULL;
    free(ptr);
    return start;
}

node* delete_after(node* start) {
    int val;
    cout << "\n Enter the value after which the node has to delete : ";
    cin >> val;

    node* ptr = start;
    while(ptr->data != val)
        ptr = ptr->next;

    node* temp = ptr->next;
    ptr->next = temp->next;
    temp->next->prev = ptr;
    free(temp);

    return start;
}

node* delete_before(node* start) {
    int val;
    cout << "\n Enter the value before which the node has to delete : ";
    cin >> val;

    node* ptr = start;
    while(ptr->data != val)
        ptr = ptr->next;

    node* temp = ptr->prev;
    if(temp == start) {
        start = delete_beg(start);
    } else {
        ptr->prev = temp->prev;
        temp->prev->next = ptr;
    }
    free(temp);
    return start;
}

node* delete_list(node* start) {
    node* temp;

    while(start !=NULL) {
        temp = start;
        start = start->next;
        delete temp;
    }
    return start;
}
