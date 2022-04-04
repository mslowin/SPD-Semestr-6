#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string tmp; 
    ifstream data("neh.data.txt");
    string s="data.",s1;
    int pom = 0;
    int N;          //ilosc zadan (np. w pierwszym zestawie wynosi 4)
    int M;          //liczba maszyn (np. w pierwszym zestawie wynosi 3)
    int P[10000];   //zadania
    int X[1000];    //kolejnosc

    for(int i = 0; i < 1; i++) {                  //petla for do iteracji po wszystkich 120 zbiorach danych
    //TODO:    zamienic w petli for, żeby i < 121

        //----------------------------------------------------------WCZYTYWANIE DANYCH
        if(i < 10) {
            s1 = "data.00" + to_string(i) + ":";
        }
        else if(i < 100) {
            s1 = "data.0" + to_string(i) + ":";
        }
		else
		{
			s1 = "data." + to_string(i) + ":";
		}
        while(tmp != s1) 
            data >> tmp; 
        data >> N >> M;
        for (int j = 0; j < N * M; j++)
            data >> P[j];
        for (int j = 0; j < N; j++)
            X[j] = j;
        //----------------------------------------------------------------------------


        //------------------------------------------------------------WYPISANIE DANYCH
        for(int i = 0; i < N * M; i++) {
            cout << P[i] << " ";
            pom++;
            if(pom == 3) {
                cout << endl; 
                pom = 0;
            }
        }
        //----------------------------------------------------------------------------

        //TODO: Algorytm szeregowania zadań neh
    }
    return 0;
}