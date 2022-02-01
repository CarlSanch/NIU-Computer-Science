
/**
 * Write a description of class Circle here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Circle
{
   private double radius;
   private double xPos;
   private double yPos;
   
   public Circle()
   {
       
    }
    
   public Circle (double newRadius)
   {
       radius = newRadius;
    }
    
   public Circle (double radius, double xPos, double yPos)
   {
       this.radius = radius;
       this.xPos = xPos;
       this.yPos = yPos;
    }
    
   public void setRadius(double newRadius)
   {
       radius = newRadius;
    }
    
   public void setXPos( double newXPos)
   {
       xPos = newXPos;
    }
    
   public void setYPos(double newYPos)
   {
       yPos = newYPos;
    }
    
   public double getRadius()
   {
       return radius;
    }
    
   public double getXPos()
   {
       return xPos;
    }
    
   public double getYPos()
    {
        return yPos;
    }
    
   public double calculateArea()
   {
       double area;
       
       area = Math.PI * Math.pow(radius, 2);
       
       return area;
    }
    
   public double calculateCircumference()
   {
       double circum;
       
       circum = 2 * Math.PI * radius;
       
       return circum;
    }
    
   public String toString()
   {
    String point = String.format("(%4.1f, %4.1f)",xPos, yPos);
    return String.format("%10.1f%15s", radius, point);
   }
}
