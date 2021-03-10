#include <iostream>
#include <chrono>
using std::cout;
using std::endl;

constexpr int INPUT = 230;

int secondaryMatrix(int**, int**, int**);
int fibonacci(int);

int main() {
	cout << "�Է°��� 230 ����" << endl;
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


	// 2�� ��� �Լ� ���� �ð�
	auto startMat{ std::chrono::system_clock::now() };
	int resultMat{ secondaryMatrix(matrixA, matrixB, matrixC) };
	auto endMat{ std::chrono::system_clock::now() };

	std::chrono::microseconds microsecondsMat{ std::chrono::duration_cast<std::chrono::microseconds>(endMat - startMat) };
	cout << "2�� ��� �Լ� ���� �ð�: " << microsecondsMat.count() << " microseconds" << endl;

	// �Ǻ���ġ �Լ� ���� �ð�
	auto startFibo{ std::chrono::system_clock::now() };
	int resultFibo{ fibonacci(INPUT) };
	auto endFibo{ std::chrono::system_clock::now() };


	std::chrono::microseconds microsecondsFibo{ std::chrono::duration_cast<std::chrono::microseconds>(endFibo - startFibo) };
	cout << "�Ǻ���ġ �Լ� ���� �ð�: " << microsecondsFibo.count() << " microseconds" << endl;


	cout << "\n������Ű��а� 12171850 ������" << endl;


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
// 3�� �ݺ��� ����� 2�� ��� ���
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
// �Ǻ���ġ �Լ�
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

