#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList
{
    private:
        struct Node
        {
            int data;
            Node* prev;
            Node* next;
            Node(int val, Node* p = nullptr, Node* n = nullptr)
            {
                data = val;
                prev = p;
                next = n;
            }
        };

        Node* head;
        Node* tail;

    public:
        // constructor
        DoublyLinkedList() { head = nullptr; tail = nullptr; }

        void push_back(int value)
        {
            Node* newNode = new Node(value);
            if (!tail) // if there's no tail, the list is empty
                head = tail = newNode;
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        void push_front(int value)
        {
            Node* newNode = new Node(value);
            if (!head) // if there's no head, the list is empty
                head = tail = newNode;
            else
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }

        void delete_val(int value)
        {
            if (!head) // Empty list
                return;

            Node* temp = head;
            while (temp && temp->data != value)
                temp = temp->next;

            if (!temp) // Value not found
                return;

            if (temp->prev)
                temp->prev->next = temp->next;
            else
                head = temp->next; // Deleting the head

            if (temp->next)
                temp->next->prev = temp->prev;
            else
                tail = temp->prev; // Deleting the tail

            delete temp;
        }

        void pop_front()
        {
            if (!head) return;

            Node* temp = head;
            head = temp->next;
            if (head)
                head->prev = nullptr;
            else
                tail = nullptr;

            delete temp;
        }

        void pop_back()
        {
            if (!tail) return;

            Node*temp = tail;
            tail = temp->prev;
            if (tail)
                tail->next = nullptr;
            else
                head = nullptr;

            delete temp;
        }

        void delete_pos(int position) // one-based counting
        {
            if (!head) return;
            if (position == 0)
            {
                pop_front();
                return;
            }

            Node* temp = head;
            for (int i = 0; i < position - 1 && temp; i++)
                temp = temp->next;

            if (!temp) return;

            if (temp->prev)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            if (temp->next)
                temp->next->prev = temp->prev;
            else
                tail = temp->prev;
        }

        void print() const
        {
            Node* current = head;
            if (!current) return;
            while (current)
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }

        void print_reverse() const
        {
            Node* current = tail;
            if (!current) return;
            while (current)
            {
                cout << current->data << " ";
                current = current->prev;
            }
            cout << endl;
        }

        ~DoublyLinkedList()
        {
            while (head)
            {
                Node* temp = head;
                head = temp->next;
                delete temp;
            }
        }
};

void print_id(string const& lab_desc);

// Driver program
int main()
{
    print_id("Lab 22: Upgrade the DLL Class");

    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward:\n";
    list.print();

    cout << "List backward:\n";
    list.print_reverse();

    list.pop_front();
    cout << "After pop_front:\n";
    list.print();

    list.pop_back();
    cout << "After pop_back:\n";
    list.print();

    list.delete_pos(2);
    cout << "After delete_pos(2):\n";
    list.print();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}

void print_id(string const& lab_desc)
{
    cout << "\nCOMSC210 | Grant Luo | " << lab_desc << "\n";
    cout << "Editor: CLion\n";
    cout << "Compiler: Apple clang version 16.0.0\n";
    cout << "File: " << __FILE__ << "\n";
    cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}