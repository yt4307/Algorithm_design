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

void ShellSort(int*&);

void CheckSort(const int*&);

random_device rd{ };
mt19937 gen{ rd() };

int main() {
	const int listSize{ 100'000'000 };
	int* list{ new int[listSize] { } };

	uniform_int_distribution<int> randInt{ 0, listSize };
	for (int i{ }; i < listSize; ++i)
		list[i] = randInt(gen);

	// �� ���� ����
	auto start{ system_clock::now() };
	ShellSort((&list)[0]);
	auto end{ system_clock::now() };

	auto execTime{ duration_cast<microseconds>(end - start) };
	cout << listSize << "�� ����: " << execTime.count() << "��s" << endl;

	// ���� ��� ���
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

// �� ����
void ShellSort(int*& list) {
	int length{ static_cast<int>(_msize(list) / sizeof(int)) };

	// https://oeis.org/A102549/internal �� ���� ������� �˷��� gap sequence�� �� ���� ���� ������ ���� �������� ã�Ҵ�.
	// �� ���������� 1750���� ���ǵǾ�������, ���� 2.25�� ���� ���� �� �� �迭�� �ִ� ����
	// 21���� ���� �ʴ� �ִ밪���� �����Ͽ� �ʱ�ȭ �Ͽ���.
	int gap[] = { 1, 4, 10, 23, 57, 132, 301, 701, 1750,
		3937, 8858, 19930, 44842, 100894, 227011, 510774,
		1149241, 2585792, 5818032, 13090572, 29453787,
		66271020, 149109795, 335497038, 754868335, 1698453753 };
	
	int gapIndex{ }, step{ };
	for (; gap[gapIndex] <= length / 2.25; ++gapIndex);

	// �κ� ����Ʈ�� ����� gap��ŭ ������ ��ҵ��� ���� ����
	while (gapIndex >= 0) { // gap�� 1�� �� ������ �ݺ�
		step = gap[gapIndex--];	// ���� gap(step)
		
		// �� �κ� ����Ʈ�� �� ��° ������ �ε��� ���� ��ȸ�Ѵ�.
		// ���� ��� step�� 3�� �� arr[0], arr[1], arr[2]�� ���� ���ҿ� ���� ���� ����.
		// ���� step���� ��ȸ�Ѵ�.
		for (int i{ step }; i < length; ++i)

			// j�� target ���Ұ� �Ǹ� ���� ����(target) a[j]�� ���� ���� a[j - step]���� ���� �� ���� �ݺ��Ѵ�.
			for (int j = i; j >= step && list[j] < list[j - step]; j -= step)

				//����(target) ������ �ε���(j)�� ������ ����(j-step)�� �ε����� �ִ� ������ ���� ��ȯ�Ѵ�.
				Swap(list[j], list[j - step]);
	}
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
