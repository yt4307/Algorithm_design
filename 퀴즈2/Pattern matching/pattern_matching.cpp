#include <iostream>
#include "deque.h"

using std::cout;
using std::endl;

using std::string;

constexpr auto scan{ -1 };
constexpr auto size{ 100 };

char ch[10]{ ' ', 'A', ' ', 'B', ' ', ' ', 'A', 'C', 'D', ' ' };
int next1[10]{ 5, 2, 3, 4, 8, 6, 7, 8, 9, 0 };
int next2[10]{ 5, 2, 1, 4, 8, 2, 7, 8, 9, 0 };


int match(string t) {
	int n1{ }, n2{ };
	int i{ }, j{ }, k{ }, N{ static_cast<int>(t.length()) }, state{ next1[0] };

	Deque dq{ };
	dq.deque = new int[size] { };
	dq.first = size / 2;
	dq.last = size / 2;

	for (i = 0; i < size; ++i)
		dq.deque[i] = 0;

	dq.insertLast(scan);

	cout << state << '[' << dq.deque[dq.first + 1] << ']' << endl;
	while (state) {
		cout << "state = " << state << endl;
		if (state == scan) {
			++j;
			if (dq.isEmpty())
				dq.insertFirst(next1[0]);
			dq.insertLast(scan);
		}
		else if (ch[state] == t[j]) {
			dq.insertLast(next1[state]);
		}
		else if (ch[state] == ' ') {
			n1 = next1[state];
			n2 = next2[state];
			dq.insertFirst(n1);

			if (n1 != n2)
				dq.insertFirst(n2);
		}
		for (k = dq.first + 1; k <= dq.last; ++k)
			cout << "[" << dq.deque[k] << "]";

		cout << endl;
		if (dq.isEmpty())
			return j;
		if (j > N)
			return 0;

		state = dq.deleteFirst();
	}
	delete[] dq.deque;
	return j - 1;
}

int main() {
	string text{ "CDAABCAAABDDACDAACAAAAAAABD" };
	int N{ static_cast<int>(text.length()) }, pos{ }, previous{ }, i{ };

	while (1) {
		pos = match(text.substr(i));

		if (pos == 0)
			break;

		pos += previous;
		i = pos;
		
		if (i <= N)
			cout << "패턴이 발생한 위치: " << pos << endl;
		else
			break;
		previous = i;
	}
	cout << "패턴 매칭 종료" << endl;
	return 0;
}
