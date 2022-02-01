

public class DriverTest
{
	public static void main(String [] args)
	{
		Employee emp1 = new Employee("Technology", "Evo", 2400);
		Employee emp2 = new Employee("Colby", "Jack", 4000);

		System.out.println(emp1.getFirstName() + "'s current yearly salary is " + (emp1.getMonSalary() * 12));
		System.out.println(emp1.getFirstName() + "'s new yearly salary is " + ((emp1.getMonSalary() * 12) + ((emp1.getMonSalary() * .10) *12)));
		
		System.out.println(emp2.getFirstName() + "'s current yearly salary is " + (emp2.getMonSalary() * 12));
		System.out.println(emp2.getFirstName() + "'s new yearly salary is " + ((emp2.getMonSalary() * 12) + ( (emp2.getMonSalary() * .10) * 12)));

		Date dte1 = new Date(3, 20, 2015);
		Date dte2 = new Date(5, 12, 2000);

		System.out.println();
		dte1.displayDate();
		dte2.displayDate();

	}
}
