#include <iostream>
#include <fstream>

using namespace std;

int* szereguj_123(int N, int *X)
{
    for(int i=0; i<N; i++)
        X[i]=i;
    return X;
}

int* szereguj_sortR(int N, int *X, int *R, int *P, int *Q)
{
    int tempR[100];  //tablica pomocnicza do sortowania

    for(int a=0; a<N; a++) 
        X[a]=a;

    for(int a=0; a<N; a++)
        tempR[a] = R[a];

    for(int i = 0; i < N - 1; i++)
        for(int j = 0; j < N - 1; j++)
            if(tempR[j] > tempR[j + 1]) 
            {
                swap(tempR[j], tempR[j+1]); 
                swap(X[j], X[j+1]);
            }
    return X;
}

int* szereguj_sortQ(int N, int *X, int *R, int *P, int *Q)
{
    int tempR[100];  //tablica pomocnicza do sortowania
    int tempP[100];  //tablica pomocnicza do sortowania
    int tempQ[100];  //tablica pomocnicza do sortowania

    for(int a=0; a<N; a++) 
        X[a]=a;
    for(int a=0; a<N; a++)
        tempR[a] = R[a];
    for(int a=0; a<N; a++)
        tempP[a] = P[a];
    for(int a=0; a<N; a++)
        tempQ[a] = Q[a];

    for(int i = 0; i < N - 1; i++)
        for(int j = 0; j < N - 1; j++)
            if(tempR[j] > tempR[j + 1]) 
            {
                swap(tempR[j], tempR[j+1]); 
                swap(tempP[j], tempP[j+1]); 
                swap(tempQ[j], tempQ[j+1]);
                swap(X[j], X[j+1]);
            }

    for(int i = 0; i < N - 1; i++)
    {
        for(int j = 0; j < N - 1; j++)   
        {
            if(tempQ[j] < tempQ[j + 1] && tempR[j] >= tempQ[j]) 
            {
                swap(tempR[j], tempR[j+1]);
                swap(tempQ[j], tempQ[j+1]); 
                swap(X[j], X[j+1]);
            }
        }
    }
    return X;
}

int oblicz_Cmax(int nr_algorytmu, int N, int*R, int*P, int*Q, int*X)
{
    switch(nr_algorytmu)
    {
    case 1:
        X = szereguj_123(N, X);                 //algorytm szereguje zadania od 1 do N
        break;
    case 2:
        X = szereguj_sortR(N, X, R, P, Q);      //algorytm szereguje zadania zgodnie z wielkosciami R (rosnaco)
        break;
    case 3:
        X = szereguj_sortQ(N, X, R, P, Q);
        break;
    }
    

    int m = 0, c = 0;
    for(int id=0;id<N;id++)
    {
        int i = X[id];
        m = max(R[i], m) + P[i];
        c = max(m+Q[i], c);
    }
    return c;
}

int main() 
{
    int N, R[100], P[100], Q[100], X[100], Cmax;

    
    string tmp; 
    string data_nr[4] = { "data.1","data.2","data.3","data.4" };

    for(int a = 1; a < 4; a++) //petla for sluzaca do przemieszczania sie pomiedzy trzema zaimplementowanymi algorytmami
    {
        ifstream data("rpq.data.txt");
        if(a==1) cout << "Algorytm 123: " << endl;
        if(a==2) cout << "Algorytm sortR: " << endl;
        if(a==3) cout << "Algorytm sortRQ: " << endl;
        for(int i = 0; i < 4; i++) //petla for sluzaca do przemieszczania sie pomiedzy czterema zbiorami danych
        {   
            //-----------------------------------------WCZYTYWANIE
            while(tmp!=data_nr[i]) 
                data>>tmp; 
            data>>N;
            for(int i=0;i<N;i++) 
                data>>R[i]>>P[i]>>Q[i];
            //---------------------------------------------------
            
            int c = oblicz_Cmax(a,N,R,P,Q,X);//----------ALGORYTM

            //------------------------------------------WYPISANIE
            cout << "To jest kolejnosc X: ";
            for(int i=0;i<N;i++) 
                cout<<X[i]+1<<" "; 
            cout<<endl;
            cout<<c<<endl;
            Cmax=Cmax+c;
            //---------------------------------------------------
        }
        cout << endl << "Cmax = " << Cmax << endl << endl;
        data.close();
        Cmax = 0;
    }
    return 0;
}