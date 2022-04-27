class KeyBySalary
{
public:
    int Salary;
    int EmployerID;

public:
    KeyBySalary() =default;

    bool operator<(const KeyBySalary& a) const{
    if (a.Salary<Salary)
    {
        return true;
    }
    if (a.Salary>Salary)
    {
        return false;
    }
    return a.EmployerID > EmployerID;
    }
    bool operator>(const KeyBySalary& a) const{
    if (a.Salary>Salary)
    {
        return true;
    }
    if (a.Salary<Salary)
    {
        return false;
    }
    return a.EmployerID < EmployerID;
    }
    bool operator==(const KeyBySalary& a) const{
    if (a.Salary==Salary)
    {
        return a.EmployerID > EmployerID;
    }
    return false;
    }
    ~KeyBySalary() = default;
    int getSalary() const { return Salary; };
    int getEmployerID() const { return EmployerID; };

};

