#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define PI 3.1415

using namespace std;

void lectura(int xi[][64][64], int N, int P);

float deltaH (int red[][64], float teta[][64], int N, int m, int n, int xi[][64][64], int P, float a[]);

void calca (int xi[][64][64], int P, float a[], int N);

float calcomega (int elemento[], int N, int xi[][64][64], int P, float a[]);

void calcteta (float teta[][64], int N, int xi[][64][64], int P, float a[]);

float solapamiento (int red[][64], int xi[][64][64], float a[], int mu, int N);

int main (void)
{
    int j, k, i;
    int N=64;
    
    int red[64][64];
    
    ofstream resultado("rep_imagen5.txt");
    ifstream inicio("imagen5.txt");

    for (i=0;i<N;i++)
    {
        for (k=0;k<N;k++)
        {
            if (!inicio.eof()) inicio >> red[i][k];
        }
    }
    
    //Dibujamos la configuración final
    for (i=0; i<N; i++)
    {
        for (k=0; k<N-1; k++) 
        {
            resultado << red[i][k] << ", " ;
        }
        resultado << red[i][N-1] << endl;
    }
    resultado << endl;  

    resultado.close();
    inicio.close();     

    return 0;
}
