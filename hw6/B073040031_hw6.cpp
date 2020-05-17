#include<iostream>
#include<iomanip>   //cotrol output of 2-digits-data beautifully
#include<vector>
using namespace std;

//	Author		葉星佑 B073040031
//	Date		2019/11/17
//	Purpose		find the number appearing odd times with binary search tree  

class leaf
{
  public:
    int data;
    leaf *left, *right;

    leaf(int x) : data(x), left(nullptr), right(nullptr) {}
    ~leaf() {}
};

class Node              //for output
{
    public:
        int data, left, right;
        Node() {}
        Node(leaf* ptr)
        {
            data = ptr->data;
            left = (ptr->left)? ptr->left->data : 0;
            right = (ptr->right)? ptr->right->data : 0;
        }
        ~Node() {}
};

class BST               //binary search tree
{
    public:
        leaf *root;

        BST() : root(nullptr) {}    //constructor
        ~BST() {}                   //destructor

        void insert(int);           //the number having not been appeared or appearing odd times will be inserted into binary search tree
        void deleted(int);          //remove the number which had been appeared
        bool search(int);           //chech if the number had been appeared

        friend ostream& operator<<(ostream&,const BST&);
        void print(vector<Node>&, leaf*) const;     //recursive traversal, const function is for suiting the overlaoding function parameter const BST&
};

int main()
{
    int x = 0;
    while(cin>>x)                   //when EOF(Ctrl+Z), exiting
    {
        BST tree;                   
        if(x == -1)                 //-1 represents a data-list ends, and -1 is not a part of the data
        {
        	cout<<tree;             //if -1 at first, in my code, means nothing in the tree, output 0 0 0
        	continue;
		}
        tree.insert(x);             //regard the first input is the root,except -1
        while(cin>>x && x != -1)
        {
            if(tree.search(x))
                tree.deleted(x);
            else
                tree.insert(x);
        }
        cout<<tree;                 //overloading
    }
    return 0;
}

void BST :: print(vector<Node> &d, leaf *current) const
{
    if(current)                     //inorder   left->root->right
    {
        print(d,current->left);
        d.push_back(current);
        print(d,current->right);
    }
}

ostream& operator <<(ostream& o,const BST& tree)
{
    leaf *current = tree.root, *previous;       
    vector<Node> node;                  //vector container stores the data from small to large
    leaf *zero = new leaf(0);           //firstly handle zero tree (nothing in the tree)
    if(tree.root == nullptr)
        node.push_back(zero);
    else
        tree.print(node,tree.root);

    o<<"node ";                         //formatted output
    for(int i=  0;i<node.size();i++)
        o<<setw(2)<<node[i].data<<" ";
    o<<endl<<"left ";
    for(int i=0;i<node.size();i++)
        o<<setw(2)<<node[i].left<<" ";
    o<<endl<<"right";
    for(int i=0;i<node.size();i++)
        o<<setw(2)<<node[i].right<<" ";
    o<<endl;        
    return o;
}

bool BST :: search(int target)              //binary search
{
    leaf *current = root;
    while(current != nullptr)
    {
        if(current->data == target)         //goal
            return true;
        else if(current->data > target)
            current = current->left;
        else if(current->data < target)
            current = current->right;
    }
    return false;                           //not found
}

void BST :: insert(int x)
{
    leaf *current = root, *previous, *newnode = new leaf(x);    //in my code, previous is necessary

    if(current == nullptr)                  //first one into the tree
        root = newnode;
    else
    {
        while(current != nullptr)           //path the right place to insert
        {
            previous = current;
            if(current->data > x)
                current = current->left;
            else if(current->data < x)
                current = current->right;
        }
        if(previous->data > x)
            previous->left = newnode;
        else 
            previous->right = newnode;
    }
}

void BST :: deleted(int x)
{
    leaf *current = root, *previous = root;
    
    if(current->left == nullptr && current->right == nullptr)       //delete the root
    {
        root = nullptr;
        delete current;
        return;
    }

    while((current->data != x) && (current->data > x && current->left != nullptr) || (current->data < x && current->right != nullptr))
    {   //find the node which I want to remove it
        previous = current;
        if(current->data > x)
            current = current->left;
        else if(current->data < x)
            current = current->right;
    }

    if(current->left == nullptr && current->right == nullptr)       //case I: the target node has no any son
    {
        if(previous->data > x)
            previous->left = nullptr;
        else 
            previous->right = nullptr;        
    }
    else if(current->left == nullptr && current->right != nullptr)  //case II-I: the target node has only right leaf
    {
        if(current == root)                                         //exception: root node
            root = root->right;
        else if(previous->data > x)
            previous->left = current->right;
        else 
            previous->right = current->right;        
    }
    else if(current->left != nullptr && current->right == nullptr)  //case II-I: the target node has only left leaf
    {
        if(current == root)                                         //exception: root node
            root = root->left;
        else if(previous->data > x)
            previous->left = current->left;
        else 
            previous->right = current->left;
    }
    else                                                            //case III: the target node has both left and right leaf
    {                                                               //successor replace will-be-removed node
        leaf *successor = current->right, *successor_p = current;         //successor_p means successor_previous_pointer
        while(successor->left != nullptr)       //go to successor   
        {
            successor_p = successor;
            successor = successor->left;
        }
        if(successor == current->right && current != root)
        {
            previous->left = successor;
            successor->left = current->left;
        }
        else
        {
            if(successor_p->data > successor->data)
            {
                if(successor->left == nullptr && successor->right == nullptr)
                    successor_p->left = nullptr;
                else if(successor->left == nullptr && successor->right != nullptr)
                    successor_p->left = successor->right;     
            }
            else
            {          
                if(successor->left == nullptr && successor->right == nullptr)
                    successor_p->right = nullptr;
                else if(successor->left == nullptr && successor->right != nullptr)
                    successor_p->right = successor->right;     
            }                 
            successor->left = current->left;      //substitute
            successor->right = current->right;

            if(current == root)                                         //exception: root node
            root = successor;
            else if(previous->data > current->data)                     //normal case
                previous->left = successor;
            else 
                previous->right = successor;
        }
    }
    delete current;                                                 //delete the removed node
}
