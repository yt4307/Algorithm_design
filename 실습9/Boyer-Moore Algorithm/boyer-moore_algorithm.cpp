#include <iostream>

using std::cout;
using std::endl;
using std::string;

constexpr int Num{ 50 };
int skip[Num]{ };

int MisChar(string&, string);

int main() {
	string text{ "VISION QUESTION ONION CAPTION GRADUATION EDUCATION" };
	string pattern{ "ATION" };

	int M{ static_cast<int>(pattern.length()) }, N{ static_cast<int>(text.length()) }; // M은 패턴의 길이, N은 텍스트의 길이

	// pos는 MisChar 함수의 반환 값(찾아낸 패턴 위치)을 저장
	// k는 반환 된 pos에 M값을 더한 값을 저장
	int pos{ }, k{ };


	// k가 N보다 크면 text의 범위를 벗어난것이므로 반복 종료
	while (k < N) {

		// text.substr메서드를 통해 이전에 찾은 패턴 이후부터 시작
		pos = MisChar(pattern, text.substr(k));
		pos += k; // 이전에 찾은 k값(pos + M)을 더해주고
		k = pos + M; // k값 업데이트
		if (k <= N) // k가 N보다 작거나 같다면, 즉 패턴이 text의 끝부분까지 존재한다면
			cout << "패턴이 발생한 위치: " << pos << endl;
	}

	cout << "\n정보통신공학과 12171850 정연한" << endl;

	return 0;
}

inline int index(char c) {
	// 알파벳 대문자만 들어온다고 가정
	if (static_cast<int>(c) >= 65)
		return static_cast<int>(c) - 65;
	else if (c == 32) // 공백문자가 들어왔을 경우의 처리
		return 26;
	else
		return static_cast<int>(c);
}

// skip 배열에 값을 넣어주는 함수
void InitSkip(string& p) {
	int M{ static_cast<int>(p.length()) }; // 패턴의 길이

	for (int i{ }; i < Num; ++i) // 패턴에 없는 문자면 패턴 문자열 길이만큼 skip
		skip[i] = M;

	for (int i{ }; i < M; ++i) // 패턴에 있는 문자면 패턴의 끝과 그 문자와의 거리만큼 skip
		skip[index(p[i])] = M - i - 1;

	// 위의 반복문을 통해, 주어진 문자열을 기준으로
	// 0(A)번째 4, 19(T)번째 3, 8(I)번째 2, 14(O)번째 1, 13(N)번째 0이고,
	// 나머지 문자(공백 문자 포함)들은 5가 값으로 들어가게 된다.
}

int MisChar(string& p, string t) {
	int M{ static_cast<int>(p.length()) }, N{ static_cast<int>(t.length()) }; // M은 패턴의 길이, N은 텍스트의 길이
	int i{ M - 1 }, j{ M - 1 }, k{ }; // 반복자 선언

	// k에 값을 집어넣기 위해 먼저 skip 배열에 값을 집어 넣음
	InitSkip(p);

	// 패턴의 오른쪽 끝에서부터 비교 시작
	while (j >= 0) {
		while (t[i] != p[j]) {
			
			// skip 배열의 특정 알파벳에 해당하는 인덱스 위치의 값을 k에 집어넣는다.
			// 만약 t[i]의 문자가 패턴 안에 있는 문자라면 skip 배열의 해당 문자의 skip 거리를 집어넣고,
			// 없다면 패턴의 길이인 5를 넣는다.
			k = skip[index(t[i])];
			
			if (M - j > k) // 패턴의 길이 - 비교해서 맞은 수가 k보다 크면 
				i += M - j; // 패턴의 길이 - 비교해서 맞은 수 만큼 오른쪽으로 가서 비교
			
			else // 그렇지 않으면 k만큼 오른쪽으로 가서 비교
				i += k;

			if (i >= N) // 끝까지 비교를 완료하면 N을 반환
				return N;

			// 패턴이 일치할 경우 왼쪽으로 계속 비교하면서 j값이 작아지는데,
			// 이 때, 불일치 발생시(t[i] != p[j]) 다시 j를 M - 1로 초기화
			j = M - 1;
		}
		--i, --j;
	}
	return i + 1;
}
