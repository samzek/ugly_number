__author__ = 'sam'

from threading import Thread
import sys

primeNumber = [2,3,5,7]
chars = ["+","-"]
count_ugly = 0
val=0

class IterElem(object):
    def __init__(self,node,i,n):
        self.node = node
        self.i = i
        self.n = n

class Node(object):
        def __init__(self,data):
            self.data = data
            self.val = "not_ugly"
            self.children = []
        def add_children(self,obj):
            self.children.append(obj)

class myThread(Thread):
    def __init__(self,threadID):
        Thread.__init__(self)
        self.threadID = threadID
        self.string = ""
        self.count = 0
    def take_node(self,string):
        self.string = string
    def run(self):
        if self.string != "":
            ugly_or_not_ugly(self.string,self)


"""
Wrapper function to insert the value in the node of the tree
"""
def add_node(char,node):
    node.add_children(Node(node.data + char))
    node.add_children(Node(node.data + "+" + char))
    node.add_children(Node(node.data + "-" + char))


def ugly_or_not_ugly(data,th):
    if "+" in data or "-" in data:
        num=eval(data)
    else:
        num=int(data)
    for i in primeNumber:
        if (num % i) == 0:
            #print th.count
            th.count += 1
            return "ugly"
    return "not ugly"

def ugly_or_not_ugly_ric(num):
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
def create_tree_ric(root,string,i):
    n=0
    node = root
    str = node.data
    var=str.translate(None,"".join(chars))
    if (len(var) == len(string)):
        if "+" in node.data or "-" in node.data:
            num=eval(node.data)
        else:
            num=int(node.data)
        ugly_or_not_ugly_ric(num)
        return
    if i == len(string):
        i -= 1
    add_node(string[i],node)
    i += 1
    for n in range(0,3,1):
        create_tree_ric(node.children[n],string,i)

def create_tree(root,string,i,threads):
    n=0
    node = root
    if i == len(string):
        i -= 1
    add_node(string[i],node)
    i += 1
    var2=node.children[0].data
    var2 = var2.translate(None,"".join(chars))
    if len(var2) == len(string):
        threads[0].take_node(node.children[0].data)
        threads[1].take_node(node.children[1].data)
        threads[2].take_node(node.children[2].data)

        for t1 in threads:
            t1.run()
        for t in threads:
            t.join()

    else:
        for n in range(0,3,1):
            create_tree(node.children[n],string,i,threads)

"""
Iterative implementation of the function: create_tree_iter that use a stack data structure to simulate recursion
"""
def create_tree_iter(stack,string,threads):
    elm = stack[0]
    while elm.n < 3:
        if elm.i == len(string):
            elm.i -= 1
        if elm.n == 0:
            add_node(string[elm.i],elm.node)
        elm.i += 1
        var2=elm.node.children[0].data
        var2 = var2.translate(None,"".join(chars))
        if len(var2) == len(string):
            threads[0].take_node(elm.node.children[0].data)
            threads[1].take_node(elm.node.children[1].data)
            threads[2].take_node(elm.node.children[2].data)

            for t2 in threads:
                t2.run()

            stack.pop(0)
            a=0
            while stack[0].n == 3:
                stack.pop(0)
                if len(stack) == 0:
                    return
                stack[0].i-=1
        else:
            nextEl = IterElem(elm.node.children[elm.n],elm.i,0)

            stack.insert(0,nextEl)
            elm.n += 1
        elm = stack[0]


"""
 "Print the 'radix tree'"
"""
def print_tree(node,space):

    for i in range(0,space,1):
        print " ",
    print node.data
    if not node.children:
       # for p in range(0,space,1):
        #    print " ",
        #print node.val
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

    stack = []
    for inputStr in text:
        if (inputStr != ""):
            global val
            global count_ugly
            root = Node(inputStr[0])
            i = 1
            threads = []
            for h in range(0,3,1):
                    threads.append(myThread(h))
            for t in threads:
               t.start()

            stack.append(IterElem(root,i,0))

            #create_tree(root,inputStr,i,threads)
            #create_tree_ric(root,inputStr,i)
            create_tree_iter(stack,inputStr,threads)
            #print "##################START PRINT TREE###################"
            #print_tree(root,space)
            #print "##################END PRINT TREE#####################"
            sum = 0
            for item in threads:
                sum += item.count
            print sum

            print count_ugly
if __name__== "__main__":
     main()
