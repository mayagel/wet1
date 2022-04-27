class KeyBySalary
{
private:
    int Salary;
    int EmployeeID;

public:
    KeyBySalary() = default;
    KeyBySalary(int salary, int empID) : EmployeeID(empID), Salary(salary) {}

    // bool operator<(const KeyBySalary& a) const{
    // if (a.salary<salary)
    // {
    //     return true;
    // }
    // if (a.salary>salary)
    // {
    //     return false;
    // }
    // return a.employee_id > employee_id;
    // }
    bool operator>(const KeyBySalary &a) const
    {
        if (a.Salary > Salary)
        {
            return true;
        }
        if (a.Salary < Salary)
        {
            return false;
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

bool operator<(const KeyBySalary &a, const KeyBySalary &b)
{
    if (a.getSalary() < b.getSalary())
    {
        return true;
    }
    if (a.getSalary() > b.getSalary())
    {
        return false;
    }
    return a.getEmployeeID() > b.getEmployeeID();
}
