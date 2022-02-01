
/**
 * Write a description of class Main here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
public class Main
{
   
  public static Scanner kb = new Scanner(System.in);
  public static void main (String [] args)
  {
      Ride [] magicKingdom = new Ride [5];
      
      int numMKRides;
      String fileName = "rideFile.txt";
      
      numMKRides = fillParkRides(magicKingdom, fileName);
      
      putOnQueue(magicKingdom, numMKRides);
      
      numMKRides = removeRide(magicKingdom, numMKRides);
      
      // Ride ride1 = new Ride("PeterPan");
      // Ride ride2 = new Ride();
      
      // ride1.fastPass.enqueue(15);
      // ride1.fastPass.enqueue(25);
      // ride1.fastPass.enqueue(5);
      // ride1.fastPass.printQueue();
      // System.out.println(ride1.fastPass);
      
      // ride1.standBy.enqueue(75);
      // ride1.standBy.printQueue();
      
      // ride1.printRide();
      
      // System.out.println(ride1);
      // System.out.println(ride2);
      
      // System.out.println(Queue.getNumberOfQueues());
      // Queue q = new Queue();
      // System.out.println(Queue.getNumberOfQueues());
      // Queue q1 = new Queue();
      // Queue q2 = new Queue();
      
    }
    
    public static int fillParkRides(Ride [] rideArray, String fileName)
    {
        int numE = 0;
        Scanner fileIn = null;
        
        try
        {
            fileIn = new Scanner(new File(fileName));
        }
        catch (FileNotFoundException ex)
        {
            System.out.println("Error opening file" + fileName);
            System.exit(1);
        }
        
        String name;
        int cap;
        double rideLength;
        Ride ride1;
        
        while (fileIn.hasNext() && numE < rideArray.length)
        {
            name = fileIn.next();
            cap = fileIn.nextInt();
            rideLength = fileIn.nextDouble();
            
            ride1 = new Ride(name, cap, rideLength);
            
            rideArray[numE] = ride1;
            numE++;
        }
        
        fileIn.close();
        return numE;
    }
    
    
    public static int removeRide(Ride [] rideArray, int numE)
    {
        String lookfor;
        
        System.out.print("Enter Name: ");
        lookfor = kb.next();
        boolean found = false;
        int index = -1;
        
        for(int i = 0; i < numE && !found; ++i)
        {
            if (lookfor.equalsIgnoreCase(rideArray[i].getRideName()))
            {
                found = true;
                
                index = i;
            }
        }
        
        if (found)
        {
        for(int i = index; i < numE - 1; ++i)
        {
            rideArray[i] = rideArray[i+1];
            numE--;
        }
       }
       else
       System.out.println("Not Found");
       
        return numE;
    }
    
    public static void putOnQueue(Ride [] rideArray, int numE)
    {
        boolean found = false;
        int i = 0;
        String lookfor;
        int qtype;
        int howmany;
        int num;
        
        System.out.print("Enter name: ");
        lookfor = kb.next();
        
        int index = -1;
        while (!found && i < numE)
        {
            if (lookfor.equalsIgnoreCase(rideArray[i].getRideName()))
            {
                found = true;
                index = i;
            }
            ++i;
        }
        
        if (found)
        {
            System.out.print("Queue type(1-FP, 2-Stby): ");
            qtype = kb.nextInt();
            System.out.println("How many: ");
            howmany = kb.nextInt();
            // System.out.println("Found: " + rideArray[index] + " " + index);
            for(i = 0; i < howmany; ++i)
            {
                System.out.print("Enter num: ");
                num = kb.nextInt();
                if (qtype == 1)
                {
                    rideArray[index].fastpass.enqueue(num);
                }
                else
                {
                    rideArray[index].standby.enqueue(num);
                }
            }
        }
        else
        {
            System.out.println("Ride not in array!");
        }
    }
}
