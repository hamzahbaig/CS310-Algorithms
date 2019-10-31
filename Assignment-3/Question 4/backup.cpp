#include <iostream>
#include <vector>

using namespace std;

char ch = 48;
struct node
{
	int sum;
	int data;
	node *left;
	node *right;
	int times;
	char label;
	
};

node *createNode(int data)
{
	node *temp = new node;
	temp->data = data;
	temp->sum = 0;
	temp->times = 0;
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
	cout <<"Weight: " << root->data << " Sum: " <<  root->sum << " Label: " << root->label << " times: " << root->times <<  endl;
	printInOrder(root->right);
}
void calculatingSum(node* root, int sumToBeAdded)
{
	if(root->left == NULL && root->right == NULL)
	{
		ch++;
		root->sum = root->data + sumToBeAdded;
		sumToBeAdded = root->sum;
		root->label = ch;
		return;
	}
	if(root->left->data >= root->right->data)
	{
		root->sum = root->data + sumToBeAdded;
		sumToBeAdded = root->sum;
		calculatingSum(root->left,sumToBeAdded);
		sumToBeAdded = 0;
		calculatingSum(root->right,sumToBeAdded);
	}
	else
	{
		root->sum = root->data + sumToBeAdded;
		sumToBeAdded = root->sum;
		calculatingSum(root->right,sumToBeAdded);
		sumToBeAdded = 0;
		calculatingSum(root->left,sumToBeAdded);

	}
	

}

node* getGreaterNode(node *a, node *b)
{
	if(a->sum >= b->sum)
	{
		return a;
	}
	return b;

}
node* getMax(node *root)
{	
	node* leftMax = new node;
	node* rightMax = new node; 
	if(root->left == NULL & root->right == NULL)
	{	
		return root;
	}
	if(root->left)
	{
		leftMax = getMax(root->left);
	}
	if(root->right)
	{
		rightMax = getMax(root->right);
	}

	node *temp;
	temp = getGreaterNode(getGreaterNode(leftMax,rightMax),root);
	return temp;
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
	temp->times = max->times;
}

int main()
{
	int entries[7] = {10,100,4,2,3,5,6};
	vector<node*> path1,path2;
	node *max1,*max2;
	node *root = insertEntries(entries,root,0,7);
	calculatingSum(root,0);
	printInOrder(root);
	// find MAXIMUM and Its PATH
	max1 = getMax(root);
	cout << "MAXIMUM1: " << max1->data << endl;
	pathExist(root,max1->data,path1);
	node *temp = new node;
	copy(max1,temp);
	max1->data = -1; max1->sum = -1;
	path1.pop_back();
	path1.push_back(temp);
	cout << endl;
	for(int i=0; i< path1.size() ;i++)
	{
		//path1[i]->times++;
		cout << "data: " << path1[i]->data << " sum: " << path1[i]->sum  << " label: " << path1[i]->label << " times: " << path1[i]->times <<endl;
	}

	cout << endl << endl;
	// find SECOND MAXIMUM and Its PATH
	printInOrder(root);

	max2 = getMax(root);
	cout << "MAXIMUM2: " << max2->data << endl;
	pathExist(root,6,path2);
	copy(max2,temp);
	max2->data = -1; max2->sum = -1;
	path2.pop_back();
	path2.push_back(temp);
	cout << endl;
	for(int i=0; i< path2.size() ;i++)
	{	
		path2[i]->times++;
		cout << "data: " << path2[i]->data << " sum: " << path2[i]->sum  << " label: " << path2[i]->label << " times: " << path2[i]->times << endl;
	}

}