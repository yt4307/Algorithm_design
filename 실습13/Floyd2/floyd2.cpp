//#define DEBUG
#include <iostream>
using std::cin;
using std::cout;
constexpr auto endl{ '\n' };

constexpr auto inf{ 99 };

template <size_t N1, size_t N2>
void Floyd2(int, const int(&)[N1][N2], int(&)[N1][N2], int(&)[N1][N2]);

template <size_t N1, size_t N2>
void Path(int(&)[N1][N2], int, int);


int main() {
	const auto s{ [temp{ 0 }] () mutable {
		cin >> temp;
		return temp;
	} () },
		e{ [temp{ 0 }] () mutable {
		cin >> temp;
		return temp;
	} () };

	// �׷����� ���� ���
	// �ڱ� �ڽ����� ���� �Ÿ��� 0, �� ���� �� �� ���� �Ÿ��� inf
	// �� �̿ܿ� ���������� ������ �Ǿ��ִٸ� �� ����ġ�� �ʱ�ȭ
	const int W[6][6]{
		{0, 0, 0, 0, 0, 0},			// ���� ���
		{0, 0, 1, inf, 1, 5},		// v1
		{0, 9, 0, 3, 2, inf},		// v2
		{0, inf, inf, 0, 4, inf},	// v3
		{0, inf, inf, 2, 0, 3},		// v4
		{0, 3, inf, inf, inf, 0}	// v5
	};

	int D[6][6]{ }; // ������ ���� �ִܰŸ�
	int P[6][6]{ }; // ����� ������ matrix

	Floyd2(5, W, D, P);

	// ��� ����� �ִ� �Ÿ� ���
	cout << "The shortest path(" << s << ", " << e << ") is v" << s << " -> ";
	Path(P, s, e);
	cout << "v" << e << endl;

	return 0;
}

template <size_t N1, size_t N2>
void Floyd2(int n, const int(&W)[N1][N2], int(&D)[N1][N2], int(&P)[N1][N2]) {
	// ��������� ���� ��带 �����ϰ� 1���� n���� �ݺ�
	for (int i{ 1 }; i <= n; ++i)
		for (int j{ 1 }; j <= n; ++j)
			D[i][j] = W[i][j]; // ����ġ matrix�� ����

	for (int k{ 1 }; k <= n; ++k)
		for (int i{ 1 }; i <= n; ++i)
			for (int j{ 1 }; j <= n; ++j)

				// k�� ���ļ� ���� �Ͱ� �׳� ���� ���� ���ؼ�
				// k�� ���İ��°� �� ����ġ�� ���ٸ�
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k; // ��� matrix�� ���İ� ��ġ�� �����ϰ�,
					D[i][j] = D[i][k] + D[k][j]; // D matrix�� ���İ��� ��Ʈ ����
				}

#ifdef DEBUG
	cout << "W[i][j] is" << endl;
	for (int i{ 1 }; i <= n; ++i) {
		for (int j{ 1 }; j <= n; ++j)
			cout << W[i][j] << '\t';
		cout << endl;
	}
	cout << endl;
#endif // DEBUG

	cout << "D[i][j] is" << endl;
	for (int i{ 1 }; i <= n; ++i) {
		for (int j{ 1 }; j <= n; ++j)
			cout << D[i][j] << '\t';
		cout << endl;
	}
	cout << endl;

	cout << "P[i][j] is" << endl;
	for (int i{ 1 }; i <= n; ++i) {
		for (int j{ 1 }; j <= n; ++j)
			cout << P[i][j] << '\t';
		cout << endl;
	}
	cout << endl;
}

template <size_t N1, size_t N2>
void Path(int(&P)[N1][N2], int q, int r) {
	// P[q][r]�� 0�� �ƴ� ��(��򰡸� ���İ� ��)
	if (P[q][r] != 0) {
		// q���� r������ �ּ� �Ÿ� Ž�� �� ���
		Path(P, q, P[q][r]);
		cout << "v" << P[q][r] << " -> ";
		Path(P, P[q][r], r);
	}
}
