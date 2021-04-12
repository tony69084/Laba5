#include <iostream>
#include <string>
using namespace std;
template <typename T>
struct Elem
{
    T data;
    Elem* next, * prev;
};
template <typename T>
class List
{
    Elem<T>* Head;
    Elem<T>* Tail;
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
    void Print(int pos);
    List& operator = (const List&);
    List& operator== (List&& L);
    template <typename T> 
    friend ostream& operator << (ostream& stream, const List&);
};
template <typename T>
List<T>::List()
{
    Head = Tail = NULL;
    Count = 0;
}
template <typename T>
List<T>::List(List&& L)
{
    Head = L.Head;
    Tail = L.Tail;
    Count = L.Count;
    L.Head = nullptr;
    L.Tail = nullptr;
}
template <typename T>
List<T>::List(const List& L)
{
    Head = Tail = NULL;
    Count = 0;
    Elem<T>* temp = L.Head;
    while (temp != 0)
    {
        PushBack(temp->data);
        temp = temp->next;
    }
}
template <typename T>
List<T>::~List()
{
    DelAll();
}
template <typename T>
void List<T>::PushFront(T n)
{
    Elem<T>* temp = new Elem<T>;
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
template <typename T>
void List<T>::PushBack(T n)
{
    Elem<T>* temp = new Elem<T>;
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
template <typename T>
void List<T>::Del(int pos)
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

    Elem<T>* Del = Head;

    while (i < pos)
    {
        Del = Del->next;
        i++;
    }

    Elem<T>* PrevDel = Del->prev;
    Elem<T>* AfterDel = Del->next;

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
template <typename T>
void List<T>::Print(int pos)
{
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem<T>* temp;

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
template <typename T>
void List<T>::Print()
{
    if (Count != 0)
    {
        Elem<T>* temp = Head;
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}
template <typename T>
void List<T>::DelAll()
{
    // Пока остаются элементы, удаляем по одному с головы
    while (Count != 0)
        Del(1);
}
template <typename T>
int List<T>::GetSize()
{
    return Count;
}

template <typename T>
List<T>& List<T>::operator = (const List<T>& L)
{
    if (this == &L)
        return *this;

    this->~List();

    Elem<T>* temp = L.Head;

    while (temp != 0)
    {
        PushBack(temp->data);
        temp = temp->next;
    }

    return *this;
}
template <typename T>
void List<T>::PeekFront() const
{
    Elem<T>* temp = Head;
    cout << temp->data << endl;
}
template <typename T>
void List<T>::PeekBack() const
{
    Elem<T>* temp = Tail;
    cout << temp->data << endl;
}
template <typename T>
void List<T>::PopFront()
{
    Del(1);
}
template <typename T>
void List<T>::PopBack()
{
    Del(9);
}
template <typename T>
List<T>& List<T>::operator== (List<T>&& L)
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
template <typename T>
ostream& operator << (ostream& stream, const List<T>& L)
{
    Elem<T>* temp = L.Head;
    while (temp != NULL)
    {
        stream << temp->data << "";
        temp = temp->next;
    }
    return stream << endl;
}
void main()
{
    List<string> L;
    const int n = 10;
    string b[n] = { "One","Two" ,"Three" ,"Four" ,"Five" ,"Six" ,"Seven" ,"Eight" ,"Nine","Ten" };
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
            L.PushFront(b[i]);
        else
            L.PushBack(b[i]);
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