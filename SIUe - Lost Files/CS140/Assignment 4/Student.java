
/**
 * Carlos Sanchez
 * CS 140-003
 * Professor Tetzner
 * Assignment 4
 */
public class Student
{
   public Person person;
   private String studentNum;
   private int [] quizzes;
   private int numQuizAttempts;
   
   public Student(Person person, String studentNum, int numQuizAttempts, int [] quiz)
   {
       this.person = person;
       this.studentNum = studentNum;
       this.numQuizAttempts = numQuizAttempts;
       quizzes = quiz;
   }
   
   public String getStudentNum()
   {
       return studentNum;
   }
   
   public int getNumQuizAttempts()
   {
       return numQuizAttempts;
    }
    
   public double quizAverage()
   {
       double quizAve;
       int total = 0;
       
       for(int i = 0; i < numQuizAttempts; ++i)
       {
           total += quizzes[i];
        }
       
       quizAve = (double) total / numQuizAttempts;
       return quizAve;
    }
    
   public void displayQuizzes()
   {
       
       for (int i = 0; i < numQuizAttempts; ++i)
       {
           System.out.print(quizzes[i] + " ");
        }
   }
}
