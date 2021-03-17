#include <iostream>
#include <random>
#include <chrono>
using std::cout;
using std::endl;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

template <typename T, size_t N>
void selectionSort(T(&)[N]);

template <typename T, size_t N>
void mergeSort(T(&)[N], int, int);

template <typename T, size_t N>
void merge(T(&)[N], int, int, int);

template <typename T, size_t N>
void checkSort(T(&)[N]);

int main() {
	int Array[]{ 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 }; // 10개의 값을 가진 배열 선언

	random_device rd;
	mt19937 gen(rd()); // 시드를 넣어서 난수 생성 엔진 초기화
	uniform_int_distribution<int> dis(0, 100000); // 0부터 10만까지 균등 분포 정의
	int Array2[100000];
	for (int i{ }; i < 100000; ++i) {
		Array2[i] = dis(gen);
	}


	// 10개 배열 정렬
	// 배열과 배열 요소의 개수를 넣어줌
	auto start1{ std::chrono::system_clock::now() };
	selectionSort(Array);
	auto end1{ std::chrono::system_clock::now() };

	std::chrono::microseconds microseconds1{ std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1) };
	cout << "10개 배열 선택 정렬 수행 시간: " << microseconds1.count() << " microseconds" << endl;

	auto start2{ std::chrono::system_clock::now() };
	mergeSort(Array, 0, sizeof(Array) / sizeof(int) - 1);
	auto end2{ std::chrono::system_clock::now() };

	std::chrono::microseconds microseconds2{ std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2) };
	cout << "10개 배열 합병 정렬 수행 시간: " << microseconds2.count() << " microseconds" << endl;

	// 제대로 정렬이 되었는지 확인
	checkSort(Array);


	
	// 100000개 배열 정렬
	auto start3{ std::chrono::system_clock::now() };
	selectionSort(Array2);
	auto end3{ std::chrono::system_clock::now() };
	std::chrono::microseconds microseconds3{ std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3) };
	cout << "10만개 배열 선택 정렬 수행 시간: " << microseconds3.count() << " microseconds" << endl;

	auto start4{ std::chrono::system_clock::now() };
	mergeSort(Array2, 0, 100000 - 1);
	auto end4{ std::chrono::system_clock::now() };
	std::chrono::microseconds microseconds4{ std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4) };
	cout << "10만개 배열 합병 정렬 수행 시간: " << microseconds4.count() << " microseconds" << endl;

	// 제대로 정렬이 되었는지 확인
	checkSort(Array2);
	

	cout << "\n정보통신공학과 12171850 정연한" << endl;
	return 0;
}

template <typename T, size_t N>
void selectionSort(T(&a)[N]) {
	int min, temp;
	for (int i{ }; i < N - 1; ++i) {
		min = i;
		for (int j{ i + 1 }; j < N; ++j) // 배열 a[i] ~ a[n - 1] 중에서 가장 작은 원소를 선택
			if (a[j] < a[min])
				min = j;

		// 최솟값을 제일 앞으로 보내기 위해 i번째 값과 min 인덱스에 있는 값을 스왑
		temp = a[min];
		a[min] = a[i];
		a[i] = temp;
	}
}

// mergeSort 함수에선 들어온 리스트를 분할하는 과정을 거친다
template <typename T, size_t N>
void mergeSort(T(&a)[N], int l, int r) {
	if (r > l) {
		int m = (r + l) / 2;
		mergeSort(a, l, m);
		mergeSort(a, m + 1, r);
		merge(a, l, m, r);
	}
}

// merge 함수에선 mergeSort에서 분할된 리스트를 정렬 및 합병한다.
template <typename T, size_t N>
void merge(T(&a)[N], int left, int mid, int right) {
	T* tmp{ new T[N] };

	int i{ left };
	int j{ mid + 1 };
	int k{ left };

	// 분할 정렬된 배열을 합병
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

	// 임시 배열의 값들을 원본 배열 a[]로 다시 복사
	for (int i{ left }; i <= right; ++i)
		a[i] = tmp[i];

	delete[] tmp;
}

template <typename T, size_t N>
void checkSort(T(&a)[N]) {
	bool sorted{ true };
	for (int i{ }; i < N - 1; ++i) {
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
