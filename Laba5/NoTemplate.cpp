#include <iostream>
using namespace std;
template <typename T>
struct Elem
{
    int data;
    Elem* next, * prev;
};
template <typename T>
class List
{
    T* Head, * Tail;
    int Count;

public:
    List();
    List(const List&);
    List(List&&);
    ~List();
    int GetSize();
    void DelAll();
    void Del(int pos = 0);
    void PushBack(T n);
    void PushFront(T n);
    void PeekFront() const;
    void PeekBack() const;
    void PopFront();
    void PopBack();
    void Print();
    void Print(T pos);
    List& operator = (const List&);
    List& operator== (List&& L);
    friend ostream& operator << (ostream& stream, const List&);
};

List::List()
{
    Head = Tail = NULL;
    Count = 0;
}
List::List(List&& L)
{
    Head = L.Head;
    Tail = L.Tail;
    Count = L.Count;
    L.Head = nullptr;
    L.Tail = nullptr;
}
List::List(const List& L)
{
    Head = Tail = NULL;
    Count = 0;
    Elem* temp = L.Head;
    while (temp != 0)
    {
        PushBack(temp->data);
        temp = temp->next;
    }
}

List::~List()
{
    DelAll();
}

void List::PushFront(int n)
{
    Elem* temp = new Elem;
    temp->prev = 0;
    temp->data = n;
    temp->next = Head;
    if (Head != 0)
        Head->prev = temp;
    if (Count == 0)
        Head = Tail = temp;
    else
        Head = temp;

    Count++;
}

void List::PushBack(int n)
{
    Elem* temp = new Elem;
    temp->next = 0;
    temp->data = n;
    temp->prev = Tail;

    if (Tail != 0)
        Tail->next = temp;

    if (Count == 0)
        Head = Tail = temp;
    else
        Tail = temp;

    Count++;
}

void List::Del(int pos)
{
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    int i = 1;

    Elem* Del = Head;

    while (i < pos)
    {
        Del = Del->next;
        i++;
    }

    Elem* PrevDel = Del->prev;
    Elem* AfterDel = Del->next;

    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    delete Del;

    Count--;
}

void List::Print(int pos)
{
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem* temp;

    if (pos <= Count / 2)
    {
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            temp = temp->next;
            i++;
        }
    }
    else
    {
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            temp = temp->prev;
            i++;
        }
    }
    cout << pos << " element: ";
    cout << temp->data << endl;
}

void List::Print()
{
    if (Count != 0)
    {
        Elem* temp = Head;
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}

void List::DelAll()
{
    // Пока остаются элементы, удаляем по одному с головы
    while (Count != 0)
        Del(1);
}

int List::GetSize()
{
    return Count;
}


List& List::operator = (const List& L)
{
    if (this == &L)
        return *this;

    this->~List();

    Elem* temp = L.Head;

    while (temp != 0)
    {
        PushBack(temp->data);
        temp = temp->next;
    }

    return *this;
}
void List::PeekFront() const
{
    Elem* temp = Head;
    cout << temp->data << endl;
}
void List::PeekBack() const
{
    Elem* temp = Tail;
    cout << temp->data << endl;
}
void List::PopFront()
{
    Del(1);
}
void List::PopBack()
{
    Del(9);
}
List& List::operator== (List&& L)
{
    if (this == &L) {
        return *this;
    }
    this ->~List();
    Head = L.Head;
    Tail = L.Tail;
    L.Head = nullptr;
    L.Tail = nullptr;
}
ostream& operator << (ostream& stream, const List& L)
{
    Elem* temp = L.Head;
    while (temp != NULL)
    {
        stream << temp->data << "";
        temp = temp->next;
    }
    return stream << endl;
}
void main()
{
    List L;

    const int n = 10;
    int a[n] = { 0,1,2,3,4,5,6,7,8,9 };
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
            L.PushFront(a[i]);
        else
            L.PushBack(a[i]);
    cout << "List L:\n";
    L.Print();
    cout << endl;
    cout << "1 element:\n";
    L.PeekFront();
    cout << endl;
    cout << "Last element:\n";
    L.PeekBack();
    cout << endl;
    cout << "Spisok bez 1 i last elementa:\n";
    L.PopFront();
    L.PopBack();
    L.Print();
    cout << endl;
}