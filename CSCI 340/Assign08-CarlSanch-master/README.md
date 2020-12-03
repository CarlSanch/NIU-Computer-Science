# CS340 Binary Tree Class

For this computer assignment, implement a derived class (as a template) to represent a binary search tree. Since a binary search tree is a binary tree, implement your binary search tree class inherited from the base class of the binary tree that you implemented in your previous assignment.

The definition of the derived class of a binary search tree (as a template) is given as follows:

```c++
template <typename T>
class binSTree : public binTree<T>
{
public:
    void insert(const T &x);       // inserts node with value x
    bool search(const T &x) const; // searches leaf with value x
    bool remove(const T &x);       // removes leaf with value x
private:
    void insert(Node<T> *&, const T &);      // private version of insert
    bool search(Node<T> *, const T &) const; // private version of search
    void remove(Node<T> *&, const T &);      // private version of remove
    bool leaf(Node<T> *node) const;          // checks if node is leaf
};
```

- The `insert()` function inserts a node with the data value `x` in the tree. 
- For the `search()` function, `x` is the data value of a leaf to be searched for. If the search is successful, the `search()` function returns **true**; otherwise, it returns **false**. 
- The `remove()` function first calls the `search()` function to determine the result of the search for a leaf with the data value `x`, and if the search is successful, then it calls the private version of the `remove()` function to remove the corresponding leaf from the tree and returns **true**; otherwise, it returns **false**. 
- The `leaf()` function simply checks if a node is a leaf.

The private versions of the member functions `insert()`, `remove()`, and `search()` can be implemented as recursive functions, but these functions have an additional argument, which is the root of the tree. The private version of the `remove()` function unlike its public version does not return any value.

To test your derived class and its member functions, the source file of a driver program **bstDriver.cc** and its header file **bstDriver.h**, are provided. This program generates a set of random integers in the range [1, N] with N = 100 and inserts them in a vector of integers and in a binary search tree. The program searches for each value of the vector in the binary search tree. If the value can be found as the data value of a leaf, then the leaf is removed from the tree. After removing all the leaves, the size of the tree and the data values in nodes are printed in ascending order by traversing the tree in inorder. This process continues until the tree becomes completely empty.

Put the implementation of your binary search tree class in a separate header file, that you create and add to your repository named **bst.h**. To use the `class Node` in your program, include the header file **node.h**, by inserting the statement: `#include “node.h”` at the top of your header file binarytree.h, and include the header file binarytree.h in your header file bst.h. Make it sure that each header file is included only once, so the contents of each header file should be guarded as follows:

```c++
// include other header files (if any)
#ifndef BST_H_
#define BST_H_

// put statements in header file

#endif
```

The correct output of this program can be found in file **bstDriver.out**, which is in the same directory with **bstDriver.cc**.

**Note:** In public versions of `insert()`, `remove()`, and `search()` functions, you’ll get a compile error when you pass the root as an argument to these functions. To eliminate the compile errors, you need to pass the `root` as `this–>root`.

**Assignment Notes:**

- Include any necessary headers and add necessary global constants.

- You are not allowed to use any I/O functions from the C library, such as scanf or printf. Instead, use the I/O functions from the C++ library, such as cin or cout.

- Add documentation to your source file (e.g. https://google.github.io/styleguide/cppguide.html#Comments).

- Prepare your Makefile (you need to construct and add Makefile) so that the TA only needs to invoke the command make to compile your source file and produce the executable file **binarySearchTree.exe**. Make sure you use exactly the same file names specified here, i.e. **binarySearchTree.exe**, in your Makefile, otherwise your **submission will get 0 points**.

- This semester you will need to make at least three commits to your local repository and at least one push to your master repository for each assignment. This will show the evolution of your assignments over time and the thought process behind the code. You will need to make sure your final push to your master repository is completed before the assignment is due (the system time stamps actions), if the assignment is late the TA will mark off points.

- When your program is ready for grading, **commit** and **push** your local repository to remote git classroom repository and follow ***Assignment Submission Instructions***.