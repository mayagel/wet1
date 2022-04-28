
#ifndef _lib
#define _lib
#include "library1.h"
#include "Avltree.h"
#include "DS.h"

#include <iostream>

 void *Init()
 {
    DataStructure *DS = new DataStructure();
    return (void *)DS;
 }
//  StatusType AddCompany(void *DS, int CompanyID, int Value)
//  {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->AddCompany(CompanyID, Value);
//  }

// StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
//  {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->AddEmployee(EmployeeID,CompanyID,Salary,Grade);
//  }

// StatusType RemoveCompany(void *DS, int CompanyID)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->RemoveCompany(CompanyID);
// }

// StatusType RemoveEmployee(void *DS, int EmployeeID)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->RemoveEmployee(EmployeeID);
// }

// StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->GetCompanyInfo(CompanyID, Value, NumEmployees);
// }

// StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary,Grade);
// }

// StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
// }

// StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
// }

// StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->HireEmployee(EmployeeID, NewCompanyID);
// }

// StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->AcquireCompany(AcquirerID, TargetID, Factor);
// }

// StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->GetHighestEarner(CompanyID, EmployeeID);
// }

// StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->GetAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
// }

// StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
// {
//     if (!DS)
//     {
//         return INVALID_INPUT;
//     }
//     return ((DataStructure *)DS)->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
// }

// StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
//             int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
//             {
//                 if (!DS)
//                     {
//                        return INVALID_INPUT;
//                     }
//                  return ((DataStructure *)DS)->GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, 
//                  MinGrade, TotalNumOfEmployees, NumOfEmployees);
//             }

void Quit(void** DS)
{
    delete ((DataStructure *)*DS);
    *DS = nullptr;
}

#endif
