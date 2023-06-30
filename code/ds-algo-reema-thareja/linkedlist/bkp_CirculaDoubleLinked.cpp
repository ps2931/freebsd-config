#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
    node *prev;
};

node *start = NULL;
node *create_ll(node *);
node *display(node *);
node *insert_beg(node *);
node *insert_end(node *);
node *delete_beg(node *);
node *delete_end(node *);
node *delete_node(node *);
node *delete_list(node *);

int main() {
    int option;
    do {
        cout << "\n\n *****MAIN MENU****";
        cout << "\n 1. Create a list";
        cout << "\n 2. Display the list";
        cout << "\n 3. Add a node at the beginning";
        cout << "\n 4. Add a node at the end";
        cout << "\n 5. Delete a node from the beginning";
        cout << "\n 6. Delete a node from the end";
        cout << "\n 7. Delete a given node";
        cout << "\n 8. Delete the entire list";
        cout << "\n 9. EXIT";

        cout << "\n\n Enter you option : ";
        cin >> option;

        switch(option) {
            case 1: start = create_ll(start);
                    cout << "\n CIRCULAR DOUBLE LINKED LIST CREATED";
                    break;
            case 2: start = display(start);
                    break;
            case 3: start = insert_beg(start);
                    break;
            case 4: start = insert_end(start);
                    break;
            case 5: start = delete_beg(start);
                    break;
            case 6: start = delete_end(start);
                    break;
            case 7: start = delete_node(start);
                    break;
            case 8: start = delete_list(start);
                    cout << "\n CIRCULAR DOUBLE LINKED LIST DELETED";
                    break;
        }
    }while(option != 9);
    return 0;
}

node* create_ll(node *start) {
    int num;
    cout << "\n Enter the data (-1 to end) : ";
    cin >> num;

    node *new_node = nullptr;
    node *ptr = nullptr;

    while(num != -1) {
        if(start == NULL) {
            new_node = new node;
            new_node->prev = NULL;
            new_node->data = num;
            new_node->next = start;
            start = new_node;
        } else {
            new_node = new node;
            new_node->data = num;
            ptr = start;

            while(ptr->next != start)
                ptr = ptr->next;

            new_node->prev = ptr;
            ptr->next = new_node;
            new_node->next = start;
            start->prev = new_node;
        }
        cout << "\n Enter the data : ";
        cout << num;
    }
    return start;
}

node* display(node *start) {
    node *ptr = start;
    while(ptr->next != start) {
        cout << "\t" << ptr->data;
        ptr = ptr->next;
    }
    cout << "\t" << ptr->data;
    return start;
}

node* insert_beg(struct node *start) {
    int num;
    cout << "\n Enter the data : ";
    cin >> num;

    node *new_node = new node;
    new_node->data = num;

    node *ptr = start;
    while(ptr->next != start)
        ptr = ptr->next;

    new_node->prev = ptr;
    new_node->next = start;
    ptr->next = new_node;
    start->prev = new_node;
    start = new_node;
   
    return start;
}

node* insert_end(node *start) {
    int num;
    cout << "\n Enter the data : ";
    cin >> num;

    node *new_node = new node;
    new_node->data = num;

    node *ptr = start;
    while(ptr->next != start)
        ptr = ptr->next;

    ptr->next = new_node;
    new_node->prev = ptr;
    new_node->next = start;
    start->prev = new_node;
    return start;
}

node* delete_beg(node *start) {
    node *ptr = start;
    while(ptr->next != start) 
        ptr = ptr->next;

    ptr->next = start->next;
    node *temp = start;
    start = start->next;
    start->prev = ptr;
    delete temp;
    return start;
}

node* delete_end(node *start) {
    node *ptr = start;
    while(ptr->next != start)
        ptr = ptr->next;

    ptr->prev->next = start;
    start->prev = ptr->prev;
    delete ptr;
    return start;
}

node* delete_node(node *start) {
    int val;
    cout << "\n Enter the value of the node which has to be deleted : ";
    cin >> val;

    node *ptr = start;
    if(ptr->data == val) {
        start = delete_beg(start);
        return start;
    } else {
        while(ptr->data != val)
            ptr = ptr->next;

        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
        return start;
    }
}

node* delete_list(node *start) {
    node *ptr  = start;
    while(ptr->next != start)
        start = delete_end(start);

    delete start;
    return start;
}
