#include "deque.h"

void Deque::insertFirst(int v) {
	deque[first--] = v;
}

void Deque::insertLast(int v) {
	deque[++last] = v;
}

int Deque::deleteFirst() {
	deque[first] = 0;
	return
		deque[++first];
}

int Deque::isEmpty() {
	if (first == last)
		return true;
	else
		return false;
}
