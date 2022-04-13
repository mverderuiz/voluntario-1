#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define PI 3.1415

using namespace std;

void lectura(int xi[][20][20], int N, int P);

float deltaH (int red[][20], float teta[][20], int N, int m, int n, int xi[][20][20], int P, float a[]);

void calca (int xi[][20][20], int P, float a[], int N);

float calcomega (int elemento[], int N, int xi[][20][20], int P, float a[]);

void calcteta (float teta[][20], int N, int xi[][20][20], int P, float a[]);

float solapamiento (int red[][20], int xi[][20][20], float a[], int mu, int N);

void p_aleatorio (int xi[][20][20], int N, int P);

int main (void)
{
    //Variables para numero de iteraciones
    int j, k, i, aux;
    int iteraciones, npasos, escrib;
    npasos = 30;
    //Variables que describen la red neuronal
    int N=20;
    int P=38;  
    float T=0.001;  
    float teta[20][20];
    int red[20][20], xi[P][20][20];
    float a[P];
    //Variables usadas en el algotitmo de ising
    int m, n;
    float deltaE, expo, p, epsilon; 
    //Solapamiento del sistema
    float s[P];
    //Variable para escribir el resultado
    ofstream resultado("38_patrones.txt");
    ofstream solap("38_patrones-sol.txt");
    //Configuracion inicial aleatoria o deformada
    bool aleatorio=false;

    srand (time(NULL));

    //Calculamos el valor de las xi, omegas y tetas
    //lectura(xi, N, P);
    p_aleatorio(xi, N, P);
    calca(xi, P, a, N);
    calcteta(teta, N, xi, P, a);

    //Calculamos la configuración inicial
    if (aleatorio==true)
    {
        for (i=0; i<N; i++)
        {
            for (k=0; k<N; k++) 
            {
                aux=(rand() % 100);
                if (aux<50) red[i][k]=1;
                else red[i][k]=0;
            }
        }
    }
    else
    {
        for (i=0; i<N; i++)
        {
            for (k=0; k<N; k++) 
            {
                aux=(rand() % 100);
                red[i][k] = xi[0][i][k];
                if (aux<30) red[i][k] = 1- red[i][k];
            }
        }
    }
    
    //Dibujamos la configuración inicial
    for (i=0; i<N; i++)
    {
        for (k=0; k<N-1; k++) 
        {
            resultado << red[i][k] << ", " ;
        }
        resultado << red[i][N-1] << endl;
    }
    resultado << endl;   

    //Inicializamos el algoritmo
    iteraciones = npasos*N*N;
    for (i=0; i<iteraciones; i++)
    {
        m = rand() % N;
        n = rand() % N;

        deltaE = deltaH(red, teta, N, m, n, xi, P, a);
        expo= exp(-deltaE/T);
        if (expo<1) p=expo;
        else p=1;
        epsilon = (rand() % 1001)/1000.;
        if (epsilon<p) red[m][n]=1-red[m][n];
        //Escribimos la nueva matriz
        escrib=N*N;
        if (i%escrib==0)
        {
            for (j=0; j<N; j++)
            {
                for (k=0; k<N-1; k++) 
                {
                    resultado << red[j][k] << ", " ;
                }
                resultado << red[j][N-1] << endl;
            }
            resultado << endl;

            solap << i/escrib << "\t";
            for (j=0;j<P;j++)
            {
                s[j] = solapamiento(red, xi, a, j, N);
                solap << s[j] << "\t";
            }           
            solap << endl;
        }
    }

    solap.close();
    resultado.close();    
    return 0;
}

void lectura(int xi[][20][20], int N, int P)
{
    int i, k, j;
    ifstream imagen0;
    ifstream imagen1;
    ifstream imagen2;
    ifstream imagen3;

    imagen0.open("patron7_ale.txt");
    imagen1.open("patron0_ale.txt");
    imagen2.open("patron1_ale.txt");
    imagen3.open("patron2_ale.txt");

    for (i=0;i<N;i++)
    {
        for (k=0;k<N;k++)
        {
            imagen0 >> xi[0][i][k];
            imagen1 >> xi[1][i][k];
            imagen2 >> xi[2][i][k];
            imagen3 >> xi[3][i][k];
        }
    }

    imagen0.close();
    imagen1.close();
    imagen2.close();
    imagen3.close();
    return;
}

float deltaH (int red[][20], float teta[][20], int N, int m, int n, int xi[][20][20], int P, float a[])
{
    int i, j;
    float incremento=0.;
    int elemento[4];
    elemento[2]=m;
    elemento[3]=n;

    if(red[m][n]==0)
    {
        for (i=0; i<N; i++) 
        {
            elemento[0]=i;
            for (j=0; j<N; j++)
            {
                elemento[1]=j;
                incremento = incremento - calcomega(elemento,N, xi, P, a)*red[i][j];
            } 
        }
        incremento = incremento + teta[m][n];
    }
    else
    {
        for (i=0; i<N; i++) 
        {
            elemento[0]=i;
            for (j=0; j<N; j++)
            {
                elemento[1]=j;
                incremento = incremento + calcomega(elemento,N, xi, P, a)*red[i][j];
            } 
        }
        incremento = incremento - teta[m][n];
    }

    return incremento;
}

void calca (int xi[][20][20], int P, float a[], int N)
{
    int r, s, w;

    for (r=0; r<P; r++)
    {
        a[r] = 0.;
        for (s=0; s<N; s++)
        {
            for (w=0; w<N; w++) a[r] = a[r] + xi[r][s][w];
        }
        a[r] = 1.*a[r]/(N*N);
    }

    return;
}

float calcomega (int elemento[], int N, int xi[][20][20], int P, float a[])
{
    int w;
    float omega;
    int i=elemento[0];
    int j=elemento[1];
    int k=elemento[2];
    int l=elemento[3];

    omega = 0.;
    if ((i!=k) || (j!=l))
    {
        for (w=0; w<P; w++) omega = omega + (xi[w][i][j]-a[w])*(xi[w][k][l]-a[w]);
    } 
    omega = 1.*omega/(N*N);
    
    return omega;
}

void calcteta (float teta[][20], int N, int xi[][20][20], int P, float a[])
{
    int i, j, k, l, w;
    int elemento[4];

    for (i=0; i<N; i++)
    {
        elemento[0]=i;
        for (j=0; j<N; j++)
        {
            elemento[1]=j;
            teta[i][j] = 0.;
            for (k=0; k<N; k++)
            {
                elemento[2]=k;
                for (l=0; l<N; l++)
                {
                    elemento[3]=l;
                    teta[i][j] = teta[i][j] + calcomega(elemento, N, xi, P, a);
                }
            }
            teta[i][j] = teta[i][j]/2.;
        }
    }

    return;
}

float solapamiento (int red[][20], int xi[][20][20], float a[], int mu, int N)
{
    float solap=0.;
    int i, j;

    for (i=0;i<N;i++)
    {
        for (j=0;j<N; j++) solap = solap + (xi[mu][i][j]-a[mu])*(red[i][j]-a[mu]);
    }
    solap=1.*solap/(N*N*a[mu]*(1-a[mu]));

    return solap;
}

void p_aleatorio (int xi[][20][20], int N, int P)
{
    int i, k, j, aux;

    srand (time(NULL));

    for (j=0; j<P; j++)
    {
        for (i=0; i<N; i++)
        {
            for (k=0; k<N; k++) 
            {
                aux=(rand() % 100);
                if (aux<50) xi[j][i][k]=1;
                else xi[j][i][k]=0;
            }
        }
    }
    

    return;
}