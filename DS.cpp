#include "DS.h"
#include "stdio.h"
#include <cstddef>

//     StatusType RemoveEmployee(int EmployeeID);
//     StatusType DataStructure::RemoveCompany(int CompanyID);
//     StatusType DataStructure::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);
//     StatusType DataStructure::HireEmployee(int EmployeeID, int NewCompanyID);
//     StatusType DataStructure::AcquireCompany(int AcquirerID, int TargetID, double Factor);
//     StatusType DataStructure::GetHighestEarner(int CompanyID, int *EmployeeID);
//     StatusType DataStructure::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);
//     StatusType DataStructure::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);
//     StatusType DataStructure::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int
//     MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

StatusType DataStructure::AddCompany(int CompanyID, int Value)
{

    if (CompanyID <= 0 || Value <= 0)
    {
        return INVALID_INPUT;
    }
    if (this->Companies->find((this->Companies)->getRoot(), CompanyID))
    {
        return FAILURE;
    }
    Company *newCompany = new Company(CompanyID, Value);
    if (!newCompany)
    {
        return ALLOCATION_ERROR;
    }
    this->Companies->insert(CompanyID, newCompany);
    return SUCCESS;
}

StatusType DataStructure::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if (CompanyID <= 0 || Salary <= 0 || Grade < 0 || EmployeeID<=0)
    {
        return INVALID_INPUT;
    }
    if (!(Companies->find((this->Companies)->getRoot(), CompanyID)) || Employees->find((this->Employees)->getRoot(), EmployeeID))
    {
        return FAILURE;
    }

    AVLNode<Company*, int> *employer = Companies->find((this->Companies)->getRoot(), CompanyID);
    Employee *newEmployee = new Employee(EmployeeID, CompanyID, Salary, Grade, employer);
    KeyBySalary *keyToInsert = new KeyBySalary(EmployeeID, Salary);

    // insert to trees
    (this->Employees)->insert(EmployeeID, *newEmployee);
    (this->EmployeesBySalary)->insert(*keyToInsert, newEmployee);
    ((employer->data)->getcomEmpBySalary()).insert(*keyToInsert, newEmployee);
    ((employer->data)->getcomEmpByID()).insert(EmployeeID, newEmployee);

    // HighestEarner
    if (newEmployee >  HighestEarner)
    {
        (HighestEarner = newEmployee);
    }
    if (newEmployee > (employer->data)->getHighestEarnerInCom())
    {
        (employer->data)->setHighestEarnerInCom(newEmployee);
    }
    if ((employer->data)->getNumEmployees() == 0)
    {
        this->CopaniesWithEmp->insert(CompanyID, employer->data);
    }
    (employer->data)->incNumEmployees();
    return SUCCESS;
}

StatusType DataStructure::RemoveEmployee(int EmployeeID)
{
    if(EmployeeID<=0)
    {
        return INVALID_INPUT;
    }
    if (!(this->Employees->find((this->Employees)->getRoot(), EmployeeID)))
    {
        return FAILURE;
    }
    AVLNode<Employee, int> *Employee = this->Employees->find((this->Employees)->getRoot(), EmployeeID);
    KeyBySalary *tempKey = new KeyBySalary(EmployeeID,Employee->data.getSalary());

    Employee->data.getEmployer().data->getcomEmpByID().remove(EmployeeID);
    Employee->data.getEmployer().data->getcomEmpBySalary().remove(*tempKey);
    Employee->data.getEmployer().data->decNumEmployees();
    if(Employee->data.getEmployer().data->getNumEmployees()==0)
    {
        this->CopaniesWithEmp->remove(Employee->data.getEmployer().data->getCompanyID());
    }
    this->Employees->remove(EmployeeID);
    this->EmployeesBySalary->remove(*tempKey);
    delete tempKey;
    return SUCCESS;
}

StatusType DataStructure::RemoveCompany(int CompanyID)
{
    if (CompanyID <= 0)
    {
        return INVALID_INPUT;
    }
    AVLNode<Company*, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
    if (!theCompany || theCompany->data->getNumEmployees() != 0)
    {
        return FAILURE;
    }
    this->Companies->remove(CompanyID);
    return SUCCESS;
}

StatusType DataStructure::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees)
{
    if (CompanyID <= 0 || Value == nullptr|| NumEmployees == nullptr)
    {
        return INVALID_INPUT;
    }
    if (!this->Companies->find((this->Companies)->getRoot(), CompanyID))
    {
        return FAILURE;
    }
    AVLNode<Company*, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
    *Value = theCompany->data->getValue();
    *NumEmployees = theCompany->data->getNumEmployees();
    return SUCCESS;
}

StatusType DataStructure::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    if (EmployeeID <= 0 || EmployerID == nullptr|| Salary == nullptr || Grade == nullptr)
    {
        return INVALID_INPUT;
    }
    if(!Employees->find((this->Employees)->getRoot(), EmployeeID))
    {
        return FAILURE;
    }
    AVLNode<Employee, int> *theEmployee = Employees->find((this->Employees)->getRoot(), EmployeeID);
    *EmployerID = theEmployee->data.getEmployeeID();
    *Salary = theEmployee->data.getSalary();
    *Grade = theEmployee->data.getGrade();
    return SUCCESS;
}

StatusType DataStructure::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
{
    if (CompanyID <= 0 || ValueIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    if (!this->Companies->find((this->Companies)->getRoot(), CompanyID))
    {
        return FAILURE;
    }
    AVLNode<Company*, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
    theCompany->data->incValue(ValueIncrease);
    return SUCCESS;
}

StatusType DataStructure::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
{
     if (EmployeeID <= 0 || SalaryIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    if(!Employees->find((this->Employees)->getRoot(), EmployeeID))
    {
        return FAILURE;
    }
    AVLNode<Employee, int> *theEmployee = Employees->find((this->Employees)->getRoot(), EmployeeID);
    theEmployee->data.addToSalary(SalaryIncrease);
    if(BumpGrade>0)
    {
    theEmployee->data.incGrade();
    }
    AVLNode<Employee, int> *newEmployee = theEmployee;

    return SUCCESS;
}

StatusType DataStructure::HireEmployee(int EmployeeID, int NewCompanyID)
{
    return SUCCESS;
//  if (EmployeeID <= 0||NewCompanyID<=0)
//     {
//         return INVALID_INPUT;
//     }
//     AVLNode<Company*, int> *theCompany = Companies->find((this->Companies)->getRoot(), NewCompanyID);
//     AVLNode<Employee, int> *theEmployee = Employees->find((this->Employees)->getRoot(), EmployeeID);
//     AVLNode<Company*, int> *employer = Companies->find((this->Companies)->getRoot(), NewCompanyID);
//     if (!theCompany ||!theEmployee||employer->data->getCompanyID() == theCompany->data->getCompanyID())
//     {
//         return FAILURE;
//     }
}

StatusType DataStructure::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
        return SUCCESS;

//     if (AcquirerID <= 0||TargetID<=0||TargetID == AcquirerID ||Factor<1.00)
//     {
//         return INVALID_INPUT;
//     }
//     AVLNode<Company*, int> *AcquirerCom = Companies->find((this->Companies)->getRoot(), AcquirerID);
//     AVLNode<Company*, int> *TargetCom = Companies->find((this->Companies)->getRoot(), TargetID);
//     if(!TargetCom || !AcquirerCom || AcquirerCom->data->getValue() < (TargetCom->data->getValue()*10))
//     {
//         return FAILURE;
//     }
}

StatusType DataStructure::GetHighestEarner(int CompanyID, int *EmployeeID)
{
    return SUCCESS;
//     if (CompanyID == 0||EmployeeID==nullptr)
//     {
//         return INVALID_INPUT;
//     }
}

StatusType DataStructure::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
{
    return SUCCESS;
}
    StatusType DataStructure::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
    {
        return SUCCESS;
    }
    StatusType DataStructure::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int
    MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
    {
        return SUCCESS;
    }
