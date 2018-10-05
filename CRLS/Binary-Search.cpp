/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：Binary-Search.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-03-01
 *   Description：
 *   Email		: hongyu.he@hotmail.com
 *	 GitHub		: https://github.com/HongyuHe
 ================================================================*/

#include <iostream>
#include <string.h>
#define MAX 1000

using namespace std;

int binary_search (int *sequence, int start,
                   int end, int target);
void testPrint (int *sequence, int start, int end);


int main()
{
    int total;
    int sequence[MAX] = {0};
    int target = 0;

    cout << "Total:___\b\b\b";
    cin >> total;
    cout << "Target:___\b\b\b";
    cin >> target;

    cout << endl << "Input :" << endl;
    for (int i = 0; i < total; i++)
    {
        cin >> sequence[i];
    }

    int result = binary_search (sequence, 0,
                                total - 1, target);

    if (result < 0)
    {
        cout << "NULL" << endl;
    }else
    {
        cout << "Result: " << result << endl;
    }

    return 0;
}

int binary_search (int *sequence, int start,
                   int end, int target)
{
    if ( end < start ) 	//handle start == 0,end == -1;
    {
        testPrint (sequence, start, end);
        return -1;

    }
	if (start == end)	//handle start == end;
    {
    	if (sequence[start] == target)
        {
        	testPrint (sequence, start, end);
        	return start;
        }else
    	{
    		return -1;
    	}
    }

    int mid = (end + start) / 2;

    cout << "Mid :" << mid << endl;
    testPrint (sequence, start, end);

    if (target > sequence[mid])
    {
        binary_search (sequence, mid + 1, end, target);

    }else if (target < sequence[mid])
    {
        binary_search (sequence, start, mid - 1, target);
    }else
    {
        return mid;
    }
}

void testPrint (int *sequence, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        cout << sequence[i] << " ";
    }
    cout << endl << "--------------" << endl;
}
