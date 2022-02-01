
/**
 * Carlos Sanchez
 * CS 140-003
 * Professor Tetzner
 * Assignment 4
 */
public class Date
{
    private int day;
    private int month;
    private int year;
    
    public Date(int month, int day, int year)
    {
        setMonth(month);
        setDay(day);
        setYear(year);
    }
    
    public int getMonth()
    {
        return month;
    }
    
    public int getDay()
    {
        return day;
    }
    
    public int getYear()
    {
        return year;
    }
    
    public void setMonth(int month)
    {
        if(month <= 12 && month >= 1)
        {
         this.month = month;
        }
        else
        {
         this.month = 1;
        }
    }
    
    public void setDay(int day)
    {
        if (month == 2)
            {
                if(day >= 1 && day <= 29)
                {
                    this.day=day;
                }
                else
                {
                    this.day = 1;
                }
            }
        else if (month == 4 || month == 6 || month == 9 ||  month == 11)
        {
            if (day >= 1 && day <= 30)
           {
             this.day = day;
           }
           else
           {
             this.day =  1;
           }
        }
        else if(month == 1 || month == 3 || month == 5 || month  == 7 || month == 8 || month == 10 || month == 12)
        {
            if (day >= 1 && day <= 31)
            {
                this.day = day;
            }
            else
            {
                this.day = 1;
            }
        }
 
    }
    
    public void setYear(int year)
    {
        if (year <= -1)
        {
            this.year = 1900;
        }
        else
        {
            this.year = year;
        }
    }
    
    public String toString()
    {
        String output = "";
        
        output = output + month + "/";
        output = output + day + "/";
        output = output + year;
        
        return output;
    }
    
}
