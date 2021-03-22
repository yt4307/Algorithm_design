#include <iostream>
#include <chrono>
#include <random>

using std::cout;
using std::endl;

using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

void selectionSort(int* (&));

void mergeSort(int* (&), int, int, int* (&));

void checkSort(int* (&));


int main() {
	// �ð������� ���� ���� ����
	auto start{ system_clock::now() };
	auto end{ system_clock::now() };

	// 10������ �迭�� ������ ���� �ֱ� ���� ��ü�� ����
	random_device rd{ };
	mt19937 gen{ rd() };
	uniform_int_distribution<int> dis{ 0, 100000 }; // 0~10������ �յ� ���� ����

	int* list{ new int[100000]{ } };
	for (int i{ }; i < 100000; ++i)
		list[i] = dis(gen);
	int* temp{ new int[100000]{ } };

	// 10���� �迭 ���� ����
	start = system_clock::now();
	selectionSort(list);
	end = system_clock::now();

	auto execTime{ duration_cast<microseconds>(end - start) };
	cout << "10���� �迭 ���� ����: " << execTime.count() << "��s" << endl;

	// 10���� �迭 ���� ����
	start = system_clock::now();
	mergeSort(list, 0, _msize(list) / sizeof(list) - 1, temp);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "10���� �迭 ���� ����: " << execTime.count() << "��s" << endl;

	// ����� ���ĵǾ����� Ȯ��
	checkSort(list);

	cout << "������Ű��а� 12171850 ������" << endl;

	delete[] list;
	delete[] temp;

	return 0;
}


void selectionSort(int* (&list)) {
	int indexMin{ }, temp{ };
	size_t n{ _msize(list) / sizeof(int) };
	for (size_t i{ }; i < n - 1; ++i, indexMin = i) {
		for (size_t j{ i + 1 }; j < n; ++j)
			if (list[j] < list[indexMin])
				indexMin = j;

		temp = list[indexMin];
		list[indexMin] = list[i];
		list[i] = temp;
	}
}

// merge sort range : [low ~ high]
void mergeSort(int* (&list), int low, int high, int* (&sorted)) {
	// 1. �⺻ ����
	if (low >= high)
		return;

	// 2. divide(����)
	int mid{ (low + high) / 2 };

	// 3. conquer(����)
	mergeSort(list, low, mid, sorted);
	mergeSort(list, mid + 1, high, sorted);

	// 4. combine(����)
	int i{ low }, j{ mid + 1 }, k{ low };
	for (; k <= high; ++k) {
		if (j > high)
			sorted[k] = list[i++];
		else if (i > mid)
			sorted[k] = list[j++];
		else if (list[i] <= list[j])
			sorted[k] = list[i++];
		else
			sorted[k] = list[j++];
	}

	// 5. copy(����)
	for (int i{ low }; i <= high; ++i)
		list[i] = sorted[i];
}


void checkSort(int* (&list)) {
	bool sorted{ true };
	size_t n{ _msize(list) / sizeof(int) };
	for (size_t i{ }; i < n - 1; ++i) {
		if (list[i] > list[i + 1])
			sorted = false;
		if (!sorted)
			break;
	}
	if (sorted)
		cout << "Sorting complete!" << endl;
	else
		cout << "Error during sorting..." << endl;
}
