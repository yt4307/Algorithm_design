#include <iostream>

using std::cout;
using std::endl;
using std::string;

void InitNext(string str);

int main() {
	string str[]{ { "AABAA" }, { "ABAABAB" }, { "ABABABAC" } }; // next �迭�� ���� ���ڿ� 3���� ����

	for (int i{ }; i < sizeof(str) / sizeof(str[0]); ++i) {
		cout << "�־��� ����: " << str[i] << endl;
		InitNext(str[i]);
	}

	cout << "\n������Ű��а� 12171850 ������" << endl;
	return 0;
}

void InitNext(string str) {
	// str�� ũ�⸦ ������ ���̷� ����
	const int M{ static_cast<int>(str.length()) };

	// ���ڿ��� ���� ������ ���ϱ� ���� next �迭 ����
	int* next{ new int[M] {} };

	// i�� ���ڿ��� ���� �� ��ġ, j�� ���ϴ� ������ ���� �� ��ġ
	// i�� j�� ���� �ϳ��� ���ڿ��� ������ �ΰ��� ���ڿ��� ���ϴ� �Ͱ� ���� ȿ���� ����.
	for (int i{ }, j{ -1 }; i < M; ++i, ++j) {

		// ���� ��� �÷ο츦 �����ϱ� ���� j�� 0 �̻��� ������ ����
		// ���ڿ��� ���� �� ���� ������ ���� �� ���� ���� ��,
		if (j >= 0 && (str[i] == str[j]))
			next[i] = next[j]; // next �迭�� i �ε����� next �迭�� j �ε��� ���� �־��ش�.
		else // j�� -1 �̰ų� ���ڿ��� ���� �� ��ġ�� ������ ���� ����ġ�� �ٸ� ��,
			next[i] = j; // next �迭�� i �ε����� j���� �־��ش�.
		
		// ���ڿ��� ���� �� ��ġ�� ������ ���� �� ��ġ�� ���� �ʴٸ�,
		while (j >= 0 && (str[i] != str[j]))
			j = next[j]; // j�� next �迭�� j �ε��� ���� �־��ش�.
	}

	// next �迭 ���
	for (int i{ }; i < M; ++i)
		cout << next[i] << ' ';
	cout << endl;

	delete[] next;
}
