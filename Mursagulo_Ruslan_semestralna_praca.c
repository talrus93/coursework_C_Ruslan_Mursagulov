#include <stdio.h>
#include <stdlib.h>


#define R_1 2
#define R_2 3
#define S 3

//Funkcia na uvoľnenie pamäte pridelenej maticiam
void dealokacia(double **polia, int riadok)
{
    int i;
    for (i = 0; i < riadok; i++)
    {
        free(polia[i]);
    }
    free(polia);
    polia = NULL;
}
//Funkcia na prideľovanie pamäte pre matice
double **all_memory(int riadok, int stlpec)
{
    double **matica;
    int i;

    if ((matica = (double **)malloc(riadok * sizeof(double *))) == NULL)
    {
        printf("Nemoje vytvorit maticu.");
        exit(1);
    }
    for (i = 0; i < riadok; i++)
    {
        if ((matica[i] = (double *)malloc(stlpec * sizeof(double))) == NULL)
        {
            printf("Nemoje vytvorit maticu.");
            dealokacia(matica, i);
            exit(1);
        }
    }
    return matica;
}
//Funkcia pre násobenie matíc
void *nasobenie(double **A, double **B, double **C, int r_1, int s)
{

    int riadok, stlpec, k;
    for (riadok = 0; riadok < r_1; riadok++)
    {
        for (stlpec = 0; stlpec < s; stlpec++)
        {
            C[riadok][stlpec] = 0;
            for (k = 0; k < s; k++)
            {
                C[riadok][stlpec] += A[riadok][k] * B[k][stlpec];
            }
        }
    }
    printf("\n Stlpcy a riadky maticy C:\n ");
    for (riadok = 0; riadok < r_1; riadok++)
    {
        for (stlpec = 0; stlpec < s; stlpec++)
        {
            printf("%lf ", C[riadok][stlpec]);
        }
        printf("\n ");
    }
}
//Funkcia na nájdenie stĺpca matice, ktorý má najväčší aritmetický priemer
void *priemer_stlpcev(double **C, int s, int r_1)
{

    int riadok, stlpec;
    double *average, array_priemer[stlpec], priemer = 0, sum = 0, max_priemer;
    average = array_priemer;

    printf("\n Priemer prvkov stlpcov matice C :\n ");
    for (riadok = 0; riadok < s; riadok++)
    {
        for (stlpec = 0; stlpec < r_1; stlpec++)
        {
            sum += C[stlpec][riadok];
        }
        priemer = sum / r_1;
        average[riadok] = priemer;
        sum = 0;
        printf("\n Priemer prvkov stlpca %d : %lf\n", riadok + 1, priemer);
    }

    printf("\n Stlpec matice C, ktoreho priemer prvkov je najvacsi:  ");
    int max_index = 0;
    max_priemer = average[0];
    for (riadok = 0; riadok < s; riadok++)
    {
        if (average[riadok] > max_priemer)
        {
            max_priemer = average[riadok];
            max_index = riadok;

        }
    }
    printf(" %d = %lf\n ",max_index + 1, max_priemer);

}

/*Hlavná funkcia umožňuje používateľovi nastaviť čísla pre matice,
potom program načíta údaje a pomocou funkcie nasobenie nájde tretiu maticu,
potom pomocou funkcie priemer_stlpcev nájde stĺpec s najväčšou priemernou hodnotou
a nakoniec kód pomocou funkcie dealokacia uvoľní pamäť alokovanú pre matice.*/
int main()
{
    double **A = all_memory(R_1, S);
    double **B = all_memory(R_2, S);
    double **C = all_memory(R_1, S);
    int riad_A, riad_B, stl_A, stl_B, i, j;


    for (riad_A = 0; riad_A < R_1; riad_A++)
    {
        for (stl_A = 0; stl_A < S; stl_A++)
        {
            printf("Zadaj riadky a stlpcy pre maticy A [%d][%d]:", riad_A, stl_A);
            scanf("%lf", &A[riad_A][stl_A]);
        }
    }

    for (riad_B = 0; riad_B < R_2; riad_B++)
    {
        for (stl_B = 0; stl_B < S; stl_B++)
        {
            printf("Zadaj riadky a stlpcy pre maticy B [%d][%d]:", riad_B, stl_B);
            scanf("%lf", &B[riad_B][stl_B]);
        }
    }

    printf("\n Stlpcy a riadky maticy A:\n ");
    for (riad_A = 0; riad_A < R_1; riad_A++)
    {
        for (stl_A = 0; stl_A < S; stl_A++)
            printf("%lf ", A[riad_A][stl_A]);
        printf("\n ");
    }


    printf("\n Stlpcy a riadky maticy B:\n ");
    for (riad_B = 0; riad_B < R_2; riad_B++)
    {
        for (stl_B = 0; stl_B < S; stl_B++)
            printf("%lf ", B[riad_B][stl_B]);
        printf("\n ");
    }


    nasobenie(A, B, C, R_1, S);
    priemer_stlpcev(C, S, R_1);
    dealokacia(A, R_1);
    dealokacia(B, R_2);
    dealokacia(C, R_1);

    return 0;
}
