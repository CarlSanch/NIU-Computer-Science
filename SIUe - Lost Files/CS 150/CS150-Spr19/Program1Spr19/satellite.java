
/**
 * Carlos Sanchez
 * Cs 150 - 002
 * Spring 2019
 * Program 1: Due Feb. 1st 
 */
public class satellite
{
    private String satName;
    private int numOfSats;
    public coordinates [] coord;
    
    public satellite(String satName, int numOfSats, coordinates [] coord)
    {
        this.satName = satName;
        this.numOfSats = numOfSats;
        this.coord = coord;
    }
    
    public String getSatName()
    {
        return satName;
    }
    
    public int getNumOfSats()
    {
        return numOfSats;
    }
    
    
}
