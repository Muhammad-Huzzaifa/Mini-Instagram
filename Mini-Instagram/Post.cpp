#include "Post.h"

bool PostNode::operator==(const PostNode& other) const {
	return timestamp == other.timestamp;
}

bool PostNode::operator<(const PostNode& other) const {
	return timestamp < other.timestamp;
}

bool PostNode::operator>(const PostNode& other) const {
	return timestamp > other.timestamp;
}

Post::Post() {}

Post::~Post() {}

void Post::addPost(const string& content, const time_t& now) {
	posts.push(PostNode({ content, now }));
}

void Post::deleteRecentPost() {
	posts.pop();
}

void Post::deleteAllPosts() {
	posts.makeNull();
}

Stack<PostNode> Post::getPosts() const {
	return posts;
}

void Post::viewPosts() const {
	Stack<PostNode> temp{ posts };
	PostNode tempPost;

	cout << "<-------------------->\n";
	while (!temp.isEmpty()) {
		tempPost = temp.topValue();
		temp.pop();
		cout << "Content: " << tempPost.content << endl;
		tm time;
		localtime_s(&time, &tempPost.timestamp);
		cout << "Timestamp: " << put_time(&time, "%Y-%m-%dT%H:%M:%S") << endl;
		cout << "<-------------------->\n";
	}
}