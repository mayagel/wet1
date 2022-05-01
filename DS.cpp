#include "DS.h"
#include "stdio.h"
#include <cstddef>


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
    Employee *newEmployeeBySal = new Employee(EmployeeID, CompanyID, Salary, Grade, employer);
    KeyBySalary *keyToInsert = new KeyBySalary(EmployeeID, Salary);

    // insert to trees
    (this->Employees)->insert(EmployeeID, *newEmployee);
    (this->EmployeesBySalary)->insert(*keyToInsert, *newEmployeeBySal);
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
        this->CompaniesWithEmp->insert(CompanyID, employer->data);
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
        this->CompaniesWithEmp->remove(Employee->data.getEmployer().data->getCompanyID());
    }
    this->EmployeesBySalary->remove(*tempKey);
    this->Employees->remove(EmployeeID);
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
    Employee *theEmployee =&(Employees->find((this->Employees)->getRoot(), EmployeeID)->data);
    KeyBySalary *keyToRemove = new KeyBySalary(EmployeeID,theEmployee->getSalary());

    //remove
    theEmployee->getEmployer().data->getcomEmpBySalary().remove(*keyToRemove);
    this->EmployeesBySalary->remove(*keyToRemove);
    
    //upgrade
    theEmployee->addToSalary(SalaryIncrease);
    if(BumpGrade>0)
    {
        theEmployee->incGrade();
    }

    //insert
    KeyBySalary *keyToInsert = new KeyBySalary(EmployeeID,theEmployee->getSalary());
    (this->EmployeesBySalary)->insert(*keyToInsert, *theEmployee);
    ((theEmployee->getEmployer().data)->getcomEmpBySalary()).insert(*keyToInsert, theEmployee);

    delete keyToRemove;
    return SUCCESS;
}
//NOT FINISHED
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
//NOT FINISHED
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
    if (CompanyID == 0||EmployeeID==nullptr)
    {
        return INVALID_INPUT;
    }
    if(CompanyID>0)
    {
        AVLNode<Company*, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
        if(!theCompany || theCompany->data->getNumEmployees() == 0)
        {
            return FAILURE;
        }
        *EmployeeID = theCompany->data->getHighestEarnerInCom()->getEmployeeID(); 
    }
    else
    {
        if(Employees->getNumOfNode()==0)
        {
            return FAILURE;
        }
         *EmployeeID = HighestEarner->getEmployeeID();
    }
    return SUCCESS;
}

StatusType DataStructure::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
{
    if(Employees == nullptr || NumOfEmployees == nullptr || CompanyID == 0)
    {
        return INVALID_INPUT;
    }
    *Employees = (int*)malloc(sizeof(int)*(*NumOfEmployees));
    if(CompanyID>0)
    {
        AVLNode<Company*, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
        if(!theCompany || theCompany->data->getNumEmployees() == 0)
        {
            return FAILURE;
        }
        *NumOfEmployees = 0;
        inOrderBySalary(theCompany->data->getcomEmpBySalary().getRoot(), Employees, NumOfEmployees);
    }
    else
    {
        if(this->Employees->getNumOfNode()==0)
        {
            return FAILURE;
        }
        *NumOfEmployees = 0;
        inOrderBySalary2(EmployeesBySalary->getRoot(), Employees, NumOfEmployees);
    }
    return SUCCESS;
}

StatusType DataStructure::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
{
    if(Employees == nullptr || this->Employees->getNumOfNode() < 1)
    {
        return INVALID_INPUT;
    }
    if(this->CompaniesWithEmp->getNumOfNode() < 1)
    {
        return FAILURE;
    }
    *Employees = (int*)malloc(sizeof(int)*NumOfCompanies);
    subInOrder(CompaniesWithEmp->getRoot(),*Employees,0,NumOfCompanies);
    return SUCCESS;
}
//NOT FINISHED
StatusType DataStructure::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int
MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    return SUCCESS;
}

//private
void DataStructure::inOrderBySalary(AVLNode<Employee*, KeyBySalary> *start, int **Employees,int *NumOfEmployees)
{
    if (start == nullptr) return;
    inOrderBySalary(start->getLeft(),Employees,NumOfEmployees);
    *Employees[*NumOfEmployees] = start->data->getEmployeeID();
    NumOfEmployees++;
    inOrderBySalary(start->getRight(),Employees,NumOfEmployees);
}

void DataStructure::inOrderBySalary2(AVLNode<Employee, KeyBySalary> *start, int **Employees,int *NumOfEmployees)
{
    if (start == nullptr) return;
    inOrderBySalary2(start->getLeft(),Employees,NumOfEmployees);
    *Employees[*NumOfEmployees] = start->data.getEmployeeID();
    NumOfEmployees++;
    inOrderBySalary2(start->getRight(),Employees,NumOfEmployees);
}

void DataStructure::subInOrder(AVLNode<Company*,int> *subtree, int *arr, int index, int size)
{
	if (subtree == nullptr) {
   	 return;
	}
	subInOrder(subtree->left, arr, index, size);
	if (index < size) {
    arr[index] = subtree->data->getHighestEarnerInCom()->getEmployeeID();
   	index += 1;
	subInOrder(subtree->right, arr, index, size);
    }
    return;
}
