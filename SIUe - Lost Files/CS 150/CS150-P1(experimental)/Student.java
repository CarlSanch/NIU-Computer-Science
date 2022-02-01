import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
/**
 * Carlos Sanchez
 * CS 150-001
 * Project 1
 * Due: 9-7-18 11:59 PM
 */
public class Student
{
   private String studentName;
   private int [] homework;
   private int numHwDone;
   
   public Student(String studentName, int numHwDone, int [] hw)
   {
       this.studentName = studentName;
       this.numHwDone = numHwDone;
       homework = hw;
   }
   
   public String getStudentName()
   {
       return studentName;
   }
   
   public int getNumHwDone()
   {
       return numHwDone;
    }
    
   public double quizAverage()
   {
       double hwAve;
       int total = 0;
       
       for(int i = 0; i < numHwDone; ++i)
       {
           total += homework[i];
        }
       
       hwAve = (double) total / numHwDone;
       return hwAve;
    }
    
}
