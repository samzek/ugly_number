#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int count_ugly = 0;

class Node{
	public:	
	char *data;
	Node *leaves;
	Node();
	Node(char *);
	Node(char);
	void add_children(Node *,int);
};
Node::Node(){;};
Node::Node(char first){
	data = new char[1];
	data[0] = first;
};
Node::Node(char *string){
	data = new char[strlen(string)+1];
	strcpy(data,string);
};

void Node::add_children(Node *nd,int index)
{
	leaves[index] = *nd;
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

void add_nodes(char c,Node *nd,bool is_leaves){
	if(is_leaves == false)
		nd->leaves = new Node[3];
	char *str;
	str = new char[strlen(nd->data)+2];
	strcpy(str,nd->data);	
	sprintf(str,"%s%c",str,c);
	if(is_leaves == false)
		nd->add_children(new Node(str),0);
	else
		ugly_or_not_ugly(str);
	str = NULL;
	
	str = new char[strlen(nd->data)+3];
	strcpy(str,nd->data);
	sprintf(str,"%s%c",str,'+');
	sprintf(str,"%s%c",str,c);
	if(is_leaves == false)
		nd->add_children(new Node(str),1);
	else
		ugly_or_not_ugly(str);
	str = NULL;
	
	str = new char[strlen(nd->data)+3];
	strcpy(str,nd->data);
	sprintf(str,"%s%c",str,'-');
	sprintf(str,"%s%c",str,c);
	if(is_leaves == false)
		nd->add_children(new Node(str),2);
	else
		ugly_or_not_ugly(str);
	
	delete []str;
};

//TODO:reduce memory utilization
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
		add_nodes(string[i],nd,true);
		return;
	}
	if (i == strlen(string))
		i--;
	add_nodes(string[i],nd,false);
	i++;
	
	for(int n = 0;n<3;n++){
		if (a != strlen(string))
			create_tree(nd->leaves[n],string,i);
	}
};
int main (int argc,char **argv)
{
	ifstream stream(argv[1]);
    string line;
    Node root;
    while (getline(stream, line)) {
    	if (line == "")
			continue;
		else {
			count_ugly = 0;
			root = Node(line[0]);
			int i = 1;
			char *inputStr = new char [line.length() + 1];
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
			cout<<count_ugly<<endl;
		}
		
    }
    return 0;
}

