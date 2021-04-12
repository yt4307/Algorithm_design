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

void CheckSort(const int*&);

// ���� ���� ����
random_device rd{ };
mt19937 gen{ rd() };

int main() {
	constexpr int listSize{ 100'000'000 }; // 1�ﰳ ������ ���� ����� 100,000,000���� �ʱ�ȭ �� listSize ����
	int* list{ new int[listSize] { } }; // �Ʒ����� ���� �ֱ� ���� �ϴ��� 0���� �ʱ�ȭ

	uniform_int_distribution<int> randInt{ 0, listSize }; // 0 ~ listSize���� �յ� ���� ����
	for (int i{ }; i < listSize; ++i) // 0���� listSize - 1���� �ݺ��ϸ�,
		list[i] = randInt(gen); // list�� ������ ������ ����

	// 1�ﰳ ����
	auto start{ system_clock::now() }; // ���� �ð�
	QuickSort(list, 0, listSize - 1); // �ð��� ������ �Լ� ����
	auto end{ system_clock::now() }; // ���� �ð�

	auto execTime{ duration_cast<microseconds>(end - start) }; // ���� �ð����� ������ �ð��� ���� ����� �ð� ���
	cout << listSize << "�� ����: " << execTime.count() << "��s" << endl;

	CheckSort(const_cast<const int*&>(list));

	cout << "\n������Ű��а� 12171850 ������" << endl;
	delete[] list;
	return 0;
}

// �� ���� ���� �ٲ��ִ� �Լ�
// ����ð��� �̵��� ���� inline �Լ��� �����Ͽ���.
inline void Swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

void QuickSort(int*& list, int low, int high) {
	if (high - low > 1) { // high���� low���� Ŭ ��,
		int mid{ (low + high) / 2 }; // mid�� low, high �� �ε����� ���� ���� ���� ������ ����

		// low, mid, high 3���� �ε��� ���� ��� �� �߰� ������ pivot�� �����ϱ� ���� �˰���
		if (list[low] > list[mid]) // ����Ʈ�� low�ε��� ���� ����Ʈ�� mid�ε��� ������ ũ�ٸ�,
			Swap(list[low], list[mid]); // �� ���� ���� �ٲ��ش�.
		if (list[low] > list[high]) // ����Ʈ�� low�ε��� ���� ����Ʈ�� high�ε��� ������ ũ�ٸ�,
			Swap(list[low], list[high]);// �� ���� ���� �ٲ��ش�.
		if (list[mid] > list[high]) // ����Ʈ�� mid�ε��� ���� ����Ʈ�� high�ε��� ������ ũ�ٸ�,
			Swap(list[mid], list[high]); // �� ���� ���� �ٲ��ش�.
		Swap(list[mid], list[high - 1]); // �� ���� ���� �ٲ��ָ�, ���������� high - 1�� �߰� ��(pivot�� �� ��)���� ����

		int& pivot{ list[high - 1] }; // ���� �˰����� ���ļ� ���� ����Ʈ�� high - 1�ε��� ���� pivot���� ���� 
		int current{ low }; // low�ε��� ������ current ���� ����
		for (int i{ high - 1 };;) { // i�� high - 1�� ����
			while (list[++current] < pivot); // ����Ʈ�� current + 1�ε��� ���� pivot���� �۴ٸ� �ݺ�
			while (list[--i] > pivot); // ����Ʈ�� i - 1�ε��� ���� pivot ���� ũ�ٸ� �ݺ�
			if (current >= i) // ���� current�ε��� ���� i�ε������� ũ�ų� ���ٸ�,
				break; // �ش� �ݺ����� �����Ѵ�.
			Swap(list[current], list[i]); // ���� ���ǿ� �ɸ��� �ʾҴٸ� �� ���� ���� �ٲ��ش�.
		}
		Swap(list[current], list[high - 1]); // ���� ���ǿ� ���� �ݺ����� �������Դٸ� �� ���� ���� �ٲ��ش�.

		QuickSort(list, low, current - 1);
		QuickSort(list, current + 1, high);
	}
	else if (list[low] > list[high]) // ����Ʈ�� low�ε��� ���� ����Ʈ�� high�ε��� ������ Ŭ ��,
		Swap(list[low], list[high]); // �� ���� ���� �ٲ��ش�.
}

void CheckSort(const int*& list) {
	bool sorted{ true };
	int n{ static_cast<int>(_msize(const_cast<int*>(list)) / sizeof(int)) }; // ����Ʈ�� ������ ������ n�� ����
	for (int i{ }; i < n - 1; ++i) {
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
