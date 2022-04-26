#include "Avltree.h"
#include "Company.h"
#include "Employee.h"
#include "library1.h"
//#include "stdio.h"
// #include "cstring"
//#include "string.h"
#ifndef _DS
#define _DS

class DataStructure
{
private:
    AVLNode<Company> *Companies;
    AVLNode<Company> *CopaniesWithEmp;
    AVLNode<Employee> *Employees;
    AVLNode<Employee> *EmployeesBySalary;
    Employee *HighestEarner;

public:
    DataStructure()
    {
        AVLNode<Company> *Companies = new AVLNode<Company>(); 
        this->Companies = Companies;
        AVLNode<Company> *CopaniesWithEmp = new AVLNode<Company>(); 
        this->CopaniesWithEmp = CopaniesWithEmp;
        AVLNode<Employee> *Employees = new AVLNode<Employee>(); 
        this->Employees = Employees;
        AVLNode<Employee> *EmployeesBySalary = new AVLNode<Employee>(); 
        this->EmployeesBySalary = EmployeesBySalary;
        HighestEarner = nullptr; 
    }
    // ~DS()=default;
    DataStructure(const DS &cd)
    {
        this->Companies = cd.Companies;
        this->CopaniesWithEmp = cd.CopaniesWithEmp;
        this->Employees = cd.Employees;
        this->EmployeesBySalary = cd.EmployeesBySalary;
        this->HighestEarner = cd.HighestEarner;
    }
    // void deleteTrees(AVLNode<CarType> *tree)
    // {
    //     if (tree)
    //     {
    //         if (**tree)
    //         {
    //             delete (*(*tree))->getmodelsTree();
    //         }
    //         deleteTrees(tree->getRight());
    //         deleteTrees(tree->getLeft());
    //     }
    // }
    // void deleteBestSell(AvlNode<CarType> *tree)
    // {
    //     if (tree)
    //     {
    //         if (**tree)
    //         {
    //             delete (*(*tree))->getBestSell();
    //         }
    //         deleteBestSell(tree->getRight());
    //         deleteBestSell(tree->getLeft());
    //     }
    // }
    ~DataStructure()
    {
      
        delete Companies;
        delete CopaniesWithEmp;
        delete Employees;
        delete EmployeesBySalary;
        // delete HighestEarner;
    };

    StatusType AddCompany(void *DS, int CompanyID, int Value);
    StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade);
    StatusType RemoveEmployee(void *DS, int EmployeeID);
    StatusType RemoveCompany(void *DS, int CompanyID);
    StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees);
    StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade);
    StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease);
    StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade);
    StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID);
    StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor);
    StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID);
    StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees);
    StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees);
    StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int
    MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
    void Quit();
};

#endif //_CDM