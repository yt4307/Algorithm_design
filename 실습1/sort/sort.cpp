#include <iostream>
using namespace std;

void insertion_sort(int*, int);
void bubble_sort(int*, int);

int main() {
	constexpr int MAX_NUM = 10;
	int list[MAX_NUM]{ };
	for (int i = 0; i < MAX_NUM; ++i)
		cin >> list[i];


	insertion_sort(list, MAX_NUM);
	cout << "최소값: " << list[0]<< endl;
	cout << "최대값: " << list[9]<< endl;

	
	cout << "정순 정렬: ";
	for (int i = 0; i < MAX_NUM; ++i) {
		cout << list[i];
		if (i != MAX_NUM - 1)
			cout << ", ";
	}
	cout << endl;


	bubble_sort(list, MAX_NUM);
	cout << "역순 정렬: ";
	for (int i = 0; i < MAX_NUM; ++i) {
		cout << list[i];
		if (i != MAX_NUM - 1)
			cout << ", ";
	}
	cout << endl;

	cout << "정보통신공학과 12171850 정연한" << endl;
	return 0;
}

// 정순 정렬용 삽입 정렬
void insertion_sort(int* list, int n) {
	int temp{ };

	for (int i = 1; i < n; ++i) {
		for (int j = i; j > 0; --j) {
			if (list[j - 1] > list[j]) {
				temp = list[j - 1];
				list[j - 1] = list[j];
				list[j] = temp;
			}
		}
	}
}

// 역순 정렬용 버블 정렬
void bubble_sort(int* list, int n) {
	int temp{ };

	for (int i = n; i > 0; i--) {
		for (int j = n - 1 - i; j >= 0; j--) {
			if (list[j] < list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}
