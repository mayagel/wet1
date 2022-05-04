

//#include "stdio.h"
// #include "cstring"
//#include "string.h"
#ifndef _DS
#define _DS
#include "Avltree.h"
#include "Company.h"
#include "Employee.h"
#include "library1.h"
#include "SalaryKey.h"

#include <iostream>


class DataStructure
{
private:
    AVLTree<Company*,int> *Companies;
    AVLTree<Company*,int> *CompaniesWithEmp;
    AVLTree<Employee*,int> *Employees;
    AVLTree<Employee*, KeyBySalary> *EmployeesBySalary;
    Employee *HighestEarner;

    void inOrderBySalary(AVLNode<Employee*, KeyBySalary> *start, int **Employees,int *NumOfEmployees);
    void inOrderBySalary2(AVLNode<Employee, KeyBySalary> *start, int **Employees,int *NumOfEmployees);
    void subInOrder(AVLNode<Company*,int> *subtree, int **Employees, int *index, int *NumOfCompanies);
    void nodeToNodeInOrder(AVLNode<Employee*,int> *subtree, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade,int *TotalNumOfEmployees,int *NumOfEmployees);
    void nodeToNodeInOrderEmployeeBySalary(AVLNode<Employee,KeyBySalary> *subtree, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade,int *TotalNumOfEmployees,int *NumOfEmployees);
    int findMinKey(AVLNode<Employee*,int> *subtree, int MinMaxEmployeeID);
    int findMaxKey(AVLNode<Employee*,int> *subtree, int MinMaxEmployeeID);
    // int findMinMaxKeyBySalary(AVLNode<Employee*,KeyBySalary> *subtree, int MinMaxEmployeeID);
    void inOrderUpdateEmployer(AVLNode<Employee*,int> *subtree,AVLNode<Company*,int> *newEmployer);
    void inOrderUpdateEmployerBySal(AVLNode<Employee*,KeyBySalary> *subtree,AVLNode<Company*,int> *newEmployer);



public:
    DataStructure()
    {
        AVLTree<Company*,int> *Companies = new AVLTree<Company*,int>(); 
        this->Companies = Companies;
        AVLTree<Company*,int> *CompaniesWithEmp = new AVLTree<Company*,int>(); 
        this->CompaniesWithEmp = CompaniesWithEmp;
        AVLTree<Employee*, int> *Employees = new AVLTree<Employee*, int>(); 
        this->Employees = Employees;
        AVLTree<Employee*, KeyBySalary> *EmployeesBySalary = new AVLTree<Employee*, KeyBySalary>(); 
        this->EmployeesBySalary = EmployeesBySalary;
        HighestEarner = nullptr; 
    }
    // ~DS()=default;
    DataStructure(const DataStructure &cd)
    {
        this->Companies = cd.Companies;
        this->CompaniesWithEmp = cd.CompaniesWithEmp;
        this->Employees = cd.Employees;
        this->EmployeesBySalary = cd.EmployeesBySalary;
        this->HighestEarner = cd.HighestEarner;
    }

    ~DataStructure()
    {
        delete Companies;
        delete CompaniesWithEmp;
        delete Employees;
        delete EmployeesBySalary;

        Companies = nullptr;
        CompaniesWithEmp =nullptr;
        Employees = nullptr;
        EmployeesBySalary = nullptr;
        // delete HighestEarner;
    };

    StatusType AddCompany(int CompanyID, int Value);
    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);
    StatusType RemoveEmployee(int EmployeeID);
    StatusType RemoveCompany(int CompanyID);
    StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
    StatusType GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);
    StatusType IncreaseCompanyValue(int CompanyID, int ValueIncrease);
    StatusType PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);
    StatusType HireEmployee(int EmployeeID, int NewCompanyID);
    StatusType AcquireCompany(int AcquirerID, int TargetID, double Factor);
    StatusType GetHighestEarner(int CompanyID, int *EmployeeID);
    StatusType GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);
    StatusType GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);
    StatusType GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int
    MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
};

#endif //_CDM