#pragma once
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Queue.h"
using namespace std;

struct NotificationNode {
	string sender;
	string about;
	time_t timestamp;
};

class Notification {
public:
	Notification();
	~Notification();

	void sendNotification(const string&, const string&, const time_t&);
	NotificationNode processRecentNotification();
	void clearAllNotifications();

	Queue<NotificationNode> getNotifications() const;
	void viewNotifications() const;

public:
	Queue<NotificationNode> notifications;
};