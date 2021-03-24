#include <iostream>
#include <random>
#include <chrono>

using std::cout;
using std::endl;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::microseconds;

void quickSort(int*&, int, int);

void checkSort(int*&);

// ���� ���� ����
random_device rd{ };
mt19937 gen(rd());

int main() {
	constexpr int maxVal1 = 10; // 10�� ������ ���� ����� 10���� �ʱ�ȭ �� maxVal1 ����
	constexpr int maxVal2 = 100000; // 10���� ������ ���� ����� 100000���� �ʱ�ȭ �� maxVal2 ����
	int* list1 = new int[maxVal1] { 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 }; // �־��� ������ �ʱ�ȭ
	int* list2 = new int[maxVal2] { }; // �Ʒ����� ���� �ֱ� ���� �ϴ��� 0���� �ʱ�ȭ

	uniform_int_distribution<int> randInt{ 0, maxVal2 }; // 0 ~ 100000���� �յ� ���� ����
	for (int i{ }; i < maxVal2; ++i) // 0���� 100000 - 1���� �ݺ��ϸ�,
		list2[i] = randInt(gen); // list2�� ������ ������ ����

	// 10�� ����
	auto start{ system_clock::now() }; // ���� �ð�
	quickSort(list1, 0, maxVal1 - 1); // �ð��� ������ �Լ� ����
	auto end{ system_clock::now() }; // ���� �ð�

	auto execTime{ duration_cast<microseconds>(end - start) }; // ���� �ð����� ������ �ð��� ���� ����� �ð� ���
	cout << "10�� ����: " << execTime.count() << "��s" << endl;

	checkSort(list1);

	// 10���� ����
	start = system_clock::now();
	quickSort(list2, 0, maxVal2 - 1);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "\n10���� ����: " << execTime.count() << "��s" << endl;

	checkSort(list2);

	cout << "\n������Ű��а� 12171850 ������" << endl;
	return 0;
}

// �� ���� ���� �ٲ��ִ� �Լ�
// ����ð��� �̵��� ���� inline �Լ��� �����Ͽ���.
inline void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

void quickSort(int*& list, int low, int high) {
	if (high - low > 1) { // high���� low���� Ŭ ��,
		int mid{ (low + high) / 2 }; // mid�� low, high �� �ε����� ���� ���� ���� ������ ����

		// low, mid, high 3���� �ε��� ���� ��� �� �߰� ������ pivot�� �����ϱ� ���� �˰���
		if (list[low] > list[mid]) // ����Ʈ�� low�ε��� ���� ����Ʈ�� mid�ε��� ������ ũ�ٸ�,
			swap(list[low], list[mid]); // �� ���� ���� �ٲ��ش�.
		if (list[low] > list[high]) // ����Ʈ�� low�ε��� ���� ����Ʈ�� high�ε��� ������ ũ�ٸ�,
			swap(list[low], list[high]);// �� ���� ���� �ٲ��ش�.
		if (list[mid] > list[high]) // ����Ʈ�� mid�ε��� ���� ����Ʈ�� high�ε��� ������ ũ�ٸ�,
			swap(list[mid], list[high]); // �� ���� ���� �ٲ��ش�.
		swap(list[mid], list[high - 1]); // �� ���� ���� �ٲ��ָ�, ���������� high - 1�� �߰� ��(pivot�� �� ��)���� ����

		int& pivot{ list[high - 1] }; // ���� �˰����� ���ļ� ���� ����Ʈ�� high - 1�ε��� ���� pivot���� ���� 
		int current{ low }; // low�ε��� ������ current ���� ����
		for (int i{ high - 1 };;) { // i�� high - 1�� ����
			while (list[++current] < pivot); // ����Ʈ�� current + 1�ε��� ���� pivot���� �۴ٸ� �ݺ�
			while (list[--i] > pivot); // ����Ʈ�� i - 1�ε��� ���� pivot ���� ũ�ٸ� �ݺ�
			if (current >= i) // ���� current�ε��� ���� i�ε������� ũ�ų� ���ٸ�,
				break; // �ش� �ݺ����� �����Ѵ�.
			swap(list[current], list[i]); // ���� ���ǿ� �ɸ��� �ʾҴٸ� �� ���� ���� �ٲ��ش�.
		}
		swap(list[current], list[high - 1]); // ���� ���ǿ� ���� �ݺ����� �������Դٸ� �� ���� ���� �ٲ��ش�.

		quickSort(list, low, current - 1);
		quickSort(list, current + 1, high);
	}
	else if (list[low] > list[high]) // ����Ʈ�� low�ε��� ���� ����Ʈ�� high�ε��� ������ Ŭ ��,
		swap(list[low], list[high]); // �� ���� ���� �ٲ��ش�.
}

void checkSort(int*& list) {
	bool sorted{ true };
	size_t n{ _msize(list) / sizeof(int) }; // ����Ʈ�� ������ ������ n�� ����
	for (size_t i{ }; i < n - 1; ++i) {
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
