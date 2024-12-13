#pragma once

template <typename T>
struct StackNode {
	T data;
	StackNode<T>* bottom;
	StackNode(const T&, StackNode<T>*);
};

template <typename T>
class Stack {
public:
	Stack();
	Stack(const Stack<T>&);
	~Stack();

	Stack<T>& operator=(const Stack<T>&);

	StackNode<T>* find(const T&) const;
	bool isEmpty() const;

	void push(const T&);
	bool pop();

	T topValue() const;

	void makeNull();

public:
	StackNode<T>* top;
};

template <typename T>
StackNode<T>::StackNode(const T& data, StackNode<T>* bottom)
	: data{ data }, bottom{ bottom } {
}

template <typename T>
Stack<T>::Stack()
	: top{ nullptr } {
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
	top = nullptr;

	Stack<T> temp;
	StackNode<T>* current{ other.top };
	while (current != nullptr) {
		temp.push(current->data);
		current = current->bottom;
	}

	while (!temp.isEmpty()) {
		push(temp.topValue());
		temp.pop();
	}
}

template <typename T>
Stack<T>::~Stack() {
	makeNull();
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	if (this == &other) {
		return *this;
	}

	makeNull();

	StackNode<T>* current = other.top;
	Stack<T> temp;

	while (current != nullptr) {
		temp.push(current->data);
		current = current->bottom;
	}

	while (!temp.isEmpty()) {
		push(temp.topValue());
		temp.pop();
	}

	return *this;
}

template <typename T>
StackNode<T>* Stack<T>::find(const T& data) const {
	StackNode<T>* current{ top };

	while (current != nullptr) {
		if (current->data == data) {
			return current;
		}
		current = current->bottom;
	}

	return current;
}

template <typename T>
bool Stack<T>::isEmpty() const {
	return top == nullptr;
}

template <typename T>
void Stack<T>::push(const T& data) {
	top = new StackNode<T>(data, top);
}

template <typename T>
bool Stack<T>::pop() {
	if (isEmpty()) {
		return false;
	}

	StackNode<T>* temp{ top };
	top = top->bottom;
	delete temp;
	temp = nullptr;
	return true;
}

template <typename T>
T Stack<T>::topValue() const {
	return top->data;
}

template <typename T>
void Stack<T>::makeNull() {
	while (!isEmpty()) {
		pop();
	}
}