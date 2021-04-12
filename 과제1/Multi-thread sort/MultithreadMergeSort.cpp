#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <thread>
#include <windows.h> // 코어의 개수가 적힌 시스템 정보를 가져오기 위해 포함

using std::cout;
using std::endl;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::microseconds;

using std::vector;

using std::thread;

void Merge(int, int, int);
void MergeSort(int, int);
void MultithreadMergeSort(int);
void CheckSort(const int*&);

// 랜덤 엔진 선언
random_device rd{ };
mt19937 gen{ rd() };

// 리스트 및 그와 관련된 변수 선언
constexpr int listSize{ 1'000'000 };
int* list{ new int[listSize] {} };
int border{ }; // 리스트 내의 경계선


int main() {
	SYSTEM_INFO info{ };
	GetSystemInfo(&info);
	int numCore{ static_cast<int>(info.dwNumberOfProcessors) };

	uniform_int_distribution<int> randInt{ 0, listSize };
	for (int i{ }; i < listSize; ++i) // 0부터 listSize - 1까지 반복하며,
		list[i] = randInt(gen); // list에 랜덤한 정수값 삽입

	// 스레드 벡터 선언
	vector<thread> threads{};

	auto start{ system_clock::now() };

	// core 개수만큼의 스레드 객체 생성
	for (int i = 0; i < numCore; ++i)
		// 스레드 벡터에 numCore를 매개변수로 하는 MultithreadMergeSort 함수를 스레드 객체를 생성하여 넣어준다.
		threads.emplace_back(MultithreadMergeSort, numCore);

	// 모든 스레드 join(실행이 완료 될 때까지 대기)
	for (auto& th : threads)
		th.join();

	// 정렬 된 8개의 조각을 하나로 합치는 과정
	Merge(0, listSize / 8 - 1, listSize / 4 - 1); // 0 ~ 1/4 지점 병함
	Merge(listSize / 4, 3 * listSize / 8 - 1, listSize / 2 - 1); // 1/4 ~ 2/4(1/2) 지점 병합
	Merge(listSize / 2, 5 * listSize / 8 - 1, 3 * listSize / 4 - 1); // 2/4 ~ 3/4 지점 병합
	Merge(3 * listSize / 4, 7 * listSize / 8 - 1, listSize - 1); // 3/4 ~ 1 지점 병합
	Merge(0, listSize / 4 - 1, listSize / 2 - 1); // 0 ~ 1/2 지점 병합
	Merge(listSize / 2, 3 * listSize / 4 - 1, listSize - 1); // 1/2 ~ 1 지점 병합
	Merge(0, listSize / 2 - 1, listSize - 1); // 0 ~ 1 지점 병합

	auto end{ system_clock::now() };
	threads.clear();

	auto execTime{ duration_cast<microseconds>(end - start) };

	cout << "Multi-thread로 Merge sort를 나눠서 시행한 시간: " << execTime.count() << "μs" << endl;
	
	// 정렬 결과 출력
	CheckSort(const_cast<const int*&>(list));

	cout << "\n정보통신공학과 12171850 정연한" << endl;
	delete[] list;
	return 0;
}

// 분할 된 부분배열을 합병하는 함수
void Merge(int low, int mid, int high) {
	int* left{ new int[mid - low + 1] {} };
	int* right{ new int[high - mid] {} };

	// lsize은 왼쪽 부분의 크기, rsize는 오른쪽 부분의 크기
	int lsize{ mid - low + 1 }, rsize{ high - mid };

	// 왼쪽 부분에 값 저장
	for (int i{ }; i < lsize; i++)
		left[i] = list[i + low];

	// 오른쪽 부분에 값 저장
	for (int i{ }; i < rsize; i++)
		right[i] = list[i + mid + 1];

	int i{}, j{}, k{ low };

	// 오름차순으로 왼쪽과 오른쪽을 병합
	while (i < lsize && j < rsize) {
		if (left[i] <= right[j])
			list[k++] = left[i++];
		else
			list[k++] = right[j++];
	}

	// 왼쪽에 남아있는 값을 리스트에 삽입
	while (i < lsize)
		list[k++] = left[i++];

	// 오른쪽에 남아있는 값을 리스트에 삽입
	while (j < rsize)
		list[k++] = right[j++];
}

// 제자리 합병 정렬
void MergeSort(int low, int high) {
	// 리스트의 중간 지점 선언
	int mid{ low + ((high - low) / 2) };
	
	// 기본 조건
	if (low >= high)
		return;

	// 앞쪽 절반 정복
	MergeSort(low, mid);

	// 뒷쪽 절반 정복
	MergeSort(mid + 1, high);

	// 정복시킬 두 반쪽을 병합
	Merge(low, mid, high);
}

// 멀티 스레드 정렬을 위한 함수
void MultithreadMergeSort(int numCore) {
	// 각 스레드마다 파트를 나눠주기 위한 변수 선언
	// border는 맨 처음에 0으로 시작하며, MultithreadMergeSort 함수에 들어오는 순서대로 파트가 정해진다.
	int threadPart{ border++ };

	// 각각의 스레드별로 low와 high를 지정해줌
	int low{ threadPart * (listSize / numCore) };
	int high{ (threadPart + 1) * (listSize / numCore) - 1 };

	// 그렇게 나눠준 low ~ high 범위를 mergesort에 넣어줌
	MergeSort(low, high);
}

void CheckSort(const int*& list) {
	bool sorted{ true };
	int n{ listSize }; // 리스트의 원소의 개수로 n을 선언
	for (int i{ }; i < n - 1; ++i) {
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
