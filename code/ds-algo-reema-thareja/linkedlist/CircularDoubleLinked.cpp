#include <iostream>
using namespace std;

struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node* head = NULL;

// function prototypes
struct node* create(int);
void insert_begin(int);
void insert_end(int);
void insert_mid(int, int);
void delete_begin();
void delete_end();
void delete_mid(int);
int search(int);
void update(int, int);
void sort();
int list_size();
void display();
void display_reverse(struct node*);
int get_data();
int get_position();

int main()
{
    char user_active = 'Y';
    int user_choice;
    int data, position;

    while( user_choice != 12)
    {
        cout << "\n\n------ Circular Doubly Linked List -------\n";
        cout << "\n1.  Insert a node at beginning";
        cout << "\n2.  Insert a node at end";
        cout << "\n3.  Insert a node at given position";
        cout << "\n4.  Delete a node from beginning";
        cout << "\n5.  Delete a node from end";
        cout << "\n6.  Delete a node from given position";
        cout << "\n7.  Print list from beginning";
        cout << "\n8.  Print list from end";
        cout << "\n9.  Search a node data";
        cout << "\n10. Update a node data";
        cout << "\n11. Sort the list";
        cout << "\n12. Exit";

        cout << "\n\n------------------------------\n";
        cout << "\nEnter your choice: ";
        cin >> user_choice;
        cout << "\n------------------------------\n";

        switch(user_choice)
        {
            case 1:
                cout << "\nInserting a node at beginning";
                data = get_data();
                insert_begin(data);
                break;

            case 2:
                cout << "\nInserting a node at end";
                data = get_data();
                insert_end(data);
                break;

            case 3:
                cout << "\nInserting a node at the given position";
                data = get_data();
                position = get_position();
                insert_mid(position, data);
                break;

            case 4:
                cout << "\nDeleting a node from beginning\n";
                delete_begin();
                break;

            case 5:
                cout << "\nDeleting a node from end\n";
                delete_end();
                break;

            case 6:
                cout << "\nDelete a node from given position\n";
                position = get_position();
                delete_mid(position);
                break;

            case 7:
                cout << "\nPrinting the list from beginning\n\n";
                display();
                break;

            case 8:
                cout << "\nPrinting the list from end\n\n";
                if (head == NULL)
                {
                    cout << "\n\tList is Empty!\n";
                } else {
                    display_reverse(head);
                }
                break;

            case 9:
                cout << "\nSearching the node data";
                data = get_data();

                if (search(data) == 1) {
                    cout << "\n\tNode Found\n";
                } else {
                    cout << "\n\tNode Not Found\n";
                }
                break;

            case 10:
                cout << "\nUpdating the node data";
                data = get_data();
                position = get_position();
                update(position, data);
                break;

            case 11:
                sort();
                cout << "\nList was sorted\n";
                break;
            case 12:
                cout << "\nProgram was terminated\n\n";
                return 0;

            default:
                cout << "\n\tInvalid Choice\n";
        }

        fflush(stdin);
    }

    return 0;
}


// creates a new node
struct node* create(int data)
{
    /* struct node* new_node = (struct node*) malloc (sizeof(struct node)); */
    struct node* new_node = new struct node;

    if (new_node == NULL)
    {
        cout << "\nMemory can't be allocated\n";
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

// insert a new node at the beginning of the list
void insert_begin(int data)
{
    struct node* new_node = create(data);

    if (new_node)
    {
        // if list is empty
        if (head == NULL)
        {
            new_node->next = new_node;
            new_node->prev = new_node;
            head = new_node;
            return;
        }
        head->prev->next = new_node;
        new_node->prev = head->prev;
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

// inserts a new node at the end
void insert_end(int data)
{
    struct node* new_node = create(data);

    if (new_node)
    {
        if (head == NULL)
        {
            new_node->next = new_node;
            new_node->prev = new_node;
            head = new_node;
            return;
        }
        head->prev->next = new_node;
        new_node->prev = head->prev;
        new_node->next = head;
        head->prev = new_node;
    }
}

// inserts node at the given position
void insert_mid(int position, int data)
{
    // checking if the position is valid or not
    if (position <= 0)
    {
        cout << "\nInvalid Position\n";
    } else if (head == NULL && position > 1) {
        cout << "\nInvalid Position\n";
    } else if (head != NULL && position > list_size()) {
        cout << "\nInvalid Position\n";
    } else if (position == 1) {
        insert_begin(data);
    } else {
        struct node *new_node = create(data);

        if (new_node != NULL) {
            struct node *temp = head, *prev = NULL;
            int i = 1;

            // traverse the list to the given position
            while (++i <= position) {
                prev = temp;
                temp = temp->next;
            }

            // update the prev node to the new noe
            prev->next = new_node;

            // update the new node to the temp (position node)
            new_node->next = temp;
        }
    }
}

void delete_begin()
{
    if (head == NULL) {
        cout << "\nList is Empty\n";
        return;
    } else  if (head->next == head) {
        delete(head);
        head = NULL;
        return;
    }

    struct node* temp = head;
    head->prev->next = head->next;
    head->next->prev = head->prev;
    head = head->next;

    delete(temp);
    temp = NULL;
}

// deletes the node from the end of the list
void delete_end()
{
    if (head == NULL) {
        cout << "\nList is Empty\n";
        return;
    } else  if (head->next == head) {
        delete(head);
        head = NULL;
        return;
    }

    struct node* last_node = head->prev;

    last_node->prev->next = head;
    head->prev = last_node->prev;

    delete(last_node);
    last_node = NULL;
}

// deletes the node from the given position
void delete_mid(int position)
{
    if (position <= 0) {
        cout << "\n Invalid Position \n";
    }
    else if (position > list_size()) {
        cout << "\n Invalid position \n";
    }
    else if (position == 1) {
        delete_begin();
    }
    else if (position == list_size()) {
        delete_end();
    }
    else {
        struct node *temp = head;
        struct node *prev = NULL;
        int i = 1;

        while (i < position) {
            prev = temp;
            temp = temp->next;
            i += 1;
        }
        prev->next = temp->next;
        temp->next->prev = prev;
        delete(temp);
        temp = NULL;
    }
}

// search the node with the given key item
int search(int key)
{
    if (head == NULL) {
        cout << "\n Not Found \n";
        return 0;
    }

    struct node* temp = head;
    do
    {
        if (temp->data == key) {
            return 1;
        }
        temp = temp->next;
    } while (temp != head);

    return 0;
}

// updates the data of the given node position
void update(int position, int new_value)
{
    if (head == NULL) {
        cout << "\n  List is Empty \n";
        return;
    } else if (position <= 0 || position > list_size()) {
        cout << "\nInvalid position\n";
        return;
    }

    struct node* temp = head;
    int i = 0;

    while (++i < position) {
        temp = temp->next;
    }
    temp->data = new_value;
}


// sorts the linked list data using insertion sort
void sort()
{
    if (head == NULL) {
        cout << "\nList  is Empty\n";
        return;
    }
    struct node* temp1 = head;
    struct node* temp2 = head;
    int key = 0, value;

    do {
        temp2 = temp1->next;

        while(temp2 != head)
        {
            if (temp1->data > temp2->data)
            {
                value = temp1->data;
                temp1->data = temp2->data;
                temp2->data = value;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }while (temp1->next != head);

}


// display the list
void display()
{
    if (head == NULL) {
        cout << "\nList  is Empty\n";
        return;
    }

    struct node* temp = head;
    do {
        cout << "\t" << temp->data;
        temp = temp->next;
    } while (temp != head);
}

// display the list from end to start
void display_reverse(struct node* temp)
{
    if (temp->next == head) {
        cout << "\t" << temp->data;
        return;
    }

    display_reverse(temp->next);
    cout << "\t" << temp->data;
}

// calculate the size of the list
int list_size()
{
    if (head == NULL) {
        return 0;
    }

    struct node* temp = head;
    int count = 0;

    do {
        count += 1;
        temp = temp->next;
    } while (temp != head);

    return count;
}


int get_data()
{
    int data;
    cout << "\n\nEnter Data: ";
    cin >> data;

    return data;
}

int get_position()
{
    int position;
    cout << "\n\nEnter Position: ";
    cin >> position;

    return position;
}
