#pragma once

template <typename T>
struct ListNode {
	T data;
	ListNode<T>* next;
	ListNode(const T&, ListNode<T>*);
};

template <typename T>
class List {
public:
	List();
	List(const List<T>&);
	~List();

	List<T>& operator=(const List<T>&);

	ListNode<T>* getHead() const;

	ListNode<T>* find(const T&) const;
	bool isEmpty() const;

	void insert(const T& data);
	bool remove(const T& data);

	void makeNull();

public:
	ListNode<T>* head;
};

template <typename T>
ListNode<T>::ListNode(const T& data, ListNode<T>* next)
	: data{ data }, next{ next } {
}

template <typename T>
List<T>::List()
	: head{ nullptr } {
}

template <typename T>
List<T>::List(const List<T>& other) {
	head = nullptr;

	ListNode<T>* current{ other.head };
	while (current != nullptr) {
		insert(current->data);
		current = current->next;
	}
}

template <typename T>
List<T>::~List() {
	makeNull();
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (this == &other) {
		return *this;
	}

	makeNull();

	ListNode<T>* current = other.head;

	while (current != nullptr) {
		insert(current->data);
		current = current->next;
	}

	return *this;
}

template <typename T>
ListNode<T>* List<T>::getHead() const {
	return head;
}

template <typename T>
ListNode<T>* List<T>::find(const T& data) const {
	ListNode<T>* current{ head };
	while (current != nullptr) {
		if (current->data == data) {
			return current;
		}
		current = current->next;
	}
	return current;
}

template <typename T>
bool List<T>::isEmpty() const {
	return head == nullptr;
}

template <typename T>
void List<T>::insert(const T& data) {
	head = new ListNode<T>(data, head);
}

template <typename T>
bool List<T>::remove(const T& data) {
	if (head == nullptr) {
		return false;
	}

	if (head->data == data) {
		ListNode<T>* temp{ head };
		head = head->next;
		delete temp;
		temp = nullptr;
		return true;
	}

	ListNode<T>* current{ head };
	ListNode<T>* previous{ nullptr };

	while (current != nullptr) {
		if (current->data == data) {
			if (previous == nullptr) {
				head = current->next;
			}
			else {
				previous->next = current->next;
			}
			delete current;
			current = nullptr;
			return true;
		}
		previous = current;
		current = current->next;
	}

	return false;
}

template <typename T>
void List<T>::makeNull() {
	while (head != nullptr) {
		ListNode<T>* temp{ head };
		head = head->next;
		delete temp;
		temp = nullptr;
	}
}