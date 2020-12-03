# CS340 Parking Garage

The Scratchemup Parking Garage contains a single lane that holds up to ten cars. Cars arrive at the south end of the garage and leave from the north end. If a customer arrives to pick up a car that is not the northernmost, all cars to the north of the car moved out, the car is driven out, and the other cars are restored in the same original order.

Write a program in C++ (**parking.cc**) that reads a group of input lines. Each line contains an **A** for **arrival** or a **D** for **departure**, which is terminated by a **:**, and a **license plate number**, which is terminated by a **:**. The program should print a message each time a car arrives or departs. When a car arrives, the message should specify when the garage is full. If there is no room for a car, the car simply leaves. When a car departs, the message should include the number of times the car was moved within the garage, including the departure itself but not the arrival.

For a departure, you need to check if the car is in the garage. If it’s not, print an error message and ignore the departure. When a car arrives and if the garage is not full, create a **C/C++ structure object** for the car that contains the `id number` (*starts with 1*), the `license plate number`, and the `number of times the car was moved` within the garage (*with initial value 0*), and insert this structure object in a **deque** container. When a car departs, delete the corresponding structure object from the deque.

To save the original ordering of the cars that are moved out from the deque to open the way for a departing car, define a *stack* container to temporarily put the moved cars in the stack, and after the departing car, retrieve all cars from the stack back to the deque into their original positions.

**Programming Notes:**

- To keep all necessary information for a car, define the following structure: 

```c++
typedef struct 
{ 
    int id;         // id starts at 1
    string lp;      // license plate of car
    int no_mv;      // number times the car has been moved
}CAR; 
```

- In addition to the `main()` routine, implement the following subroutines in your program:

    - `void get_input_vals(const string &line, char &act, string &lp)` Extracts individual components from the input line line, where `act` indicates if the line corresponds to *an arrival* or *a departure* event, and `lp` is the *license plate number* of the arriving/departing car.
    - `void arrival(const CAR &car, deque<CAR> &D)` Prints a message stating that a car is arrived. It gets the id number and the license plate number of the car from the car object, and in the message, species those values. If the garage is not full, inserts the car object in the `deque D`; otherwise, prints a message stating that “*the garage is full!*”.
    - `void departure(const string &lp, deque<CAR> &D, stack<CAR> &S)` Prints a message stating that the car with the license plate number `lp` is departed, and in that message specifies the number of times the car was moved within the garage. For every car moved from the deque `D` to the stack `S` and back to `D`, it updates the value `no_mv` in the CAR object of that car.
    
- The `main()` routine gets the input data from the stdin, line by line. For each input line, it calls the subroutine `get_input_vals()` to extract the character act, which indicates an arrival or departure, and the license plate number. If **act is not** the character ‘**A**’ or ‘**D**’, prints an error message indicating the invalid action. For an arrival, it fills the individual components in a Car object and calls the function `arrival()` to process the arrival. For a departure, it calls the function `departure()` to process the departure.

- Create a Makefile that builds an executable **parking.exe**, to test your program execute your program as `./parking.exe < parking.in`. This will redirect the content of **parking.in** as standard input for your code.

- Output results to a file named **parking.out** and add to your repository.

- You can find the correct output of this program in the output file **parkingresults.out** in your repository. You can compare two output files by executing `diff parkingresults.out parking.out`.

**Assignment Notes:**

- Include any necessary headers and add necessary global constants.

- You are not allowed to use any I/O functions from the C library, such as scanf or printf. Instead, use the I/O functions from the C++ library, such as cin or cout.

- Add documentation to your source file (e.g. https://google.github.io/styleguide/cppguide.html#Comments).

- Prepare your Makefile (you need to construct and add Makefile) so that the TA only needs to invoke the command make to compile your source file and produce the executable file **parking.exe**. Make sure you use exactly the same file names specified here, i.e. **parking.cc** and **parking.exe**, in your Makefile, otherwise your **submission will get 0 points**.

- This semester you will need to make at least three commits to your local repository and at least one push to your master repository for each assignment. This will show the evolution of your assignments over time and the thought process behind the code. You will need to make sure your final push to your master repository is completed before the assignment is due (the system time stamps actions), if the assignment is late the TA will mark off points.

- When your program is ready for grading, **commit** and **push** your local repository to remote git classroom repository and follow ***Assignment Submission Instructions***.
