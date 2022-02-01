
/**
 * Write a description of class Queue here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Queue
{
    private int [] elements;
    private int size;
    private int head;
    private int tail;
    private static int numOfQueues = 0;
    public Queue()
    {
        elements = new int [10];
        tail = 0;
        head = 0;
        size = 0;
        numOfQueues++;
    }
    
    public Queue(int size)
    {
        elements = new int [size];
        tail = 0;
        head = 0;
        this.size = size;
    }
    
    public int getQueueLength()
    {
        return tail;
    }
    
    public int getQueueMaxSize()
    {
        return size;
    }
    
    public static int getNumberOfQueues()
    {
        return numOfQueues;
    }
    
    public void enqueue(int num)
    {
        if (tail < size)
        {
            elements [tail] = num;
            tail++;
        }
        else 
        {
            System.out.println("Queue Full");
        }
    }
    
    public void dequeue()
    {
        if (!isEmpty());
        for (int i = 0; i < tail - 1; ++i)
        {
           elements[i] = elements[1 + 1];
           tail--;
        }
    }
    
    public void printQueue()
    {
        for (int i = 0; i < tail; ++i)
        {
        System.out.print(elements[i] + " ");
        }
        System.out.println(" ");
    }
    
    public int inFront()
    {
        if (!isEmpty())
        {
            return elements[0];
        }
        else
        return -1;
    }
    
    public boolean isEmpty()
    {
        if (tail ==0)
            return true;
            else
            return false;
            
    }
    
    // public String toString()
    // {
        
    // }
}
