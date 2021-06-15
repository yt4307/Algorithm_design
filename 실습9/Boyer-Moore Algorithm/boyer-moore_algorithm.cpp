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

	int M{ static_cast<int>(pattern.length()) }, N{ static_cast<int>(text.length()) }; // M�� ������ ����, N�� �ؽ�Ʈ�� ����

	// pos�� MisChar �Լ��� ��ȯ ��(ã�Ƴ� ���� ��ġ)�� ����
	// k�� ��ȯ �� pos�� M���� ���� ���� ����
	int pos{ }, k{ };


	// k�� N���� ũ�� text�� ������ ������̹Ƿ� �ݺ� ����
	while (k < N) {

		// text.substr�޼��带 ���� ������ ã�� ���� ���ĺ��� ����
		pos = MisChar(pattern, text.substr(k));
		pos += k; // ������ ã�� k��(pos + M)�� �����ְ�
		k = pos + M; // k�� ������Ʈ
		if (k <= N) // k�� N���� �۰ų� ���ٸ�, �� ������ text�� ���κб��� �����Ѵٸ�
			cout << "������ �߻��� ��ġ: " << pos << endl;
	}

	cout << "\n������Ű��а� 12171850 ������" << endl;

	return 0;
}

inline int index(char c) {
	// ���ĺ� �빮�ڸ� ���´ٰ� ����
	if (static_cast<int>(c) >= 65)
		return static_cast<int>(c) - 65;
	else if (c == 32) // ���鹮�ڰ� ������ ����� ó��
		return 26;
	else
		return static_cast<int>(c);
}

// skip �迭�� ���� �־��ִ� �Լ�
void InitSkip(string& p) {
	int M{ static_cast<int>(p.length()) }; // ������ ����

	for (int i{ }; i < Num; ++i) // ���Ͽ� ���� ���ڸ� ���� ���ڿ� ���̸�ŭ skip
		skip[i] = M;

	for (int i{ }; i < M; ++i) // ���Ͽ� �ִ� ���ڸ� ������ ���� �� ���ڿ��� �Ÿ���ŭ skip
		skip[index(p[i])] = M - i - 1;

	// ���� �ݺ����� ����, �־��� ���ڿ��� ��������
	// 0(A)��° 4, 19(T)��° 3, 8(I)��° 2, 14(O)��° 1, 13(N)��° 0�̰�,
	// ������ ����(���� ���� ����)���� 5�� ������ ���� �ȴ�.
}

int MisChar(string& p, string t) {
	int M{ static_cast<int>(p.length()) }, N{ static_cast<int>(t.length()) }; // M�� ������ ����, N�� �ؽ�Ʈ�� ����
	int i{ M - 1 }, j{ M - 1 }, k{ }; // �ݺ��� ����

	// k�� ���� ����ֱ� ���� ���� skip �迭�� ���� ���� ����
	InitSkip(p);

	// ������ ������ ���������� �� ����
	while (j >= 0) {
		while (t[i] != p[j]) {
			
			// skip �迭�� Ư�� ���ĺ��� �ش��ϴ� �ε��� ��ġ�� ���� k�� ����ִ´�.
			// ���� t[i]�� ���ڰ� ���� �ȿ� �ִ� ���ڶ�� skip �迭�� �ش� ������ skip �Ÿ��� ����ְ�,
			// ���ٸ� ������ ������ 5�� �ִ´�.
			k = skip[index(t[i])];
			
			if (M - j > k) // ������ ���� - ���ؼ� ���� ���� k���� ũ�� 
				i += M - j; // ������ ���� - ���ؼ� ���� �� ��ŭ ���������� ���� ��
			
			else // �׷��� ������ k��ŭ ���������� ���� ��
				i += k;

			if (i >= N) // ������ �񱳸� �Ϸ��ϸ� N�� ��ȯ
				return N;

			// ������ ��ġ�� ��� �������� ��� ���ϸ鼭 j���� �۾����µ�,
			// �� ��, ����ġ �߻���(t[i] != p[j]) �ٽ� j�� M - 1�� �ʱ�ȭ
			j = M - 1;
		}
		--i, --j;
	}
	return i + 1;
}
