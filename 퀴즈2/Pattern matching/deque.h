#pragma once

struct Deque {
public:
	Deque() : deque{ }, first{ }, last{ } { }
	void insertFirst(int v);
	void insertLast(int v);
	int deleteFirst();
	int isEmpty();

	int* deque;
	int first, last;
};
