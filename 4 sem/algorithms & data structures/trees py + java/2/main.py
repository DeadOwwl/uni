import sys


class Tree:
    def __init__(self, n):
        self.info = n
        self.left = None
        self.right = None

    def add(self, n):
        if self.info is None:
            self.info = n
        else:
            if n < self.info:
                if self.left is None:
                    self.left = Tree(n)
                else:
                    self.left.add(n)
            elif n > self.info:
                if self.right is None:
                    self.right = Tree(n)
                else:
                    self.right.add(n)

    def left_traversal(self):
        if self.info is None:
            return
        else:
            w.write(str(self.info) + '\n')
            if self.left:
                self.left.left_traversal()
            if self.right:
                self.right.left_traversal()

    def find_min(self):
        if self.left is not None:
            return self.left.find_min()
        else:
            return self.info

    def find(self, n):
        if self.info is None:
            return False
        if self.info == n:
            return True
        elif n > self.info:
            if self.right is None:
                return False
            return self.right.find(n)
        elif self.left in None:
            return False
            return self.left.find(n)

    def delete(self, n):
        if self.find(n) == n:
            if self.info is None:
                return None
            if n < self.info:
                self.left = self.left.delete(n)
                return self
            elif n > self.info:
                self.right = self.right.delete(n)
                return self

            if self.left is None:
                return self.right
            elif self.right is None:
                return self.left
            else:
                min_node = self.right.find_min()
                self.info = min_node
                self.right = self.right.delete(min_node)
                return self
        else: return self


f = open('input.txt')
w = open('output.txt', 'w')
q = sys.getrecursionlimit()
sys.setrecursionlimit(1024 * 1024 * 1024)
q = sys.getrecursionlimit()
de = int(f.readline())
f.readline()
tree = Tree(int(f.readline()))
for line in f:
    tree.add(int(line))
tree = tree.delete(de)
tree.left_traversal()