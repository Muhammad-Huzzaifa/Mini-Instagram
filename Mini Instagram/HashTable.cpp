#include "HashTable.h"

HashTable::HashTable()
	: size{ 50 }, indexesFilled{ 0 } {
	
	arr = new Pair * [size];
	for (int i{ 0 }; i < size; ++i) {
		arr[i] = nullptr;
	}
}

HashTable::~HashTable() {
	for (int i{ 0 }; i < size; ++i) {

		Pair* current{ arr[i] };
		while (current != nullptr) {

			Pair* temp{ current };
			current = current->next;
			delete temp;
			temp = nullptr;
		}
	}

	delete[] arr;
}

void HashTable::insertPair(const string& username, const string& password) {
	int index{ hashFunction(username) };

	if (arr[index] == nullptr) {
		indexesFilled++;
	}
	
	Pair* current{ arr[index] };
	while (current != nullptr) {

		if (current->username == username) {
			return;
		}

		current = current->next;
	}

	Pair* newPair{ new Pair({username, password, arr[index]}) };
	arr[index] = newPair;

	if (indexesFilled > (size * 0.8)) {
		resize();
	}
}

bool HashTable::existUsername(const string& username) const {
	int index{ hashFunction(username) };

	Pair* current{ arr[index] };
	while (current != nullptr) {

		if (current->username == username) {
			return true;
		}

		current = current->next;
	}

	return false;
}

string HashTable::getPassword(const string& username) const {
	int index{ hashFunction(username) };

	Pair* current{ arr[index] };
	while (current != nullptr) {

		if (current->username == username) {
			return current->password;
		}

		current = current->next;
	}

	return "";
}

int HashTable::hashFunction(const string& username) const {
	int hash{ 0 };
	for (const char ch : username) {
		hash += ch;
	}
	return hash % size;
}

void HashTable::resize() {
	int tempSize{ size };
	size *= 2;

	Pair** newArr{ new Pair * [size] };
	for (int i{ 0 }; i < size; ++i) {
		newArr[i] = nullptr;
	}

	for (int i{ 0 }; i < tempSize; ++i) {

		Pair* current{ arr[i] };
		while (current != nullptr) {

			Pair* next{ current->next };
			int index{ hashFunction(current->username) };
			current->next = newArr[index];
			newArr[index] = current;
			current = next;
		}
	}

	delete[] arr;
	arr = newArr;
}