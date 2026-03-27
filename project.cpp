#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int emp_count = 0;
int total_days = 22;

struct employee
{
	string id;
	string name;
	string designation;
	int basic_salary;
	string joining_date;
};

struct attendance
{
	string month;
	int present_days;
	int absent_days;
	int leave_days;
	int overtime_hours;
};

void employee_add_data(employee emp[], attendance att[], int& n)
{
	if (n >= 50)
	{
		cout << "NO MORE EMPLOYEES CAN BE ADDED." << endl;
		return;
	}

	cout << "----- ENTER EMPLOYEE DATA -----" << endl << endl;

	cout << "EMPLOYEE " << n + 1 << endl;
	cout << "----------" << endl;

	cout << "ID : ";
	cin >> emp[n].id;
	cin.ignore();

	cout << "Name : ";
	getline(cin, emp[n].name);

	cout << "Designation : ";
	getline(cin, emp[n].designation);

	cout << "Basic Salary : ";
	cin >> emp[n].basic_salary;

	cout << "Joining Date : ";
	cin >> emp[n].joining_date;

	cout << endl;

	cout << "EMPLOYEE ADDED SUCCESSFULLY....." << endl;

	cout << endl;

	att[n].present_days = 0;
	att[n].absent_days = 0;
	att[n].leave_days = 0;
	att[n].overtime_hours = 0;
	att[n].month = "N/A";

	n++;
}

void employee_view_data(employee emp[], int n)
{
	cout << "----- VIEW EMPLOYEE DATA -----" << endl << endl;

	string search_id;

	cout << "Enter an Employee ID : ";
	cin >> search_id;

	cout << endl;

	bool found = false;

	for (int i = 0; i < n; i++)
	{
		if (search_id == emp[i].id)
		{
			found = true;

			cout << "EMPLOYEE " << i + 1 << endl;
			cout << "----------" << endl;

			cout << "ID           : " << emp[i].id << endl;
			cout << "Name         : " << emp[i].name << endl;
			cout << "Designation  : " << emp[i].designation << endl;
			cout << "Basic Salary : " << emp[i].basic_salary << endl;
			cout << "Joining Date : " << emp[i].joining_date << endl;

			cout << endl;
		}
	}

	if (!found)
	{
		cout << "EMPLOYEE NOT FOUND....." << endl << endl;
	}
}

void employee_mark_attendance(employee emp[], attendance att[], int n)
{
	cout << "----- MARK EMPLOYEE ATTENDANCE -----" << endl << endl;

	string search_id;

	cout << "Enter an Employee ID : ";
	cin >> search_id;

	bool found = false;

	for (int i = 0; i < n; i++)
	{
		if (search_id == emp[i].id)
		{
			found = true;

			cout << "Enter Month (in words) : ";
			cin >> att[i].month;

			cout << endl;

			cout << "EMPLOYEE " << i + 1 << endl;
			cout << "----------" << endl;

			do
			{
				cout << "Enter days present (0-22): ";
				cin >> att[i].present_days;
				if (att[i].present_days < 0 || att[i].present_days > 22)
				{
					cout << "Invalid input! Please enter between 0 and 22." << endl;
				}
			} while (att[i].present_days < 0 || att[i].present_days > 22);

			att[i].absent_days = total_days - att[i].present_days;
			cout << "Absent days : " << att[i].absent_days << endl;

			do
			{
				cout << "Enter days leave (0-" << att[i].present_days << "): ";
				cin >> att[i].leave_days;
				if (att[i].leave_days < 0 || att[i].leave_days > att[i].present_days)
				{
					cout << "Invalid input! Leave days cannot exceed present days." << endl;
				}
			} while (att[i].leave_days < 0 || att[i].leave_days > att[i].present_days);

			cout << "Enter overtime hours : ";
			cin >> att[i].overtime_hours;

			cout << endl;

			cout << "ATTENDANCE MARKED SUCCESSFULLY....." << endl << endl;
		}
	}

	if (!found)
	{
		cout << "EMPLOYEE NOT FOUND....." << endl;
	}

	cout << endl;
}

void employee_view_attendance(employee emp[], attendance att[], int n)
{
	cout << "----- VIEW EMPLOYEE ATTENDANCE -----" << endl << endl;

	string search_id;

	cout << "Enter an Employee ID : ";
	cin >> search_id;

	bool found = false;

	for (int i = 0; i < n; i++)
	{
		if (search_id == emp[i].id)
		{
			found = true;

			cout << "Month : " << att[i].month << endl << endl;

			cout << "EMPLOYEE " << i + 1 << endl;
			cout << "----------" << endl;

			cout << "Days Present   : " << att[i].present_days << endl;
			cout << "Days Absent    : " << att[i].absent_days << endl;
			cout << "Days Leave     : " << att[i].leave_days << endl;
			cout << "Overtime Hours : " << att[i].overtime_hours << endl;
		}
	}

	if (!found)
	{
		cout << "EMPLOYEE NOT FOUND....." << endl;
	}

	cout << endl;
}

void employee_salary_calculation(employee emp[], attendance att[], int n, float net_salary[])
{
	cout << "----- MONTHLY PAYSLIP OF EMPLOYEE -----" << endl << endl;

	string search_id;

	cout << "Enter an Employee ID : ";
	cin >> search_id;

	bool found = false;

	for (int i = 0; i < n; i++)
	{
		if (search_id == emp[i].id)
		{
			found = true;

			float per_day_salary = 0.00;
			per_day_salary = (float)emp[i].basic_salary / total_days;

			float base_salary = 0.00;
			base_salary = (att[i].present_days + att[i].leave_days) * per_day_salary;

			float hourly_rate = 0.00;
			hourly_rate = per_day_salary / 8.0;
			float overtime_pay = att[i].overtime_hours * hourly_rate * 1.5;

			float bonus = 0.00;
			if (att[i].present_days == 22)
			{
				bonus = emp[i].basic_salary * 0.10;
			}
			else if (att[i].present_days >= 20)
			{
				bonus = emp[i].basic_salary * 0.05;
			}

			float gross_salary = 0.00;

			gross_salary = base_salary + overtime_pay + bonus;

			float tax = 0.00;
			if (gross_salary > 100000)
			{
				tax = gross_salary * 0.10;
			}
			else if (gross_salary >= 50000)
			{
				tax = gross_salary * 0.05;
			}
			else if (gross_salary < 50000)
			{
				tax = 0.00;
			}

			net_salary[i] = gross_salary - tax;

			cout << "Month : " << att[i].month << endl << endl;

			cout << "Employee " << i + 1 << endl;
			cout << "----------" << endl;

			cout << "Basic Salary  : " << emp[i].basic_salary << endl;
			cout << "Base Salary   : " << base_salary << endl;
			cout << "Overtime Pay  : " << overtime_pay << endl;
			cout << "Bonus         : " << bonus << endl;
			cout << "Gross Salary  : " << gross_salary << endl;
			cout << "Tax Deduction : " << tax << endl;
			cout << "Net Salary    : " << net_salary[i] << endl;
		}
	}

	if (!found)
	{
		cout << "EMPLOYEE NOT FOUND....." << endl;
	}

	cout << endl;
}

void employee_data_save(employee emp[], attendance att[], int n, float net_salary[])
{
	ofstream emp_file("employees.txt");
	ofstream att_file("attendance.txt");
	ofstream sal_file("salary.txt");

	if (!emp_file || !att_file || !sal_file)
	{
		cout << "Error opening file!" << endl;
		return;
	}

	emp_file << n << endl;
	att_file << n << endl;
	sal_file << n << endl;

	for (int i = 0; i < n; i++)
	{
		emp_file << endl;
		emp_file << emp[i].id << endl;
		emp_file << emp[i].name << endl;
		emp_file << emp[i].designation << endl;
		emp_file << emp[i].basic_salary << endl;
		emp_file << emp[i].joining_date << endl;

		att_file << endl;
		att_file << emp[i].id << endl;
		att_file << att[i].month << endl;
		att_file << att[i].present_days << endl;
		att_file << att[i].absent_days << endl;
		att_file << att[i].leave_days << endl;
		att_file << att[i].overtime_hours << endl;

		sal_file << emp[i].id << endl;
		sal_file << net_salary[i] << endl;
	}

	emp_file.close();
	att_file.close();
	sal_file.close();

	cout << "DATA SAVED SUCCESSFULLY TO FILES....." << endl << endl;
}

void employee_data_load(employee emp[], attendance att[], int& n, float net_salary[])
{
	ifstream emp_file("employees.txt");
	ifstream att_file("attendance.txt");
	ifstream sal_file("salary.txt");

	if (!emp_file || !att_file || !sal_file)
	{
		cout << "Error opening files!" << endl;
		return;
	}

	string temp;

	emp_file >> n;
	att_file >> n;
	sal_file >> n;

	emp_file.ignore();
	att_file.ignore();
	sal_file.ignore();

	for (int i = 0; i < n; i++)
	{
		emp_file.ignore();
		getline(emp_file, emp[i].id);
		getline(emp_file, emp[i].name);
		getline(emp_file, emp[i].designation);
		emp_file >> emp[i].basic_salary;
		emp_file.ignore();
		getline(emp_file, emp[i].joining_date);

		getline(att_file, temp);
		getline(att_file, emp[i].id);
		getline(att_file, att[i].month);
		att_file >> att[i].present_days;
		att_file >> att[i].absent_days;
		att_file >> att[i].leave_days;
		att_file >> att[i].overtime_hours;
		att_file.ignore();


		getline(sal_file, emp[i].id);
		sal_file >> net_salary[i];
		sal_file.ignore();

	}

	emp_file.close();
	att_file.close();
	sal_file.close();

	cout << "DATA LOADED SUCCESSFULLY FROM FILES....." << endl << endl;
}


int main()
{
	employee emp[50];
	attendance att[50];
	float net_salary[50] = { 0 };

	cout << "----------------------------------------------------------------------" << endl << endl;
	cout << "---------- EMPLOYEE SALARY AND ATTENDANCE MANAGEMENT SYSTEM ----------" << endl << endl;
	cout << "----------------------------------------------------------------------" << endl << endl;

	cout << "WELCOME TO 'NEXVORA DYNAMICS'" << endl << endl;

	int choice_menu;

	do
	{
		cout << "----- MENU -----" << endl << endl;
		cout << "1. Add Employee." << endl;
		cout << "2. View Employee." << endl;
		cout << "3. Mark Attendance." << endl;
		cout << "4. View Attendance." << endl;
		cout << "5. Calculate Salary." << endl;
		cout << "6. Save Employee Data to file." << endl;
		cout << "7. Read Employee Data from file." << endl;
		cout << "8. Exit." << endl;

		cout << "---------------------------------------------------" << endl;

		cout << "What do you want to do : ";
		cin >> choice_menu;

		cout << "---------------------------------------------------" << endl << endl;

		if (choice_menu == 1)
		{
			employee_add_data(emp, att, emp_count);
		}
		else if (choice_menu == 2)
		{
			employee_view_data(emp, emp_count);
		}
		else if (choice_menu == 3)
		{
			employee_mark_attendance(emp, att, emp_count);
		}
		else if (choice_menu == 4)
		{
			employee_view_attendance(emp, att, emp_count);
		}
		else if (choice_menu == 5)
		{
			employee_salary_calculation(emp, att, emp_count, net_salary);
		}
		else if (choice_menu == 6)
		{
			employee_data_save(emp, att, emp_count, net_salary);
		}
		else if (choice_menu == 7)
		{
			employee_data_load(emp, att, emp_count, net_salary);
		}
		else if (choice_menu == 8)
		{
			cout << "Exiting the Program....." << endl;
		}
		else
		{
			cout << "Invalid Choice....." << endl;
		}
	} while (choice_menu != 8);
}
