#include "App.h"

App::App()
	: logedInUser{ nullptr } {
}

App::~App() {}

void App::run() {
	system("cls");
	bool exit{ false };

	while (!exit) {
		cout << "<---WELCOME TO MINI-INSTAGRAM--->\n";
		cout << "1. Sign up\n2. Login\n3. Exit\nEnter your choice: ";
		int choice;
		cin >> choice;

		cin.ignore();
		cout << "<-------------------->\n\n";

		if (choice == 1) {
			signup();
		}
		else if (choice == 2) {
			login();
		}
		else if (choice == 3) {
			cout << "Exiting...\n";
			cout << "<-------------------->\n";
			exit = true;
			break;
		}
		else {
			cout << "Invalid choice...\n";
			cout << "<-------------------->\n";
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("pause");
		system("cls");
	}
}

void App::signup() {
	UserNode user{ UserNode() };

	cout << "<-------------------->\n";
	cout << "Enter your name (Alphabets/Space): ";
	getline(cin, user.name);
	while (!isValidName(user.name) || users.find(user) != nullptr) {
		cout << "Invalid or already taken! Enter again (Alphabets/Space): ";
		getline(cin, user.name);
	}

	cout << "Enter your password (No Space/ No ,/At least 8): ";
	getline(cin, user.password);
	while (!isValidPassword(user.password)) {
		cout << "Invalid password! Enter again (No Space/ No ,/At least 8): ";
		getline(cin, user.password);
	}

	cout << "Enter your city (Alphabets/Space): ";
	getline(cin, user.city);
	while (!isValidName(user.city)) {
		cout << "Invalid city! Enter again (Alphabets/Space): ";
		getline(cin, user.city);
	}

	user.lastLoginTime = 0;

	users.insert(user);
	friends.addUser(user.name);
	loginHash.insertPair(user.name, user.password);

	cout << "<-------------------->\n";
	cout << "Account is created successfully.\n";
	cout << "<-------------------->\n";
}

void App::login() {
	string name, password;

	cout << "<-------------------->\n";
	cout << "Enter your name (Alphabets/Space): ";
	getline(cin, name);
	while (!isValidName(name)) {
		cout << "Invalid name! Enter again (Alphabets/Space): ";
		getline(cin, name);
	}

	cout << "Enter your password (No Space/ No ,/At least 8): ";
	getline(cin, password);
	while (!isValidPassword(password)) {
		cout << "Invalid password! Enter again (No Space/ No ,/At least 8): ";
		getline(cin, password);
	}
	cout << "<-------------------->\n";

	if (loginHash.getPassword(name) == password) {
		cout << "You are loged in successfully.\n";
		cout << "<-------------------->\n";

		UserNode tempUser{ UserNode() };
		tempUser.name = name;
		logedInUser = &users.find(tempUser)->data;

		time_t now{ time(nullptr) };
		logedInUser->lastLoginTime = now;

		User user(logedInUser, &users, &friends, &messages);

		system("pause");
		system("cls");

		bool logedOut{ false };
		while (!logedOut) {
			cout << "<---" << name << "--->\n";
			cout << " 1. Add post\n 2. Delete recent post\n 3. Delete all posts\n 4. Viw own posts\n 5. View friends posts\n 6. Search user\n 7. View friend sugesstions\n 8. Send friend request\n 9. Viw own friends\n10. Block friend\n11. Send message\n12. View conversation\n13. Delete recent message\n14. Delete all messages\n15. Show notifications\n16. Process notification\n17. Logout\nEnter your choice: ";
			int ichoice;
			cin >> ichoice;

			cin.ignore();
			cout << "<-------------------->\n\n";

			if (ichoice == 1) {
				string content;
				cout << "Enter the content of the post: ";
				getline(cin, content);
				user.addPost(content);
			}
			else if (ichoice == 2) {
				user.deleteRecentPost();
			}
			else if (ichoice == 3) {
				user.deleteAllPosts();
			}
			else if (ichoice == 4) {
				user.viewPosts();
			}
			else if (ichoice == 5) {
				user.viewFriendsPosts();
			}
			else if (ichoice == 6) {
				search();
			}
			else if (ichoice == 7) {
				user.viewFriendSugesstions();
			}
			else if (ichoice == 8) {
				string username;
				cout << "Enter username you want to send friend request: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.sendFriendRequest(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 9) {
				cout << name << "\'s friend list:\n";
				user.viewFriends();
			}
			else if (ichoice == 10) {
				string username;
				cout << "Enter frined\'s name you want to block: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.blockActiveFriend(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 11) {
				string username, content;
				cout << "Enter your frined\'s name: ";
				getline(cin, username);
				cout << "Enter your message: ";
				getline(cin, content);

				cout << "<-------------------->\n";
				user.sendMessage(username, content);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 12) {
				string username;
				cout << "Enter your friend\'s name whose conversation you want to see: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.viewCoversation(username);
			}
			else if (ichoice == 13) {
				string username;
				cout << "Enter your friend\'s name b/w which you want to delete recent message: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.deleteRecentMessage(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 14) {
				string username;
				cout << "Enter your friend\'s name b/w you want to delete conversation: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.deleteAllMessages(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 15) {
				user.viewNotifications();
			}
			else if (ichoice == 16) {
				processNotification(user);
			}
			else if (ichoice == 17) {
				cout << "Logging out...\n";
				cout << "<-------------------->\n";
				logedInUser = nullptr;
				logedOut = true;
				break;
			}
			else {
				cout << "Invalid choice...\n";
				cout << "<-------------------->\n";
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			system("pause");
			system("cls");
		}
	}
	else {
		cout << "Incorrect name or password...\n";
		cout << "<-------------------->\n";
	}
}

void App::search() {
	List<string> searchedUsers;

	string lowerCase(const string&);
	void searchUsers(TreeNode<UserNode>*, const string&, List<string>&);

	string tosearch;
	cout << "Enter your search: ";
	getline(cin, tosearch);
	cout << "<-------------------->\n\n";

	searchUsers(users.getRoot(), lowerCase(tosearch), searchedUsers);
	if (!searchedUsers.isEmpty()) {
		cout << "Users found in search:\n";
		cout << "<-------------------->\n";
		ListNode<string>* current{ searchedUsers.getHead() };
		while (current != nullptr) {
			if (current->data != logedInUser->name) {
				cout << "# " << current->data << endl;
				cout << "<-------------------->\n";
			}
			else {
				cout << "# You" << endl;
				cout << "<-------------------->\n";
			}
			current = current->next;
		}
	}
	else {
		cout << "No user found from your search.\n";
		cout << "<-------------------->\n";
	}
}

string lowerCase(const string& original) {
	string lower{ original };
	transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
	return lower;
}

void searchUsers(TreeNode<UserNode>* root, const string& lower, List<string>& searchedUsers) {
	if (root != nullptr) {
		searchUsers(root->right, lower, searchedUsers);

		if (lowerCase(root->data.name).find(lower) != string::npos) {
			searchedUsers.insert(root->data.name);
		}

		searchUsers(root->left, lower, searchedUsers);
	}
}

void App::processNotification(User& user) {
	NotificationNode earliest{ user.processNotification() };

	if (earliest.about == "Friend request") {
		tm* time{ localtime(&earliest.timestamp) };
		cout << "Friend request from " << earliest.sender << " at " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1. Accept friend request\n2. Reject friend request\n3. Remain unseen for later\nEnter your choice: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1) {
			cout << "<-------------------->\n";
			user.acceptFriendRequest(earliest.sender);
			cout << "<-------------------->\n";
		}
		else if (rchoice == 2) {
			cout << "<-------------------->\n";
			user.blockActiveFriend(earliest.sender);
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3) {
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
	else if (earliest.about == "Message") {
		tm* time{ localtime(&earliest.timestamp) };
		cout << "Message from " << earliest.sender << " at " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1. View conversation\n2. Mark as reed and go\n3. Remain unseen for later\nEnter your choice: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1) {
			cout << "<-------------------->\n";
			user.viewCoversation(earliest.sender);
		}
		else if (rchoice == 2) {
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3) {
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
	else if (earliest.about == "Post") {
		tm* time{ localtime(&earliest.timestamp) };
		cout << "Post from " << earliest.sender << " at " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1. See friends posts\n2. Mark as reed and go\n3. Remain unseen for later\nEnter your choice: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1) {
			cout << "<-------------------->\n";
			user.viewFriendsPosts();
		}
		else if (rchoice == 2) {
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3) {
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
}

bool App::isValidName(const std::string& name) {
	for (char ch : name) {
		if (!isalpha(ch) && !isspace(ch)) {
			return false;
		}
	}
	return !name.empty();
}

bool App::isValidPassword(const std::string& password) {
	if (password.length() < 8) {
		return false;
	}

	for (char ch : password) {
		if (isspace(ch) || ch == ',') {
			return false;
		}
	}
	return true;
}