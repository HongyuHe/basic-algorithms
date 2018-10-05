/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：Square-Matrix-Multiplication_simple.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-03-11
 *   Description：
 *   Email		: hongyu.he@hotmail.com
 *	 GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#include <vector>

#define MAX 1000

using namespace std;

void insertion_sort (int *sequence, int total);
int binary_search (int *sequence, int start, int end, int target);
void printSqc (int *sequence, int total);

int main ()
{
    int total = 0;
    int sequence[MAX] = {0};

    cin >> total;
    cout << "Input: " << endl;
    for (int i = 0; i < total; i++)
    {
        cin >> sequence[i];
    }

	insertion_sort (sequence, total);

    cout << "Output: ";

    printSqc (sequence, total);

    return 0;

}

void insertion_sort (int *sequence, int total)
{
	for (int j = 1; j < total; j++)
    {
    //Print：
        printSqc (sequence, total);

        int key = sequence[j];
		int expos = binary_search (sequence, 0, j - 1, key);

		cout << "ExchPos: " << expos << endl;

		for (int i = j - 1; i >= expos; i--)
		{
			sequence[i + 1] = sequence[i];
		}
        sequence[expos] = key;

    }
}

int binary_search (int *sequence, int start,
                   int end, int target)
{
	if ( end < start ) 	//handle start == 0,end == -1;
    {
        return ++end;

    }
	if (start == end)	//handle start == end;
    {
    	if (sequence[start] == target)
        {
        	return start;
        }else
    	{
    		if (target > sequence[start])
    		{
    			return ++start;
    		}else
    		{
    			return start;
    		}
    	}
    }
    //if (start == end) //mid id not among the sequence, return the position where inserting the key;
    //{
       // if (target >= sequence[start])
        //{
		//	return ++start;
       // }else
       // {
      //  	return start;
      //  }
    //}

    int mid = (end + start) / 2;
    //cout << "Mid :" << mid << endl;

    if (target > sequence[mid])
    {
        binary_search (sequence, mid + 1, end, target);

    }else if (target < sequence[mid])
    {
        binary_search (sequence, start, mid - 1, target);
    }else
    {
        return ++mid;
    }
}

void printSqc (int *sequence, int total)
{
	for (int i = 0; i < total; i++)
        {
            cout << sequence[i] << " ";
        }
        cout << endl << "---------------------" << endl;
}
