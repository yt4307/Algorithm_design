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
	// 시간측정을 위한 변수 선언
	auto start{ system_clock::now() };
	auto end{ system_clock::now() };

	// 10만개의 배열에 랜덤한 값을 넣기 위한 객체들 선언
	random_device rd{ };
	mt19937 gen{ rd() };
	uniform_int_distribution<int> dis{ 0, 100000 }; // 0~10만까지 균등 분포 정의

	int* list{ new int[100000]{ } };
	for (int i{ }; i < 100000; ++i)
		list[i] = dis(gen);
	int* temp{ new int[100000]{ } };

	// 10만개 배열 선택 정렬
	start = system_clock::now();
	selectionSort(list);
	end = system_clock::now();

	auto execTime{ duration_cast<microseconds>(end - start) };
	cout << "10만개 배열 선택 정렬: " << execTime.count() << "μs" << endl;

	// 10만개 배열 병합 정렬
	start = system_clock::now();
	mergeSort(list, 0, _msize(list) / sizeof(list) - 1, temp);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "10만개 배열 병합 정렬: " << execTime.count() << "μs" << endl;

	// 제대로 정렬되었는지 확인
	checkSort(list);

	cout << "정보통신공학과 12171850 정연한" << endl;

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
	// 1. 기본 조건
	if (low >= high)
		return;

	// 2. divide(분할)
	int mid{ (low + high) / 2 };

	// 3. conquer(정복)
	mergeSort(list, low, mid, sorted);
	mergeSort(list, mid + 1, high, sorted);

	// 4. combine(병합)
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

	// 5. copy(복사)
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
