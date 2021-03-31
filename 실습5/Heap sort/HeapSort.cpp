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

void swap(int&, int&);

void maxHeapSort(int*&);

void maxHeapify(int*&, int, int);

void minHeapSort(int*&);

void minHeapify(int*&, int, int);

void checkSort1(int*&);

void checkSort2(int*&);

// 랜덤 엔진 선언
random_device rd{ };
mt19937 gen(rd());

int main() {
	constexpr int maxVal1{ 10 }; // 10개 정렬을 위해 상수값 10으로 초기화 된 maxVal1 선언
	constexpr int maxVal2{ 100000 }; // 10만개 정렬을 위해 상수값 100000으로 초기화 된 maxVal2 선언
	int* list1{ new int[maxVal1] { 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 } }; // 주어진 값으로 초기화
	int* list2{ new int[maxVal2] {} }; // 아래에서 값을 넣기 위해 일단은 0으로 초기화

	uniform_int_distribution<int> randInt{0, maxVal2}; // 0 ~ 100000까지 균등 분포 정의

	for (int i{ }; i < maxVal2; ++i) // 0부터 100000 - 1까지 반복하며,
		list2[i] = randInt(gen); // list2에 랜덤한 정수값 삽입

	// 10개 정렬
	auto start{ system_clock::now() }; // 시작 시간
	maxHeapSort(list1); // 실행 시간을 측정할 함수 실행
	auto end{ system_clock::now() }; // 종료 시간
	// start, end의 초기화 시간 때문에 실제 실행시간보다 좀 더 오래 걸림
	
	auto execTime{ duration_cast<microseconds>(end - start) }; // 끝난 시간에서 시작한 시간을 빼어 실행된 시간 계산
	cout << "10개 최대 힙 정렬: " << execTime.count() << "μs" << endl;

	for (int i{ }; i < 10; ++i)
		cout << list1[i] << ' ';
	cout << '\n';
	checkSort1(list1);

	start = system_clock::now();
	minHeapSort(list1);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "\n10개 최소 힙 정렬: " << execTime.count() << "μs" << endl;
	
	for (int i{ }; i < 10; ++i)
		cout << list1[i] << ' ';
	cout << '\n';
	checkSort2(list1);

	// 10만개 정렬
	start = system_clock::now();
	maxHeapSort(list2);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "\n10만개 최대 힙 정렬: " << execTime.count() << "μs" << endl;

	checkSort1(list2);

	start = system_clock::now();
	minHeapSort(list2);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "\n10만개 최소 힙 정렬: " << execTime.count() << "μs" << endl;

	checkSort2(list2);

	cout << "\n정보통신공학과 12171850 정연한" << endl;
	return 0;
}

// 두 값을 서로 바꿔주는 함수
// 실행시간의 이득을 위해 inline 함수로 선언하였다.
inline void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

// 최대 힙 정렬
void maxHeapSort(int*& list) {
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // n은 힙의 크기
	
	// max heap 이므로 list[n]의 원소를 오름차순으로 정렬
	for (int i{ n / 2 - 1 }; i >= 0; --i) {
		maxHeapify(list, n, i); // i는 내부 노드
	}

	// 힙에서 최대값을 추출
	for (int i{ n - 1 }; i > 0; --i) {
		swap(list[0], list[i]); 
		maxHeapify(list, i, 0);
	}
}

void maxHeapify(int*& list, int n, int i) {
	int p{ i }; // 부모 노드 인덱스
	int l{ i * 2 + 1 }; // 왼쪽 자식 노드 인덱스
	int r{ i * 2 + 2 }; // 오른쪽 자식 노드 인덱스

	// 만약 왼쪽 자식 노드 인덱스가 힙의 크기보다 작고,
	// 리스트의 부모 노드 인덱스 값이 리스트의 왼쪽 자식 노드 인덱스 값보다 작다면,
	if (l < n && list[p] < list[l])
		p = l; // 부모 노드 인덱스에 왼쪽 자식 노드 인덱스를 대입한다. 

	// 만약 오른쪽 자식 노드 인덱스가 힙의 크기보다 작고,
	// 리스트의 부모 노드 인덱스가 리스트의 오른쪽 자식 노드 인덱스보다 작다면,
	if (r < n && list[p] < list[r])
		p = r; // 부모 노드 인덱스에 오른쪽 자식 노드 인덱스를 대입한다.

	if (i != p) { // 위의 제어문에 의해 i와 p가 서로 달라졌다면,
		swap(list[i], list[p]); // 리스트의 i 인덱스 값과 리스트의 p 인덱스 값을 서로 바꿔준 뒤,
		maxHeapify(list, n, p); // 다시 한 번 heapify함수를 수행한다.
	}
}

// 최소 힙 정렬
void minHeapSort(int*& list) {
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // n은 힙의 크기

	// min heap 이므로 list[n]의 원소를 내림차순으로 정렬
	for (int i{ n / 2 - 1 }; i >= 0; --i) {
		minHeapify(list, n, i); // i는 내부 노드
	}

	// 힙에서 최소값을 추출
	for (int i{ n - 1 }; i > 0; --i) {
		swap(list[0], list[i]);
		minHeapify(list, i, 0);
	}
}

void minHeapify(int*& list, int n, int i) {
	int p{ i }; // 부모 노드 인덱스
	int l{ i * 2 + 1 }; // 왼쪽 자식 노드 인덱스
	int r{ i * 2 + 2 }; // 오른쪽 자식 노드 인덱스

	// 만약 왼쪽 자식 노드 인덱스가 힙의 크기보다 작고,
	// 리스트의 부모 노드 인덱스 값이 리스트의 왼쪽 자식 노드 인덱스 값보다 크다면,
	if (l < n && list[p] > list[l])
		p = l; // 부모 노드 인덱스에 왼쪽 자식 노드 인덱스를 대입한다. 

	// 만약 오른쪽 자식 노드 인덱스가 힙의 크기보다 작고,
	// 리스트의 부모 노드 인덱스가 리스트의 오른쪽 자식 노드 인덱스보다 크다면,
	if (r < n && list[p] > list[r])
		p = r; // 부모 노드 인덱스에 오른쪽 자식 노드 인덱스를 대입한다.

	if (i != p) { // 위의 제어문에 의해 i와 p가 서로 달라졌다면,
		swap(list[i], list[p]); // 리스트의 i 인덱스 값과 리스트의 p 인덱스 값을 서로 바꿔준 뒤,
		minHeapify(list, n, p); // 다시 한 번 heapify함수를 수행한다.
	}
}

// 오름차순 체크
void checkSort1(int*& list) {
	bool sorted{ true };
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // 리스트의 원소의 개수로 n을 선언
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

// 내림차순 체크
void checkSort2(int*& list) {
	bool sorted{ true };
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // 리스트의 원소의 개수로 n을 선언
	for (int i{ n - 1 }; i > 0; --i) {
		if (list[i] < list[i + 1])
			sorted = false;
		if (!sorted)
			break;
	}
	if (sorted)
		cout << "Sorting complete!" << endl;
	else
		cout << "Error during sorting..." << endl;
}
