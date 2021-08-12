#include <iostream>
#include <mysql.h>
#include <sstream>

using namespace std;
stringstream stmt;

string query;
const char* q;
int qstate;

typedef struct sqlVar
{
	MYSQL* conn;
}sqlVar;

typedef struct Student
{
	string name;
	int grade;
	double math;
	double english;
	double science;
	double socialStudies;
}Student;


void addStudent(MYSQL* conn)
{
	Student std;
	cout << "ENTER THE STUDENTS NAME and GRADE" << endl;
	cin >> std.name;
	cin >> std.grade;
	cout << "ENTER THE STUDENTS MATH, ENGLISH, SCIENCE, and SOCIAL STUDIES GRADE" << endl;
	cin >> std.math;
	cin >> std.english;
	cin >> std.science;
	cin >> std.socialStudies;

	stmt.str("");
	stmt << "INSERT INTO student(name, grade) VALUES('" << std.name << "','" << std.grade << "')";
	query = stmt.str();
	q = query.c_str();
	cout << q << endl;
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << "ADDING THE STUDENT WAS SUCCESSFULL" << endl;
	}
	else
	{
		cout << "NOT SUCCESSFULL" << endl;
	}

	stmt.str("");
	stmt << "INSERT INTO grades(math, english, science, social_studies) VALUES('" << std.math << "', '" << std.english << "', '" << std.science << "', '" << std.socialStudies << "')";
	query = stmt.str();
	q = query.c_str();
	cout << q << endl;
	qstate = mysql_query(conn, q);

	system("cls");
	if (!qstate)
	{
		cout << "ADDING THE STUDENT GRADES WAS SUCCESSFULL" << endl;
	}
	else
	{
		cout << "NOT SUCCESSFULL" << endl;
	}

}

void deleteStudent(MYSQL* conn)
{
	int id;
	cout << "ENTER THE STUDENT ID YOU WISH TO DELETE" << endl;
	cin >> id;

	stmt.str("");
	stmt << "DELETE FROM student where id = " << id;
	query = stmt.str();
	q = query.c_str();
	cout << q << endl;
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << "DELETEION WAS SUCCESSFUL" << endl;
	}
	else
	{
		cout << "DELETION WAS NOT SUCCESSFUL" << endl;
	}

	stmt.str("");
	stmt << "DELETE FROM grades where id = " << id;
	query = stmt.str();
	q = query.c_str();
	qstate = mysql_query(conn, q);
	system("cls");
	if (!qstate)
	{
		cout << "DELETEION WAS SUCCESSFUL" << endl;
	}
	else
	{
		cout << "DELETION WAS NOT SUCCESSFUL" << endl;
	}
}

void createTable(MYSQL* conn)
{
	query = "CREATE TABLE student (id int AUTO_INCREMENT PRIMARY KEY, name varchar(32), grade int)";
	q = query.c_str();
	cout << q << endl;
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << "TABLE CREATION SUCESSFUL " << endl;
	}
	else
	{
		cout << "TABLE WAS NOT CREATED" << endl;
	}

	query = "CREATE TABLE grades (id int AUTO_INCREMENT PRIMARY KEY, math double, english double, science double, social_studies double)";
	q = query.c_str();
	cout << q << endl;
	qstate = mysql_query(conn, q);
	system("cls");
	if (!qstate)
	{
		cout << "TABLE CREATION SUCESSFUL " << endl;
	}
	else
	{
		cout << "TABLE WAS NOT CREATED" << endl;
	}
}


void deleteTable(MYSQL* conn)
{
	query = "DROP TABLE student";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << "SUCCESFULL DELETED" << endl;
	}
	else 
	{
		cout << "UNSUCCESSFULLY DELETED" << endl;
	}

	query = "DROP TABLE grades";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	system("cls");
	if (!qstate)
	{
		cout << "SUCCESFULL DELETED" << endl;
	}
	else
	{
		cout << "UNSUCCESSFULLY DELETED" << endl;
	}
}

void printDB(MYSQL* conn)
{
	system("cls");
	MYSQL_RES* result;
	MYSQL_ROW  row;

	string query1 = "SELECT * FROM student";
	string query2 = "SELECT * FROM grades";
	const char* q1 = query1.c_str();
	const char* q2 = query2.c_str();
	qstate = mysql_query(conn, q1);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			cout << "ID " << row[0] << " Name " << row[1] << " Grade " << row[2] << endl;
		}
	}

	cout << "\n\n ---- GRADES ----\n\n";

	qstate = mysql_query(conn, q2);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			cout << "ID " << row[0] << " Math " << row[1] << " English " << row[2] << " Science " << row[3] << " Social Studies " << row[4] << endl;
		}
	}
}

void updateGrades(MYSQL* conn)
{
	int id;
	string subject = "";
	double grade;

	cout << "ENTER THE STUDENTS ID YOU WISH TO CHANGE, THE SUBJECT YOU WISH TO CHANGE, AND THE NEW GRADE" << endl;
	cin >> id;
	cin >> subject;
	cin >> grade;
	stmt.str("");
	stmt << "UPDATE grades SET " << subject << " = " << grade << " WHERE id = " << id;
	query = stmt.str();
	q = query.c_str();
	qstate = mysql_query(conn, q);
	system("cls");
	if (!qstate)
	{
		cout << "UPDATING GRADES WAS SUCCESSFUL" << endl;
	}
	else
	{
		cout << "UPDATING GRADES WAS NOT SUCCESSFUL" << endl;
	}
}

void printMenu()
{
	cout << "\n\n----ENTER AN OPTION----" << endl;
	cout << "1. Create Database for student management" << endl;
	cout << "2. Add a student to the database" << endl;
	cout << "3. Delete a student from the database" << endl;
	cout << "4. Update a students grade in the database based on the student ID" << endl;
	cout << "5. Print out the databases" << endl;
	cout << "6. Delete the database" << endl;
	cout << "7. Quit" << endl;
}

int main()
{
	int option = -1;
	sqlVar sql;
	sql.conn = mysql_init(0);
	sql.conn = mysql_real_connect(sql.conn, "localhost", "root", "*********", "students", 3306, NULL, 0);

	if (sql.conn)
	{
		cout << "CONNECTION WAS A SUCCESS " << endl;
	}
	else
	{
		cout << "CONNECTION UNSUCCESSFUL" << endl;
		return -1;
	}

	while (option != 7)
	{
		printMenu();
		cin >> option;

		switch (option)
		{
		case 1:
			createTable(sql.conn);
			break;
		case 2:
			addStudent(sql.conn);
			break;
		case 3:
			deleteStudent(sql.conn);
			break;
		case 4:
			updateGrades(sql.conn);
			break;
		case 5:
			printDB(sql.conn);
			break;
		case 6:
			deleteTable(sql.conn);
			break;
		default:
			break;
		}

	}


	mysql_close(sql.conn);
	return 0;
}
