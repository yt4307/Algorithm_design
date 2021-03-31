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

void swap(int&, int&);

void maxHeapSort(int*&);

void maxHeapify(int*&, int, int);

void minHeapSort(int*&);

void minHeapify(int*&, int, int);

void checkSort1(int*&);

void checkSort2(int*&);

// ���� ���� ����
random_device rd{ };
mt19937 gen(rd());

int main() {
	constexpr int maxVal1{ 10 }; // 10�� ������ ���� ����� 10���� �ʱ�ȭ �� maxVal1 ����
	constexpr int maxVal2{ 100000 }; // 10���� ������ ���� ����� 100000���� �ʱ�ȭ �� maxVal2 ����
	int* list1{ new int[maxVal1] { 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 } }; // �־��� ������ �ʱ�ȭ
	int* list2{ new int[maxVal2] {} }; // �Ʒ����� ���� �ֱ� ���� �ϴ��� 0���� �ʱ�ȭ

	uniform_int_distribution<int> randInt{0, maxVal2}; // 0 ~ 100000���� �յ� ���� ����

	for (int i{ }; i < maxVal2; ++i) // 0���� 100000 - 1���� �ݺ��ϸ�,
		list2[i] = randInt(gen); // list2�� ������ ������ ����

	// 10�� ����
	auto start{ system_clock::now() }; // ���� �ð�
	maxHeapSort(list1); // ���� �ð��� ������ �Լ� ����
	auto end{ system_clock::now() }; // ���� �ð�
	// start, end�� �ʱ�ȭ �ð� ������ ���� ����ð����� �� �� ���� �ɸ�
	
	auto execTime{ duration_cast<microseconds>(end - start) }; // ���� �ð����� ������ �ð��� ���� ����� �ð� ���
	cout << "10�� �ִ� �� ����: " << execTime.count() << "��s" << endl;

	for (int i{ }; i < 10; ++i)
		cout << list1[i] << ' ';
	cout << '\n';
	checkSort1(list1);

	start = system_clock::now();
	minHeapSort(list1);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "\n10�� �ּ� �� ����: " << execTime.count() << "��s" << endl;
	
	for (int i{ }; i < 10; ++i)
		cout << list1[i] << ' ';
	cout << '\n';
	checkSort2(list1);

	// 10���� ����
	start = system_clock::now();
	maxHeapSort(list2);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "\n10���� �ִ� �� ����: " << execTime.count() << "��s" << endl;

	checkSort1(list2);

	start = system_clock::now();
	minHeapSort(list2);
	end = system_clock::now();

	execTime = duration_cast<microseconds>(end - start);
	cout << "\n10���� �ּ� �� ����: " << execTime.count() << "��s" << endl;

	checkSort2(list2);

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

// �ִ� �� ����
void maxHeapSort(int*& list) {
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // n�� ���� ũ��
	
	// max heap �̹Ƿ� list[n]�� ���Ҹ� ������������ ����
	for (int i{ n / 2 - 1 }; i >= 0; --i) {
		maxHeapify(list, n, i); // i�� ���� ���
	}

	// ������ �ִ밪�� ����
	for (int i{ n - 1 }; i > 0; --i) {
		swap(list[0], list[i]); 
		maxHeapify(list, i, 0);
	}
}

void maxHeapify(int*& list, int n, int i) {
	int p{ i }; // �θ� ��� �ε���
	int l{ i * 2 + 1 }; // ���� �ڽ� ��� �ε���
	int r{ i * 2 + 2 }; // ������ �ڽ� ��� �ε���

	// ���� ���� �ڽ� ��� �ε����� ���� ũ�⺸�� �۰�,
	// ����Ʈ�� �θ� ��� �ε��� ���� ����Ʈ�� ���� �ڽ� ��� �ε��� ������ �۴ٸ�,
	if (l < n && list[p] < list[l])
		p = l; // �θ� ��� �ε����� ���� �ڽ� ��� �ε����� �����Ѵ�. 

	// ���� ������ �ڽ� ��� �ε����� ���� ũ�⺸�� �۰�,
	// ����Ʈ�� �θ� ��� �ε����� ����Ʈ�� ������ �ڽ� ��� �ε������� �۴ٸ�,
	if (r < n && list[p] < list[r])
		p = r; // �θ� ��� �ε����� ������ �ڽ� ��� �ε����� �����Ѵ�.

	if (i != p) { // ���� ����� ���� i�� p�� ���� �޶����ٸ�,
		swap(list[i], list[p]); // ����Ʈ�� i �ε��� ���� ����Ʈ�� p �ε��� ���� ���� �ٲ��� ��,
		maxHeapify(list, n, p); // �ٽ� �� �� heapify�Լ��� �����Ѵ�.
	}
}

// �ּ� �� ����
void minHeapSort(int*& list) {
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // n�� ���� ũ��

	// min heap �̹Ƿ� list[n]�� ���Ҹ� ������������ ����
	for (int i{ n / 2 - 1 }; i >= 0; --i) {
		minHeapify(list, n, i); // i�� ���� ���
	}

	// ������ �ּҰ��� ����
	for (int i{ n - 1 }; i > 0; --i) {
		swap(list[0], list[i]);
		minHeapify(list, i, 0);
	}
}

void minHeapify(int*& list, int n, int i) {
	int p{ i }; // �θ� ��� �ε���
	int l{ i * 2 + 1 }; // ���� �ڽ� ��� �ε���
	int r{ i * 2 + 2 }; // ������ �ڽ� ��� �ε���

	// ���� ���� �ڽ� ��� �ε����� ���� ũ�⺸�� �۰�,
	// ����Ʈ�� �θ� ��� �ε��� ���� ����Ʈ�� ���� �ڽ� ��� �ε��� ������ ũ�ٸ�,
	if (l < n && list[p] > list[l])
		p = l; // �θ� ��� �ε����� ���� �ڽ� ��� �ε����� �����Ѵ�. 

	// ���� ������ �ڽ� ��� �ε����� ���� ũ�⺸�� �۰�,
	// ����Ʈ�� �θ� ��� �ε����� ����Ʈ�� ������ �ڽ� ��� �ε������� ũ�ٸ�,
	if (r < n && list[p] > list[r])
		p = r; // �θ� ��� �ε����� ������ �ڽ� ��� �ε����� �����Ѵ�.

	if (i != p) { // ���� ����� ���� i�� p�� ���� �޶����ٸ�,
		swap(list[i], list[p]); // ����Ʈ�� i �ε��� ���� ����Ʈ�� p �ε��� ���� ���� �ٲ��� ��,
		minHeapify(list, n, p); // �ٽ� �� �� heapify�Լ��� �����Ѵ�.
	}
}

// �������� üũ
void checkSort1(int*& list) {
	bool sorted{ true };
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // ����Ʈ�� ������ ������ n�� ����
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

// �������� üũ
void checkSort2(int*& list) {
	bool sorted{ true };
	int n{ static_cast<int>(_msize(list) / sizeof(int)) }; // ����Ʈ�� ������ ������ n�� ����
	for (int i{ n - 1 }; i > 0; --i) {
		if (list[i] < list[i + 1])
			sorted = false;
		if (!sorted)
			break;
	}
	if (sorted)
		cout << "Sorting complete!" << endl;
	else
		cout << "Error during sorting..." << endl;
}
