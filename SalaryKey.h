class KeyBySalary
{
private:
    int Salary;
    int EmployerID;

public:
    KeyBySalary() =default;

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

bool operator<(const KeyBySalary& a,const KeyBySalary& b){
    if (a.getSalary()<b.getSalary())
    {
        return true;
    }
    if (a.getSalary()>b.getSalary())
    {
        return false;
    }
    return a.getEmployerID() > b.getEmployerID();
}
