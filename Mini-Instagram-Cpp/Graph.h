#pragma once
#include <string>
#include "List.h"
using namespace std;

template <typename T>
struct Edge {
	T data;
	string weight;
	Edge(const T&, const string&);

	bool operator==(const Edge<T>&) const;
};

template <typename T>
struct GraphNode {
	T data;
	List<Edge<T>> adjacencyList;
	GraphNode(const T&);

	bool operator==(const GraphNode<T>&) const;
};

template <typename T>
class Graph {
public:
	Graph();
	Graph(const Graph<T>&);
	~Graph();

	Graph<T>& operator=(const Graph<T>&);

	ListNode<GraphNode<T>>* firstNode();
	ListNode<GraphNode<T>>* findNode(const T&);
	ListNode<Edge<T>>* findEdge(const T&, const T&);

	bool addNode(const T&);
	bool removeNode(const T&);

	bool addEdge(const T&, const T&, const string&);
	bool changeEdgeWeight(const T&, const T&, const string&);
	bool removeEdge(const T&, const T&);

	void makeNull();

public:
	List<GraphNode<T>> nodes;
};

template <typename T>
Edge<T>::Edge(const T& data, const string& weight)
	: data{ data }, weight{ weight } {
}

template <typename T>
bool Edge<T>::operator==(const Edge<T>& other) const {
	return data == other.data;
}

template <typename T>
GraphNode<T>::GraphNode(const T& data)
	: data{ data } {
}

template <typename T>
bool GraphNode<T>::operator==(const GraphNode<T>& other) const {
	return data == other.data;
}

template <typename T>
Graph<T>::Graph() {}

template <typename T>
Graph<T>::Graph(const Graph<T>& other) {
	ListNode<GraphNode<T>>* current = other.nodes.getHead();
	while (current != nullptr) {
		addNode(current->data.data);
		current = current->next;
	}

	current = other.nodes.getHead();
	while (current != nullptr) {
		ListNode<Edge<T>>* edgeCurrent{ current->data.adjacencyList.getHead() };
		while (edgeCurrent != nullptr) {
			addEdge(current->data.data, edgeCurrent->data.data, edgeCurrent->data.weight);
			edgeCurrent = edgeCurrent->next;
		}
		current = current->next;
	}
}

template <typename T>
Graph<T>::~Graph() {}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& other) {
	if (this != &other) {
		nodes.makeNull();

		ListNode<GraphNode<T>>* current = other.nodes.getHead();
		while (current != nullptr) {
			addNode(current->data.data);
			current = current->next;
		}

		current = other.nodes.getHead();
		while (current != nullptr) {
			ListNode<Edge<T>>* edgeCurrent{ current->data.adjacencyList.getHead() };
			while (edgeCurrent != nullptr) {
				addEdge(current->data.data, edgeCurrent->data.data, edgeCurrent->data.weight);
				edgeCurrent = edgeCurrent->next;
			}
			current = current->next;
		}
	}
	return *this;
}

template <typename T>
ListNode<GraphNode<T>>* Graph<T>::firstNode() {
	return nodes.getHead();
}

template <typename T>
ListNode<GraphNode<T>>* Graph<T>::findNode(const T& data) {
	return nodes.find(GraphNode<T>(data));
}

template <typename T>
ListNode<Edge<T>>* Graph<T>::findEdge(const T& node, const T& edge) {
	return nodes.find(GraphNode<T>(node))->data.adjacencyList.find(Edge<T>(edge, ""));
}

template <typename T>
bool Graph<T>::addNode(const T& vertex) {
	if (nodes.find(GraphNode<T>(vertex)) != nullptr) {
		return false;
	}

	nodes.insert(GraphNode<T>(vertex));
	return true;
}

template <typename T>
bool Graph<T>::removeNode(const T& vertex) {
	ListNode<GraphNode<T>>* node{ nodes.find(GraphNode<T>(vertex)) };

	if (node == nullptr) {
		return false;
	}

	ListNode<GraphNode<T>>* current{ nodes.getHead() };
	while (current != nullptr) {
		current->data.adjacencyList.remove(Edge<T>(vertex, ""));
		current = current->next;
	}

	nodes.remove(GraphNode<T>(vertex));
	return true;
}

template <typename T>
bool Graph<T>::addEdge(const T& from, const T& to, const string& weight) {
	ListNode<GraphNode<T>>* fromNode{ nodes.find(GraphNode<T>(from)) };
	ListNode<GraphNode<T>>* toNode{ nodes.find(GraphNode<T>(to)) };

	if (fromNode != nullptr && toNode != nullptr && fromNode != toNode) {
		if (fromNode->data.adjacencyList.find(Edge<T>(to, weight)) == nullptr && toNode->data.adjacencyList.find(Edge<T>(from, weight)) == nullptr) {
			fromNode->data.adjacencyList.insert(Edge<T>(to, weight));
			toNode->data.adjacencyList.insert(Edge<T>(from, weight));
			return true;
		}
	}

	return false;
}

template <typename T>
bool Graph<T>::changeEdgeWeight(const T& from, const T& to, const string& weight) {
	ListNode<GraphNode<T>>* fromNode{ nodes.find(GraphNode<T>(from)) };
	ListNode<GraphNode<T>>* toNode{ nodes.find(GraphNode<T>(to)) };

	if (fromNode != nullptr && toNode != nullptr && fromNode != toNode) {
		ListNode<Edge<T>>* edgeNode{ fromNode->data.adjacencyList.find(Edge<T>(to, "")) };

		if (edgeNode != nullptr) {
			edgeNode->data.weight = weight;

			ListNode<Edge<T>>* reverseEdgeNode{ toNode->data.adjacencyList.find(Edge<T>(from, "")) };
			if (reverseEdgeNode != nullptr) {
				reverseEdgeNode->data.weight = weight;
			}

			return true;
		}
	}

	return false;
}

template <typename T>
bool Graph<T>::removeEdge(const T& from, const T& to) {
	ListNode<GraphNode<T>>* fromNode{ nodes.find(GraphNode<T>(from)) };
	ListNode<GraphNode<T>>* toNode{ nodes.find(GraphNode<T>(to)) };

	if (fromNode != nullptr && toNode != nullptr && fromNode != toNode) {
		fromNode->data.adjacencyList.remove(Edge<T>(to, ""));
		toNode->data.adjacencyList.remove(Edge<T>(from, ""));
		return true;
	}

	return false;
}

template <typename T>
void Graph<T>::makeNull() {
	ListNode<GraphNode<T>>* current{ nodes.getHead() };
	while (current != nullptr) {
		current->data.adjacencyList.makeNull();
		current = current->next;
	}
	nodes.makeNull();
}