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
	cout << "�ּҰ�: " << list[0]<< endl;
	cout << "�ִ밪: " << list[9]<< endl;

	
	cout << "���� ����: ";
	for (int i = 0; i < MAX_NUM; ++i) {
		cout << list[i];
		if (i != MAX_NUM - 1)
			cout << ", ";
	}
	cout << endl;


	bubble_sort(list, MAX_NUM);
	cout << "���� ����: ";
	for (int i = 0; i < MAX_NUM; ++i) {
		cout << list[i];
		if (i != MAX_NUM - 1)
			cout << ", ";
	}
	cout << endl;

	cout << "������Ű��а� 12171850 ������" << endl;
	return 0;
}

// ���� ���Ŀ� ���� ����
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

// ���� ���Ŀ� ���� ����
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
