/*================================================================
*   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
*
*   FileName   ：Strassen-Matrix-Multiplication.cpp
*   Author     ：He Hongyu(Ray)
*   Date       ：2018-08-14
*   Description：unfinished......
*
================================================================*/
#include <iostream>

using namespace std;

void InitMatrix (int n, int **matrix);

int main()
{
    int n;
    cout << "n of square matrixs:" << endl;
    cin >> n;

    int **matrix_A = new int *[n];
    int **matrix_B = new int *[n];
    int **matrix_C = new int *[n];
    InitMatrix (n, matrix_A);
    InitMatrix (n, matrix_B);
    InitMatrix (n, matrix_C);



    return 0;
}

void InitMatrix (int n, int **matrix)
{
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n]();   //Initialize with 0;
    }
}
