#include <stdio.h>
#include <stdlib.h>




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
void *nasobenie(double **A, double **B, double **C, int r_1, int s_1,int r_2, int s_2)
{

    int riadok, stlpec, k;
    for (riadok = 0; riadok < r_1; riadok++)
    {
        for (stlpec = 0; stlpec < s_2; stlpec++)
        {
            C[riadok][stlpec] = 0;
            for (k = 0; k < s_1; k++)
            {
                C[riadok][stlpec] += A[riadok][k] * B[k][stlpec];
            }
        }
    }
    printf("\n Stlpcy a riadky maticy C:\n ");
    for (riadok = 0; riadok < r_1; riadok++)
    {
        for (stlpec = 0; stlpec < s_2; stlpec++)
        {
            printf("%lf ", C[riadok][stlpec]);
        }
        printf("\n ");
    }
}
//Funkcia na nájdenie stĺpca matice, ktorý má najväčší aritmetický priemer
void *priemer_stlpcev(double **C, int s_1, int r_1)
{

    int riadok, stlpec;
    double *average, array_priemer[stlpec], priemer = 0, sum = 0, max_priemer;
    average = array_priemer;

    printf("\n Priemer prvkov stlpcov matice C :\n ");
    for (riadok = 0; riadok < s_1; riadok++)
    {
        for (stlpec = 0; stlpec < r_1; stlpec++)
        {
            sum += C[stlpec][riadok];
        }
        priemer = sum / r_1;
        average[riadok] = priemer;

        printf("\n Priemer prvkov stlpca %d : %lf\n", riadok + 1, priemer);
    }

    printf("\n Stlpec matice C, ktoreho priemer prvkov je najvacsi:  ");
    int max_index = 0;
    max_priemer = average[0];
    for (riadok = 0; riadok < s_1; riadok++)
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
    int riad_A, riad_B, stl_A, stl_B, R_1, R_2, S_1,S_2, i, j;

    printf("Zadaj rozmer maticy A: " );
    scanf("%d %d", &R_1, &S_1);

    printf("Zadaj rozmer maticy B: " );
    scanf("%d %d", &R_2, &S_2);


    double **A = all_memory(R_1, S_1);
    double **B = all_memory(R_2, S_2);
    double **C = all_memory(R_1, S_2);


    while(S_1 != R_2)
    {
        printf("poсet stlpcov prvej matice musi rovnat poctu riadkov druhej matice: \n");
        printf("Zadaj rozmer maticy A: " );
        scanf("%d %d", &R_1, &S_1);
        printf("Zadaj rozmer maticy B: " );
        scanf("%d %d", &R_2, &S_2);
    }

    while(R_1,S_1<=0)
    {
        printf("Zadaj kladnu hodnotu pre maticy A! Tak este raz: ");
        scanf("%d %d", &R_1, &S_1);
    }

    while(R_2,S_2<=0)
    {
        printf("Zadaj kladnu hodnotu pre maticy B! Tak este raz: ");
        scanf("%d %d", &R_2, &S_2);
    }


    for (riad_A = 0; riad_A < R_1; riad_A++)
    {
        for (stl_A = 0; stl_A < S_1; stl_A++)
        {
            printf("Zadaj riadky a stlpcy pre maticy A [%d][%d]:", riad_A, stl_A);
            scanf("%lf", &A[riad_A][stl_A]);
            if (scanf("%lf",&A[riad_A][stl_A]) != 1)
            {
                printf("Ne zadal cislo. \n");
                return 0;

            }

        }
    }


    for (riad_B = 0; riad_B < R_2; riad_B++)
    {
        for (stl_B = 0; stl_B < S_2; stl_B++)
        {
            printf("Zadaj riadky a stlpcy pre maticy B [%d][%d]:", riad_B, stl_B);
            scanf("%lf", &B[riad_B][stl_B]);
             if (scanf("%lf",&B[riad_B][stl_B]) != 1)
            {
                printf("Ne zadal cislo. \n");
                return 0;

            }
        }
    }

    printf("\n Stlpcy a riadky maticy A:\n ");
    for (riad_A = 0; riad_A < R_1; riad_A++)
    {
        for (stl_A = 0; stl_A < S_1; stl_A++)
            printf("%lf ", A[riad_A][stl_A]);
        printf("\n ");
    }


    printf("\n Stlpcy a riadky maticy B:\n ");
    for (riad_B = 0; riad_B < R_2; riad_B++)
    {
        for (stl_B = 0; stl_B < S_2; stl_B++)
            printf("%lf ", B[riad_B][stl_B]);
        printf("\n ");
    }


    nasobenie(A, B, C, R_1, S_1, R_2, S_2);
    priemer_stlpcev(C, S_2, R_1);
    dealokacia(A, R_1);
    dealokacia(B, R_2);
    dealokacia(C, R_1);

    return 0;
}
