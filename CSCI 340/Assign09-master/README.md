# CS340.3 Heaps and Heapsort
For this computer assignment, you are to write a C++ program to sort items in several input files, using the heapsort technique. For each input file, your program first reads the items from the input file and builds a heap structure for these items. Then, it retrieves these items from the heap structure in order and prints them out on stdout. Pointers to input files, certain constant definitions, and the prototypes of the function templates are included in the header file **heap.h**.

Implement the following function templates in **heap.cc**:

```c++
template <typename T> void get_list(vector<T> &v, const char *path)
```
It opens an input file for reading, then reads the items from the file and inserts them in a vector. Finally, it closes the input file. The first argument `v` to this function is the vector and the second argument `path` is the full path name of the input file.

```c++
template<typename T, typename P> void construct_heap(vector<T> &v, P pred)
``` 

It constructs a heap structure from the items of vector `v` and uses the predicate `pred` to compare the items when building the heap. It calls the function `make_heap()` to construct the heap and the function `sort_heap()` to sort the items in the heap using the predicate `pred`. **Both functions are in the STL.**

The definition of the **print_list** class is included in the header file **heap.h**. Implement its member functions (as templates) there:

```c++
template<typename T> print_list<T>::print_list(const unsigned &s, 
                                                const unsigned &w, 
                                                const unsigned &l, 
                                                const unsigned &c)
```

The constructor of the **print_list** class, where `s` is the heap size, `w` is the minimum number of chars written in printout, `l` is the maximum number of items printed in a single line, and `c` is used as a counter with the **default value 0** that can be used to insert the newline characters in printout.


```c++
template<typename T> void print_list<T>::operator()(const T &x)
```

It can be used to print the item `x` of a heap on stdout. For proper printout, insert the following statements at the beginning of this function:

```c++
cout.width(wid); 
cout.precision(2);
cout << fixed << showpoint;
```

The binary predicates `greater<>()` and `less<>()` (in the [STL](http://www.cplusplus.com/reference/functional/greater/)) take two arguments and return a boolean value to the calling routine. The call `greater<T>(x, y)` takes the arguments `x` and `y` as inputs, and if `x` is *greater than* `y`, it returns `true`; otherwise, it returns `false`; and the call `less<T>(x, y)` returns `true` if `x` is less than `y`; otherwise, it returns `false`. To build a heap, the driver program uses these two predicates.

The `main()` routine for your program is given in the source file **heap.cc**, in the same directory with **heap.h**. Within **heap.cc** add implementations of the subroutines defined above. This routine acts as a driver for your heap structure, where several vector objects are defined.

### Programming Notes:

Include any necessary headers and add necessary global constants.

You are not allowed to use any I/O functions from the C library, such as scanf or printf. Instead, use the I/O functions from the C++ library, such as cin or cout.

Add documentation to your source file (e.g. https://google.github.io/styleguide/cppguide.html#Comments).

Prepare your Makefile (you need to construct and add **Makefile**) so that the TA only needs to invoke the command make to compile your source file and produce the executable file **heap.exe**. Make sure you use exactly the same file names specified here, i.e. **heap.cc** and **heap.exe**, in your **Makefile**. Otherwise your submission will get 0 points.

This semester you will need to make at least three commits to your local repository and at least one push to your master repository for each assignment. This will show the evolution of your assignments over time and the thought process behind the code. You will need to make sure your final push to your master repository is completed before the assignment is due (the system time stamps actions), if the assignment is late the TA will mark off points.

When your program is ready for grading, commit and push your local repository to remote git classroom repository and follow Assignment Submission Instructions.