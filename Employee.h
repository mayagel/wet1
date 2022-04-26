#ifndef _Employee
#define _Employee
#include "Company.h"
#include "Avltree.h"
//namespace data_structure
//{
class Employee
{
private:
    int EmployeeID;
    int Salary;
    int Grade;
    int EmployerID;
    AVLNode<Company> Employer;
public:
    Employee() = default;
    Employee(int EmployeeID, int Salary,int Grade,int modelGrade) : EmployeeID(EmployeeID), Salary(Salary), Grade(Grade), EmployerID(EmployerID),Employer(Employer){
    };
    Employee(const Employee &ce)
    {
        EmployeeID = ce.EmployeeID;
        Salary = ce.Salary;
        Grade = ce.Grade;
        EmployerID = ce.EmployerID;
        //Employer = 
    }
    ~Employee() = default;
    //CarModel &operator++();//function that increases modelSells by 1 and add 10 to grade
    // void higherGrade();
    // void changeBest() { best = !best; }
    // void makeDemo() { demo = true; }
    // void lowerGrade(int t);                      //decreases 100/t from grade
    bool operator<(const Employee &emp) const; //based on EmployeeID
    bool operator>(const Employee &emp) const; //based on EmployeeID
    Employee &operator=(const Employee &emp);
    int getEmployeeID() { return EmployeeID; };
    int getGrade() { return Grade; };
    int getSalary() { return Salary; };
    int getEmployerID() { return EmployerID; };
    void setSalary(int t) { Salary = t; }
    void setGrade(int t) { Grade = t; }
    //  bool operator==(const Employee &emp);
};
//}

#endif