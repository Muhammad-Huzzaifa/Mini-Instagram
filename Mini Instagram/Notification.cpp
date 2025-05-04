#include "Notification.h"

Notification::Notification() {}

Notification::~Notification() {}

void Notification::sendNotification(const string& sender, const string& about, const time_t& now) {
	notifications.enqueue(NotificationNode({ sender, about, now }));
}

NotificationNode Notification::processNotification() {
	NotificationNode recent{ notifications.frontValue() };
	notifications.dequeue();
	return recent;
}

void Notification::clearAllNotifications() {
	notifications.makeNull();
}

Queue<NotificationNode> Notification::getNotifications() const {
	return notifications;
}

void Notification::viewNotifications() const {
	Queue<NotificationNode> temp{ notifications };
	NotificationNode tempNotification;

	cout << "<-------------------->\n";
	while (!temp.isEmpty()) {
		tempNotification = temp.frontValue();
		temp.dequeue();
		cout << tempNotification.about << " from " << tempNotification.sender << endl;
		tm* time{ localtime(&tempNotification.timestamp) };
		cout << "Timestamp: " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;
		cout << "<-------------------->\n";
	}
}