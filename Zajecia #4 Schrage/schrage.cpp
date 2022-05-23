#include <iostream>

using namespace std;

int  max_time_of_jobs(int num_of_jobs, int *R, int *P, int *Q);
int* sort_and_return_new_array(int *R, int num_of_elements);
int* sort_easy(int *R, int num_of_elements);
// int  max_Q(int num_of_jobs, int *tab_RQ[2]);

int main()
{
    //  X   = { 0, 1, 2, 3, 4, 5, 6}
    int R[] = {10,13,11,20,30, 0,30};
    int P[] = { 5, 6, 7, 4, 3, 6, 2};
    int Q[] = { 7,26,24,21, 8,17, 0};
    const int num_of_jobs = sizeof(R)/sizeof(R[0]);   // dla przykładu podstawowego wynosi 7
    int pom = 0;
    int X[num_of_jobs];         // przechowywuje kolejność wykonywania się zadań
    int tab_RQ[num_of_jobs][2]; // przechowuje R i Q zadań, aby je porównać (druga tabela, kora byla na ta tablicy)

    for (int i = 0; i < num_of_jobs; i++) // przypisanie kolejności 1,2,3,... do tablicy X[]
        X[i] = i;

    int max_time = max_time_of_jobs(num_of_jobs,R,P,Q); // dla przykładu podstawowego wynosi 250

    int temp = 0;   // zmienna pomocnicza do iteracji po tablicy sortR

    int *sortR = sort_and_return_new_array(R, num_of_jobs); // sortR jest tablicą zawierającą posortowane element z tablicy R

    for(int t = 0; t < num_of_jobs; t++)    // kolejnych chwil czasu jest 7 i po inich iterujemy
    {
        //----------
        temp = t;       // zmienne utworzone, aby iterować jedynie po liczbach z tablicy sortR
        t = sortR[t];   // dla przypadku podstawowego będzie 7 iteracji dla t równych 0, 10, 11, 13, 20, 30, 30
        //----------

        pom = 0;
        cout << "Wszystkie zadania, ktorych R jest miejszy od danej chwili:   (chwila = " << t << ")" << endl;
        cout << " R\tQ" << endl;
        for(int i = 0; i < num_of_jobs; i++)
        {
            if(R[i] < t)
            {
                tab_RQ[i][0] = R[i];
                tab_RQ[i][1] = Q[i];
                pom ++;                 // 7 w ostatniej iteracji

                cout << tab_RQ[i][0] << "\t" << tab_RQ[i][1] << endl;
            }
            // int max_Q_idx = max_Q(pom, tab_RQ);
        }
        cout << endl;

        //----------
        t = temp;   // powrót zmiennej t do zakresu, żeby nie była większa od num_of_jobs
        //----------
    }
    return 0;
}

int* sort_and_return_new_array(int *R, int num_of_elements)
{
    // static int newArray[num_of_elements];
    int *newArray = new int [num_of_elements];  // utworzenie nowej tablicy, która będzie sortowana
    int temp = 0;
    for(int i = 0; i < num_of_elements; i++)    // przypisanie nowej tablicy zmiennych z tablicy R
        newArray[i] = R[i];
    

    for(int i = 0; i < num_of_elements; i++)
	{		
		for(int j = i + 1; j < num_of_elements; j++)
		{
			if(newArray[i] > newArray[j])
			{
				temp = newArray[i];
				newArray[i] = newArray[j];
				newArray[j] = temp;
			}
		}
	}
    
    return newArray;
}

int max_time_of_jobs(int num_of_jobs,int *R, int *P, int *Q)
{
  // funkcja zlicza całkowity maksymalny czas w najgorszym przypadku działania. Tego czasu na pewno nie da się przekroczyć
  // prawdopodobnie na późniejszym etapie pisania programu nie będzie trzeba obliczać tego czasu
    int max_time = 0;
    for(int i = 0; i < num_of_jobs; i ++)
    {
        max_time = max_time + R[i] + P[i] + Q[i];
    }
    return max_time;
}

// int max_Q(int num_of_jobs, int *tab_RQ[2])
// {
//   for(int i = 0; i < num_of_jobs; i++)
//   {
//     if(i == num_of_jobs - 1)
//       break;
//     else
//     {
//       swap(tab_RQ[i][1], tab_RQ[i+1][1]);
//     }
//     cout << tab_RQ[i][0] << "  " << tab_RQ[i][1] << endl;
//   }
//   return 1;
// }