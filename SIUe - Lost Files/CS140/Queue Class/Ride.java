
/**
 * Write a description of class Ride here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Ride
{
    private String rideName;
    private int capacity;
    private double rideLength;
    public Queue fastpass;
    public Queue standby;
    
    public Ride()
    {
        rideName = "xxx";
        capacity = 0;
        rideLength = 0;
        fastpass = new Queue();
        standby = new Queue();
    }
    
    public Ride (String rideName)
    {
        this.rideName = rideName;
        capacity = 0;
        rideLength = 0;
        fastpass = new Queue();
        standby = new Queue();
    }
    
    public Ride (String rideName, int capacity, double rideLength)
    {
        this.rideName = rideName;
        this.capacity = capacity;
        this.rideLength = rideLength;
        fastpass = new Queue();
        standby = new Queue();
    }
    
    public void setRideName(String rideName)
    {
        this.rideName = rideName;
    }
    
    public void setCapacity(int capacity)
    {
        this.capacity = capacity;
    }
    
    public void setRideLength(double rideLength)
    {
        this.rideLength = rideLength;
    }
    
    public String getRideName()
    {
        return rideName;
    }
    
    public int getCapacity()
    {
        return capacity;
    }
    
    public double getRideLength()
    {
        return rideLength;
    }
    
    public void printRide()
    {
        System.out.println("Ride Name: " + rideName);
        System.out.println("Capacity: " + capacity + "\tRide Length: " + rideLength);
        System.out.println("Fast Pass Queue");
        fastpass.printQueue();
        System.out.println("Stand By Queue:");
        standby.printQueue();
    }
    
    public String toString()
    {
        String output = "";
        String formatted = String.format("%.2f", rideLength);
        output = output +"Ride Name: " + rideName + "\n";
        
        output = output + "Capacity: " + capacity + "\tRide Length: " + rideLength + "\n";
        output = output + "Fast Pass Queue" + fastpass + "\n";
        output = output + "Stand By Queue:" + standby;
        
        return output;
    }
}
