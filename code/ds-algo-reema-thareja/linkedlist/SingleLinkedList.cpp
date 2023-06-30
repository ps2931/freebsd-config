#include <malloc.h>
#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

node *start = NULL;
node *create_ll(node *);
node *display(node *);
node *insert_beg(node *);
node *insert_end(node *);
node *insert_before(node *);
node *insert_after(node *);
node *delete_beg(node *);
node *delete_end(node *);
node *delete_node(node *);
node *delete_after(node *);
node *delete_list(node *);
node *sort_list(node *);

int main(int argc, char *argv[]) {
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
        cout << "\n 9.  Delete a given node";
        cout << "\n 10. Delete a node after a given node";
        cout << "\n 11. Delete the entire list";
        cout << "\n 12. Sort the list";
        cout << "\n 13. EXIT";

        cout << "\n Enter your option : ";
        cin >> option;
        switch (option) {
            case 1:  start = create_ll(start);
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
            case 9:  start = delete_node(start);
                     break;
            case 10: start = delete_after(start);
                     break;
            case 11: start = delete_list(start);
                     break;
            case 12: start = sort_list(start);
                     break;
        }
    } while(option != 13);

    return 0;
}

node *create_ll(node* start) {
    node *new_node, *ptr;
    int num;
    cout << "\n Enter the data (-1 to EXIT): ";
    cin >> num;
    while(num != -1) {
        /* new_node = (node*)malloc(sizeof(node)); */
        new_node = new node;
        new_node -> data = num;
        if (start == NULL) {
            new_node -> next = NULL;
            start = new_node;
        } else {
            ptr = start;

            while(ptr->next != NULL)
                ptr = ptr->next;

            ptr->next = new_node;
            new_node->next = NULL;
        }
        cout << "\n Enter the data (-1 to EXIT) : ";
        cin >> num;
    }
    return start;
}

node *display(node* start) {
    node *ptr;
    ptr = start;
    while(ptr != NULL) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    return start;
}

node* insert_beg(node* start) {
    node *new_node;
    int num;
    cout << "\n Enter the data : ";
    cin >> num;
    /* new_node = (node *)malloc(sizeof(node)); */
    new_node = new node;
    new_node->data = num;
    new_node->next = start;
    start = new_node;
    return start;
}

node* insert_end(node* start) {
    node *ptr, *new_node;
    int num;

    cout << "\n Enter the data : ";
    cin >> num;
    
    /* new_node = (node *)malloc(sizeof(node)); */
    new_node = new node;
    new_node->data = num;
    new_node->next = NULL;

    ptr = start;
    while(ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = new_node;
    return start;
}

node *insert_before(node* start) {
    node *new_node, *ptr, *preptr;
    int num, val;
    
    cout << "\n Enter the data : ";
    cin >> num;
    
    cout << "\n Enter the value before which the data has to be inserted : ";
    cin >> val;
    
    /* new_node = (node *)malloc(sizeof(node)); */
    new_node = new node;
    new_node -> data = num;
    ptr = start;

    while(ptr->data != val) {
        preptr = ptr;
        ptr = ptr->next;
    }
    preptr->next = new_node;
    new_node->next = ptr;
    return start;
}

node *insert_after(node* start) {
    node *new_node, *ptr, *preptr;
    int num, val;
    
    cout << "\n Enter the data : ";
    cin >> num;

    cout << "\n Enter the value after which the data has to be inserted : ";
    cin >> val;

    /* new_node = (node *)malloc(sizeof(node)); */
    new_node = new node;
    new_node->data = num;
    
    ptr = start;
    preptr = ptr;
    while(preptr->data != val) {
        preptr = ptr;
        ptr = ptr->next;
    }
    preptr->next = new_node;
    new_node->next = ptr;
    return start;
}

node* delete_beg(node* start) {
    node *ptr;
    ptr = start;
    start = start->next;
    delete ptr;
    return start;
}

node* delete_end(node* start) {
    node *ptr, *preptr;
    ptr = start;
    while(ptr->next != NULL) {
        preptr = ptr;
        ptr = ptr->next;
    }
    preptr->next = NULL;
    delete ptr;
    return start;
}

node* delete_node(node* start) {
    node *ptr, *preptr;
    
    int val;
    cout << "\n Enter the value of the node which has to be deleted : ";
    cin >> val;

    ptr = start;
    if(ptr->data == val) {
        start = delete_beg(start);
        return start;
    } else {
        while(ptr->data != val) {
            preptr = ptr;
            ptr = ptr->next;
        }
        preptr->next = ptr->next;
        delete ptr;
        return start;
    }
}

node* delete_after(node* start) {
    node* ptr, *preptr;
    int val;
    
    cout << "Enter the value after which the node has to be deleted : ";
    cin >> val;

    ptr = start;
    preptr = ptr;
    while(preptr->data != val) {
        preptr = ptr;
        ptr = ptr->next;
    }
    preptr->next = ptr->next;
    delete ptr;
    return start;
}

node* delete_list(node* start) {
    node* ptr;
    if(start != NULL) {
        ptr = start;
        while(ptr != NULL) {
            cout << "\n" << ptr->data << " is to be deleted next";
            start = delete_beg(ptr);
            ptr = start;
        }
    }
    return start;
}

node* sort_list(node* start) {
    node *ptr1, *ptr2;
    int temp;
    ptr1 = start;
    while(ptr1->next != NULL) {
        ptr2 = ptr1->next;
        while(ptr2 != NULL) {
            if(ptr1->data > ptr2->data) {
                temp = ptr1->data;
                ptr1->data = ptr2->data;
                ptr2->data = temp;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return start;
}

