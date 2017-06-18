#include <iostream>
#include <vector>

using namespace std;

void printArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void swap(int p, int r, int* arr) {
	int temp = arr[p];
	arr[p] = arr[r];
	arr[r] = temp;
}

int partition(int *arr, int p, int r) {
	int pivot = arr[r];
	while (p < r)
	{
		while (arr[p] < pivot) p++;

		while (arr[r] > pivot) r--;

		if (arr[p] == arr[r]) p++;
		else if (p < r) swap(p, r, arr);
	}
	return r;
}

void swap2(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void bubblesort(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}


void quicksort(int* arr, int p, int r)
{
	if (p < r)
	{
		int j = partition(arr, p, r);
		quicksort(arr, p, j - 1);
		quicksort(arr, j + 1, r);
	}
}

int main() {
	int arr[] = { 2, 6, 3, 5, 1, 7, 8, 4, 9 };
	int size = 9;
	printArray(arr, size);
	quicksort(arr, 0, size - 1);
	printArray(arr, size);

}