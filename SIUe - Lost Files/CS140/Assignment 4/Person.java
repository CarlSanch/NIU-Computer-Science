
/**
 * Carlos Sanchez
 * CS 140-003
 * Professor Tetzner
 * Assignment 4
 */
public class Person
{
    private String firstName;
    private String lastName;
    public Date dateOfBirth;
    
    public Person(String firstName, String lastName, Date dateOfBirth)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.dateOfBirth = dateOfBirth;
    }
    
    public String getFirstName()
    {
        return firstName;
    }
    
    public String getLastName()
    {
        return lastName;
    }
    
    public Date getDateOfBirth()
    {
        return dateOfBirth;
    }
    
    public void setFirstName(String fname)
    {
        firstName = fname;
    }
    
    public void setLastName(String lname)
    {
        lastName = lname;
    }
    
    public void setDateOfBirth(Date dob)
    {
       dateOfBirth = dob;
    }
    
    public void setDateOfBirth(int month, int day, int year)
    {
        dateOfBirth = new Date(month, day, year);
        dateOfBirth.setMonth(month);
        dateOfBirth.setDay(day);
        dateOfBirth.setYear(year);
    }
}
