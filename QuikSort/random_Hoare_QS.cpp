/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   : random_Hoare_QS.cpp
 *   Author    	: He Hongyu (Ray)
 *   Date       : 2018-10-18
 *   Description: C++ implementation of QuickSort using Hoare's
   				 partition scheme (Following CRLS pseudo code from MIT).
 *   Email		: hongyu.he@hotmail.com
 *   GitHub		: https://github.com/HongyuHe
 ================================================================*/
 #include <iostream>
 #include <cstdlib>
 #include <ctime>
 #include <vector>

using namespace std;

int HoarePartition(vector<int>& sequence, int low, int high);
int RandomPartition(vector<int>& sequence, int low, int high);
void RandomQuickSort(vector<int>& sequence, int low, int high);

int main ()
{
	vector<int> sequence = {3, 9, 6, 7, 5, 4, 1, 8, 2, 10};

	RandomQuickSort(sequence, 0, sequence.size() - 1);

	for (auto num:sequence ) { //Print result;
		cout << num << " ";
	}
	cout << endl;
	return 0;
}

void SwapValue(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int HoarePartition(vector<int>& sequence, int low, int high) {
	int pivot = sequence.at(low); //Select the first element as pivot;
	int i = low;
	int j = i + 1;

	while (j <= high) {
		if (sequence.at(j) < pivot) {
			i++; // Increase i before swaping in order to avoid the pivot and move on;
			SwapValue(sequence.at(i), sequence.at(j));
		}
		j++;
	}
	SwapValue(sequence.at(i), sequence.at(low)); //Put pivot in the right place

	return i;
}

int RandomPartition(vector<int>& sequence, int low, int high) {
	srand(time(NULL));
	int random_pivot = rand() % (high - low + 1) + low;
	//Give the random pivot value to the first element;
	SwapValue(sequence.at(low), sequence.at(random_pivot));

	return HoarePartition(sequence, low, high);
}

void RandomQuickSort(vector<int>& sequence, int low, int high) {
	if (high > low) {
		int part_index = RandomPartition(sequence, low, high);

		RandomQuickSort(sequence, low, part_index - 1);
		RandomQuickSort(sequence, part_index + 1, high);
	}
}
