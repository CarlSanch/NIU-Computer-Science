#include "binTree.h"

#ifndef BST_H_
#define BST_H_


template <typename T>
class binSTree : public binTree<T>
{
public:
        void insert(const T &x);
        bool search(const T &x) const;   
	bool remove(const T &x);
private:
	void insert(Node<T> *&, const T &);
	bool search(Node<T> *, const T &) const;
	void remove(Node<T> *&, const T &);
	bool leaf(Node<T> *node) const;

};
#endif

	//start public functions
	template <typename T>
	void binSTree<T>::insert(const T &x)
	{
		insert(this->root, x); 
	}
	
	template <typename T>
	bool binSTree<T>::search(const T &x) const
	{
		if( search(this->root, x) == true)
			return true;
		else
			return false;
	}
	
	template <typename T>
	bool binSTree<T>::remove(const T &x)
	{
		return remove(this->root, x);
	}
	
	//start private functions
	template <typename T>
	void binSTree<T>::insert(Node<T> *&node, const T& value)
	{
		if (node == nullptr)
		{
			
		}

		if (value < node->value)
		{
			node->left = insert(node->left, value);
		}

		else if (value > node->value)
		{
			node->right = insert(node->right, value);
		}

	}

	template <class T>
	bool binSTree<T>::search(Node<T> *node, const T& value) const
	{
	
		int temp = nullptr;

		while (node != nullptr)
		{
			if (value > node->temp)
			{
				node = node->right;
			}

			else if (value < node->temp)
			{
				node = node->left;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	template <typename T>
	void binSTree<T>::remove(Node<T> *&node, const T& value)
	{
		if (node == nullptr)
		{
			node;
		}

		if (value < node->value)
		{
			node->left = remove(node->left, value);
		}

		else if (value > node->value)
		{
			node->right = remove(node->right, value);
		}

		else
		{
			if (node->left == nullptr)
			{
				Node<T> * temp = node->right;
				temp;
			}

			else if (node->right == nullptr)
			{
				Node<T> * temp = node->left;
				temp;
			}

			

		}
	}

	template <class T>
	bool binSTree<T>::leaf(Node<T> *node) const
	{

	}


