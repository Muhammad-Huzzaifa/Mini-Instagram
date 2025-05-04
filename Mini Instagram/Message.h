#pragma once
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Stack.h"
using namespace std;

struct MessageNode {
	string sender;
	string content;
	time_t timestamp;
};

class Message {
public:
	Message(const string&, const string&);
	~Message();

	void sendMessage(const string&, const string&, const time_t&);
	void deleteRecentMessage();
	void deleteAllMessages();

	pair<string, string> getUsers() const;
	Stack<MessageNode> getMessages() const;
	void viewMessages() const;

	bool operator==(const Message&);

public:
	string user1;
	string user2;
	Stack<MessageNode> messages;
};