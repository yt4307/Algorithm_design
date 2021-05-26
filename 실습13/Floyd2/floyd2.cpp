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

	// 그래프의 인접 행렬
	// 자기 자신으로 가는 거리는 0, 한 번에 갈 수 없는 거리는 inf
	// 그 이외에 직접적으로 연결이 되어있다면 그 가중치로 초기화
	const int W[6][6]{
		{0, 0, 0, 0, 0, 0},			// 더미 노드
		{0, 0, 1, inf, 1, 5},		// v1
		{0, 9, 0, 3, 2, inf},		// v2
		{0, inf, inf, 0, 4, inf},	// v3
		{0, inf, inf, 2, 0, 3},		// v4
		{0, 3, inf, inf, inf, 0}	// v5
	};

	int D[6][6]{ }; // 정점들 간의 최단거리
	int P[6][6]{ }; // 결과를 저장할 matrix

	Floyd2(5, W, D, P);

	// 모든 경로의 최단 거리 출력
	cout << "The shortest path(" << s << ", " << e << ") is v" << s << " -> ";
	Path(P, s, e);
	cout << "v" << e << endl;

	return 0;
}

template <size_t N1, size_t N2>
void Floyd2(int n, const int(&W)[N1][N2], int(&D)[N1][N2], int(&P)[N1][N2]) {
	// 인접행렬의 더미 노드를 제외하고 1부터 n까지 반복
	for (int i{ 1 }; i <= n; ++i)
		for (int j{ 1 }; j <= n; ++j)
			D[i][j] = W[i][j]; // 가중치 matrix를 복사

	for (int k{ 1 }; k <= n; ++k)
		for (int i{ 1 }; i <= n; ++i)
			for (int j{ 1 }; j <= n; ++j)

				// k를 거쳐서 가는 것과 그냥 가는 것을 비교해서
				// k를 거쳐가는게 더 가중치가 낮다면
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k; // 결과 matrix에 거쳐간 위치를 저장하고,
					D[i][j] = D[i][k] + D[k][j]; // D matrix에 거쳐가는 루트 저장
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
	// P[q][r]이 0이 아닐 때(어딘가를 거쳐갈 때)
	if (P[q][r] != 0) {
		// q에서 r까지의 최소 거리 탐색 및 출력
		Path(P, q, P[q][r]);
		cout << "v" << P[q][r] << " -> ";
		Path(P, P[q][r], r);
	}
}
