#include <iostream>
#include <locale>
using std::cin;
using std::cout;
using std::wcin;
const auto endl{ '\n' };

using std::wstring;

int LevenshteinDistanceA(wstring&, wstring&);
double LevenshteinDistanceB(wstring&, wstring&);

int main() {
	// ���̵� ���ڿ��� ����ϱ� ������ �������� �ѱ��� �ѱ���� �������ش�.
	setlocale(LC_ALL, "ko_KR");

	// ���̵� ���ڿ��� ���� �� �ִ� wstring���� ���ڿ� ���� ����
	wstring str1{ }, str2{ };
	cout << "Source: ";
	wcin >> str1;
	cout << "Target: ";
	wcin >> str2;

	cout << "(a) Levenshtein Distance : " << LevenshteinDistanceA(str1, str2) << endl << endl;
	cout << "(b) Levenshtein Distance : " << LevenshteinDistanceB(str1, str2) << endl;

	cout << "\n������Ű��а� 12171850 ������" << endl;
	return 0;
}

template <typename T>
inline const T& min(const T& left, const T& mid, const T& right) {
	// mid�� left���� ū�� ���ϰ� right�� left���� ū�� ���ؼ�
	// left�� ���� ������ left��ȯ �ƴ϶�� ���� �� ����
	return (mid > left) && (right > left) ? left : (mid > right ? right : mid);
}

int LevenshteinDistanceA(wstring& str1, wstring& str2) {
	// ����Ʈ ���� �� �ʱ�ȭ
	// + 2�� �� ����: �⺻������ ���ڿ��̱� ������ ���鹮�ڰ� �� �ڸ� + 1
	// �ű⿡ 0�� �ƴ϶� 1���� length()���� ���� ���Ƿ� �������� �� + 1�ؼ� �� + 2
	int** list{ new int* [static_cast<int>(str1.length()) + 2]{ } };
	for (int i{ }; i < static_cast<int>(str1.length()) + 2; ++i)
		list[i] = new int[static_cast<int>(str2.length()) + 2]{ };

	// source ���ڿ� ������(��) ù��° ä���
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		list[i][0] = i;
	// target ���ڿ� ������(��) ù��° ä���
	for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
		list[0][j] = j;

	// ù��° ���� ù��° ���� ������ ���� ���� ä���
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
			// ���Ϸ��� �� ���ڿ��� ���ڰ� ���� ���
			if (str1[i - 1] == str2[j - 1])
				// ���� ��(���� �밢�� ���� ��)�� �״�� �����´�.(dp)
				list[i][j] = list[i - 1][j - 1];
			else // �׷��� �ʴٸ� ���� ��, ���� ��, ���� ������ ���� 1�� ���� �� �� ���� ���� ���� �����´�.
				list[i][j] = min(list[i][j - 1] + 1, list[i - 1][j] + 1, list[i - 1][j - 1] + 1);

	// ���� ���
	for (int i{ }; i <= static_cast<int>(str1.length()); ++i) {
		for (int j{ }; j <= static_cast<int>(str2.length()); ++j)
			cout << list[i][j] << '\t';
		cout << endl;
	}

	// ���������� ���� �� Levenshtein distance ��ȯ
	return list[str1.length()][str2.length()];
}

double LevenshteinDistanceB(wstring& str1, wstring& str2) {
	// ����Ʈ ���� �� �ʱ�ȭ
	// + 2�� �� ����: �⺻������ ���ڿ��̱� ������ ���鹮�ڰ� �� �ڸ� + 1
	// �ű⿡ 0�� �ƴ϶� 1���� length()���� ���� ���Ƿ� �������� �� + 1�ؼ� �� + 2
	double** list{ new double* [static_cast<int>(str1.length()) + 2]{ } };
	for (int i{ }; i < static_cast<int>(str1.length()) + 2; ++i)
		list[i] = new double[static_cast<int>(str2.length()) + 2]{ };

	// source ���ڿ� ������(��) ù��° ä���
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		list[i][0] = i;
	// target ���ڿ� ������(��) ù��° ä���
	for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
		list[0][j] = j;

	// ù��° ���� ù��° ���� ������ ���� ���� ä���
	for (int i{ 1 }; i <= static_cast<int>(str1.length()); ++i)
		for (int j{ 1 }; j <= static_cast<int>(str2.length()); ++j)
			// ���Ϸ��� �� ���ڿ��� ���ڰ� ���� ���
			if (str1[i - 1] == str2[j - 1])
				// ���� ��(���� �밢�� ���� ��)�� �״�� �����´�.(dp)
				list[i][j] = list[i - 1][j - 1];
			else // �׷��� �ʴٸ� ���� ��(����), ���� ��(����), ���� ��(��ȯ)�鿡
				 // ���� 0.7, 0.5, 0.3�� ���� �� �� ���� ���� ���� �����´�.
				list[i][j] = min(list[i][j - 1] + 0.7, list[i - 1][j] + 0.5, list[i - 1][j - 1] + 0.3);

	// ���� ���
	for (int i{ }; i <= static_cast<int>(str1.length()); ++i) {
		for (int j{ }; j <= static_cast<int>(str2.length()); ++j)
			cout << list[i][j] << '\t';
		cout << endl;
	}

	// ���������� ���� �� Levenshtein distance ��ȯ
	return list[str1.length()][str2.length()];
}
