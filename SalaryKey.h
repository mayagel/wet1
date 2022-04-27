class KeyBySalary
{
public:
    int Salary;
    int EmployeeID;

public:
    KeyBySalary() = default;
    KeyBySalary(int salary, int empID) : EmployeeID(empID), Salary(salary) {};

    bool operator<(const KeyBySalary& a) const{
    if (a.Salary<Salary)
    {
        return true;
    }
    if (a.Salary>Salary)
    {
        return false;
    }
    return a.EmployeeID > EmployeeID;
    }
    bool operator>(const KeyBySalary& a) const
    {
        if (a.Salary>Salary)
        {
           if (a.Salary > Salary)
            {
                return true;
            }
            if (a.Salary < Salary)
            {
             return false;
            }
        }
          return a.EmployeeID < EmployeeID;
    }
    bool operator==(const KeyBySalary &a) const
    {
        if (a.Salary == Salary)
        {
            return a.EmployeeID > EmployeeID;
        }
        return false;
    }
    ~KeyBySalary() = default;
    int getSalary() const { return Salary; };
    int getEmployeeID() const { return EmployeeID; };
};
