
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Main
{
    public static Scanner keyboard = new Scanner(System.in);
    public static final int MAXSIZE = 15;

    public static void main(String [] args)
    {
        VBSpikeInfo cougars[];
        cougars = new VBSpikeInfo[MAXSIZE];

        int numElements;
        double average;

        numElements = fillArray(cougars);

        average = findKillsAverage(cougars, numElements);

        printResults(cougars, numElements, average);


    }
    
    public static int fillArray(VBSpikeInfo [] array)
    {
        int numE = 0;
        Scanner fileIn = null;
        System.out.println("Enter the name of the file: ");
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
            String name = fileIn.next();
            int attempt = fileIn.nextInt();
            int kill = fileIn.nextInt();
            int err = fileIn.nextInt();
            VBSpikeInfo info = new VBSpikeInfo(name, attempt, kill, err);
            array[numE] = info;
            numE++;
        }
        return numE;
    }

    public static double findKillsAverage(VBSpikeInfo [] cougars, int numE)
    {
       int total = 0;
       double average;
       
       for (int i = 0; i <numE; ++i)
       {
           total = total + cougars[i].getKills();
        }
       average = (double) total / numE;
       return average;
    }
   // Implement printResults
    public static void printResults(VBSpikeInfo [] cougars, int numElements, double average)
    {
        String stuff;
        System.out.printf("Average spikes that were kills: %.2f%n", average);
        System.out.printf("%-16s%9s%10s%15s%n", "Player Name", "Attempted", "Kills", "Percent Kills");
        for (int i = 0; i < numElements; i++)
        {
            stuff = cougars[i].toString();
            System.out.print(stuff + "\n");
        }
        
    }



}