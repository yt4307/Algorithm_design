#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

template <size_t N>
void selectionSort(int(&)[N]);

template <size_t N>
void mergeSort(int(&)[N], int, int, int(&)[N]);

template <size_t N>
void checkSort(int(&)[N]);


int main() {
	// 시간측정을 위한 변수 선언
	auto start{ system_clock::now() };
	auto end{ system_clock::now() };

	int list[10]{ 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 };
	int temp[10]{ };

	// 10개 배열 선택 정렬
	start = system_clock::now();
	selectionSort(list);
	end = system_clock::now();

	auto execTime{ duration_cast<microseconds>(end - start) };
	cout << "10개 배열 선택 정렬: " << execTime.count() << "μs" << endl;

	// 10개 배열 병합 정렬
	start = system_clock::now();
	mergeSort(list, 0, sizeof(list) / sizeof(int) - 1, temp);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "10개 배열 병합 정렬: " << execTime.count() << "μs" << endl;

	// 제대로 정렬되었는지 확인
	checkSort(list);

	cout << "정보통신공학과 12171850 정연한" << endl;

	return 0;
}


template <size_t N>
void selectionSort(int(&list)[N]) {
	int indexMin{ }, temp{ };
	for (int i{ }; i < N - 1; ++i, indexMin = i) {
		for (int j{ i + 1 }; j < N; ++j)
			if (list[j] < list[indexMin])
				indexMin = j;

		temp = list[indexMin];
		list[indexMin] = list[i];
		list[i] = temp;
	}
}

// merge sort range : [low ~ high]
template <size_t N>
void mergeSort(int(&list)[N], int low, int high, int(&sorted)[N]) {
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


template <size_t N>
void checkSort(int(&list)[N]) {
	bool sorted{ true };

	for (int i{ }; i < N - 1; ++i) {
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
