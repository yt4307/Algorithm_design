#include <iostream>

using std::cout;
using std::endl;
using std::string;

void InitNext(string str);

int main() {
	string str[]{ { "AABAA" }, { "ABAABAB" }, { "ABABABAC" } }; // next 배열을 구할 문자열 3가지 선언

	for (int i{ }; i < sizeof(str) / sizeof(str[0]); ++i) {
		cout << "주어진 문장: " << str[i] << endl;
		InitNext(str[i]);
	}

	cout << "\n정보통신공학과 12171850 정연한" << endl;
	return 0;
}

void InitNext(string str) {
	// str의 크기를 패턴의 길이로 설정
	const int M{ static_cast<int>(str.length()) };

	// 문자열에 대한 패턴을 구하기 위해 next 배열 선언
	int* next{ new int[M] {} };

	// i는 문자열의 현재 비교 위치, j는 비교하는 패턴의 현재 비교 위치
	// i와 j를 통해 하나의 문자열을 가지고 두개의 문자열을 비교하는 것과 같은 효과를 낸다.
	for (int i{ }, j{ -1 }; i < M; ++i, ++j) {

		// 버퍼 언더 플로우를 방지하기 위해 j는 0 이상의 값으로 제한
		// 문자열의 현재 비교 값이 패턴의 현재 비교 값과 같을 때,
		if (j >= 0 && (str[i] == str[j]))
			next[i] = next[j]; // next 배열의 i 인덱스에 next 배열의 j 인덱스 값을 넣어준다.
		else // j가 -1 이거나 문자열의 현재 비교 위치가 패턴의 현재 비교위치와 다를 때,
			next[i] = j; // next 배열의 i 인덱스에 j값을 넣어준다.
		
		// 문자열의 현재 비교 위치가 패턴의 현재 비교 위치와 같지 않다면,
		while (j >= 0 && (str[i] != str[j]))
			j = next[j]; // j에 next 배열의 j 인덱스 값을 넣어준다.
	}

	// next 배열 출력
	for (int i{ }; i < M; ++i)
		cout << next[i] << ' ';
	cout << endl;

	delete[] next;
}
