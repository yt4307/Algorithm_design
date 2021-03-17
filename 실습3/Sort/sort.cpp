#include <iostream>
#include <random>
#include <chrono>
using std::cout;
using std::endl;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;


// merge������ �ϱ� ���� �ӽ� �迭 ����
int tmp[100000];

void selectionSort(int[], int);
void mergeSort(int[], int, int, int);
void merge(int[], int, int, int, int);
void checkSort(int[], int);

int main() {
	int Array[]{ 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 }; // 10���� ���� ���� �迭 ����

	random_device rd;
	mt19937 gen(rd()); // �õ带 �־ ���� ���� ���� �ʱ�ȭ
	uniform_int_distribution<int> dis(0, 100000); // 0���� 10������ �յ� ���� ����
	int *Array2 = new int[100000];
	for (int i{}; i < 100000; ++i) {
		Array2[i] = dis(gen);
	}


	// 10�� �迭 ����
	// �迭�� �迭 ����� ������ �־���
	auto start1{ std::chrono::system_clock::now() };
	selectionSort(Array, sizeof(Array) / sizeof(int));
	auto end1{ std::chrono::system_clock::now() };

	std::chrono::microseconds microseconds1{ std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1) };
	cout << "10�� �迭 ���� ���� ���� �ð�: " << microseconds1.count() << " microseconds" << endl;

	auto start2{ std::chrono::system_clock::now() };
	mergeSort(Array, 0, sizeof(Array) / sizeof(int) - 1, sizeof(Array) / sizeof(int));
	auto end2{ std::chrono::system_clock::now() };

	std::chrono::microseconds microseconds2{ std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2) };
	cout << "10�� �迭 �պ� ���� ���� �ð�: " << microseconds2.count() << " microseconds" << endl;

	// ����� ������ �Ǿ����� Ȯ��
	checkSort(Array, sizeof(Array) / sizeof(int));



	// 100000�� �迭 ����
	auto start3{ std::chrono::system_clock::now() };
	selectionSort(Array2, 100000);
	auto end3{ std::chrono::system_clock::now() };
	std::chrono::microseconds microseconds3{ std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3) };
	cout << "10���� �迭 ���� ���� ���� �ð�: " << microseconds3.count() << " microseconds" << endl;

	auto start4{ std::chrono::system_clock::now() };
	mergeSort(Array2, 0, 100000 - 1, 100000);
	auto end4{ std::chrono::system_clock::now() };
	std::chrono::microseconds microseconds4{ std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4) };
	cout << "10���� �迭 �պ� ���� ���� �ð�: " << microseconds4.count() << " microseconds" << endl;

	// ����� ������ �Ǿ����� Ȯ��
	checkSort(Array2, 100000);


	cout << "\n������Ű��а� 12171850 ������" << endl;
	return 0;
}

void selectionSort(int a[], int n) {
	int min, temp;
	for (int i{ }; i < n - 1; ++i) {
		min = i;
		for (int j{ i + 1 }; j < n; ++j) // �迭 a[i] ~ a[n - 1] �߿��� ���� ���� ���Ҹ� ����
			if (a[j] < a[min])
				min = j;

		// �ּڰ��� ���� ������ ������ ���� i��° ���� min �ε����� �ִ� ���� ����
		temp = a[min];
		a[min] = a[i];
		a[i] = temp;
	}
}

// mergeSort �Լ����� ���� ����Ʈ�� �����ϴ� ������ ��ģ��
void mergeSort(int a[], int l, int r, int n) {
	if (r > l) {
		int m = (r + l) / 2;
		mergeSort(a, l, m, n);
		mergeSort(a, m + 1, r, n);
		merge(a, l, m, r, n);
	}
}

// merge �Լ����� mergeSort���� ���ҵ� ����Ʈ�� ���� �� �պ��Ѵ�.
void merge(int a[], int left, int mid, int right, int n) {
	int i{ left };
	int j{ mid + 1 };
	int k{ left };

	// ���� ���ĵ� �迭�� �պ�
	while (i <= mid && j <= right) {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}

	while (i <= mid)
		tmp[k++] = a[i++];
	while (j <= right)
		tmp[k++] = a[j++];

	// �ӽ� �迭�� ������ ���� �迭 a[]�� �ٽ� ����
	for (int i{ left }; i <= right; ++i)
		a[i] = tmp[i];
	
}


void checkSort(int a[], int n) {
	bool sorted{ true };
	for (int i{ }; i < n - 1; ++i) {
		if (a[i] > a[i + 1])
			sorted = false;
		if (!sorted)
			break;
	}
	if (sorted)
		cout << "Sorting complete!" << endl;
	else
		cout << "Error during sorting..." << endl;
}
