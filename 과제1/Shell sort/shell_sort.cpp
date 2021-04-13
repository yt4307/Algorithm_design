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

void ShellSort(int*&);

void CheckSort(const int*&);

random_device rd{ };
mt19937 gen{ rd() };

int main() {
	const int listSize{ 100'000'000 }; // 정렬을 위해 상수값으로 초기화 된 listSize 상수 선언
	int* list{ new int[listSize] { } }; // 아래에서 값을 넣기 위해 일단은 0으로 초기화

	uniform_int_distribution<int> randInt{ 0, listSize }; // 0 ~ listSize까지 균등 분포 정의
	for (int i{ }; i < listSize; ++i) // 0부터 listSize - 1까지 반복하며,
		list[i] = randInt(gen); // list에 랜덤한 정수값 삽입
	
	// 수행 시간 측정 시작
	auto start{ system_clock::now() };

	// 셸 정렬 수행
	ShellSort((&list)[0]);
	
	// 수행 시간 측정 종료
	auto end{ system_clock::now() };

	// 끝난 시간에서 시작한 시간을 빼어 총 수행 시간 계산
	auto execTime{ duration_cast<microseconds>(end - start) };
	cout << listSize << "개 정렬: " << execTime.count() << "μs" << endl;

	// 정렬 결과 출력
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

// 셸 정렬
void ShellSort(int*& list) {
	int length{ static_cast<int>(_msize(list) / sizeof(int)) };

	// https://oeis.org/A102549/internal 를 통해 현재까지 알려진 gap sequence들 중 가장 좋은 성능을 내는 시퀀스를 찾았다.
	// 위 페이지에는 1750까지 정의되어있으며, 이후 2.25를 곱해 나온 값 중 배열의 최대 값인
	// 21억을 넘지 않는 최대값까지 정리하여 초기화 하였다.
	int gap[] = { 1, 4, 10, 23, 57, 132, 301, 701, 1750,
		3937, 8858, 19930, 44842, 100894, 227011, 510774,
		1149241, 2585792, 5818032, 13090572, 29453787,
		66271020, 149109795, 335497038, 754868335, 1698453753 };
	
	int gapIndex{ }, step{ };
	for (; gap[gapIndex] <= length / 2.25; ++gapIndex);

	// 부분 리스트를 만들어 gap만큼 떨어진 요소들을 삽입 정렬
	while (gapIndex >= 0) { // gap이 1이 될 때까지 반복
		step = gap[gapIndex--];	// 현재 gap(step)
		
		// 각 부분 리스트의 두 번째 요소의 인덱스 부터 순회한다.
		// 예를 들어 step이 3일 때 arr[0], arr[1], arr[2]는 이전 요소와 비교할 것이 없다.
		// 따라서 step부터 순회
		for (int i{ step }; i < length; ++i)

			// j는 target 요소가 되며, 현재 요소 a[j]가 이전 요소 a[j - step]보다 작을 때 까지 반복한다.
			for (int j = i; j >= step && list[j] < list[j - step]; j -= step)

				// 리스트의 현재 요소 인덱스(j)와 이전 요소(j-step) 인덱스의 값을 교환한다.
				Swap(list[j], list[j - step]);
	}
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
