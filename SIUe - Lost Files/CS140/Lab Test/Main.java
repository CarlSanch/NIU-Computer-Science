
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
public class Main
{
    public static final int MAXSIZE = 50;
    public static Scanner keyboard = new Scanner(System.in);

    public static void main(String [] args)
    {
        Circle myCirc = new Circle();
        Circle [] circArray = new Circle[MAXSIZE];

        int numCircles = fillArray(circArray);

        boolean againFlag = true;
        String selection;
        double average;
        do
        {
            System.out.printf("Choose from the following:\n");
            System.out.printf("\tA. Add a circle\n");
            System.out.printf("\tB. Remove a circle\n");
            System.out.printf("\tC. Print statistics\n");
            System.out.printf("\tD. Print circles whose center is to left of y-axis\n");
            System.out.printf("\tE. Average area of circles\n");
            System.out.printf("\tF. Exit\n");
            System.out.printf("Enter Selection: ");
            selection = keyboard.next();
            switch (selection.toUpperCase().charAt(0))
            {
                case 'A':
                    numCircles = addACircle(circArray, numCircles);
                    break;
                case 'B':
                    numCircles = removeACircle(circArray, numCircles);
                    break;
                case 'C':
                    displayStatistics(circArray, numCircles);
                    break;
                case 'D':
                    circlesLeftOfYAxis(circArray, numCircles);
                    break;
                case 'E':
                    average = averageAreaCircles(circArray, numCircles);
                    if (average != -1)
                        System.out.printf("Average of all circles is: %.2f%n", average);
                    else
                        System.out.println("There are no circles in the List");                
                    break;
                case 'F':
                    againFlag = false;
                    break;
                default:
                    System.out.printf("Invalid! Try again\n");

            }     
        } while (againFlag);        

    }
    
    public static int fillArray(Circle [] array)
    {
        String fileName;
        System.out.print("Enter the file name: ");
        fileName = keyboard.next();
        Scanner fin = null;
        try
        {
            fin = new Scanner(new File(fileName));
        }
        catch(FileNotFoundException ex)
        {
            System.out.println("File not found");
            System.exit(1);
        }

        int count = 0;
        while(fin.hasNext() && count < MAXSIZE)
        {
            array[count] = new Circle(fin.nextDouble(), fin.nextDouble(), fin.nextDouble());
            count++;
        }
        fin.close();
        return count;        
    }

    public static void displayStatistics(Circle [] array, int numE)
    {
        System.out.println("Statistics for Circles in List");
        if (numE > 0)
        {
            System.out.printf("%5s%9s%15s%15s%10s%n", "Index", "Radius", "Center", "Circumference","Area");
            for (int i = 0; i < numE; ++ i)
            {
                System.out.printf("%d.%27s%15.2f%10.2f%n", i, array[i],array[i].calculateCircumference(),array[i].calculateArea());
            }
        }
        else
            System.out.println("No Circles in List");
    }

    // Method: averageAreaCircles
    // computes and returns the average of all of the areas of the circles
    // You can assume there are circles in the array
    public static double averageAreaCircles(Circle [] array, int numE)
    {
       double aveArea;
       double total = 0;
       
       for (int i = 0; i < numE; ++i)
       {
           total = total + array[i].calculateArea();
        }
       
       aveArea = total/numE;
        
       return aveArea;
    }
    
    //Method addACircle
    // This method asks the user to type in the radius and the x and y positions
    // of a circle. It then puts the information into the last position of the array
    // You can assume there is room in the array and that the user types valid 
    // information in when asked.
    // You must use the keyboard scanner declared above (as a field)
    public static int addACircle(Circle [] array, int numE)
    {
        System.out.print("Enter the radius, x position, and y position: ");
        double radius = keyboard.nextDouble();
        double xPos = keyboard.nextDouble();
        double yPos = keyboard.nextDouble();
        
        Circle circ1 = new Circle (radius, xPos, yPos);
        numE++;
        array[numE - 1] = circ1;
        
        
        return numE;
    }





    // Method circlesLeftOfYAxis
    // This method prints all of the circles whose center are to the left
    // of the Y-axis. If there are circles in the list
    // but none to the left of the y axis, it will just print nothing.
    // [Note: use the toString in the  class to print each circle in the array]
    public static void circlesLeftOfYAxis(Circle [] array, int numE)
    {
        for (int i = 0; i < numE; ++i)
        {
        if (array[i].getXPos() <= -1)
        {
            System.out.println(array[i].toString());
        }
       }
    }



    //Method removeACircle
    // This method asks the user to type in the index of  the circle
    // to be removed. It then removes the circle at that index position
    // by shifting all the items in the array after the index entered down and subtracting
    // one from the number of elements. The number of elements is returned.
    // You may assume that the user will type in a valid index and that there is at least
    // one circles int the array.
    // You must use the keyboard scanner declared above (as a field)  
    public static int removeACircle(Circle [] array, int numE)
    {
        System.out.print("Enter the index to be removed: ");
        int choice = keyboard.nextInt();
        
        for (int i = choice; i < numE; ++i)
        {
            array[i] = array[i + 1];
        }
        numE--;
        return numE;
    }


    
}