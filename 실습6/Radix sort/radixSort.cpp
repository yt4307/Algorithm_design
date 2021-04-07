#include <iostream>
using std::cout;
using std::endl;

template <size_t N>
void radixSort(int(&)[N], int, int);

template <size_t N>
void checkSort(int(&)[N]);

int main() {
	int list[]{ 170, 45, 75, 90, 2, 24, 802, 66 };
	

	cout << "정렬 전 리스트" << endl;
	for (auto iter : list)
		cout << iter << ' ';
	cout << endl;

	radixSort(list, 3, 10);
	cout << "정렬 후 리스트" << endl;
	for (auto iter : list)
		cout << iter << ' ';
	cout << endl;

	checkSort(list);
	
	cout << "\n정보통신공학과 12171850 정연한" << endl;
	return 0;
}

/**
   * @data  정수 배열
   * @size  data의 정수들의 개수
   * @p  숫자의 최대 자리수
   * @k  기수(10진법을 사용한다면 10)
   *
   */
template <size_t N>
void radixSort(int(&list)[N], int p, int k) {
	int* counts{ }, // 특정 자리에서 숫자들의 카운트
		* temp{ }; // 정렬된 배열을 담을 임시 장소
	int index{ }, pval{ };

	// 메모리 할당
	if ((counts = new int[k] { }) == NULL)
		return;
	if ((temp = new int[N] { }) == NULL)
		return;
	for (int n{ }; n < p; ++n) { // 1의 자리, 10의자리, 100의 자리 순으로 진행
		for (int i{ }; i < k; ++i)
			counts[i] = 0; // 초기화
		// 위치값 계산.
		// n:0 => 1,  1 => 10, 2 => 100
		pval = static_cast<int>(pow(static_cast<double>(k), static_cast<double>(n)));

		// 각 숫자의 발생횟수를 센다.
		for (int j{ }; j < N; ++j) {
			// 253이라는 숫자라면
			// n:0 => 3,  1 => 5, 2 => 2
			index = static_cast<int>(list[j] / pval) % k;
			counts[index] = counts[index] + 1;
		}

		// 카운트 누적합을 구한다. 계수정렬을 위해서.
		for (int i{ 1 }; i < k; ++i) {
			counts[i] = counts[i] + counts[i - 1];
		}

		// 카운트를 사용해 각 항목의 위치를 결정한다.
		// 계수정렬 방식
		for (int j{ N - 1 }; j >= 0; --j) { // 뒤에서부터 시작
			index = static_cast<int>(list[j] / pval) % k;
			temp[counts[index] - 1] = list[j];
			counts[index] = counts[index] - 1; // 해당 숫자 카운트를 1 감소
		}
		// 임시 데이터 복사
		memcpy(list, temp, N * sizeof(int));
	}
	delete[] counts;
	delete[] temp;
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
