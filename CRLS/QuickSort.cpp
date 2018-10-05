/*================================================================
*   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
*
*   FileName   ：QuickSort.cpp
*   Author     ：He Hongyu(Ray)
*   Date       ：2018-03-21
*   Description：
*   Email	   : hongyu.he@hotmail.com
*	 GitHub	   : https://github.com/HongyuHe
================================================================*/
#include <iostream>
#include <vector>

using namespace std;

template <typename T1,typename T2>
void ExchangeVal (T1 *num_1, T2 *num_2);

void QuickSort(vector<double>& sequence, int left, int right);

int main()
{
    int total = 0;
    vector<double> sequence;

    cout << "Total: ";
    cin >> total;
    sequence.resize(total);

    for (int i = 0; i < total; i++) {
        cin >> sequence.at(i);
    }

    QuickSort(sequence, 0, sequence.size() - 1);

    //Output:
    for (vector<double>::iterator it = sequence.begin();
         it < sequence.end(); it++) {
        cout << *it << " " ;
    }
    cout << endl;

    return 0;
}

void QuickSort(vector<double>& sequence, int left, int right) {
	if (left < right) {
		return;
	}

    int i = left;
    int j = i + 1;
    int pivot = i;

    while (j <= right) {

        if (sequence.at(j) < sequence.at(pivot)) {
          i++;  //increase i before exchange value, otherwise, pivot will be changed;
          ExchangeVal (&sequence.at(i), &sequence.at(j));
        }
        j++;
    }
    ExchangeVal (&sequence.at(i), &sequence.at(pivot));

    QuickSort (sequence, left, i - 1);
    QuickSort (sequence, i + 1, right);
}

template <typename T1,typename T2>
void ExchangeVal (T1 *num_1, T2 *num_2) {
    T1 tmp = *num_1;
    *num_1 = *num_2;
    *num_2 = tmp;
}
