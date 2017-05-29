#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct person {
    string first_name;
    string last_name;
    int age;
    person *next;
    person();
};

person::person() {
    next = 0;
}

struct list {
    person *first;
    int size = 0;
    void add_person(string first_name, string last_name, int age);
    void delete_person(int id);
    void show_list(int id);
    void special_peoples(char key);
    list();
    bool check(char key, string name, int age);
};

list::list() {
    first = 0;
}

void list::add_person(string first_name, string last_name, int age)
{
    person *sb_new = new person; // stworzenie elementu
    
    sb_new->first_name = first_name;
    sb_new->last_name = last_name;
    sb_new->age = age;
    
    if (first == 0) //czy to pierwszy element?
    {
        //przypisanie jako pierwszy element
        first = sb_new;
    }
    else
    {
        //przypisanie jako ostatni element
        person *temp = first;
        
        while (temp->next)
        {
            temp = temp->next;
        }
        
        temp->next = sb_new;
        sb_new->next = 0;
    }
    size++;
}

void list::show_list(int id)
{
    int j = 1;
    person *temp = first;
    
    
    while (temp)
    {
        //wyswietlaj póki temp nie jest nullem
        //zaczynajac od wprowadzonego id-ka
        if (id <= j)
        {
            cout << "\n\tFirst name: " << temp->first_name <<
            "\n\tLast name: "<< temp->last_name <<
            "\n\tAge: " << temp->age<< endl;
        }
        //nastepny element
        temp=temp->next;
        j++;
        
    }
    if (size == 0)
        cout << "\nNie moge wyswietlic, lista jest pusta.";
    else if (size<id) //zprawdzenie w razie pustej lub za malej listy
        cout <<"\n\tPrzepraszam uzytkowniku, ale nie moge zaczac od " << id << " elementu.\n"<<
               "\tMoja dlugosc to tylko " << size << ".\n";
}

void list::delete_person(int id)
{
    if (id == 1) // dla pierwszego el.
    {
        //pierwszy el. wskazuje na 2 el.
        person *temp = first;
        first = temp->next;
    }
    
    if (id>=2) // dla reszty el.
    {
        int i = 1;
        person *temp = first;
        
        while (temp)
        {
            if((i+1) == id) break;
            
            temp = temp->next;
            i++;
        }
        
        //sprawdzenie czy nie jest to ostatni element
        if (temp->next->next == 0)
            temp->next = 0;
        //znalezlismy wskaznik przed tym ktory chcemy usunac
        //wiec nadpisujemy nestępny (czyli ten)
        //elementem o jeden dalej od niego
        else
            temp->next = temp->next->next;
    }
    
    // zmniejszenie licznika wielkosci listy i informacja gdyby byla pusta
    size--;
    if (size == 0)
    {
        cout << "\nLista zostala wyczyszczona lub jest pusta.";
        first = 0;
    }
}

//funkcja do kroku 4
void list::special_peoples(char key)
{
    int counter = 0;
    person *temp = first;
    //sprawdza czy element ma przedostatnia litere imienia
    //taka jak wprowadzony char,
    //czy wiek jest wiekszy niż 18
    bool test = check(key, temp->first_name, temp->age);

    //sprawdzenie pierwszego elementu
    if (test)
    {
        person *sb_new = new person; //nowy element
        first = sb_new;
        
        string first, last;
        int age;
        cout<<"\nPodaj imie: ";
        cin >> first;
        cout << "Podaj nazwisko: ";
        cin >> last;
        cout << "Podaj wiek: ";
        cin >> age;
        
        sb_new->first_name = first;
        sb_new->last_name = last;
        sb_new->age = age;
        sb_new->next = temp;

        counter++;
        size++;
    }
    
    //sprawdzenie reszty elementow
    while(temp->next)
    {
        test = check(key, temp->next->last_name, temp->next->age);
        
        //stwórz do co 2 użytkownika o wieku>18..... i tak dalej
        if (counter%2 == 0 && test)
        {
            person *sb_new = new person;
            string first, last;
            int age;
            
            cout<<"\nPodaj imie: ";
            cin >> first;
            cout << "Podaj nazwisko: ";
            cin >> last;
            cout << "Podaj wiek: ";
            cin >> age;
            
            sb_new->first_name = first;
            sb_new->last_name = last;
            sb_new->age = age;
            
            //przypisuje do nowego el. adres nastepnego
            //oraz do bierzącego el., nowo stworzony el.
            sb_new->next = temp->next;
            temp->next = sb_new;
            size++;
        }
        
        if (test)
            counter++;
        temp = temp->next;
    }
}

//jak juz wspomnialem, sprawdza imie i wiek
bool list::check(char key, string name, int age)
{
    unsigned long pos = name.length() - 1;
    if (name[pos - 1] == key && age>18)
        return true;
    else
        return false;
        
}

int main() {
    string first, last;
    int n, age, del;
    char key;
    //Krok1
    cout << "Podaj ilość osob które chcesz zapisać do listy:  ";
    cin >> n;
    list *base = new list;
    
    for (int i=0; i<n; i++)
    {
        cout<<"\nPodaj imie: ";
        cin >> first;
        cout << "Podaj nazwisko: ";
        cin >> last;
        cout << "Podaj wiek: ";
        cin >> age;
        base->add_person(first, last, age);
    }
    
    //Krok2 i 'jakiś' adres
    int random = (rand() % (base->size + 1));
    cout << "\nWyswietle liste zaczynajac od " << random << " elementu."<< endl;
    base->show_list(random);
    
    //Krok4
    do{
        cout << "Ktora osobe mam wymazac z listy? Zakres: <1," << base->size << ">\n";
        cin >> del;
    }while( del < 1 || del > base->size);
    
    base->delete_person(del);
    
    //małe sprawdzenie zeby nie wyszly dziwne rzeczy
    if(base->size == 0)
    {
        cout << "\n\n===Lista jest pusta, nie mam na czym pracowac.==="<<
                "\n\tMuszę zakończyć to co zacząłem!";
        return 0;
    }
    
    //Krok4
    cout << "\nPodaj litere, po jakiej mam przeszukiwac imiona? ";
    cin >> key;
    base->special_peoples(key);
    
    //Krok5 wyswietle cala liste dla zobaczenia efektu, zostawiam zakomentowany losowy el.
    //random = (rand() % (base->size + 1));
    //cout << "\nWyswietle liste zaczynajac od " << random << " elementu."<< endl;
    //base->show_list(random);
    base->show_list(1);
    
    //Krok6 usuwanie listy stworzona funkcja
    for (int k = base->size ; k>0; k--)
        base->delete_person(1);
    
    //tak dla pewnosci sprawdzimy dlugosc
    base->show_list(1);
    return 0;
}
