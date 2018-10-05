/*================================================================
*   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
*
*   FileName   ：Find-Maximum-Subarray.cpp
*   Author     ：He Hongyu(Ray)
*   Date       ：2018-03-06
*   Description：Using "Divide and Conquer" method to find the maximum subarray;
*   Email	   : hongyu.he@hotmail.com
*	GitHub	   : https://github.com/HongyuHe
================================================================*/
#include <iostream>
#include <limits.h>

using namespace std;

#define MAX_SIZE 1000

typedef struct ArrayInfo
{
    int leftBorder;
    int rightBorder;
    int sum;
}
ArrayInfo;

ArrayInfo find_maximum_subarray (int *original_array,
				 				 int right,
				 				 int left);
ArrayInfo find_max_crossing_subarrry (int *original_array,
				      				 int right,
				      				 int left);
ArrayInfo arrayCompare (ArrayInfo leftMaxArray,
                        ArrayInfo rightMaxArray,
                        ArrayInfo crossMaxArray);

int main()
{
    int total = 0;
    int original_array[MAX_SIZE] = {0};
    ArrayInfo maxSubArray;

    cin >> total;
    cout << "Input :" << endl;

    for (int i = 0; i < total; i++)
    {
        cin >> original_array[i];
    }

    maxSubArray = find_maximum_subarray (original_array, 0, total - 1);

    cout << "Output(maxSubArray): " << endl;
    for (int i = maxSubArray.leftBorder;
             i <= maxSubArray.rightBorder;
             i++)
    {
        cout << original_array[i] << " ";
    }
    cout << endl;

    return 0;
}

ArrayInfo find_maximum_subarray (int *original_array, int left, int right)
{
    ArrayInfo maxSubArray;
    ArrayInfo leftMaxArray;
    ArrayInfo rightMaxArray;
    ArrayInfo crossMaxArray;

    if (left == right)
    {
        maxSubArray.rightBorder = right;
        maxSubArray.leftBorder = left;
        maxSubArray.sum = original_array[left];

        return maxSubArray;
    }

    int mid = (right + left) / 2;

    leftMaxArray = find_maximum_subarray (original_array, right, mid);
    rightMaxArray = find_maximum_subarray (original_array, mid + 1, left);
    crossMaxArray = find_max_crossing_subarrry (original_array, left, right);

    maxSubArray = arrayCompare (leftMaxArray, rightMaxArray, crossMaxArray);
    return maxSubArray;
}

ArrayInfo find_max_crossing_subarrry (int *original_array, int left, int right)
{
    ArrayInfo crossMaxArray;
    int mid = (right + left) / 2;

    int leftBorder = mid;
    int leftSum =  INT_MIN;
    int curSum = 0;

    for (int i = mid; i >= left; i--)
    {
        curSum += original_array[i];
        if (curSum > leftSum)
        {
            leftSum = curSum;
            leftBorder = i;
        }
    }
    crossMaxArray.leftBorder = leftBorder;
//-----------------------------------------
    int rightSum =  INT_MIN;
    int rightBorder = mid + 1;	//here must be (mid+1) rather than mid, or original_array[mid] will be sumed twice;
    curSum = 0;

    for (int i = mid + 1; i <= right; i++)
    {
        curSum += original_array[i];
        if (curSum > rightSum)
        {
            rightSum = curSum;
            rightBorder = i;
        }
    }
    crossMaxArray.rightBorder = rightBorder;
    crossMaxArray.sum = rightSum + leftSum;

    return crossMaxArray;
}

ArrayInfo arrayCompare (ArrayInfo leftMaxArray,
                        ArrayInfo rightMaxArray,
                        ArrayInfo crossMaxArray)
{
    ArrayInfo arrayInfoList[] = {rightMaxArray, crossMaxArray, leftMaxArray};
    ArrayInfo maxSubArray(rightMaxArray);

    for (int i = 0; i < 3; i++)
    {
        if (arrayInfoList[i].sum > maxSubArray.sum)
        {
            maxSubArray = arrayInfoList[i];
        }
    }

    return maxSubArray;
}
