
/**
 * Carlos Sanchez
 * CS 140-003
 * Lab Section 25
 * Professor Tetzner
 */
import java.util.Scanner;
public class Main
{
    public static Scanner kb = new Scanner(System.in);

    public static void main(String [] args)
    {
        String input;
        int x1;
        int x2;
        int y1;
        int y2;
        char userChoice;
        String userInput;
        boolean changeXY;
        
        LineSegment coord0 = new LineSegment(x1, y1, x2, y2);
        
        System.out.println("Enter the x and y coordinate of the first end point: ");
        x1 = kb.nextInt();
        y1 = kb.nextInt();
        
        System.out.println("Enter the x and y coordinate of the second end point: ");
        x2 = kb.nextInt();
        y2 = kb.nextInt();
        
        System.out.print("Line Segment: " + coord0.print);
        System.out.println("The length of the line segment is: " + coord0.computeLength);
        System.out.println("the line segment " + coord0.determineQuadrant);
        
        System.out.println("Would you like to enter another line segment (y/n): ");
        userInput = kb.next();
        userChoice = userInput.charAt(0);
        
        do
        {
         LineSegment coord1 = new LineSegment(x1, y1, x2, y2);
         x1 = kb.nextInt();
         x2 = kb.nextInt();
         y1 = kb.nextInt();
         y2 = kb.nextInt();
         
         System.out.println("Enter the x and y coordinate of the first end point: ");
         x1 = kb.nextInt();
         y1 = kb.nextInt();
        
         System.out.println("Enter the x and y coordinate of the second end point: ");
         x2 = kb.nextInt();
         y2 = kb.nextInt();
        
         System.out.print("Line Segment: " + coord0.print);
         System.out.println("The length of the line segment is: " + coord0.computeLength);
         System.out.println("the line segment " + coord0.determineQuadrant);
        
         System.out.println("Would you like to enter another line segment (y/n): ");
         userInput = kb.next();
         userChoice = userInput.charAt(0);
        } while (userChoice == 'y');
        
        if( userChoice == 'n')
        {
            
            System.out.println("You entered a total of " +  + " line segments");
        }
        // this variable used to allow the 
                      // use to type Y or N when asked about
                      // changing point 
        // As you develop your program, add any variables
        // you may need here 

       
        
        // Declare an object of the Line Segment class
        // Use the constructor with no formal parameters 



        // You are to finish the rest of main to create the output given. 
        // This program will also have a method called enterLineSegmentEndPoints
        // that allows the user to enter the end points of a line segment. The header
        // for the method is given below main.
        // Declare any variables you may need in the section above
        // Some suggestions might be:
        // First get the loop going that will continue asking if there is
        // another line segment until the user types in anything other than Y
        // Next get the method to enter the endpoints working - see output for formatting
        // Then compute the length of the line segment using the method you wrote in the class
        // Next for the quadrant, you might want to store the string returned from the method 
        // class and then check the first character to determine what to print
        // Finally put in the code that will print the total number of line segments
        // entered after the user indicates they are done.

        // NOTE: Get little pieces to work at a time - do NOT type it all in at once











     }

     // Add the code to this method wrapper so that it allows the user to enter the 
     // end points of the line segments as shown on the output
     public static void enterLineSegmentEndPoints(LineSegment line)
     {

     }

}
