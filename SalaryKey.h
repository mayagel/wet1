

#pragma once

#ifndef SALARY_KEY
#define SALARY_KEY
#include <stdio.h>

class KeyBySalary
{
public:
    int EmployeeID;
    int Salary;

public:
    KeyBySalary(){};
    KeyBySalary(int salary, int empID) : EmployeeID(empID), Salary(salary){};

    bool operator<(const KeyBySalary &a) const
    {
        if (Salary > a.Salary)
        {
            return true;
        }
        if (Salary < a.Salary)
        {
            return false;
        }
        return EmployeeID < a.EmployeeID;
    }
    KeyBySalary operator=(const KeyBySalary &a)
    {
        this->Salary = a.Salary;
        this->EmployeeID = a.EmployeeID;
        return *this;
    }
    bool operator>(const KeyBySalary &a) const
    {
        if (Salary < a.Salary)
        {
            return true;
        }
        if (Salary > a.Salary)
        {
            return false;
        }
        return EmployeeID > a.EmployeeID;
    }
    bool operator==(const KeyBySalary &a) const
    {
        if (a.Salary == Salary)
        {
            return a.EmployeeID == EmployeeID;
        }
        return false;
    }
    ~KeyBySalary() { printf(" i was here "); };
    int getSalary() const { return Salary; };
    int getEmployeeID() const { return EmployeeID; };
};

#endif
