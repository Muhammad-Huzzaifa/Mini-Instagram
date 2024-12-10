#pragma once
#include <limits>
#include <cctype>
#include "User.h"
#include "HashTable.h"
using namespace std;

class App {
public:
	App();
	~App();

	void run();

	void signup();
	void login();
	void search();

	void processNotification(User&);

public:
	UserNode* logedInUser;
	Tree<UserNode> users;
	Friend friends;
	List<Message> messages;
	HashTable loginHash;

	bool isValidName(const string&);
	bool isValidPassword(const string&);
};