////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////

public class Employee
{
	String firstName;
	String lastName;
	int monSalary;

	public Employee(String firstName, String lastName, int monSalary)
	{
		this.firstName = firstName;
		this.lastName = lastName;
		this.monSalary = monSalary;
	}

	public static void main(String [] args)
	{

	}
		public String getFirstName()
		{
			return firstName;
		}

		public String getLastName()
		{
			return lastName;
		}

		public int getMonSalary()
		{
			return monSalary;
		}

		public void setFirstName(String firstName)
		{
			this.firstName = firstName;
		}

		public void setLastName(String lastName)
		{
			this.lastName = lastName;
		}

		public void setMonSalary(int monSalary)
		{
			if (monSalary > 0)
			{
				this.monSalary = monSalary;
			}
			else
			{
				System.out.println("Salary cannot be negative!");
			}
		}

}
