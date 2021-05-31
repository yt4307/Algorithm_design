#define DEBUG
#include <iostream>
using std::cout;
constexpr auto endl{ '\n' };

template <size_t N1, size_t N2>
int CalculateCheese(const int(&)[N1][N2]);

template <size_t N1, size_t N2>
int CalculateCheeseWithTrap(const int(&)[N1][N2]);

int main() {
	// cheese[8][0]에서 cheese[0][8]로 이동
	// 쥐는 항상 오른쪽 또는 위쪽으로만 이동할 수 있다.
	// 치즈가 있으면 1 없으면 0
	const int cheese[9][9]{
	{0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0} };

	// 치즈가 있으면 1, 함정이 있으면 2, 아무것도 없다면 0
	const int cheeseWithTrap[9][9]{
	{0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 2, 0},
	{1, 0, 2, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 2, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 2, 1, 2, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0} };

	for (int i{ }; i < 9; ++i) {
		for (int j{ }; j < 9; ++j)
			cout << cheese[i][j] << '\t';
		cout << endl;
	}

	cout << CalculateCheese(cheese) << endl;					//예제 1
	cout << CalculateCheeseWithTrap(cheeseWithTrap) << endl;	//예제 2


	cout << "\n정보통신공학과 12171850 정연한" << endl;
	return 0;
}

// 아주 짧은 인라인 함수에선 소문자를 사용할 수 있다.
// 예를 들어 리턴값을 캐시하지 않고 루프 안에서 호출할 정도로 가벼운 함수라면 소문자 이름을 사용할 수 있다.
template <typename T>
inline const T max(const T& a, const T& b) {
	return a >= b ? a : b;
}

// 먹을 수 있는 최대 치즈 개수를 계산하는 함수
template <size_t N1, size_t N2>
int CalculateCheese(const int(&cheese)[N1][N2]) {
	// [N1][N2]개의 먹을 수 있는 최대 치즈 개수를 저장하는 행렬
	int result[9][9]{ };

	// 원본 행렬의 시작위치(8열 0행)에 치즈가 있으면,
	// result 행렬의 시작위치의 값을 1로 변경
	if (cheese[8][0])
		result[8][0] = 1;

	// 맨 왼쪽 세로줄 검사, [8][0]은 했으니 [7][0]부터 검사
	for (int i{ 7 }; i >= 0; --i)
		// [i][0]에 치즈가 없으면 그대로
		if (cheese[i][0] == 0)
			result[i][0] = result[i + 1][0];

		// 있으면 아래쪽 값 + 1 대입
		else
			result[i][0] = result[i + 1][0] + 1;

	// 맨 아래쪽 가로줄 검사, [8][0]은 했으니 [8][1]부터 검사
	for (int j{ 1 }; j < 9; ++j)
		// [8][j]에 치즈가 없으면 그대로
		if (cheese[8][j] == 0)
			result[8][j] = result[8][j - 1];

		// 있으면 왼쪽 값 + 1 대입
		else
			result[8][j] = result[8][j - 1] + 1;
	
	// [8][0]부터 [0][0]까지, [8][0]부터 [8][8]까지는 검사했으므로,
	// [7][0]부터 [0][8]까지 검사
	for (int i{ 7 }; i >= 0; --i)
		for (int j{ 1 }; j < 9; ++j)
			// [i][j]에 치즈가 없으면 그대로
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i + 1][j], result[i][j - 1]);

			// 있으면 아래쪽 값, 왼쪽 값을 비교해서 더 큰 값 + 1 대입
			else
				result[i][j] = max(result[i + 1][j], result[i][j - 1]) + 1;
		
#ifdef DEBUG
	cout << endl;
	// 먹을 수 있는 최대 치즈 개수 표시
	for (int i{ }; i < 9; ++i) {
		for (int j{ }; j < 9; ++j)
			cout << result[i][j] << '\t';
		cout << endl;
	}
#endif // DEBUG

	// 먹을 수 있는 최대 치즈 개수 반환
	return result[0][8];
}

// 먹을 수 있는 최대 치즈 개수를 구하는 함수입니다. 근데 이제 함정을 곁들인
template <size_t N1, size_t N2>
int CalculateCheeseWithTrap(const int(&cheese)[N1][N2]) {
	int result[9][9]{ };

	if (cheese[8][0])
		result[8][0] = 1;

	// 치즈가 있거나 아무것도 없을때는 그대로 진행하지만 쥐덫이 있는 경우는 피해가야 한다.
	for (int i{ 7 }; i >= 0; --i)
		if (cheese[i][0] == 0)
			result[i][0] = result[i + 1][0];

		else if (cheese[i][0] == 1)
			result[i][0] = result[i + 1][0] + 1;

		// 쥐덫이 있는 경우
		else {
			// 쥐덫의 위치에 -1 대입 이후 반복문을 빠져나온다.
			result[i][0] = -1;
			break;
		}

	// 맨 아래쪽 가로줄도 동일하게 진행
	for (int j{ 1 }; j < 9; ++j)
		if (cheese[8][j] == 0)
			result[8][j] = result[8][j - 1];

		else if (cheese[8][j] == 1)
			result[8][j] = result[8][j - 1] + 1;

		else {
			result[8][j] = -1;
			break;
		}

	// 나머지 [7][0]부터 [0][8]까지 검사
	for (int i{ 7 }; i >= 0; --i)
		for (int j{ 1 }; j < 9; ++j)
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]);

			else if (cheese[i][j] == 1)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]) + 1;

			// 함정을 만나면 함정 체크만 하고 넘어간다.
			else
				result[i][j] = -1;

#ifdef DEBUG
	cout << endl;
	// 먹을 수 있는 최대 치즈 개수 표시
	for (int i{ }; i < 9; ++i) {
		for (int j{ }; j < 9; ++j)
			cout << result[i][j] << '\t';
		cout << endl;
	}
#endif // DEBUG

	return result[0][8];
}
