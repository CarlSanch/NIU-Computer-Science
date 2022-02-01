
/**
 * Write a description of class EggOrder here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class EggOrder
{
    String customerName;
    int numDoz;
    int numExtra;
    final int DOZEN = 12;
    
    public EggOrder()
    {
        
    }
    
    public EggOrder(String name, int numDoz, int numExtra)
    {
        customerName = name;
        this.numDoz = numDoz;
        this.numExtra = numExtra;
    }
    
    
    public EggOrder(String name, int totalEggs)
    {
        customerName = name;
        numDoz = totalEggs / DOZEN;
        numExtra = totalEggs % DOZEN;
    }
    
    public String getCustomerName()
    {
        return customerName;
    }
    
    public int getNumDoz()
    {
        return numDoz;
    }
    
    public int getNumExtra()
    {
        return numExtra;
    }
    
    public int getTotalEggs()
    {
        int totalEggs;
        
        totalEggs = (numDoz * DOZEN) + numExtra;
        
        return totalEggs;
    }
}
