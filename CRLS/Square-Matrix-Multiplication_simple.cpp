/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：Square-Matrix-Multiplication_simple.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-05-05
 *   Description：simple matrix multiplacation which is O(n^2)
 *   Email		: hongyu.he@hotmail.com
 *	 GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#define MAX_N 100

using namespace std;

int main()
{
    int n = 0;
    int matrix_1[MAX_N][MAX_N] = {0};
    int matrix_2[MAX_N][MAX_N] = {0};
    int matrix_result[MAX_N][MAX_N] = {0};

    cout << "n for square matrix?" << endl;
    cin >> n;

    cout << "Input Matrix_1: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix_1[i][j];
        }
    }
    cout << "Input Matrix_2: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix_2[i][j];
        }
    }

    //Mutiply:
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                matrix_result[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }

    //Print:
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix_result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
