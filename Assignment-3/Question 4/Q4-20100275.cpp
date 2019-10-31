#include <iostream>
#include <vector>

using namespace std;


// ORDER OF COMPLEXITY (n)

char ch = 48;
struct node
{
	int sum;
	int data;
	node *left;
	node *right;
	char label;
	int total_sum;
	int max_side_sum;
	int left_leaf;
	int right_leaf;

};

node *createNode(int data)
{
	node *temp = new node;
	temp->data = data;
	temp->sum = 0;
	temp->label = '-';
	temp->left = NULL;temp->right = NULL;
	return temp;
}

node *insertEntries(int entries[], node *root,int i,int n)
{
	if(i<n)
	{
		node *temp = createNode(entries[i]);
		root = temp;

		root->left = insertEntries(entries,root->left,2 * i +1, n);

		root->right = insertEntries(entries,root->right, 2 * i +2,n);
	}
	return root;
}

void printInOrder(node *root)
{
	if (root == NULL)
	{
		return;
	}
	printInOrder(root->left);
	cout <<"label:" << root->label << " Weight: " << root->data << " TS: " << root->total_sum << " MSS: " << root->max_side_sum << " LL: " << root->left_leaf << " RL: " << root->right_leaf << endl;

	printInOrder(root->right);
}

void labeling(node* root)
{
	if(root->right == NULL && root->left == NULL)
	{
		ch++;
		root->label = ch;
		return;
	}
	labeling(root->right);
	labeling(root->left);
}
node* getGreaterNode(node *a, node *b,string flag)
{
	if(flag == "sum")
	{
		if(a->data >= b->data)
		{
			return a;
		}
		return b;
	}
	else if(flag == "max_side_sum")
	{
		if(a->max_side_sum >= b->max_side_sum)
		{
			return a;
		}
		return b;
	}
	else if(flag == "left_leaf")
	{
		if(a->left->data >= a->right->data)
		{
			return a->left;
		}
		return a->right;
	}
	else if(flag == "right_leaf")
	{
		if(a->right->data >= a->left->data)
		{
			return a->right;
		}
		return a->left;
	}
	
	

}


bool pathExist(node*root, int value, vector<node*>& path)
{	
	if(!root)
	{
		return false;
	}
	path.push_back(root);

	if(root->data == value)
	{
		return true;
	}

	if(pathExist(root->left,value,path) || pathExist(root->right,value,path))
	{
		return true;
	}

	path.pop_back();
	return false;
}


void copy(node* max, node* temp)
{
	temp->data = max->data;
	temp->sum = max->sum;
	temp->label = max->label;
}

void sumCal(node *root)
{
	if(root->left->left == NULL && root->right->right == NULL)
	{
		root->total_sum = root->data + root->left->data + root->right->data;
		root->max_side_sum = root->data + (getGreaterNode(root->right,root->left,"sum"))->data; 
		root->left_leaf = root->left->data;
		root->right_leaf = root->right->data;
		return;
	}
	sumCal(root->left);
	sumCal(root->right);
	root->total_sum = root->left->max_side_sum + root->right->max_side_sum + root->data;
	root->max_side_sum = root->data + getGreaterNode(root->right,root->left,"max_side_sum")->max_side_sum;
	root->left_leaf = getGreaterNode(root->left,root,"left_leaf")->data;
	root->right_leaf = getGreaterNode(root->right,root,"right_leaf")->data;

	if(root->total_sum < root->left->total_sum + root->data)
	{
		root->total_sum = root->left->total_sum + root->data;
		root->max_side_sum = root->data + root->left->max_side_sum;
		root->left_leaf = root->left->left_leaf;
		root->right_leaf= root->left->right_leaf;
	}
	else if(root->total_sum < root->right->total_sum + root->data)
	{
		root->total_sum = root->right->total_sum + root->data;
		root->max_side_sum= root->data + root->right->max_side_sum;
		root->left_leaf = root->right->left_leaf;
		root->right_leaf= root->right->right_leaf;
	}

}

int maximum(node* a, node *b,string flag)
{
	if(flag == "left")
	{
		if(a->left_leaf >= b->left_leaf)
		{
			return a->left_leaf;
		}
		return b->left_leaf;
	}
	else if(flag == "right")
	{
		if(a->right_leaf >= b->right_leaf)
		{
			return a->right_leaf;
		}
		return b->right_leaf;

	}
	
}

int main()
{
	int entries[15] = {17,20,4,5,7,35,6,3,6,16,12,18,1,2,3};
	//int entries[15] = {29, 6, 11, 15, 5, 10, 20, 1, 3, 4, 2, 15, 45, 10, 50};
	//int entries[7] = {27,15,3,17,37,7,4};
	//int entries[7] = {7,5,6,1,2,3,4};
	//int entries[7] = {10,100,4,2,3,5,6};
	//int entries[7] = {20,5,7,3,6,16,12};
	vector<node*> path1,path2;
	int max1_node_value,max2_node_value;
	node *root = insertEntries(entries,root,0,15);
	labeling(root);
	sumCal(root);
	//printInOrder(root);
	
	pathExist(root,root->left_leaf,path1);


	
	pathExist(root,root->right_leaf,path2);

	

	cout << "TOTAL MAX UNION SUM: " << root->total_sum << endl;
	cout << "PATH1: " ;
	for(int i=0; i<path1.size();i++)
	{
		cout << path1[i]->data << " ";
	}
	cout << endl << "PATH2: " ;
	for(int i=0; i<path2.size();i++)
	{
		cout << path2[i]->data << " ";
	}

	
}