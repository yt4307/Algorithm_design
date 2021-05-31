#define DEBUG
#include <iostream>
using std::cout;
constexpr auto endl{ '\n' };

template <size_t N1, size_t N2>
int CalculateCheese(const int(&)[N1][N2]);

template <size_t N1, size_t N2>
int CalculateCheeseWithTrap(const int(&)[N1][N2]);

int main() {
	// cheese[8][0]���� cheese[0][8]�� �̵�
	// ��� �׻� ������ �Ǵ� �������θ� �̵��� �� �ִ�.
	// ġ� ������ 1 ������ 0
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

	// ġ� ������ 1, ������ ������ 2, �ƹ��͵� ���ٸ� 0
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

	cout << CalculateCheese(cheese) << endl;					//���� 1
	cout << CalculateCheeseWithTrap(cheeseWithTrap) << endl;	//���� 2


	cout << "\n������Ű��а� 12171850 ������" << endl;
	return 0;
}

// ���� ª�� �ζ��� �Լ����� �ҹ��ڸ� ����� �� �ִ�.
// ���� ��� ���ϰ��� ĳ������ �ʰ� ���� �ȿ��� ȣ���� ������ ������ �Լ���� �ҹ��� �̸��� ����� �� �ִ�.
template <typename T>
inline const T max(const T& a, const T& b) {
	return a >= b ? a : b;
}

// ���� �� �ִ� �ִ� ġ�� ������ ����ϴ� �Լ�
template <size_t N1, size_t N2>
int CalculateCheese(const int(&cheese)[N1][N2]) {
	// [N1][N2]���� ���� �� �ִ� �ִ� ġ�� ������ �����ϴ� ���
	int result[9][9]{ };

	// ���� ����� ������ġ(8�� 0��)�� ġ� ������,
	// result ����� ������ġ�� ���� 1�� ����
	if (cheese[8][0])
		result[8][0] = 1;

	// �� ���� ������ �˻�, [8][0]�� ������ [7][0]���� �˻�
	for (int i{ 7 }; i >= 0; --i)
		// [i][0]�� ġ� ������ �״��
		if (cheese[i][0] == 0)
			result[i][0] = result[i + 1][0];

		// ������ �Ʒ��� �� + 1 ����
		else
			result[i][0] = result[i + 1][0] + 1;

	// �� �Ʒ��� ������ �˻�, [8][0]�� ������ [8][1]���� �˻�
	for (int j{ 1 }; j < 9; ++j)
		// [8][j]�� ġ� ������ �״��
		if (cheese[8][j] == 0)
			result[8][j] = result[8][j - 1];

		// ������ ���� �� + 1 ����
		else
			result[8][j] = result[8][j - 1] + 1;
	
	// [8][0]���� [0][0]����, [8][0]���� [8][8]������ �˻������Ƿ�,
	// [7][0]���� [0][8]���� �˻�
	for (int i{ 7 }; i >= 0; --i)
		for (int j{ 1 }; j < 9; ++j)
			// [i][j]�� ġ� ������ �״��
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i + 1][j], result[i][j - 1]);

			// ������ �Ʒ��� ��, ���� ���� ���ؼ� �� ū �� + 1 ����
			else
				result[i][j] = max(result[i + 1][j], result[i][j - 1]) + 1;
		
#ifdef DEBUG
	cout << endl;
	// ���� �� �ִ� �ִ� ġ�� ���� ǥ��
	for (int i{ }; i < 9; ++i) {
		for (int j{ }; j < 9; ++j)
			cout << result[i][j] << '\t';
		cout << endl;
	}
#endif // DEBUG

	// ���� �� �ִ� �ִ� ġ�� ���� ��ȯ
	return result[0][8];
}

// ���� �� �ִ� �ִ� ġ�� ������ ���ϴ� �Լ��Դϴ�. �ٵ� ���� ������ �����
template <size_t N1, size_t N2>
int CalculateCheeseWithTrap(const int(&cheese)[N1][N2]) {
	int result[9][9]{ };

	if (cheese[8][0])
		result[8][0] = 1;

	// ġ� �ְų� �ƹ��͵� �������� �״�� ���������� �㵣�� �ִ� ���� ���ذ��� �Ѵ�.
	for (int i{ 7 }; i >= 0; --i)
		if (cheese[i][0] == 0)
			result[i][0] = result[i + 1][0];

		else if (cheese[i][0] == 1)
			result[i][0] = result[i + 1][0] + 1;

		// �㵣�� �ִ� ���
		else {
			// �㵣�� ��ġ�� -1 ���� ���� �ݺ����� �������´�.
			result[i][0] = -1;
			break;
		}

	// �� �Ʒ��� �����ٵ� �����ϰ� ����
	for (int j{ 1 }; j < 9; ++j)
		if (cheese[8][j] == 0)
			result[8][j] = result[8][j - 1];

		else if (cheese[8][j] == 1)
			result[8][j] = result[8][j - 1] + 1;

		else {
			result[8][j] = -1;
			break;
		}

	// ������ [7][0]���� [0][8]���� �˻�
	for (int i{ 7 }; i >= 0; --i)
		for (int j{ 1 }; j < 9; ++j)
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]);

			else if (cheese[i][j] == 1)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]) + 1;

			// ������ ������ ���� üũ�� �ϰ� �Ѿ��.
			else
				result[i][j] = -1;

#ifdef DEBUG
	cout << endl;
	// ���� �� �ִ� �ִ� ġ�� ���� ǥ��
	for (int i{ }; i < 9; ++i) {
		for (int j{ }; j < 9; ++j)
			cout << result[i][j] << '\t';
		cout << endl;
	}
#endif // DEBUG

	return result[0][8];
}
