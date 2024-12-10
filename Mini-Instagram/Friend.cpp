#include "Friend.h"

Friend::Friend() {}

Friend::~Friend() {}

bool Friend::haveActiveRelation(const string& user1, const string& user2) {
	ListNode<GraphNode<string>>* user1Node{ friends.findNode(user1) };
	ListNode<Edge<string>>* user1RelationUser2{ friends.findEdge(user1, user2) };

	if (user1Node == nullptr || user1RelationUser2 == nullptr || user1RelationUser2->data.weight != "active") {
		return false;
	}

	return true;
}

bool Friend::havePendingRelation(const string& user1, const string& user2) {
	ListNode<GraphNode<string>>* user1Node{ friends.findNode(user1) };
	ListNode<Edge<string>>* user1RelationUser2{ friends.findEdge(user1, user2) };

	if (user1Node == nullptr || user1RelationUser2 == nullptr || user1RelationUser2->data.weight != "pending") {
		return false;
	}

	return true;
}

bool Friend::haveNoRelation(const string& user1, const string& user2) {
	ListNode<GraphNode<string>>* user1Node{ friends.findNode(user1) };
	ListNode<Edge<string>>* user1RelationUser2{ friends.findEdge(user1, user2) };

	if (user1Node == nullptr || user1RelationUser2 == nullptr) {
		return true;
	}

	return false;
}

void Friend::addUser(const string& name) {
	friends.addNode(name);
}

void Friend::removeUser(const string& user) {
	friends.removeNode(user);
}

void Friend::sendFriendRequest(const string& from, const string& to) {
	friends.addEdge(from, to, "pending");
}

void Friend::acceptFriendRequest(const string& from, const string& to) {
	friends.changeEdgeWeight(from, to, "active");
}

void Friend::blockActiveFriend(const string& from, const string& to) {
	friends.removeEdge(from, to);
}

Graph<string> Friend::getFriends() const {
	return friends;
}

List<Edge<string>> Friend::getFriendList(const string& name) {
	return friends.findNode(name)->data.adjacencyList;
}

void Friend::viewFriends(const string& user) {
	ListNode<Edge<string>>* current{ friends.findNode(user)->data.adjacencyList.getHead() };

	if (current != nullptr) {
		cout << "<-------------------->\n";
		while (current != nullptr) {
			cout << "Name: " << current->data.data << ", Status: " << current->data.weight << endl;
			cout << "<-------------------->\n";
			current = current->next;
		}
	}
	else {
		cout << "<-------------------->\n";
		cout << user << " have no any friend.\n";
		cout << "<-------------------->\n";
	}
}