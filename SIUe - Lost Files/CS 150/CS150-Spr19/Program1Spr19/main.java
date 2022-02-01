
/**
 * Carlos Sanchez
 * Cs 150 - 002
 * Spring 2019
 * Program 1: Due Feb. 1st 
 */

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
public class main
{
    public static final int MAXSIZE = 999;
    public static void main(String [] args)
    {
        String fileName = "satellites.txt";
        satellite [] satGroup = new satellite [MAXSIZE];
   
        loadArray(fileName);
    }

    public static void loadArray(String fileName)
    {
        int i = 0;
        Scanner fileIn = null;
        System.out.println("Now looking for file name: satellites");
        try
        {
            fileIn = new Scanner(new File(fileName));
        }
        catch (FileNotFoundException ex)
        {
            System.out.println("File not found!");
            System.exit(1);
        }
        
        while (fileIn.hasNext() || fileIn.hasNextInt())
        {   
            int numE = 0;
            String satelliteName = fileIn.next();
            int numOfSatellites = fileIn.nextInt();
            
            coordinates [] satArray = new coordinates[numOfSatellites];
            //insert array here
            while(fileIn.hasNextInt())
            {
                int x = fileIn.nextInt();
                int y = fileIn.nextInt();
                satArray[numE] = new coordinates(x, y);
                numE++;
            }
            //create a new satellite here to store all info
            satellite sat1;
            
            sat1 = new satellite(satelliteName, numOfSatellites, satArray);
            
            displaySatellites(sat1, numE);
        }
        
        fileIn.close();
    }
    
    //will display everything for the output
    public static void displaySatellites(satellite sat1, int numE)
    {
        System.out.println("Group Name: " + sat1.getSatName()); 
        System.out.println("Number of Satellites: " + sat1.getNumOfSats());
        System.out.printf("%-15s%-22s%13s%n", "#", "X", "Y");
        for(int i = 0; i < numE; i++)
        {
            System.out.printf("%-15s%-22s%13s%n", i, sat1.coordinates.getXCoord(), sat1.coordinates.getYCoord());
        }
        System.out.println("");
        System.out.println("Results for distances:");
        for (int i = 0; i < numE; i++)
        {
           //Call getSatDistance method, do a loop to traverse all satellites in array
           
           System.out.printf("");
        }
        System.out.println("");
        System.out.println("Results for angles:");
        for (int i = 0; i < numE; i++)
        {
            //Call getSatAngle method, do a loop to traverse all the satellites in array
            
            System.out.printf("");
        }
        System.out.println("");
        System.out.println("Closest pair: "); //call satDistance
        System.out.println("Farthest pair: "); //call satDistance
    }
    
    //will need to call two different satellites in parameter
    //This method will have to print all the distances
    public double satDistance(satellite sat1)
    {
        double satelliteDistance = 0;
        int x1;
        int y1;
        int x2;
        int y2;
        
        satelliteDistance = Math.sqrt((Math.pow(x1-x2, 2)) + (Math.pow(y1 - y2, 2)));
        
        return satelliteDistance;
    }
    
    public double satDistanceMax(satellite sat1)
    {
        double satelliteDistance = 0;
        int x1;
        int y1;
        int x2;
        int y2;
        
        satelliteDistance = Math.sqrt((Math.pow(x1-x2, 2)) + (Math.pow(y1 - y2, 2)));
        
        return satelliteDistance;
    }
    
    //will need to call 2 satellites in parameter;
    //this method will have to print all the angles
    public double satAngle(satellite sat1)
    {
        double satelliteAngle = 0;
        int x1;
        int y1;
        int x2;
        int y2;
        
        satelliteAngle = Math.atan2(y2 - y1, x2 - x1) * 180 / Math.PI;
        
        return satelliteAngle;
    }
    
    public double satAngleMax(satellite sat1)
    {
        double satelliteAngle = 0;
        int x1;
        int y1;
        int x2;
        int y2;
        
        satelliteAngle = Math.atan2(y2 - y1, x2 - x1) * 180 / Math.PI;
        
        
        
        return satelliteAngle;
    }
    
    
}
