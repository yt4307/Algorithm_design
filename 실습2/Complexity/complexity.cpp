#include <iostream>
#include <chrono>
using std::cout;
using std::endl;

constexpr int INPUT = 230;

int secondaryMatrix(int**, int**, int**);
int fibonacci(int);

int main() {
	cout << "입력값은 230 고정" << endl;
	int** matrixA = new int* [INPUT];
	int** matrixB = new int* [INPUT];
	int** matrixC = new int* [INPUT];
	for (int j = 0; j < INPUT; ++j) {
		matrixA[j] = new int[INPUT];
		matrixB[j] = new int[INPUT];
		matrixC[j] = new int[INPUT];
	}

	for (int i = 0; i < INPUT; ++i) {
		for (int j = 0; j < INPUT; ++j) {
			matrixA[j][i] = 1;
			matrixB[j][i] = 2;
			matrixC[j][i] = 3;
		}
	}


	// 2차 행렬 함수 수행 시간
	auto startMat{ std::chrono::system_clock::now() };
	int resultMat{ secondaryMatrix(matrixA, matrixB, matrixC) };
	auto endMat{ std::chrono::system_clock::now() };

	std::chrono::microseconds microsecondsMat{ std::chrono::duration_cast<std::chrono::microseconds>(endMat - startMat) };
	cout << "2차 행렬 함수 수행 시간: " << microsecondsMat.count() << " microseconds" << endl;

	// 피보나치 함수 수행 시간
	auto startFibo{ std::chrono::system_clock::now() };
	int resultFibo{ fibonacci(INPUT) };
	auto endFibo{ std::chrono::system_clock::now() };


	std::chrono::microseconds microsecondsFibo{ std::chrono::duration_cast<std::chrono::microseconds>(endFibo - startFibo) };
	cout << "피보나치 함수 수행 시간: " << microsecondsFibo.count() << " microseconds" << endl;


	cout << "\n정보통신공학과 12171850 정연한" << endl;


	for (int j = 0; j < INPUT; ++j) {
		delete[] matrixA[j];
		delete[] matrixB[j];
		delete[] matrixC[j];
	}
	delete[] matrixA;
	delete[] matrixB;
	delete[] matrixC;

	return 0;
}

// Cubic complexity
// 3중 반복문 사용한 2차 행렬 계산
int secondaryMatrix(int** matrixA, int** matrixB, int** matrixC) {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				matrixA[k][k] = matrixB[k][k] + matrixC[k][k];
			}
			matrixB[j][j] = matrixC[j][j] + matrixA[j][j];
		}
		matrixC[i][i] = matrixA[i][i] + matrixB[i][i];
	}


	return 0;
}

// Exponential complexity
// 피보나치 함수
int fibonacci(int n) {
	int before = 0, cur = 1, i, temp;
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else {
		for (i = 1; i < n; i++) {
			temp = cur;
			cur = before + cur;
			before = temp;
		}
		return cur;
	}
}

