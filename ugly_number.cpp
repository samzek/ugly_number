#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

int count_ugly = 0;

class Node{
	public:	
	char *data;
	Node *leaves;
	Node();
	Node(char *);
	Node(char);
	void add_children(Node,int);
};
Node::Node(){;};
Node::Node(char first){
	data = new char[1];
	data[0] = first;
};
Node::Node(char *string){
	data = string;
};
struct stack_t {
	Node *nd;
	int i;
	int n;	
};

typedef stack_t Stack;

void Node::add_children(Node nd,int index)
{
	leaves[index] = nd;
};

void ugly_or_not_ugly(char string[]){
	int val = 0;
	if ((strpbrk(string,"+") != NULL) || (strpbrk(string,"-")!= NULL)) 
	{
		val = atoi(&string[0]);
		for(int i=1;i<strlen(string);i++)
		{
			switch(string[i]){
				case ('+'):
					val += atoi(&string[++i]);
					break;
				case ('-'):
					val -= atoi(&string[++i]);
					break;
				default:
					;
			}
		}
	}
	else
	{
		val = atoi(&string[0]); 
	}
	if (val % 2 == 0 || val % 3 == 0 || val % 5 == 0 || val % 7 ==0){
		count_ugly++;
		return;
	}
};

void add_nodes(char c,Node *nd,bool is_leaves,char *string_used){
	if(is_leaves == false)
		nd->leaves = new Node[3];
	char *str;
	str = new char[strlen(string_used)+2];
	strcpy(str,string_used);	
	sprintf(str,"%s%c",str,c);
	if(is_leaves == false)
		nd->add_children(Node(str),0);
	else{
		ugly_or_not_ugly(str);
	}
	str = NULL;
	
	str = new char[strlen(string_used)+3];
	strcpy(str,string_used);
	sprintf(str,"%s%c",str,'+');
	sprintf(str,"%s%c",str,c);
	if(is_leaves == false)
		nd->add_children(Node(str),1);
	else{
		ugly_or_not_ugly(str);
	}
	str = NULL;
	
	str = new char[strlen(string_used)+3];
	strcpy(str,string_used);
	sprintf(str,"%s%c",str,'-');
	sprintf(str,"%s%c",str,c);
	if(is_leaves == false)
		nd->add_children(Node(str),2);
	else{
		ugly_or_not_ugly(str);
	}

};

void create_tree(Node root,char string[],int i){
	Node *nd = &root;
	int a=0;
	for(int h=0;h<strlen(nd->data);h++)
	{
		if(*(nd->data+h)!='+' && *(nd->data+h)!='-')
		{
			a++;
		}
	}
		if (a == strlen(string)-1){
			add_nodes(string[i],nd,true,nd->data);
			return;
		}
	/*
	if (a == strlen(string)-2 || strlen(string)-2 == 0){
		//This solution fail with only one test case
		char *str;
		str = new char[strlen(nd->data)+2];
		strcpy(str,nd->data);	
		sprintf(str,"%s%c",str,string[i]);
		if(strlen(string)-2 == 0)
			ugly_or_not_ugly(str);
		else
			add_nodes(string[i+1],nd,true,str);
		str = NULL;
		
		str = new char[strlen(nd->data)+3];
		strcpy(str,nd->data);
		sprintf(str,"%s%c",str,'+');
		sprintf(str,"%s%c",str,string[i]);
		if(strlen(string)-2 == 0)
			ugly_or_not_ugly(str);
		else
			add_nodes(string[i+1],nd,true,str);
		str = NULL;
		
		str = new char[strlen(nd->data)+3];
		strcpy(str,nd->data);
		sprintf(str,"%s%c",str,'-');
		sprintf(str,"%s%c",str,string[i]);
		if(strlen(string)-2 == 0)
			ugly_or_not_ugly(str);
		else
			add_nodes(string[i+1],nd,true,str);
		
		delete []str;
		return;
	}
	*/
	if (i == strlen(string))
		i--;
	add_nodes(string[i],nd,false,nd->data);
	i++;
	
	for(int n = 0;n<3;n++){
		if (a != strlen(string))
			create_tree(nd->leaves[n],string,i);
	}
};
void create_tree_iter(Stack *stack,char string[],int pop){
	Stack *elm = &stack[pop];
	while(elm->n < 3){
		if (elm->i == strlen(string))
			elm->i--;
		int a=0;
		for(int h=0;h<strlen(elm->nd->data);h++)
		{
			if(*(elm->nd->data+h)!='+' && *(elm->nd->data+h)!='-')
			{
				a++;
			}
		}
		if (a == strlen(string)-1){
			add_nodes(string[elm->i],elm->nd,true,elm->nd->data);
			pop--;
			while(stack[pop].n == 3){
				if (pop == 0)
					return;
				stack[--pop].i--;
			}
		}
		else {
			if (elm->n == 0)
				add_nodes(string[elm->i],elm->nd,false,elm->nd->data);
			elm->i++;
			Stack nextEl;
			nextEl.nd = &elm->nd->leaves[elm->n];
			nextEl.i = elm->i;
			nextEl.n = 0;
			stack[++pop] = nextEl;
			elm->n+=1;
		}
	elm = &stack[pop];
	}
}
int main (int argc,char **argv)
{
	ifstream stream(argv[1]);
    string line;
    Node root;
    char *inputStr;
    int i,el_to_pop;
    Stack *stack;	
    while (getline(stream, line)) {
    	if (line == "")
			continue;
		else {
			count_ugly = 0;
			root = Node(line[0]);
			i = 1;
			inputStr = new char [line.length() + 1];
			
			//data structure for iterative implementation
			/*
			stack = new Stack[(int)pow(3,line.length()-1)];
			el_to_pop = 0;
			stack[0].nd = &root;
			stack[0].i = i;
			stack[0].n = 0;
			*/
			for(int p = 0;p<line.length();p++)
				inputStr[p] = line[p];
			inputStr[line.length()] = '\0';
			if(atoi(inputStr) == 0)
				count_ugly++;
			else
				if(strlen(inputStr) == 1)
					ugly_or_not_ugly(inputStr);
				else
					create_tree(root,inputStr,i);
					//create_tree_iter(stack,inputStr,el_to_pop);
			//cout<<"Node's dimension: "<<sizeof(Node)<<endl;
			cout<<count_ugly<<endl;
		}
		
    }
    return 0;
}

