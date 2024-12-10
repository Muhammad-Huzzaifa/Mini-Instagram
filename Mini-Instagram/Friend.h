#pragma once
#include <iostream>
#include "Graph.h"
using namespace std;

class Friend {
public:
	Friend();
	~Friend();

	bool haveActiveRelation(const string&, const string&);
	bool havePendingRelation(const string&, const string&);
	bool haveNoRelation(const string&, const string&);

	void addUser(const string&);
	void removeUser(const string&);

	void sendFriendRequest(const string&, const string&);
	void acceptFriendRequest(const string&, const string&);
	void blockActiveFriend(const string&, const string&);

	Graph<string> getFriends() const;
	List<Edge<string>> getFriendList(const string&);
	void viewFriends(const string&);

public:
	Graph<string> friends;
};