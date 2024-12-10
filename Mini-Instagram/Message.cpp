#include "Message.h"

Message::Message(const string& user1, const string& user2)
	: user1{ user1 }, user2{ user2 } {
}

Message::~Message() {}

void Message::sendMessage(const string& sender, const string& content, const time_t& now) {
	messages.push(MessageNode{ sender, content, now });
}

void Message::deleteRecentMessage() {
	messages.pop();
}

void Message::deleteAllMessages() {
	messages.makeNull();
}

pair<string, string> Message::getUsers() const {
	return { user1, user2 };
}

Stack<MessageNode> Message::getMessages() const {
	return messages;
}

void Message::viewMessages() const {
	Stack<MessageNode> temp{ messages };
	MessageNode tempMessage;

	if (!temp.isEmpty()) {
		cout << "<-------------------->\n";
		while (!temp.isEmpty()) {
			tempMessage = temp.topValue();
			temp.pop();
			cout << tempMessage.sender << ": " << tempMessage.content << endl;
			tm time;
			localtime_s(&time, &tempMessage.timestamp);
			cout << "Timestamp: " << put_time(&time, "%Y-%m-%dT%H:%M:%S") << endl;
			cout << "<-------------------->\n";
		}
	}
	else {
		cout << "<-------------------->\n";
		cout << "There is no any message between " << user1 << " and " << user2 << endl;
		cout << "<-------------------->\n";
	}
}

bool Message::operator==(const Message& other) {
	return ((user1 == other.user1 && user2 == other.user2) || (user1 == other.user2 && user2 == other.user1));
}