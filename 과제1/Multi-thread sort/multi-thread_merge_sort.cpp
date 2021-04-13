// 8���� ���μ����� ������ CPU�� �������� �ۼ��Ǿ����ϴ�.
// �ڸ��� ���뿡 ���ؼ��� �ּ��� ���� �ʾҽ��ϴ�.
// ��� �ĺ����� �̸������ε� ����� �а��� �����ϵ��� �����Ͽ����ϴ�.

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <thread>
#include <windows.h> // �ھ��� ������ ���� �ý��� ������ �������� ���� ����

using std::cout;
using std::endl;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::microseconds;

using std::vector;

using std::thread;

void Merge(int, int, int);
void MergeSort(int, int);
void MultithreadMergeSort(int);
void CheckSort(const int*&);

// ���� ���� ����
random_device rd{ };
mt19937 gen{ rd() };

// ����Ʈ �� �׿� ���õ� ���� ����
// ����Ʈ�� ����� ������ ��, �ݵ�� ���μ��� ������ ����� �����ؾ� �Ѵ�.
// �� �����尡 �����޴� ũ�Ⱑ �����ؾ� �Ǳ� ����.
constexpr int listSize{ 100'000'000 };
int* list{ new int[listSize] {} };
int border{ }; // ����Ʈ ���� ��輱


int main() {
	SYSTEM_INFO info{ }; // �ý��� ������ ������ ��ü ����
	GetSystemInfo(&info); // �ý��� ������ ������ info ������ �־��ش�.
	int numCore{ static_cast<int>(info.dwNumberOfProcessors) }; // �ý��� �������� (��)���μ����� ������ �����´�.

	uniform_int_distribution<int> randInt{ 0, listSize }; // 0 ~ listSize���� �յ� ���� ����
	for (int i{ }; i < listSize; ++i) // 0���� listSize - 1���� �ݺ��ϸ�,
		list[i] = randInt(gen); // list�� ������ ������ ����

	// �� ������ ���� ����
	vector<thread> threads{ };

	// ���� �ð� ���� ����
	auto start{ system_clock::now() };

	// ���μ����� ������ŭ�� ������ ��ü ����
	for (int i = 0; i < numCore; ++i)
		// ������ ���Ϳ� numCore�� �Ű������� �ϴ� MultithreadMergeSort �Լ��� ������ ��ü�� �����Ͽ� �־��ش�.
		threads.emplace_back(MultithreadMergeSort, numCore);

	// ��� ������ join(������ �Ϸ� �� ������ ���)
	for (auto& th : threads)
		th.join();

	// ���� �� 8���� ������ �ϳ��� ��ġ�� ����
	// �� �κе� ������ ��Ƽ ������� �ذ��ؾ� �ϳ�, ���� ������ ������ ���̽� ������ �ذ����� ���� ������ ��������.
	Merge(0, listSize / 8 - 1, listSize / 4 - 1); // 0 ~ 1/4 ���� ����
	Merge(listSize / 4, 3 * listSize / 8 - 1, listSize / 2 - 1); // 1/4 ~ 2/4(1/2) ���� ����
	Merge(listSize / 2, 5 * listSize / 8 - 1, 3 * listSize / 4 - 1); // 2/4 ~ 3/4 ���� ����
	Merge(3 * listSize / 4, 7 * listSize / 8 - 1, listSize - 1); // 3/4 ~ 1 ���� ����
	Merge(0, listSize / 4 - 1, listSize / 2 - 1); // 0 ~ 1/2 ���� ����
	Merge(listSize / 2, 3 * listSize / 4 - 1, listSize - 1); // 1/2 ~ 1 ���� ����
	Merge(0, listSize / 2 - 1, listSize - 1); // 0 ~ 1 ���� ����

	// ���� �ð� ���� ����
	auto end{ system_clock::now() };

	// Ȥ�� �� ���۵��� �����ϱ� ���� ������ ���͸� ����ش�.
	threads.clear();

	// ���� �ð����� ������ �ð��� ���� �� ���� �ð� ���
	auto execTime{ duration_cast<microseconds>(end - start) };

	cout << listSize << "���� �����͸� Multi-thread�� �����\nMerge sort�� "
		<< numCore << "�������� ������ ������ �ð�: " << execTime.count() << "��s" << endl;

	// ���� ��� ���
	CheckSort(const_cast<const int*&>((&list)[0]));

	cout << "\n������Ű��а� 12171850 ������" << endl;

	delete[] list;
	return 0;
}

// ���� �� �κй迭�� �պ��ϴ� �Լ�
void Merge(int low, int mid, int high) {
	// ������ ���� �ӽ� �迭 �ΰ� ����
	int* left{ new int[mid - low + 1] {} };
	int* right{ new int[high - mid] {} };

	// lsize�� ���� �κ��� ũ��, rsize�� ������ �κ��� ũ��
	int lsize{ mid - low + 1 }, rsize{ high - mid };

	// ���� �ӽ� �迭�� ���� �κ� �� ����
	for (int i{ }; i < lsize; i++)
		left[i] = list[i + low];

	// ������ �ӽ� �迭�� ������ �κ� �� ����
	for (int i{ }; i < rsize; i++)
		right[i] = list[i + mid + 1];

	// �ݺ��� ����
	// ��, k�� list�� �ε��� ���̹Ƿ�, low���� ����
	int i{}, j{}, k{ low };

	// ������������ ���ʰ� �������� ����
	while (i < lsize && j < rsize) {
		if (left[i] <= right[j])
			list[k++] = left[i++];
		else
			list[k++] = right[j++];
	}

	// ���ʿ� �����ִ� ���� ����Ʈ�� ����
	while (i < lsize)
		list[k++] = left[i++];

	// �����ʿ� �����ִ� ���� ����Ʈ�� ����
	while (j < rsize)
		list[k++] = right[j++];

	// �� ���� �ӽ� �迭 ����
	// �޸𸮸� ���� ���������� ������ 2õ������ ������ ���ϰ� ���α׷��� ������.
	delete[] left;
	delete[] right;
}

// ���ڸ� �պ� ����
void MergeSort(int low, int high) {
	// �⺻ ����
	if (low >= high)
		return;

	// ������ ���� ����Ʈ�� �߰� ���� ����
	int mid{ low + ((high - low) / 2) };

	// ���� ���� ����
	MergeSort(low, mid);

	// ���� ���� ����
	MergeSort(mid + 1, high);

	// ������ų �� ������ ����
	Merge(low, mid, high);
}

// ��Ƽ ������ ������ ���� �Լ�
void MultithreadMergeSort(int numCore) {
	// �� �����帶�� ��Ʈ�� �����ֱ� ���� ���� ����
	// border�� �� ó���� 0���� �����ϸ�, MultithreadMergeSort �Լ��� ������ ������� ��Ʈ�� ��������.
	int threadPart{ border++ };

	// ������ �����庰�� low�� high�� ��������
	int low{ threadPart * (listSize / numCore) };
	int high{ (threadPart + 1) * (listSize / numCore) - 1 };

	// �׷��� ������ low ~ high ������ MergeSort�� �־���
	MergeSort(low, high);
}

void CheckSort(const int*& list) {
	bool sorted{ true };
	int n{ listSize }; // ����Ʈ�� ������ ������ n�� ����
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
