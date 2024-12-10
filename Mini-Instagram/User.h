#pragma once
#include "Post.h"
#include "Notification.h"
#include "Friend.h"
#include "Message.h"
#include "Tree.h"

struct UserNode {
	string name;
	string password;
	string city;
	time_t lastLoginTime;
	Post posts;
	Notification notifications;

	bool operator==(const UserNode&) const;
	bool operator<(const UserNode&) const;
	bool operator>(const UserNode&) const;
};

class User {
public:
	User(UserNode*, Tree<UserNode>*, Friend*, List<Message>*);
	~User();

	void sendFriendRequest(const string&);
	void acceptFriendRequest(const string&);
	void blockActiveFriend(const string&);
	void viewFriends();

	void addPost(const string&);
	void deleteRecentPost();
	void deleteAllPosts();
	void viewPosts() const;
	void viewFriendsPosts() const;

	void sendMessage(const string&, const string&);
	void deleteRecentMessage(const string&);
	void deleteAllMessages(const string&);
	void viewCoversation(const string&);

	void sendNotification(const string&, const string&, const time_t& = time(nullptr));
	NotificationNode processRecentNotification();
	void clearAllNotifications();
	void viewNotifications() const;

public:
	UserNode* user;
	Tree<UserNode>* users;
	Friend* friends;
	List<Message>* messages;
};