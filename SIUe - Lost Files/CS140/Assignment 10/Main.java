
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Main
{
    public static final int MAX_ORDERS = 100;
    public static Scanner keyboard = new Scanner (System.in);

    public static void main(String [] args)
    {
        EggOrder [] novemberOrders = new EggOrder [MAX_ORDERS];
        int numElements;

        numElements = fillArray(novemberOrders);

        printReport(novemberOrders, numElements);

    }

    // fillArray method
    // This method asks the user to type in the file to be loaded into the array
    // and makes sure it opens correctly. If it doesn't open correctly, it should
    // print the message "File not found" and then exit the program. The method
    // will then read the information from the file and create an Eggorder object 
    // put it into the array. The method returns the number of orders that were 
    // read in
    public static int fillArray(EggOrder [] novemberOrders)
    {
        int numE = 0;
        Scanner fileIn = null;
        System.out.println("Enter the name of the file: ");
        try
        {
            fileIn = new Scanner(new File(keyboard.next()));
        }
        catch (FileNotFoundException e)
        {
            System.out.println("File not found!");
            System.exit(1);
        }
        while (fileIn.hasNext() || fileIn.hasNextInt())
        {
            String name = fileIn.next();
            int number = fileIn.nextInt();
            EggOrder order = new EggOrder(name, number);
            novemberOrders[numE] = order;
            numE++;
        }
        return numE;
    }

    // printReport
    // Prints the report as shown below
    public static void printReport(EggOrder [] novemberOrders, int numElements)
    {
        System.out.printf("%-24s%-10s%-16s%-10s%n", "Name", "Dozens", "Individuals", "Total Eggs");
        int total = 0;
        for (int i = 0; i < numElements; i++)
        {
            System.out.printf("%-24s%6d%15d%15d%n", novemberOrders[i].getCustomerName(), novemberOrders[i].getNumDoz(), novemberOrders[i].getNumExtra(), novemberOrders[i].getTotalEggs());
            total = total + novemberOrders[i].getTotalEggs();
        }
        System.out.print("Total eggs sold this month: " + total);
    }
}