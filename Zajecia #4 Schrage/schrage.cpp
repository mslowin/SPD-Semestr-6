#include <iostream>

using namespace std;

int max_time_of_jobs(int num_of_jobs, int *R, int *P, int *Q);
// int max_Q(int num_of_jobs, int *tab_RQ[2]);

int main()
{
    //  X   = { 0, 1, 2, 3, 4, 5, 6}
    int R[] = {10,13,11,20,30, 0,30};
    int P[] = { 5, 6, 7, 4, 3, 6, 2};
    int Q[] = { 7,26,24,21, 8,17, 0};
    const int num_of_jobs = sizeof(R)/sizeof(R[0]);
    int pom = 0;
    int X[num_of_jobs];
    int tab_RQ[num_of_jobs][2]; // przechowuje R i Q zadań, aby je porównać (druga tabela, kora byla na ta tablicy)

    for (int i = 0; i < num_of_jobs; i++)
        X[i] = i;

    int max_time = max_time_of_jobs(num_of_jobs,R,P,Q);


    for(int t = 0; t <= 31; t++)  // TODO: Zmienić to iterowanie jakoś, żeby było oki (może iterować tylko po kolejnych wartościach R)
    // for(int t = R[0]; t <= R[num_of_jobs]; t++)
    {
      pom = 0;
      cout << "Wszystkie zadania, ktorych R jest miejszy od danej chwili:   (chwila = " << t << ")" << endl;
      cout << " R\tQ" << endl;
      for(int i = 0; i < num_of_jobs; i++)
      {
        // cout << t << endl;
        if(R[i] < t)
        {
          tab_RQ[i][0] = R[i];
          tab_RQ[i][1] = Q[i];
          pom ++; // 7 w ostatnim miejscu

          cout << tab_RQ[i][0] << "\t" << tab_RQ[i][1] << endl;
        }
        // int max_Q_idx = max_Q(pom, tab_RQ);
      } 
      cout << endl;
    }
    return 0;
}

int max_time_of_jobs(int num_of_jobs,int *R, int *P, int *Q)
{
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