#include <iostream>
#include <thread>
#include <string>
#pragma warning(disable:4996);
using namespace std;

struct Received {
    string message;
    string time;
    int sender;
    Received* next;
};
struct Sent {
    string message;
    string time;
    int receiver;
    Sent* next;
};
struct List {
    int key;
    Sent* s_messages;
    Received* r_messages;
    List* next;
};

void print_sent_messages(Sent*);
void print_received_messages(Received*);
void print_sent_messages_by_key(Sent*, int);
void print_received_messages_by_key(Received*, int);

void insert_sent_message(Sent**, Sent*);
void insert_received_message(Received**, Received*);
void sent_message(List*, string, int);

Sent* delete_sent_message_position(Sent*, int);
Received* delete_received_message_position(Received*, int);

string currentDateTime();

void clear_sent_messages(Sent**);
void clear_received_messages(Received**);

bool isUniqueKey(List*, int);

void print_nodes(List*);

void insert_new_node(List**, int);
void insert_new_node_by_position(List**, int, int);
void initialize(List**, int);

void delete_by_key(List**, int);
void delete_by_position(List**, int);

List* search_by_key(List*, int);
List* search_by_position(List*, int);

//getters
string getMessage();
int getReceiversKey();
int getReceiversPosition();
int getKey();
int getPosition();
int getVariant(int);

//menus
void print_main_menu();
void print_insert_menu();
void print_delete_menu();
void print_select_menu();
void print_node_menu();
void messages_received_menu();
void messages_sent_menu();

//messages
void incorrect_position();
void node_not_found();
void list_is_empty();
void deleted_node(int);

int main()
{
    List* head = NULL, *current_node = NULL;
    int key, position, select_menu, select_delete, select_insert, selection_menu;
    int node_menu, select_messages;
    string message;
    bool isUnique;
    start: do {
        system("CLS");
        print_main_menu();
        select_menu = getVariant(4);
        if (select_menu != 4)
        {
            print_nodes(head);
        }
        switch (select_menu)
        {
        case 1:
            print_select_menu();
            selection_menu = getVariant(2);
            switch (selection_menu)
            {
            case 1:
                isUnique = true;
                key = getKey();
                isUnique = isUniqueKey(head, key);
                if (isUnique)
                {
                    cout << "This key is not exsist in this list!" << endl;
                    current_node = NULL;
                }
                else
                {
                    current_node = search_by_key(head, key);
                }
                break;
            case 2:
                position = getPosition();
                current_node = search_by_position(head, position);
                break;
            }
            if (current_node)
            {
                do
                {
                    system("CLS");
                    print_node_menu();
                    node_menu = getVariant(4);
                    switch (node_menu)
                    {
                    case 1:
                        message = getMessage();
                        isUnique = true;
                        while (isUnique)
                        {
                            key = getKey();
                            isUnique = isUniqueKey(head, key);
                            if (isUnique)
                            {
                                cout << "This key is not exsist in this list!" << endl;
                            }
                        }
                        sent_message(current_node, message, key);
                        break;
                    case 2:
                        messages_sent_menu();
                        select_messages = getVariant(3);
                        switch (select_messages)
                        {
                        case 1:
                            print_sent_messages(current_node->s_messages);
                            break;
                        case 2:
                            key = getKey();
                            print_sent_messages_by_key(current_node->s_messages, key);
                            break;
                        case 3:
                            position = getPosition();
                            delete_sent_message_position(current_node->s_messages, position);
                            break;
                        }
                        break;
                    case 3:
                        messages_received_menu();
                        select_messages = getVariant(3);
                        switch (select_messages)
                        {
                        case 1:
                            print_received_messages(current_node->r_messages);
                            break;
                        case 2:
                            key = getKey();
                            print_received_messages_by_key(current_node->r_messages, key);
                            break;
                        case 3:
                            position = getPosition();
                            delete_received_message_position(current_node->r_messages, position);
                            break;
                        }
                        break;
                    }
                    if (node_menu != 4)
                    {
                        system("pause");
                    }
                } while (node_menu != 4);
                goto start;
            }
            break;
        case 2:
            print_insert_menu();
            select_insert = getVariant(2);
            switch (select_insert)
            {
            case 1:
                isUnique = false;
                while (!isUnique)
                {
                    key = getKey();
                    isUnique = isUniqueKey(head, key);
                    if (!isUnique)
                    {
                        cout << "Key is exsist in this list!" << endl;
                    }
                }
                insert_new_node(&head, key);
                break;
            case 2:
                position = getPosition();
                isUnique = false;
                while (!isUnique)
                {
                    key = getKey();
                    isUnique = isUniqueKey(head, key);
                    if (!isUnique)
                    {
                        cout << "Key is exsist in this list!" << endl;
                    }
                }
                insert_new_node_by_position(&head, key, position);
                break;
            }
            break;
        case 3:
            print_delete_menu();
            select_delete = getVariant(2);
            switch (select_delete)
            {
            case 1:
                isUnique = true;
                while (isUnique)
                {
                    key = getKey();
                    isUnique = isUniqueKey(head, key);
                    if (isUnique)
                    {
                        cout << "This key is not exsist in this list!" << endl;
                    }
                }
                delete_by_key(&head, key);
                break;
            case 2:
                position = getPosition();
                delete_by_position(&head, position);
                break;
            }
            break;
        }
        if (select_menu != 4)
        {
            print_nodes(head);
            system("pause");
        }
    } while (select_menu != 4);
    return 0;
}

//////////////////////////////////////////////LIST///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//check if is unique
bool isUniqueKey(List* head, int key)
{
    if (head != NULL)
    {
        List* pv = head;
        do
        {
            if (pv->key == key)
            {
                return false;
            }
            pv = pv->next;
        } while (pv != head);
        return true;
    }
    return true;
}
//print
void print_nodes(List* head)
{
    if (head != NULL)
    {
        List* pv = head;
        int position = 1;
        do
        {
            cout << "N(" << position << ") = " << pv->key << "\t";
            pv = pv->next;
            position++;
        } while (pv != head);
        cout << endl;
    }
    else
    {
        list_is_empty();
    }
}
//insert 
void initialize(List** head, int key)
{
    List* pv = new List;
    pv->key = key;
    pv->next = pv;
    pv->r_messages = {};
    pv->s_messages = {};
    *head = pv;
}
void insert_new_node(List** head, int key)
{
    List* pv1 = *head;
    if (*head != NULL)
    {
        do
        {
            pv1 = pv1->next;
        } while (pv1->next != *head);
        List* pv = new List;
        pv->key = key;
        pv->next = pv1->next;
        pv->r_messages = {};
        pv->s_messages = {};
        pv1->next = pv;
    }
    else
    {
        initialize(head, key);
    }
}
void insert_new_node_by_position(List** head, int key, int position)
{
    if (position > 0)
    {
        if (*head != NULL)
        {
            List* pv1 = *head;
            int current_position = 1;
            while (current_position < position - 1)
            {
                pv1 = pv1->next;
                current_position++;
            }
            List* pv = new List;
            pv->key = key;
            pv->next = pv1->next;
            pv->r_messages = {};
            pv->s_messages = {};
            if (pv1->next == *head)
            {
                *head = pv;
            }
            pv1->next = pv;
        }
        else
        {
            initialize(head, key);
        }
    }
    else
    {
        incorrect_position();
    }
}
//delete
void delete_by_key(List** head, int key)
{
    if ((*head)->next != *head)
    {
        List* pv = *head;
        List* pv1 = (*head)->next;
        while (pv1->key != key)
        {
            pv1 = pv1->next;
            pv = pv->next;
        }
        pv->next = pv1->next;
        if (pv1 == *head)
        {
            *head = pv1->next;
        }
        clear_sent_messages(&(pv1->s_messages));
        clear_received_messages(&(pv1->r_messages));
        delete pv1;
        pv1 = {};
    }
    else
    {
        clear_sent_messages(&((*head)->s_messages));
        clear_received_messages(&((*head)->r_messages));
        delete* head;
        *head = {};
    }
}
void delete_by_position(List** head, int position)
{
    if (position > 0)
    {
        if ((*head)->next == *head)
        {
            clear_sent_messages(&((*head)->s_messages));
            clear_received_messages(&((*head)->r_messages));
            delete* head;
            *head = {};
        }
        else if ((*head) != NULL)
        {
            int current_position = 1;
            List* pv = *head;
            List* pv1 = *head;
            while (current_position != position)
            {
                pv = pv->next;
                current_position++;
            }
            while (pv1->next != pv)
            {
                pv1 = pv1->next;
            }
            if (pv == *head)
            {
                *head = pv->next;
            }
            pv1->next = pv->next;
            clear_sent_messages(&(pv->s_messages));
            clear_received_messages(&(pv->r_messages));
            delete pv;
            pv = {};
        }
    }
    else
    {
        incorrect_position();
    }
}
//search
List* search_by_key(List* head, int key)
{
    if (head != NULL)
    {
        List* pv = head;
        while (pv->key != key)
        {
            pv = pv->next;
        }
        return pv;
    }
    else
    {
        return NULL;
    }
}
List* search_by_position(List* head, int position)
{
    if (position > 0)
    {
        if (head != NULL)
        {
            int current_position = 1;
            List* pv = head;
            while (current_position != position)
            {
                pv = pv->next;
                current_position++;
            }
            return pv;
        }
    }
    else
    {
        incorrect_position();
        return NULL;
    }
}

/////////////////////////////////////////////////////LIST////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_sent_messages(Sent* head)
{
    if (head != NULL)
    {
        Sent* pv = head;
        while(pv != NULL)
        {
            cout << "Message: " << pv->message << ", to: " << pv->receiver << ", at: "  << pv->time << endl;
            pv = pv->next;
        }
    }
    else
    {
        cout << "You don't have any messages(:" << endl;
    }
}
void print_received_messages(Received* head)
{
    if (head != NULL)
    {
        Received* pv = head;
        while (pv != NULL)
        {
            cout << "Message: " << pv->message << ", from: " << pv->sender << ", at: " << pv->time << endl;
            pv = pv->next;
        }
    }
    else
    {
        cout << "You don't have any messages(:" << endl;
    }
}
void print_sent_messages_by_key(Sent* head, int key)
{
    if (head != NULL)
    {
        Sent* pv = head;
        while (pv != NULL)
        {
            if (pv->receiver == key)
            {
                cout << "Message: " << pv->message << ", to: " << pv->receiver << ", at: " << pv->time << endl;
            }
            pv = pv->next;
        }
    }
    else
    {
        cout << "You don't have any messages(:" << endl;
    }
}
void print_received_messages_by_key(Received* head, int key)
{
    if (head != NULL)
    {
        Received* pv = head;
        while (pv != NULL)
        {
            if (pv->sender == key)
            {
                cout << "Message: " << pv->message << ", from: " << pv->sender << ", at: " << pv->time << endl;
            }
            pv = pv->next;
        }
    }
    else
    {
        cout << "You don't have any messages(:" << endl;
    }
}

Sent* delete_sent_message_position(Sent* head, int position)
{
    if (0 < position)
    {
        int current_position = 1;
        Sent* pv = head;
        Sent* current_element = head;
        if (position == 1)
        {
            current_element = current_element->next;
            delete head;
            head = current_element;
        }
        else
        {
            while (current_position != position - 1)
            {
                current_position++;
                pv = pv->next;
                if (!pv)
                {
                    break;
                }
            }
            if (pv)
            {
                current_element = pv;
                pv = pv->next;
                current_element->next = pv->next;
                delete pv;
                pv = {};
            }
        }
    }
    else
    {
        incorrect_position();
    }
    return head;
}
Received* delete_received_message_position(Received* head, int position)
{
    if (0 < position)
    {
        int current_position = 1;
        Received* pv = head;
        Received* current_element = head;
        if (position == 1)
        {
            current_element = current_element->next;
            delete head;
            head = {};
            head = current_element;
        }
        else
        {
            while (current_position != position - 1)
            {
                current_position++;
                pv = pv->next;
                if (!pv)
                {
                    break;
                }
            }
            if (pv)
            {
                current_element = pv;
                pv = pv->next;
                current_element->next = pv->next;
                delete pv;
                pv = {};
            }
        }
    }
    else
    {
        incorrect_position();
    }
    return head;
}
void insert_sent_message(Sent** head, Sent* pv)
{
    if (*head == NULL)
    {
        *head = pv;
        (*head)->next = NULL;
    }
    else
    {
        pv->next = *head;
        *head = pv;
    }
}
void insert_received_message(Received** head, Received* pv)
{
    if (*head == NULL)
    {
        *head = pv;
        (*head)->next = NULL;
    }
    else
    {
        pv->next = *head;
        *head = pv;
    }
}
void sent_message(List* node, string message, int to)
{
    Sent* ps = new Sent;
    Received* pr = new Received;
    ps->message = message;
    ps->receiver = to;
    ps->time = currentDateTime();
    pr->message = message;
    pr->sender = node->key;
    pr->time = ps->time;
    insert_sent_message(&(node->s_messages), ps);
    while (node->key != to)
    {
        node = node->next;
    }
    insert_received_message(&(node->r_messages), pr);
}

string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}
void clear_sent_messages(Sent** head)
{
    if (*head != NULL)
    {
        Sent* pv = (*head)->next;
        while (pv != NULL)
        {
            delete* head;
            pv = pv->next;
            *head = pv;
        }
    }
}
void clear_received_messages(Received** head)
{
    if (*head != NULL)
    {
        Received* pv = (*head)->next;
        while (pv != NULL)
        {
            delete* head;
            pv = pv->next;
            *head = pv;
        }
    }
}

/////////////////////////////////////////////////////////////ETC/////////////////////////////////////////////////////////////////////////////////////////////////////

//menus
void print_main_menu()
{
    cout << "(1: SELECT NODE, 2: INSERT NEW NODE, 3: DELETE NODE, 4: EXIT)" << endl;
    cout << "Select any value:";
}
void print_insert_menu()
{
    cout << "(1: INSERT NEW NODE TO END, 2: INSERT NEW NODE BY POSITION)" << endl;
    cout << "Select any value:";
}
void print_delete_menu()
{
    cout << "(1: DELETE NODE BY KEY, 2: DELETE NODE BY POSITION)" << endl;
    cout << "Select any value:";
}
void print_select_menu()
{
    cout << "(1: SELECT NODE BY KEY, 2: SELECT NODE BY POSITION)" << endl;
    cout << "Select any value:";
}
void print_node_menu()
{
    cout << "(1: SEND MESSAGE, 2: SHOW SENT MESSAGES, 3: SHOW RECEIVED MESSAGES, 4: EXIT)" << endl;
    cout << "Select any value:";
}
void messages_received_menu()
{
    cout << "(1: SHOW ALL MESSAGES, 2: SHOW MESSAGES BY SENDER'S KEY, 2: DELETE MESSAGE BY POSITION)" << endl;
    cout << "Select any value:";
}
void messages_sent_menu()
{
    cout << "(1: SHOW ALL MESSAGES, 2: SHOW MESSAGES BY RECEIVER'S KEY, 2: DELETE MESSAGE BY POSITION)" << endl;
    cout << "Select any value:";
}

//getters
string getMessage()
{
    string message;
    cout << "Enter message: ";
    cin.ignore();
    getline(cin, message);
    return message;
}
int getReceiversKey()
{
    int key;
    cout << "Enter receiver's key: ";
    cin >> key;
    return key;
}
int getReceiversPosition()
{
    int position;
    cout << "Enter receiver's position: ";
    cin >> position;
    return position;
}
int getKey()
{
    int key;
    cout << "Enter key: ";
    cin >> key;
    return key;
}
int getPosition()
{
    int position;
    cout << "Enter position: ";
    cin >> position;
    return position;
}
int getVariant(int maxvalue)
{
    int variant;
    cin >> variant;
    while (variant < 1 || variant > maxvalue)
    {
        cout << "Incorrect input!\nTry again: ";
        cin >> variant;
    }
    return variant;
}

//messages
void incorrect_position()
{
    cout << "You entered incorrect position!" << endl;
}
void node_not_found()
{
    cout << "Node not found!" << endl;
}
void list_is_empty()
{
    cout << "List is empty!" << endl;
}
void deleted_node(int key)
{
    cout << "Deleted node is with key: " << key << endl;
}

//////////////////////////////////////////////////////////////////////////ETC//////////////////////////////////////////////////////////////////////////////////////////