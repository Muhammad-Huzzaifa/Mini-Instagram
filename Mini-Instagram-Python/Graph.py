from List import List


class Edge:
    def __init__(self, data, weight):
        self.data = data
        self.weight = weight

    def __eq__(self, other):
        return self.data == other.data


class GraphNode:
    def __init__(self, data):
        self.data = data
        self.adjacencyList = List()
    
    def __eq__(self, other):
        return self.data == other.data
    

class Graph:
    def __init__(self):
        self.nodes = List()
    
    def firstNode(self):
        return self.nodes.getHead()

    def findNode(self, data):
        return self.nodes.find(GraphNode(data))

    def findEdge(self, node, edge):
        return self.nodes.find(GraphNode(node)).data.adjacencyList.find(Edge(edge, ""));

    def addNode(self, vertex):
        if self.nodes.find(GraphNode(vertex)):
            return False
        self.nodes.insert(GraphNode(vertex))
        return True

    def removeNode(self, vertex):
        node = self.nodes.find(GraphNode(vertex))
        if node == None:
            return False
        current = self.nodes.getHead()
        while current:
            current.data.adjacencyList.remove(Edge(vertex, ""))
            current = current.next
        self.nodes.remove(GraphNode(vertex))
        return True

    def addEdge(self, fromNode, toNode, weight):
        fromTemp = self.nodes.find(GraphNode(fromNode))
        toTemp = self.nodes.find(GraphNode(toNode))
        if fromTemp and toTemp and fromTemp != toTemp:
            if fromTemp.data.adjacencyList.find(Edge(toNode, "")) == None and toTemp.data.adjacencyList.find(Edge(fromNode, "")) == None:
                fromTemp.data.adjacencyList.insert(Edge(toNode, weight))
                toTemp.data.adjacencyList.insert(Edge(fromNode, weight))
                return True   
        return False

    def changeEdgeWeight(self, fromNode, toNode, weight):
        fromTemp = self.nodes.find(GraphNode(fromNode))
        toTemp = self.nodes.find(GraphNode(toNode))
        if fromTemp and toTemp and fromTemp != toTemp:
            edgeNode = fromTemp.data.adjacencyList.find(Edge(toNode, ""))
            if edgeNode:
                edgeNode.data.weight = weight
                reverseEdgeNode = toTemp.data.adjacencyList.find(Edge(fromNode, ""))
                if reverseEdgeNode:
                    reverseEdgeNode.data.weight = weight
                return True
        return False

    def removeEdge(self, fromNode, toNode):
        fromTemp = self.nodes.find(GraphNode(fromNode))
        toTemp = self.nodes.find(GraphNode(toNode))
        if fromTemp and toTemp and fromTemp != toTemp:
            fromTemp.data.adjacencyList.remove(Edge(toNode, ""))
            toTemp.data.adjacencyList.remove(Edge(fromNode, ""))
            return True
        return False
    
    def makeNull(self):
        current = self.nodes.getHead()
        while current:
            current.data.adjacencyList.makeNull()
            current = current.next
        self.nodes.makeNull()