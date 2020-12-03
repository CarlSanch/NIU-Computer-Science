/* Carlos Sanchez
 * z1729554
 * CS340-3
 *
 * I certify that this is my own work and where appropriate an extension of the starter code
 * provided for the assignment.
*/ 

#ifndef H_BINTREE
#define H_BINTREE

#include "node.h"

template <typename T> class binTree{

public:
    binTree();                                      // default constructor
    unsigned size() const;                          // returns size of tree
    unsigned height() const;                        // returns height of tree
    virtual void insert(const T&);                  // inserts node in tree
    void inorder(void (*)(const T&));               // inorder traversal of tree

protected:
    Node<T> *root;                                  // root of tree
    
private:
    unsigned size(Node<T> *) const;                 // private version of size()
    unsigned height(Node<T> *) const;               // private version of height() 
    void insert(Node<T> *&, const T&);              // private version of insert() 
    void inorder(Node<T> *, void (*)(const T&));    // private version of inorder()
};

#endif
	template<class T>
	binTree <T>::binTree()
	{
		root = 0; // Need to create the root for the functions
	}

	template <typename T>
	unsigned binTree<T>::size() const
	{
		return size(root); //calls private version of size
	}
	
	template <typename T>
	unsigned binTree<T>::height()const
	{
		return height(root); //calls private version of height
	}

	template <typename T>
	void binTree<T>::insert(const T& v)
	{
		insert(root, v); // calls private version of insert
	}

	template <typename T>
	void binTree<T>::inorder(void (*temp) (const T&))
	{
		inorder(root, temp);// calls private version of inorder
	}

	template <class T>
	unsigned binTree<T>::size(Node <T> * pointer) const
	{
		if (pointer == 0)
		{
			return 0; // if the root is zero, then we return the size of the tree, which is zero
		}
		else
		{
			return (size(pointer->left) + 1 + size(pointer->right));
			//(size(pointer->left) reads the left side of the tree, while
			//size(pointer->right) reads the right side
		}
	}

	template <class T>
	unsigned binTree<T>::height(Node<T> * pointer) const
	{
		if (pointer == 0)
		{
			return 0;//height is zero if the tree's root is zero
		}
		else
		{
			int leftHeight = height(pointer->left);
			int rightHeight = height(pointer->right);

			if(leftHeight > rightHeight)
			{
				return 1 + leftHeight; //bigger side of the tree will determine tree height
			}
			else
			{
				return 1 + rightHeight;
			}
		}
	}

	template <class T> 
	void binTree<T>::insert(Node <T>*& node, const T& temp)
	{
		if (node == 0)
		{
			Node <T> * tmpNode;
			tmpNode = new Node <T>(temp);
			node = tmpNode;	
			//if no tree, we must create one. Here we are doing just that by creating a new node
			//then setting current node, or root, to be that new node
		}
		else
		{
			int leftHeight = height(node->left);
			int rightHeight = height(node->right);

			if(leftHeight <= rightHeight)
			{
				insert(node->left, temp);//Adding new node to the left if it is smaller
			}
			else
			{
				insert(node->right, temp);//Adding node to the right if it is smaller
			}
		}	
	}

	template<class T>
	void binTree<T>::inorder(Node <T>* node, void(*print)(const T&))
	{
		if(node != 0)
		{
			inorder(node->left, print);
			print(node->data);
			inorder(node->right, print);
			//if Node isn't zero, we traverse the tree inorder starting with left then right
		}
	}
