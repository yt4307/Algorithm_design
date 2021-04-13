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

void QuickSort(int*&, int, int);

void CheckSort(const int*&);

// ���� ���� ����
random_device rd{ };
mt19937 gen{ rd() };

int main() {
	constexpr int listSize{ 100'000'0 }; // ������ ���� ��������� �ʱ�ȭ �� listSize ��� ����
	int* list{ new int[listSize] { } }; // �Ʒ����� ���� �ֱ� ���� �ϴ��� 0���� �ʱ�ȭ

	uniform_int_distribution<int> randInt{ 0, listSize }; // 0 ~ listSize���� �յ� ���� ����
	for (int i{ }; i < listSize; ++i) // 0���� listSize - 1���� �ݺ��ϸ�,
		list[i] = randInt(gen); // list�� ������ ������ ����

	// ���� �ð� ���� ����
	auto start{ system_clock::now() };

	// �� ���� ����
	QuickSort((&list)[0], 0, listSize - 1);

	// ���� �ð� ���� ����
	auto end{ system_clock::now() };

	// ���� �ð����� ������ �ð��� ���� �� ���� �ð� ���
	auto execTime{ duration_cast<microseconds>(end - start) };
	cout << listSize << "�� �� ����: " << execTime.count() << "��s" << endl;

	CheckSort(const_cast<const int*&>((&list)[0]));

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

// �� ������ �ǹ��� �������� ������ ��Ҹ� �ִ��� �����ϰ� ������� �ּ��� �ӵ��� ���δ�.
// �׷��� �׷��ٰ� �ؼ� �迭�� ó������ ������ ��ȸ�ϸ鼭 ��Ȯ�� �߰����� ã�°� �ʹ� �ð��� �����ɸ���.
// ���� ������ 3���� ���� ��� �� �� �߰����� �ش��ϴ� ���� �ǹ������� ����ش�.
void QuickSort(int*& list, int low, int high) {
	// �⺻ ����
	if (low >= high)
		return;

	// �ǹ� ���� ���ϱ� ���� �߰� �� ����
	int mid{ [=] () -> auto {
		uniform_int_distribution<int> list_random_value{low, high}; // low ~ high ���� �յ� ���� ����

		// ������ 3���� ���� ���� ���� ũ�Ⱑ 3�� �迭 ����� ���ÿ� ���� ������ �ʱ�ȭ
		int num[3]{ list_random_value(gen), list_random_value(gen), list_random_value(gen) };

		return (num[0] > num[1]) // num[0] > num[1]�� ���̸� �ݷ� �� ������, �����̸� �ݷ� �� ������
			? ((num[0] > num[2]) ? ((num[1] > num[2]) ? num[1] : num[2]) : num[0])  // �� ��
			: ((num[1] > num[2]) ? ((num[0] > num[2]) ? num[0] : num[2]) : num[1]); // �� ��

		// ���� ��� num[0] > num[1] �̰�, num[0] < num[2] �̸�,
		// num[0]�� num[1]���� ũ�� num[2]���� �۴�. ���� �߰� ���� num[0]
	}() }; // ���� ������ �������� ���� �Լ��̱⿡ ���ٽ����� �ۼ��Ͽ���.

	// ������ ã�� mid �ε����� �ǹ� ������ ����ϱ� ���� ����Ʈ�� �� �ε��� ���� ���� �ٲ��ش�.
	Swap(list[mid], list[high]);

	int& pivot{ list[high] }; // ������ ã�� �˰������� �ǹ� �� ����
	int target{ low - 1 }; // ���� �������� �ε���
	for (int i{ low }; i < high; ++i) // i�� low ���� high - 1(�Ǻ� - 1)���� ��ȸ�ϸ鼭
		if (list[i] < pivot) // ����Ʈ�� i �ε��� ���� �ǹ� ������ �۴ٸ�,

			// ����Ʈ�� ���� ��� �ε����� 1 ������Ű��, ����Ʈ�� i �ε����� ���� ���� �ٲ��ش�.
			Swap(list[++target], list[i]);

	// ��� �ݺ��� ������ ����Ʈ�� ���� ��� �ε����� 1 ������Ű��, �ǹ� ���� ���� ���� �ٲ��ش�.
	Swap(list[++target], pivot);

	// ���� ���� ����
	QuickSort(list, low, target - 1);

	// ���� ���� ����
	QuickSort(list, target + 1, high);
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
