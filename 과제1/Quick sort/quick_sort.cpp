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

void QuickSort(int*&, int, int);

void CheckSort(const int*&);

// 랜덤 엔진 선언
random_device rd{ };
mt19937 gen{ rd() };

int main() {
	constexpr int listSize{ 100'000'0 }; // 정렬을 위해 상수값으로 초기화 된 listSize 상수 선언
	int* list{ new int[listSize] { } }; // 아래에서 값을 넣기 위해 일단은 0으로 초기화

	uniform_int_distribution<int> randInt{ 0, listSize }; // 0 ~ listSize까지 균등 분포 정의
	for (int i{ }; i < listSize; ++i) // 0부터 listSize - 1까지 반복하며,
		list[i] = randInt(gen); // list에 랜덤한 정수값 삽입

	// 수행 시간 측정 시작
	auto start{ system_clock::now() };

	// 퀵 정렬 수행
	QuickSort((&list)[0], 0, listSize - 1);

	// 수행 시간 측정 종료
	auto end{ system_clock::now() };

	// 끝난 시간에서 시작한 시간을 빼어 총 수행 시간 계산
	auto execTime{ duration_cast<microseconds>(end - start) };
	cout << listSize << "개 퀵 정렬: " << execTime.count() << "μs" << endl;

	CheckSort(const_cast<const int*&>((&list)[0]));

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

// 퀵 정렬은 피벗을 기준으로 양쪽의 요소를 최대한 동등하게 나누어야 최선의 속도를 보인다.
// 그러나 그렇다고 해서 배열을 처음부터 끝까지 순회하면서 정확히 중간값을 찾는건 너무 시간이 오래걸린다.
// 따라서 임의의 3개의 값을 골라 그 중 중간값에 해당하는 값을 피벗값으로 골라준다.
void QuickSort(int*& list, int low, int high) {
	// 기본 조건
	if (low >= high)
		return;

	// 피벗 값을 구하기 위해 중간 값 설정
	int mid{ [=] () -> auto {
		uniform_int_distribution<int> list_random_value{low, high}; // low ~ high 까지 균등 분포 정의

		// 임의의 3개의 값을 고르기 위해 크기가 3인 배열 선언과 동시에 랜덤 값으로 초기화
		int num[3]{ list_random_value(gen), list_random_value(gen), list_random_value(gen) };

		return (num[0] > num[1]) // num[0] > num[1]가 참이면 콜론 앞 항으로, 거짓이면 콜론 뒷 항으로
			? ((num[0] > num[2]) ? ((num[1] > num[2]) ? num[1] : num[2]) : num[0])  // 앞 항
			: ((num[1] > num[2]) ? ((num[0] > num[2]) ? num[0] : num[2]) : num[1]); // 뒷 항

		// 예를 들어 num[0] > num[1] 이고, num[0] < num[2] 이면,
		// num[0]이 num[1]보단 크고 num[2]보단 작다. 따라서 중간 값은 num[0]
	}() }; // 여러 곳에서 재사용하지 않을 함수이기에 람다식으로 작성하였다.

	// 위에서 찾은 mid 인덱스를 피벗 값으로 사용하기 위해 리스트의 두 인덱스 값을 서로 바꿔준다.
	Swap(list[mid], list[high]);

	int& pivot{ list[high] }; // 위에서 찾은 알고리즘으로 피벗 값 설정
	int target{ low - 1 }; // 현재 정렬중인 인덱스
	for (int i{ low }; i < high; ++i) // i는 low 부터 high - 1(피봇 - 1)까지 순회하면서
		if (list[i] < pivot) // 리스트의 i 인덱스 값이 피벗 값보다 작다면,

			// 리스트의 현재 요소 인덱스를 1 증가시키고, 리스트의 i 인덱스와 서로 값을 바꿔준다.
			Swap(list[++target], list[i]);

	// 모든 반복이 끝나면 리스트의 현재 요소 인덱스를 1 증가시키고, 피벗 값과 서로 값을 바꿔준다.
	Swap(list[++target], pivot);

	// 앞쪽 절반 정복
	QuickSort(list, low, target - 1);

	// 뒤쪽 절반 정복
	QuickSort(list, target + 1, high);
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
