#pragma once
#include <limits>
#include <cctype>
#include <fstream>
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
	void traverseForSaving(ofstream& ufile, ofstream& pfile, ofstream& nfile, TreeNode<UserNode>* root);
	void loadUsers();
	void saveUsers();

	void loadFriends();
	void saveFriends();

	void loadMessages();
	void saveMessages();

public:	
	UserNode* logedInUser;
	Tree<UserNode> users;
	Friend friends;
	List<Message> messages;
	HashTable loginHash;

	bool isValidName(const string&);
	bool isValidPassword(const string&);
};