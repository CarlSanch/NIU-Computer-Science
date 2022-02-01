
/**
 * Carlos Sanchez
 * CS 140-003 
 * Lab Section 21
 * Professor Tetzner
 */
public class LineSegment
{
    private int x1;
    private int y1;
    private int x2;
    private int y2;

    public LineSegment()
    {
    }
    public LineSegment(int x1, int y1, int x2, int y2)
    {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;

    }
    public void setPoint1(int x, int y)
    {
        this.x1 = x;
        this.y1 = y;
    }
    public void setPoint2(int x, int y)
    {
        this.x2 = x;
        this.y2 = y;
    } 
    public int getPoint1X()
    {
        return x1;
    }
    public int getPoint1Y()
    {
        return y1;
    }
    public int getPoint2X()
    {
        return x2;
    }
    public int getPoint2Y()
    {
        return y2;
    }        
    public String determineQuadrant()
    {
        String quadRet;
        if ((x1 > 0)&&(y1 > 0))
        {
            quadRet = "is completely in Quadrant 1";
            System.out.println(quadRet);
        }
        else if ((x1 > 0)&&(y1 < 0))
        {
            quadRet = "is completely in Quadrant 4";
            System.out.println(quadRet);
        }
        else if (( x1 < 0)&&(y1 > 0))
        {
            quadRet = "is completely in Quadrant 2";
            System.out.println(quadRet);
        }
        else if (( x1 < 0)&&(y1 < 0))
        {
            quadRet = "is completely in Quadrant 3";
            System.out.println(quadRet);
        }
        else if ((x2 > 0)&&(y2 > 0))
        {
            quadRet = "is completely in Quadrant 1";
            System.out.println(quadRet);
        }
        else if ((x2 > 0)&&(y2 < 0))
        {
            quadRet = "is completely in Quadrant 4";
            System.out.println(quadRet);
        }
        else if (( x2 < 0)&&(y2 > 0))
        {
            quadRet = "is completely in Quadrant 2";
            System.out.println(quadRet);
        }
        else if (( x2 < 0)&&(y2 < 0))
        {
            quadRet = "is completely in Quadrant 3";
            System.out.println(quadRet);
        }
        else
        {
            quadRet = "Crosses an Axis";
            System.out.println(quadRet);
        }
        return quadRet;
    }
    public double computeLength()
    {
        double lineDist;
        lineDist = Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
        return lineDist;
    }
    //Prints the point in the format (x1, y1) to (x2, y2)
    public void print()
    {
        System.out.print("(" + x1 + ", " + y1 + ") to (" + x2 + ", " + y2 + ")");
    }
}    