#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string tmp; 
    ifstream data("neh.data.txt");
    int pom = 0;
    int N, M;
    int P[10000]; //zadania
    int X[1000];  //kolejnosc
    //--------------------------------------------------WCZYTYWANIE DANYCH
    while(tmp!="data.000:") 
        data>>tmp; 
    data>>N>>M;
    for (int j = 0; j < N * M; j++)
        data >> P[j];
    for (int j = 0; j < N; j++)
        X[j] = j;
    //--------------------------------------------------------------------


    //----------------------------------------------------WYPISANIE DANYCH
    for(int i = 0; i < N * M; i++) {
        cout << P[i] << " ";
        pom++;
        if(pom == 3) {
            cout << endl; 
            pom = 0;
        }
    }
    //--------------------------------------------------------------------

    return 0;
}