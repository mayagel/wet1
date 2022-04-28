#include "Employee.h"

bool Employee::operator<(const Employee &emp) const
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
bool Employee::operator>(const Employee &emp) const
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