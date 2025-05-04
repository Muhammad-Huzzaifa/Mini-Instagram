#pragma once
#include <string>
using namespace std;

struct Pair {
	string username;
	string password;
	Pair* next;
};

class HashTable {
public:
	HashTable();
	~HashTable();

	void insertPair(const string&, const string&);
	bool existUsername(const string&) const;
	string getPassword(const string&) const;

public:
	int size, indexesFilled;
	Pair** arr;

	int hashFunction(const string&) const;
	void resize();
};