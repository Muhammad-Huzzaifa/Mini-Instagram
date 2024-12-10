#include "App.h"

App::App()
	: logedInUser{ nullptr } {
}

App::~App() {}

void App::run() {
	bool exit{ false };

	while (!exit) {
		cout << "<---WELCOME TO MINI-INSTAGRAM--->\n";
		cout << "1. Sign up\n2. Login\n3. Exit\nEnter your choice: ";
		int choice;
		cin >> choice;
		cin.ignore();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "<-------------------->\n\n";


		if (choice == 1) {
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
		else if (choice == 2) {
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
					cout << "1.  Add post\n2.  Delete recent post\n3.  Delete all posts\n4.  Viw own posts\n5.  View friends posts\n6.  Search user\n7.  Send friend request\n8.  Viw own friends\n9.  Block friend\n10. Send message\n11. View Conversation\n12. Delete recent message\n13. Delete all messages\n14. Show notifications\n15. Process recent notification\n16. Logout\nEnter your choice: ";
					int ichoice;
					cin >> ichoice;
					cin.ignore();
					//cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
					else if (ichoice == 7) {
						string username;
						cout << "Enter username you want to send friend request: ";
						getline(cin, username);

						cout << "<-------------------->\n";
						user.sendFriendRequest(username);
						cout << "<-------------------->\n";
					}
					else if (ichoice == 8) {
						cout << name << "\'s friend list:\n";
						user.viewFriends();
					}
					else if (ichoice == 9) {
						string username;
						cout << "Enter frined\'s name you want to block: ";
						getline(cin, username);

						cout << "<-------------------->\n";
						user.blockActiveFriend(username);
						cout << "<-------------------->\n";
					}
					else if (ichoice == 10) {
						string username, content;
						cout << "Enter your frined\'s name: ";
						getline(cin, username);
						cout << "Enter your message: ";
						getline(cin, content);

						cout << "<-------------------->\n";
						user.sendMessage(username, content);
						cout << "<-------------------->\n";
					}
					else if (ichoice == 11) {
						string username;
						cout << "Enter your friend\'s name whose conversation you want to see: ";
						getline(cin, username);

						cout << "<-------------------->\n";
						user.viewCoversation(username);
					}
					else if (ichoice == 12) {
						string username;
						cout << "Enter your friend\'s name b/w which you want to delete recent message: ";
						getline(cin, username);

						cout << "<-------------------->\n";
						user.deleteRecentMessage(username);
						cout << "<-------------------->\n";
					}
					else if (ichoice == 13) {
						string username;
						cout << "Enter your friend\'s name b/w you want to delete conversation: ";
						getline(cin, username);

						cout << "<-------------------->\n";
						user.deleteAllMessages(username);
						cout << "<-------------------->\n";
					}
					else if (ichoice == 14) {
						user.viewNotifications();
					}
					else if (ichoice == 15) {
						NotificationNode recent{ user.processRecentNotification() };

						if (recent.about == "Friend request") {
							tm time;
							localtime_s(&time, &recent.timestamp);
							cout << "Friend request from " << recent.sender << " at " << put_time(&time, "%Y-%m-%dT%H:%M:%S") << endl;

							cout << "1. Accept friend request\n2. Reject friend request\n3. Remain unseen for later\nEnter your choice: ";
							int rchoice;
							cin >> rchoice;
							cin.ignore();
							//cin.ignore(numeric_limits<streamsize>::max(), '\n');

							while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
								cin >> rchoice;
								cin.ignore();
								//cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}

							if (rchoice == 1) {
								cout << "<-------------------->\n";
								user.acceptFriendRequest(recent.sender);
								cout << "<-------------------->\n";
							}
							else if (rchoice == 2) {
								cout << "<-------------------->\n";
								user.blockActiveFriend(recent.sender);
								cout << "<-------------------->\n";
							}
							else if (rchoice == 3) {
								// user.sendNotification(recent.sender, recent.about, recent.timestamp);
								cout << "<-------------------->\n";
							}
						}
						else if (recent.about == "Message") {
							tm time;
							localtime_s(&time, &recent.timestamp);
							cout << "Message from " << recent.sender << " at " << put_time(&time, "%Y-%m-%dT%H:%M:%S") << endl;

							cout << "1. View conversation\n2. Mark as reed and go\n3. Remain unseen for later\nEnter your choice: ";
							int rchoice;
							cin >> rchoice;
							cin.ignore();
							//cin.ignore(numeric_limits<streamsize>::max(), '\n');

							while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
								cin >> rchoice;
								cin.ignore();
								//cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}

							if (rchoice == 1) {
								cout << "<-------------------->\n";
								user.viewCoversation(recent.sender);
							}
							else if (rchoice == 2) {
								cout << "<-------------------->\n";
							}
							else if (rchoice == 3) {
								// user.sendNotification(recent.sender, recent.about, recent.timestamp);
								cout << "<-------------------->\n";
							}
						}
						else if (recent.about == "Post") {
							tm time;
							localtime_s(&time, &recent.timestamp);
							cout << "Post from " << recent.sender << " at " << put_time(&time, "%Y-%m-%dT%H:%M:%S") << endl;

							cout << "1. See friends posts\n2. Mark as reed and go\n3. Remain unseen for later\nEnter your choice: ";
							int rchoice;
							cin >> rchoice;
							cin.ignore();
							//cin.ignore(numeric_limits<streamsize>::max(), '\n');

							while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
								cin >> rchoice;
								cin.ignore();
								//cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}

							if (rchoice == 1) {
								cout << "<-------------------->\n";
								user.viewFriendsPosts();
							}
							else if (rchoice == 2) {
								cout << "<-------------------->\n";
							}
							else if (rchoice == 3) {
								// user.sendNotification(recent.sender, recent.about, recent.timestamp);
								cout << "<-------------------->\n";
							}
						}
					}
					else if (ichoice == 16) {
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

					system("pause");
					system("cls");
				}
			}
			else {
				cout << "Incorrect name or password...\n";
				cout << "<-------------------->\n";
			}
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

		system("pause");
		system("cls");
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