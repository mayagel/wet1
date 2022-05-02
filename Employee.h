#ifndef _Employee
#define _Employee
#include "Avltree.h"

class Company;

class Employee
{
private:
    int EmployeeID;
    int EmployerID;
    int Salary;
    int Grade;
    AVLNode<Company*,int> *Employer;

public:
    Employee() = default;
    Employee(int EmployeeID) : EmployeeID(EmployeeID) {}
    Employee(int EmployeeID, int EmployerID, int Salary, int Grade, AVLNode<Company*,int> *Employer) : EmployeeID(EmployeeID),
                                                                                                       EmployerID(EmployerID),
                                                                                                       Salary(Salary),
                                                                                                       Grade(Grade),
                                                                                                       Employer(Employer)
                                                                                                       {}


    ~Employee() = default;
    // Employee(const Employee &emp)
    // {
    //     EmployeeID = emp.EmployeeID;
    //     EmployerID = emp.EmployerID;
    //     Salary = emp.Salary;
    //     Grade = emp.Grade;
    //     Employer = emp.Employer;  //the check if new is needed
    // }
    Employee(const Employee &emp) = default;

    // bool operator<(const Employee &emp) const; // based on EmployeeID
    // bool operator>(const Employee &emp) const; // based on EmployeeID
    // Employee &operator=(const Employee &emp);

    //geters
    int getEmployeeID() { return EmployeeID; };
    int getGrade() { return Grade; };
    int getSalary() { return Salary; };
    int getEmployerID() { return EmployerID; };
    AVLNode<Company*,int>& getEmployer() {return *Employer; };
    
    //seters
    void addToSalary(int t) { Salary += t; }
    void incGrade() { Grade++; }

    bool operator<(const Employee &emp) const
    {

        if(this->Salary < emp.Salary)
        {
            return true;
        }
        else if(this->Salary == emp.Salary)
        {
            if(this->EmployeeID > emp.EmployeeID)
            {
                return true;
            }
        }
        return false;
    }
    bool operator>(const Employee &emp) const
    {
        if(this->Salary > emp.Salary)
        {
            return true;
        }
        else if(this->Salary == emp.Salary)
        {
            if(this->EmployeeID < emp.EmployeeID)
            {
                return true;
            }
        }
        return false;
    }

};

#endif