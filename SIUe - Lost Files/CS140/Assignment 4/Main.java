



import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
/**
 * Carlos Sanchez
 * CS 140-003
 * Professor Tetzner
 * Assignment 4
 */
public class Main
{
    public static Scanner keyboard = new Scanner(System.in);
    public static final int MAX_CLASS_SIZE = 100;
    
    public static void main(String [] args)
    {           
        int num140Students;
        String lastNameSearchFor;
        Student [] cs140Class = new Student [MAX_CLASS_SIZE];
        String fileName;
        
        System.out.print("Enter the class file name: ");
        fileName = keyboard.next();
        // fileName = "cs140Data.txt"; // might want to uncomment for testing purposes
        num140Students = loadArray(cs140Class, fileName);
        
        System.out.println("\nPrints all students' numbers, names, and birthdays ");
        printStudentReport(cs140Class, num140Students);
        
        System.out.println("\n\nPrints all students in class with their average");
        printClassReport(cs140Class, num140Students);
        
        System.out.println("\n\nAsk user to type last name and print the student information and average");
        System.out.println("If more than one with same last name it will print them all");
        System.out.println("If the name isn't there, it will print - Not Found");
        System.out.print("Enter last name: ");
        lastNameSearchFor = keyboard.next();
        searchAndPrintStudent(cs140Class, num140Students, lastNameSearchFor);
        
        System.out.println("\n\nSort by student number and print");
        sortClass(cs140Class, num140Students);
        printStudentReport(cs140Class, num140Students);
        
        System.out.println("\n\nPrint Quiz Report");
        printQuizReport(cs140Class, num140Students);
        
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
        
        Student stud1;
        Person person1;
        Date date1;
        
        while (fileIn.hasNext() || fileIn.hasNextInt())
        {
            String firstName = fileIn.next();
            String lastName = fileIn.next();
            String idNum = fileIn.next();
            int day = fileIn.nextInt();
            int month = fileIn.nextInt();
            int year = fileIn.nextInt();
            int numAttempts = fileIn.nextInt();
            
            int [] quizzes = new int [10];
            while (fileIn.hasNextInt())
            {
               int numQ = 0;
               quizzes[numQ] = fileIn.nextInt();
               numQ++;
            }
            
            
            date1 = new Date(month, day, year);
            person1 = new Person(firstName, lastName, date1);
            stud1 = new Student(person1, idNum, numAttempts, quizzes);
            
            
            
            numE++;
        }
        
        fileIn.close();
        return numE;
    }
    
    public static void printQuizReport(Student [] array, int numStudents)
    {
       System.out.printf("%-20s%-20s%-11s%n", "Student Name", "Number of Attempts", "Quiz Grades");
       for (int i = 0; i < numStudents; ++i)
       {
           String fullName = array[i].person.getLastName() + "," + array[i].person.getFirstName();
           System.out.printf("%-20s%-23d", fullName, array[i].getNumQuizAttempts());
           array[i].displayQuizzes();
           System.out.println();
        }
    }
    
    public static void printClassReport(Student [] array, int numStudents)
    {
        System.out.printf("%-19s%16s%15s%n", "Student Name", "Student Number", "Quiz Average");
        for (int i = 0; i < numStudents; ++i)
        {
            String name = array[i].person.getLastName() + "," + array[i].person.getFirstName();
            System.out.printf("%-19s%16s%15.2f%n", name, array[i].getStudentNum(), array[i].quizAverage());
            
        }
    }
    
     public static void printStudentReport(Student [] array, int numStudents)
    {
        System.out.printf("%-15s%-22s%13s%n", "Student Number", "Student Name", "Date of Birth");
        for (int i = 0; i < numStudents; ++i)
        {
            String fullName = array[i].person.getLastName() + array[i].person.getFirstName();
            System.out.printf("%-15s%-22s%13s%n", array[i].getStudentNum(), fullName, array[i].person.getDateOfBirth());
            
        }
   }
    
    public static void searchAndPrintStudent(Student [] array, int numStudents, String lookfor)
    {
        boolean found = false;
       
        for (int i = 0; i < numStudents; ++i)
        {
            if (lookfor.equalsIgnoreCase(array[i].person.getLastName()))
            {
                found = true;
                String fullName = array[i].person.getLastName() + "," + array[i].person.getFirstName();
                System.out.printf("%-30s%5.2f%n", fullName, array[i].quizAverage());
            }
        }
        if (found == false)
        {
            System.out.println("Not Found");
        }
    }
    
    public static void sortClass(Student [] array, int numStudents)
    {
        
    }
    
}