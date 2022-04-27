#ifndef _Employee
#define _Employee
#include "Company.h"
#include "Avltree.h"
// namespace data_structure
//{
class Employee
{
private:
    int EmployeeID;
    int EmployerID;
    int Salary;
    int Grade;
    AVLNode<Company*, int> *Employer;

public:
    Employee() = default;
    Employee(int EmployeeID) : EmployeeID(EmployeeID) {}
    Employee(int EmployeeID, int EmployerID, int Salary, int Grade, AVLNode<Company*,int> *Employer) : EmployeeID(EmployeeID),
                                                                                                       EmployerID(EmployerID),
                                                                                                       Salary(Salary),
                                                                                                       Grade(Grade),
                                                                                                       Employer(new AVLNode<Company*,int>())
                                                                                                       {};


    ~Employee() = default;
    Employee(const Employee &emp)
    {
        EmployeeID = emp.EmployeeID;
        EmployerID = emp.EmployerID;
        Salary = emp.Salary;
        Grade = emp.Grade;
        Employer = emp.Employer;
    }
    bool operator<(const Employee &emp) const; // based on EmployeeID
    bool operator>(const Employee &emp) const; // based on EmployeeID
    // Employee &operator=(const Employee &emp);
    int getEmployeeID() { return EmployeeID; };
    int getGrade() { return Grade; };
    int getSalary() { return Salary; };
    int getEmployerID() { return EmployerID; };
    void setSalary(int t) { Salary = t; }
    void setGrade(int t) { Grade = t; }
    //  bool operator==(const Employee &emp);
};

#endif