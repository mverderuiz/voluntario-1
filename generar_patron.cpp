#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define PI 3.1415

using namespace std;

int main (void)
{
    int N=20;
    int i, k, aux, red[N][N];

    ofstream resultado("patron_ale.txt");

    srand (time(NULL));

    for (i=0; i<N; i++)
    {
        for (k=0; k<N; k++) 
        {
            aux=(rand() % 100);
            if (aux<50) red[i][k]=1;
            else red[i][k]=0;
        }
    }

    for (i=0; i<N; i++)
    {
        for (k=0; k<N-1; k++) 
        {
            resultado << red[i][k] << "\t" ;
        }
        resultado << red[i][N-1] << endl;
    }
    resultado << endl;  

    return 0;
}
