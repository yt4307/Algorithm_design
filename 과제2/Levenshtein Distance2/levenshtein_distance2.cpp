#define DEBUG
#include <iostream>
#include <locale>
using std::cin;
using std::cout;
using std::wcin;
const auto endl{ '\n' };

using std::wstring;

double LevenshteinDistance(const wstring&, const wstring&);
void DistanceTrace(double**&, const wstring&, const wstring&);

int main() {
	// 와이드 문자열을 사용하기 때문에 로케일을 한국의 한국어로 설정해준다.
	setlocale(LC_ALL, "ko_KR");

	// 와이드 문자열을 받을 수 있는 wstring으로 문자열 변수 선언
	wstring str1{ }, str2{ };
	cout << "Source: ";
	wcin >> str1;
	cout << "Target: ";
	wcin >> str2;

	cout << "=> Levenshtein Distance = " << LevenshteinDistance(str1, str2) << endl;

	cout << "\n정보통신공학과 12171850 정연한" << endl;
	return 0;
}

template <typename T>
inline const T& min(const T& left, const T& mid, const T& right) {
	// mid가 left보다 큰지 비교하고 right가 left보다 큰지 비교해서
	// left가 제일 작으면 left반환 아니라면 뒤의 식 수행
	return (mid > left) && (right > left) ? left : (mid > right ? right : mid);
}

double LevenshteinDistance(const wstring& str1, const wstring& str2) {
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

#ifdef DEBUG
	// 동작 출력
	cout << endl;
	for (int i{ }; i <= static_cast<int>(str1.length()); ++i) {
		for (int j{ }; j <= static_cast<int>(str2.length()); ++j)
			cout << list[i][j] << '\t';
		cout << endl;
	}
#endif // DEBUG

	// 거리 추적
	DistanceTrace(list, str1, str2);

	// 최종적으로 연산 된 Levenshtein distance 반환
	return list[str1.length()][str2.length()];
}

void DistanceTrace(double**& list, const wstring& str1, const wstring& str2) {
	// 아래에서 진행 될 삽입, 삭제, 교환 연산을 실행 순서대로 집어넣는 배열
	double* distanceList{ new double[static_cast<int>(str1.length() * str2.length()) + 1]{ } };
	// 삽입, 삭제, 교환 연산 중 최소값을 넣을 변수
	double minNum{ };

	// list 행렬의 맨 끝부터 시작하게 하기 위해 반복자 i, j, k 선언
	int i{ static_cast<int>(str1.length()) };
	int j{ static_cast<int>(str2.length()) };
	int k{ static_cast<int>(str1.length() * str2.length())};
	while (!(i == 0 && j == 0)) {
		// 삽입, 삭제, 교환 연산 중 가장 작은 값을 찾아 minNum에 대입한다.
		minNum = min(list[i][j - 1], list[i - 1][j], list[i - 1][j - 1]);

		// 만약 minNum의 값이 현재 값과 같다면 다음 연산으로 넘김
		if (minNum == list[i][j])
			i--, j--;
		
		// minNum의 값과 현재 값이 서로 다르다면,
		// 같은 값을 찾아 distanceList에 해당 연산에 해당하는 거리를 넣어준다.
		else
			if (minNum == list[i][j - 1]) { // 삽입 연산
				distanceList[k--] = 0.7;
				j--;
			}
			else if (minNum == list[i - 1][j]) { // 삭제 연산
				distanceList[k--] = 0.5;
				i--;
			}
			else if (minNum == list[i - 1][j - 1]) { // 교환 연산
				distanceList[k--] = 0.3;
				i--, j--;
			}
	}

	// 위의 반복문에서 끝에서부터 역순으로 집어넣은 값들을 정순으로 출력
	for (int i{ }; i <= static_cast<int>(str1.length() * str2.length()); ++i)
		if (distanceList[i] == 0.7)
			cout << "삽입 연산 " << distanceList[i] << endl;
		else if (distanceList[i] == 0.5)
			cout << "삭제 연산 " << distanceList[i] << endl;
		else if (distanceList[i] == 0.3)
			cout << "교환 연산 " << distanceList[i] << endl;
}
