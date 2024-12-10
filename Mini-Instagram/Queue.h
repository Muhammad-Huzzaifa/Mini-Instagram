#ifndef QUEUE
#define QUEUE

template <typename T>
struct QueueNode {
	T data;
	QueueNode<T>* next;
	QueueNode(const T&, QueueNode<T>*);
};

template <typename T>
class Queue {
public:
	Queue();
	Queue(const Queue<T>&);
	~Queue();

	Queue<T>& operator=(const Queue<T>&) const;

	QueueNode<T>* find(const T&) const;
	bool isEmpty() const;

	void enqueue(const T&);
	bool dequeue();

	T frontValue() const;

	void makeNull();

public:
	QueueNode<T>* front, * rear;
};

// #include "Queue.cpp"

template <typename T>
QueueNode<T>::QueueNode(const T& data, QueueNode<T>* next)
	: data{ data }, next{ next } {
}

template <typename T>
Queue<T>::Queue()
	: front{ nullptr }, rear{ nullptr } {
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
	front = nullptr;
	rear = nullptr;

	QueueNode<T>* current{ other.front };
	while (current != nullptr) {
		enqueue(current->data);
		current = current->next;
	}
}

template <typename T>
Queue<T>::~Queue() {
	makeNull();
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) const {
	if (this == &other) {
		return *this;
	}

	makeNull();

	QueueNode<T>* current = other.front;

	while (current != nullptr) {
		push(current->data);
		current = current->next;
	}

	return *this;
}

template <typename T>
QueueNode<T>* Queue<T>::find(const T& data) const {
	QueueNode<T>* current{ front };

	while (current != nullptr) {
		if (current->data == data) {
			return current;
		}
		current = current->next;
	}

	return current;
}

template <typename T>
bool Queue<T>::isEmpty() const {
	return front == nullptr;
}

template <typename T>
void Queue<T>::enqueue(const T& val) {
	if (isEmpty()) {
		front = rear = new QueueNode<T>(val, nullptr);
	}
	else {
		rear = rear->next = new QueueNode<T>(val, nullptr);
	}
}

template <typename T>
bool Queue<T>::dequeue() {
	if (isEmpty()) {
		return false;
	}

	QueueNode<T>* temp{ front };
	if (front == rear) {
		front = rear = nullptr;
	}
	else {
		front = front->next;
	}
	delete temp;
	temp = nullptr;
	return true;
}

template <typename T>
T Queue<T>::frontValue() const {
	return front->data;
}

template <typename T>
void Queue<T>::makeNull() {
	while (!isEmpty()) {
		dequeue();
	}
}

#endif