#include <iostream>
#include <random>
#include <chrono>

using std::cout;
using std::endl;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::microseconds;

void quickSort(int*&, int, int);

void CheckSort(const int*&);

// 랜덤 엔진 선언
random_device rd{ };
mt19937 gen{ rd() };

int main() {
	constexpr int listSize{ 100'000'000 }; // 1억개 정렬을 위해 상수값 100,000,000으로 초기화 된 listSize 선언
	int* list{ new int[listSize] { } }; // 아래에서 값을 넣기 위해 일단은 0으로 초기화

	uniform_int_distribution<int> randInt{ 0, listSize }; // 0 ~ listSize까지 균등 분포 정의
	for (int i{ }; i < listSize; ++i) // 0부터 listSize - 1까지 반복하며,
		list[i] = randInt(gen); // list에 랜덤한 정수값 삽입

	// 1억개 정렬
	auto start{ system_clock::now() }; // 시작 시간
	QuickSort(list, 0, listSize - 1); // 시간을 측정할 함수 실행
	auto end{ system_clock::now() }; // 종료 시간

	auto execTime{ duration_cast<microseconds>(end - start) }; // 끝난 시간에서 시작한 시간을 빼어 실행된 시간 계산
	cout << listSize << "개 정렬: " << execTime.count() << "μs" << endl;

	CheckSort(const_cast<const int*&>(list));

	cout << "\n정보통신공학과 12171850 정연한" << endl;
	delete[] list;
	return 0;
}

// 두 값을 서로 바꿔주는 함수
// 실행시간의 이득을 위해 inline 함수로 선언하였다.
inline void Swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

void QuickSort(int*& list, int low, int high) {
	if (high - low > 1) { // high값이 low보다 클 때,
		int mid{ (low + high) / 2 }; // mid는 low, high 두 인덱스를 합한 것의 절반 값으로 선언

		// low, mid, high 3개의 인덱스 값을 골라 그 중간 값으로 pivot을 설정하기 위한 알고리즘
		if (list[low] > list[mid]) // 리스트의 low인덱스 값이 리스트의 mid인덱스 값보다 크다면,
			Swap(list[low], list[mid]); // 두 값을 서로 바꿔준다.
		if (list[low] > list[high]) // 리스트의 low인덱스 값이 리스트의 high인덱스 값보다 크다면,
			Swap(list[low], list[high]);// 두 값을 서로 바꿔준다.
		if (list[mid] > list[high]) // 리스트의 mid인덱스 값이 리스트의 high인덱스 값보다 크다면,
			Swap(list[mid], list[high]); // 두 값을 서로 바꿔준다.
		Swap(list[mid], list[high - 1]); // 두 값을 서로 바꿔주며, 최종적으로 high - 1이 중간 값(pivot에 들어갈 값)으로 선정

		int& pivot{ list[high - 1] }; // 위의 알고리즘을 거쳐서 나온 리스트의 high - 1인덱스 값을 pivot으로 설정 
		int current{ low }; // low인덱스 값으로 current 값을 설정
		for (int i{ high - 1 };;) { // i는 high - 1로 선언
			while (list[++current] < pivot); // 리스트의 current + 1인덱스 값이 pivot보다 작다면 반복
			while (list[--i] > pivot); // 리스트의 i - 1인덱스 값이 pivot 보다 크다면 반복
			if (current >= i) // 만약 current인덱스 값이 i인덱스보다 크거나 같다면,
				break; // 해당 반복문을 종료한다.
			Swap(list[current], list[i]); // 위의 조건에 걸리지 않았다면 두 값을 서로 바꿔준다.
		}
		Swap(list[current], list[high - 1]); // 위의 조건에 의해 반복문을 빠져나왔다면 두 값을 서로 바꿔준다.

		QuickSort(list, low, current - 1);
		QuickSort(list, current + 1, high);
	}
	else if (list[low] > list[high]) // 리스트의 low인덱스 값이 리스트의 high인덱스 값보다 클 때,
		Swap(list[low], list[high]); // 두 값을 서로 바꿔준다.
}

void CheckSort(const int*& list) {
	bool sorted{ true };
	int n{ static_cast<int>(_msize(const_cast<int*>(list)) / sizeof(int)) }; // 리스트의 원소의 개수로 n을 선언
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
