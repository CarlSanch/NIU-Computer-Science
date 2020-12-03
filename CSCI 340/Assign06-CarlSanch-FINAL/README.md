# CS340 The Josephus Problem

The problem is known as the **Josephus problem** (or Josephus permutation) and postulates a group of people of size N >= 1 are standing in a circle waiting to be eliminated. Counting begins at a specified point in the circle and proceeds around the circle in a specified direction. After a specified number of M >= 1 people are counted, the M^th person in the circle is eliminated. The procedure is repeated with the remaining people, starting with the next person, going in the same direction and counting the same number of people, until only one person remains.

For example, suppose that **M = 3** and there are **N = 5** people named **A**, **B**, **C**, **D** and **E**. We count three people starting at **A**, so that **C** is eliminated first. We then begin at **D** and count **D**, **E** and back to **A**, so that **A** is eliminated next. Then we count **B**, **D** and **E**, and finally **B**, **D** and **B**, so that **D** is the one who remains last.

For this computer assignment, you are to write and implement a C++ program to simulate and solve the Josephus problem. The input to the program is the number `M` and a `list of N names`, which is clockwise ordering of the circle, beginning with the person from whom the count is to start. After each removal, the program should print the names of all people in the circle until only one person remains. However, to save printing space, print the names of the remaining people only after `K >= 1` eliminations, where `K` is also an input argument to the program. The input arguments `N`, `M` and `K` can be entered from `stdin` in the given order. (see **josephus.d** for values)

**Programming Notes:**

- Name the people in the circle in the following sequence: **A1**, **A2** ... **A9**, **B1**, **B2** ... **B9**, **C1**, **C2** ..., and start counting from the person **A1**. Enter input values `N`, `M` and `K` when the program prompts for them and use a `list<string>` container to store the names of `N` people.

- `void init_vals(list<string> &L, args &in)` It reads the input values `N`, `M` and `K` of the `struct args` in when the program prompts for them. The routine prints out those values on `stdout`, and fills the names of people in the `list L`. You can find the definition of the struct args in the header file **josephus.h**, which is defined as: 

```c++
struct args 
{
	unsigned N;
	unsigned M;
	unsigned K;
}; 
```

- `void print_list(const list<string> &L, const unsigned &cnt)` It prints out the contents of the `list L` at the beginning and after removing `K` names (each time) from the list, until only one name remains in the list, where `cnt` has an **initial value 0** and it indicates the total number of removals so far. At the end, it also prints the name of the last remaining person. For printout, **print only up to 12 names** in a single line, where the names are separated by single spaces.

- The `main()` routine first calls the routine `init_vals()` and initializes `cnt` to 0, and then calls the `print_list()` to print out the names of people in circle. After that it locates the M^th person in the list, and using the member function `erase()`, it removes that person from the list, and by calling the `print_list()` prints out the current contents of the list. This process continues (in a loop) until only one person remains in the list. 
	
	- If `i` (with initial value 0) indicates the position of a person in `list L`, then the statement: `j = (i + (M –1))%L.size()` returns the position of the M^th person from the position `i`. 
	
	- Since the argument to the `erase()` function is an iterator, you can convert the index value `j` to an iterator by the `advance(p, j)` function, where `p = L.begin()`.

- To store the names in an empty list, first change the size of the list to `N`, and then use the `generate()` function in the STL. The last argument to this function is the function object `SEQ(N)`, which is defined in the header file `josephus.h`.

**Assignment Notes:**

- Include any necessary headers and add necessary global constants.

- You are not allowed to use any I/O functions from the C library, such as scanf or printf. Instead, use the I/O functions from the C++ library, such as cin or cout.

- Add documentation to your source file (e.g. https://google.github.io/styleguide/cppguide.html#Comments).

- Prepare your Makefile (you need to construct and add Makefile) so that the TA only needs to invoke the command make to compile your source file and produce the executable file **josephus.exe**. Make sure you use exactly the same file names specified here, i.e. **josephus.cc** and **josephus.exe**, in your Makefile, otherwise your **submission will get 0 points**.

- This semester you will need to make at least three commits to your local repository and at least one push to your master repository for each assignment. This will show the evolution of your assignments over time and the thought process behind the code. You will need to make sure your final push to your master repository is completed before the assignment is due (the system time stamps actions), if the assignment is late the TA will mark off points.

- When your program is ready for grading, **commit** and **push** your local repository to remote git classroom repository and follow ***Assignment Submission Instructions***.
