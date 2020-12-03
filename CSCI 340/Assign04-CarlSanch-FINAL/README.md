# CSCI340 - Word Scanner
For this computer assignment, you are to write and implement an interactive C++ program to scan and process a stream of words of a plain text.

Your program should start with an empty list of words. (Combinations of blanks, tabs, and newline characters to separate words.) After reading each word from the input stream, check the word for punctuation marks:

- if the first letter of the word is preceded or the last letter is followed by punctuation marks, delete punctuation marks from the word
- if a word contains punctuation marks in the middle, ignore the letters beyond these punctuation marks

*For example*, if the word is **fish,** (fish comma) then the resulting word should be **fish** however, if the word is **fish_net** then the resulting word would be **fish**.

**Programming Notes:**

1. Use a [map container](http://www.cplusplus.com/reference/map/map/) to store the words, where each word is represented by a `pair<string, int>`. The first element of the [pair](http://www.cplusplus.com/reference/utility/pair/?kw=pair), named `first`, contains the name of the input word, and the second element of the pair, named `second`, contains its frequency in the input stream. To use a map container in your program, insert the statement: `#include <map>` in your header file, and to use the functions in the STL, also insert the statement: `#include <algorithm>`in your header file.

2. In addition to the `main()` routine, implement the following subroutines in your program:
    - `void get_words(map<string, int>&)` - it gets a word from the input stream and removes its punctuation marks
    - `void print_words(const map<string, int>&)` - it prints the final list of words and their frequencies, it also prints the number of nonempty words and the number of distinct words in the input stream
    - `void clean_entry(const string&, string&)` - it cleans a word from its punctuation marks, the first argument is the original word in the input stream and the second argument contains the same word after cleaning

3. The `main()` routine calls the subroutine `get_words()` to get words from the input stream. To clean an individual word from its punctuation marks, `get_words()` calls the subroutine `clean_entry ()`.

4. You can check the size of the [string](http://www.cplusplus.com/reference/string/string/?kw=string) returned by `clean_entry` using the member function `length()`. For string `s`, the statement `s.length()` returns the total number of characters in `s`. If the returned length is 0 (i.e., the original word contains nothing but punctuation marks), simply ignore the word and read in the next one.

5. Use a map container to store the cleaned words (but not the empty words). The statement  `m[s]++` copies the string `s` into map `m` and updates its frequency. Remember a map keeps only one copy of each individual item (in sorted order) specified in its first argument key and stores its frequency in its second argument value. When key is used as an index to a map, it returns the corresponding value in the map.

6. You can implement the subroutine `clean_entry()` as follows:
    - Initialize an index variable to indicate the first character in a word, and then scan the word until an alphanumeric character is found. You can use the C library function `isalnum()` to check a character in the input string. If the character is alphanumeric, this function returns true; otherwise, it returns false. Initialize another index variable for this position and continue scanning the word until the first punctuation mark. If the word does not contain any alphanumeric characters, you must stop scanning the word when you reach the end of the word. An alternative approach to find the values of these two index variables is to use the function `find_if()` in the STL. In this case, you need to have two predicates: one of them returns true if a character is alphanumeric but the other one returns true if the character is non-alphanumeric, and each of these predicates can be used as the third argument to `find_if()` function. 
    - At this point you have two index variables; the first one indicates the position of the first alphanumeric character and the second one indicates the position just after the last alphanumeric character. If the word does not have any alphanumeric characters, then both index values indicate the same position.
    - Copy the word from the first alphanumeric character until the last one to another string. Use the member function `substr()` for this task. For string `s`, the statement `s.substr(pos, len)` returns the substring from `s`, where the index value `pos` indicates the starting position of the substring and `len` specifies its size.
    - Finally, convert all capital letters in the cleaned word to lowercase letters. You can convert a character to lowercase by the C library function `tolower()`. Instead of using a loop for this task, try to use the function `for_each()` in the STL, where you need to have a unary function as the third argument to `for_each()` function.

7. Print the number of nonempty words in the input stream and the number of distinct words. You can obtain the number of elements in a map by the member function `size()`. Also print the contents of your map name of each word and its frequency (`NO_ITEMS` words per line and the words are left aligned). To allocate certain number of spaces for an output value, use the manipulator: `setw(ITEM_W)`, and for its left alignment, use the [manipulator left](http://www.cplusplus.com/reference/ios/left/) in your `cout` statement. In your program, use `NO_ITEMS = 3` and `ITEM_W = 16`. For printing, the `main()` routine calls the subroutine `print_words()`.

8. Create a Makefile that builds an executable `assignment04.exe`, to test your program execute your program as `./assignment04.exe < assignment04.in`. This will redirect the content of `assignment04.in` as standard input for your code.  You can compare results with standard output from assignment found in `results04.out`. 

**Assignment Notes:**

* Include any necessary headers and add necessary global constants. 

* You are not allowed to use any I/O functions from the C library, such as `scanf` or `printf`. Instead, use the I/O functions from the C++ library, such as `cin` or `cout`.

* Add documentation to your source file (e.g. https://google.github.io/styleguide/cppguide.html#Comments).

* Prepare your Makefile (**you need to construct and add Makefile**) so that the TA only needs to invoke the command `make` to compile your source file and produce the executable file `assignment04.exe`.  Make sure you use exactly the same file names specified here, i.e. `assignment04.cc` and `assignment04.exe`, in your `Makefile`. Otherwise your submission will get 0 points.

This semester you will need to make at least ***three commits*** to your local repository and at least one push to your master repository for each assignment. This will show the evolution of your assignments over time and the thought process behind the code. You will need to make sure your final ***push*** to your master repository is completed before the assignment is due (the system time stamps actions), if the assignment is late the TA will mark off points.

When your program is ready for grading, ***commit*** and ***push*** your local repository to remote git classroom repository and follow _**Assignment Submission Instructions**_.
