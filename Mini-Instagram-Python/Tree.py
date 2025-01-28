class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class Tree:
    def __init__(self):
        self.root = None

    def __rotateRight(self, root):
        leftChild = root.left
        root.left = leftChild.right
        leftChild.right = root
        return leftChild

    def __rotateLeft(self, root):
        rightChild = root.right
        root.right = rightChild.left
        rightChild.left = root
        return rightChild

    def __height(self, root):
        if root == None:
            return -1
        return max(self.__height(root.left), self.__height(root.right)) + 1
    
    def __balanceFactor(self, root):
        return self.__height(root.left) - self.__height(root.right)

    def getRoot(self):
        return self.root
    
    def find(self, data):
        def findHelper(root, data):
            if root == None:
                return None
            if data < root.data:
                return findHelper(root.left, data)
            elif data > root.data:
                return findHelper(root.right, data)
            else:
                return root
        return findHelper(self.root, data)
    
    def isEmpty(self):
        return self.root == None
    
    def insert(self, data):
        def insertHelper(root, data):
            if root == None:
                return True, TreeNode(data)
            if data < root.data:
                _, root.left = insertHelper(root.left, data)
            elif data > root.data:
                _, root.right = insertHelper(root.right, data)
            else:
                return False, root
            if self.__balanceFactor(root) > 1:
                if data < root.left.data:
                    root = self.__rotateRight(root)
                else:
                    root.left = self.__rotateLeft(root.left)
                    root = self.__rotateRight(root)
            elif self.__balanceFactor(root) < -1:
                if data > root.right.data:
                    root = self.__rotateLeft(root)
                else:
                    root.right = self.__rotateRight(root.right)
                    root = self.__rotateLeft(root)
            return True, root
        ret, self.root = insertHelper(self.root, data)
        return ret
    
    def remove(self, data):
        def removeHelper(root, data):
            if root == None:
                return False, None
            if data < root.data:
                _, root.left = removeHelper(root.left, data)
            elif data > root.data:
                _, root.right = removeHelper(root.right, data)
            else:
                if root.left == None:
                    return True, root.right
                elif root.right == None:
                    return True, root.left
                else:
                    predecessor = root.left
                    while predecessor.right:
                        predecessor = predecessor.right
                    root.data = predecessor.data
                    _, root.left = removeHelper(root.left, predecessor.data)
            if root == None:
                return True, None
            if self.__balanceFactor(root) > 1:
                if self.__balanceFactor(root.left) >= 0:
                    root = self.__rotateRight(root)
                else:
                    root.left = self.__rotateLeft(root.left)
                    root = self.__rotateRight(root)
            elif self.__balanceFactor(root) < -1:
                if self.__balanceFactor(root.right) <= 0:
                    root = self.__rotateLeft(root)
                else:
                    root.right = self.__rotateRight(root.right)
                    root = self.__rotateLeft(root)
            return True, root
        ret, self.root = removeHelper(self.root, data)
        return ret
    
    def makeNull(self):
        self.root = None