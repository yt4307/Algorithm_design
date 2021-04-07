#include <iostream>
using std::cout;
using std::endl;

template <size_t N>
void radixSort(int(&)[N], int, int);

template <size_t N>
void checkSort(int(&)[N]);

int main() {
	int list[]{ 170, 45, 75, 90, 2, 24, 802, 66 };
	

	cout << "���� �� ����Ʈ" << endl;
	for (auto iter : list)
		cout << iter << ' ';
	cout << endl;

	radixSort(list, 3, 10);
	cout << "���� �� ����Ʈ" << endl;
	for (auto iter : list)
		cout << iter << ' ';
	cout << endl;

	checkSort(list);
	
	cout << "\n������Ű��а� 12171850 ������" << endl;
	return 0;
}

/**
   * @data  ���� �迭
   * @size  data�� �������� ����
   * @p  ������ �ִ� �ڸ���
   * @k  ���(10������ ����Ѵٸ� 10)
   *
   */
template <size_t N>
void radixSort(int(&list)[N], int p, int k) {
	int* counts{ }, // Ư�� �ڸ����� ���ڵ��� ī��Ʈ
		* temp{ }; // ���ĵ� �迭�� ���� �ӽ� ���
	int index{ }, pval{ };

	// �޸� �Ҵ�
	if ((counts = new int[k] { }) == NULL)
		return;
	if ((temp = new int[N] { }) == NULL)
		return;
	for (int n{ }; n < p; ++n) { // 1�� �ڸ�, 10���ڸ�, 100�� �ڸ� ������ ����
		for (int i{ }; i < k; ++i)
			counts[i] = 0; // �ʱ�ȭ
		// ��ġ�� ���.
		// n:0 => 1,  1 => 10, 2 => 100
		pval = static_cast<int>(pow(static_cast<double>(k), static_cast<double>(n)));

		// �� ������ �߻�Ƚ���� ����.
		for (int j{ }; j < N; ++j) {
			// 253�̶�� ���ڶ��
			// n:0 => 3,  1 => 5, 2 => 2
			index = static_cast<int>(list[j] / pval) % k;
			counts[index] = counts[index] + 1;
		}

		// ī��Ʈ �������� ���Ѵ�. ��������� ���ؼ�.
		for (int i{ 1 }; i < k; ++i) {
			counts[i] = counts[i] + counts[i - 1];
		}

		// ī��Ʈ�� ����� �� �׸��� ��ġ�� �����Ѵ�.
		// ������� ���
		for (int j{ N - 1 }; j >= 0; --j) { // �ڿ������� ����
			index = static_cast<int>(list[j] / pval) % k;
			temp[counts[index] - 1] = list[j];
			counts[index] = counts[index] - 1; // �ش� ���� ī��Ʈ�� 1 ����
		}
		// �ӽ� ������ ����
		memcpy(list, temp, N * sizeof(int));
	}
	delete[] counts;
	delete[] temp;
}

template <size_t N>
void checkSort(int(&list)[N]) {
	bool sorted{ true };
	for (int i{ }; i < N - 1; ++i) {
		if (list[i] > list[i + 1])
			sorted = false;
		if (!sorted)
			break;
	}
	if (sorted)
		cout << "Sorting complete!" << endl;
	else
		cout << "Error during sorting..." << endl;
}
