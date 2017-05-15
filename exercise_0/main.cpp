#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

int n, g, d, k, dodatnie = 0, ujemne = 0;
//int n=13, d=-9, g=2, k=2, dodatnie = 0, ujemne = 0;

void wprowadz_dane()
{
    cout << "Podaj n:" << endl;
    do{
        cin >> n;
    }while(n<=0);
    cout << "Podaj przedzia¸ <d, g>";
    do {
    cin >> d >> g;
    }while(g<d);
    cout << "przedzia¸ to: <" << d << ", " << g << ">" << endl;
    cout << "Podaj k:" << endl;
    cin >> k;
}

int randomowe_liczby(){
    return ((rand() % (g - d + 1)) + d);
}

void wypełnij_losowymi(int id ,int tab[id])
{
    for (int i=0;i<n;i++)
    {
        tab[i] = randomowe_liczby();
    }
}

void wyswietl_kolumny(int kol, int tab[kol])
{
    cout << "Wyświetle " << kol << " liczb, po " << k << " w wierszu.\n";
    for (int j=0;j<kol;j++)
    {
        if( j%k==0 )
            cout << "\n\t";
        cout << tab[j] << "  ";
    }
    cout << "\n==== wyświetlone ====\n";
}

void licz_parzyste(int tab[])
{
    int pos = 0, neg = 0;
    for(int i=0; i<n; i++)
    {
        if(tab[i]%2 == 0)
        {
            if(tab[i] >= 0)
                pos++;
            else
                neg++;
        }
    }
    dodatnie = pos;
    ujemne = neg;
    cout << "\nDodatnie: " << dodatnie << ", ujemne: "<< ujemne << endl;
}

void wypelnij(int A[n], int tabB[dodatnie], int tabC[ujemne])
{
    int liczB = 0, liczC = 0;
    for(int i=0; i<n; i++)
    {
        if(A[i]%2 == 0)
            if(A[i] >= 0)
            {
                tabB[liczB] = A[i];
                liczB++;
            }
            else
            {
                tabC[liczC] = A[i];
                liczC++;
            }
    }
}

void sortowanie( int tab[], int size )
{
    for( int i = 0; i < size; i++ )
    {
        for( int j = 0; j < size - 1; j++ )
        {
            if( tab[ j ] > tab[ j + 1 ] )
                swap( tab[ j ], tab[ j + 1 ] );
            
        }
    }
}


int main()
{
    wprowadz_dane();
    cout << "\n\tWielkość tabeli A: "<< n << "\n\tliczb w jednej lini wydruku: "<< k << "\n\tZakres: <"
         << g <<", " << d << ">\n\n";
    int A[n];
    //wprowadz_do_tablicy(tab);
    wypełnij_losowymi(n, A);
    wyswietl_kolumny(n, A);
    licz_parzyste(A);
    int B[dodatnie];
    int C[ujemne];
    wypelnij(A, B, C);
    wyswietl_kolumny(dodatnie, B);
    wyswietl_kolumny(ujemne, C);
    sortowanie(B, dodatnie);
    sortowanie(C, ujemne);
    cout << "\n==== Posortowane ==== \n\nB:\n";
    wyswietl_kolumny(dodatnie, B);
    cout << "\nC:\n";
    wyswietl_kolumny(ujemne, C);

    return 0;
}
