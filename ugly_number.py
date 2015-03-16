__author__ = 'sam'

import sys

class Node(object):
        def __init__(self,data):
            self.data = data
            self.children = []
        def add_children(self,obj):
            self.children.append(obj)

primeNumber = [2,3,5,7]
chars = ["+","-"]
count_ugly = 0

"""
Wrapper function to insert the value in the node of the tree
"""
def add_node(char,node):
    node.add_children(Node(node.data + char))
    node.add_children(Node(node.data + "+" + char))
    node.add_children(Node(node.data + "-" + char))

def ugly_or_not_ugly(num):
    global count_ugly
    for i in primeNumber:
        if (num % i) == 0:
            count_ugly += 1
            return

"""
This function create the "radix tree" and evaluate if the expression, in the leaves of the tree, create an ugly number
or not. it use the eval function to calculate the result of expressions at runtime and ugly_or_not_ugly function to
control whether it's ugly.
"""
def create_tree(root,string,i):
    n=0
    node = root
    str = node.data
    var=str.translate(None,"".join(chars))
    if (len(var) == len(string)):
        if "+" in node.data or "-" in node.data:
            num=eval(node.data)
        else:
            num=int(node.data)
        ugly_or_not_ugly(num)
        return
    if i == len(string):
        i -= 1
    add_node(string[i],node)
    i += 1
    for n in range(0,3,1):
        create_tree(node.children[n],string,i)

"""
Print the "radix tree"
"""
def print_tree(node,space):

    for i in range(0,space,1):
        print " ",
    print node.data
    if not node.children:
        space -= 1
        return
    for i in node.children:
        space += 1
        print_tree(i,space)
        space -= 1

"""
It picks a line from input file and it creates the tree that contains every possible expressions.
"""
def main():
    space = 0
    if len(sys.argv) != 2:
        print "One input file required"
        return
    file = open((sys.argv[1]),"r")
    text = file.read().splitlines()
    file.close()

    for inputStr in text:
        global count_ugly
        count_ugly = 0
        root = Node(inputStr[0])
        i = 1
        create_tree(root,inputStr,i)
        #print "##################START PRINT TREE###################"
        #print_tree(root,space)
        #print "##################END PRINT TREE#####################"
        print count_ugly

if __name__== "__main__":
     main()
