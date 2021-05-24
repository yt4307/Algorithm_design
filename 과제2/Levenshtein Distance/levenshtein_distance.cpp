#include <iostream>
#include <locale>
using std::cin;
using std::cout;
using std::wcin;
const auto endl{ '\n' };

using std::wstring;

int LevenshteinDistanceA(wstring&, wstring&);
double LevenshteinDistanceB(wstring&, wstring&);

int main() {
	// 와이드 문자열을 사용하기 때문에 로케일을 한국의 한국어로 설정해준다.
	setlocale(LC_ALL, "ko_KR");

	// 와이드 문자열을 받을 수 있는 wstring으로 문자열 변수 선언
	wstring str1{ }, str2{ };
	cout << "Source: ";
	wcin >> str1;
	cout << "Target: ";
	wcin >> str2;

	cout << "(a) Levenshtein Distance : " << LevenshteinDistanceA(str1, str2) << endl << endl;
	cout << "(b) Levenshtein Distance : " << LevenshteinDistanceB(str1, str2) << endl;

	cout << "\n정보통신공학과 12171850 정연한" << endl;
	return 0;
}

template <typename T>
inline const T& min(const T& left, const T& mid, const T& right) {
	// mid가 left보다 큰지 비교하고 right가 left보다 큰지 비교해서
	// left가 제일 작으면 left반환 아니라면 뒤의 식 수행
	return (mid > left) && (right > left) ? left : (mid > right ? right : mid);
}

int LevenshteinDistanceA(wstring& str1, wstring& str2) {
	// 리스트 선언 및 초기화
	// + 2를 한 이유: 기본적으로 문자열이기 때문에 공백문자가 들어갈 자리 + 1
	// 거기에 0이 아니라 1부터 length()까지 값이 들어가므로 여유공간 또 + 1해서 총 + 2
	int** list{ new int* [static_cast<int>(str1.length()) + 2]{ } };
	for (int i{ }; i < static_cast<int>(str1.length()) + 2; ++i)
		list[i] = new int[static_cast<int>(str2.length()) + 2]{ };

	// source 문자열 세로줄(열) 첫번째 채우기
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		list[i][0] = i;
	// target 문자열 가로줄(행) 첫번째 채우기
	for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
		list[0][j] = j;

	// 첫번째 열과 첫번째 행을 제외한 남은 공간 채우기
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
			// 비교하려는 두 문자열의 문자가 같을 경우
			if (str1[i - 1] == str2[j - 1])
				// 직전 값(좌측 대각선 위의 값)을 그대로 가져온다.(dp)
				list[i][j] = list[i - 1][j - 1];
			else // 그렇지 않다면 위의 값, 좌측 값, 직전 값들의 각각 1을 더한 값 중 가장 작은 값을 가져온다.
				list[i][j] = min(list[i][j - 1] + 1, list[i - 1][j] + 1, list[i - 1][j - 1] + 1);

	// 동작 출력
	for (int i{ }; i <= static_cast<int>(str1.length()); ++i) {
		for (int j{ }; j <= static_cast<int>(str2.length()); ++j)
			cout << list[i][j] << '\t';
		cout << endl;
	}

	// 최종적으로 연산 된 Levenshtein distance 반환
	return list[str1.length()][str2.length()];
}

double LevenshteinDistanceB(wstring& str1, wstring& str2) {
	// 리스트 선언 및 초기화
	// + 2를 한 이유: 기본적으로 문자열이기 때문에 공백문자가 들어갈 자리 + 1
	// 거기에 0이 아니라 1부터 length()까지 값이 들어가므로 여유공간 또 + 1해서 총 + 2
	double** list{ new double* [static_cast<int>(str1.length()) + 2]{ } };
	for (int i{ }; i < static_cast<int>(str1.length()) + 2; ++i)
		list[i] = new double[static_cast<int>(str2.length()) + 2]{ };

	// source 문자열 세로줄(열) 첫번째 채우기
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		list[i][0] = i;
	// target 문자열 가로줄(행) 첫번째 채우기
	for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
		list[0][j] = j;

	// 첫번째 열과 첫번째 행을 제외한 남은 공간 채우기
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
			// 비교하려는 두 문자열의 문자가 같을 경우
			if (str1[i - 1] == str2[j - 1])
				// 직전 값(좌측 대각선 위의 값)을 그대로 가져온다.(dp)
				list[i][j] = list[i - 1][j - 1];
			else // 그렇지 않다면 좌측 값(삽입), 위의 값(삭제), 직전 값(교환)들에
				 // 각각 0.7, 0.5, 0.3을 더한 값 중 가장 작은 값을 가져온다.
				list[i][j] = min(list[i][j - 1] + 0.7, list[i - 1][j] + 0.5, list[i - 1][j - 1] + 0.3);

	// 동작 출력
	for (int i{ }; i <= static_cast<int>(str1.length()); ++i) {
		for (int j{ }; j <= static_cast<int>(str2.length()); ++j)
			cout << list[i][j] << '\t';
		cout << endl;
	}

	// 최종적으로 연산 된 Levenshtein distance 반환
	return list[str1.length()][str2.length()];
}
