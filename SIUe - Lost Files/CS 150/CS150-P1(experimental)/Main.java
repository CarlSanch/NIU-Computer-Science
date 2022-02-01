import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
/**
 * Carlos Sanchez
 * CS 150-001
 * Project 1
 * Due: 9-7-18 11:59 PM
 */
public class Main
{
    public static Scanner keyboard = new Scanner(System.in);
    
    public static void main(String [] args)
    {
        int num140Students;
        String lastNameSearchFor;
        Student [] cs140Class = new Student [100];
        String fileName;
        
        System.out.print("Enter the class file name: ");
        fileName = keyboard.next();
        // fileName = "cs140Data.txt"; // might want to uncomment for testing purposes
        num140Students = loadArray(cs140Class, fileName);
    }
    
    public static int loadArray(Student [] array, String fileName)
    {
        int numE = 0;
        int i = 0;
        Scanner fileIn = null;
        System.out.println("Enter then name of the file: ");
        try
        {
            fileIn = new Scanner(new File(keyboard.next()));
        }
        catch (FileNotFoundException ex)
        {
            System.out.println("File not found!");
            System.exit(1);
        }
        
        
        while (fileIn.hasNext() || fileIn.hasNextInt())
        {
            String firstName = fileIn.next();
            String lastName = fileIn.next();
            
            int [] homework = new int [10];
            while (fileIn.hasNextInt())
            {
               int numQ = 0;
               homework[numQ] = fileIn.nextInt();
               numQ++;
            }
            
            int [] programs = new int [6];
            while (fileIn.hasNextInt())
            {
               int numQ = 0;
               programs[numQ] = fileIn.nextInt();
               numQ++;
            }
            
            int test1 = fileIn.nextInt();
            int test2 = fileIn.nextInt();
            
            int finalExam = fileIn.nextInt();
           
            numE++;
        }
        
        fileIn.close();
        return numE;
    }
}
