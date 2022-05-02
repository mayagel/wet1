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
    KeyBySalary *keyToInsert = new KeyBySalary(Salary, EmployeeID);

    // insert to trees
    (this->Employees)->insert(EmployeeID, *newEmployee);
    (this->EmployeesBySalary)->insert(*keyToInsert, *newEmployeeBySal);
    ((employer->data)->getcomEmpBySalary()).insert(*keyToInsert, newEmployeeBySal);
    ((employer->data)->getcomEmpByID()).insert(EmployeeID, newEmployee);

    // HighestEarner
    if(this->Employees->getNumOfNode()==1)
    {
        (HighestEarner = newEmployee);
    }
    else if (*newEmployee >  *HighestEarner)
    {
        (HighestEarner = newEmployee);
    }
    if(employer->data->getNumEmployees()==0)
    {
        (employer->data)->setHighestEarnerInCom(newEmployee);
    }
    else if (*newEmployee > *(employer->data)->getHighestEarnerInCom())
    {
        (employer->data)->setHighestEarnerInCom(newEmployee);
    }
    if ((employer->data)->getNumEmployees() == 0)
    {
        this->CompaniesWithEmp->insert(CompanyID, employer->data);
    }

    //numOfEmployees++
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
    KeyBySalary *tempKey = new KeyBySalary(Employee->data.getSalary(),EmployeeID);

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
    KeyBySalary *keyToRemove = new KeyBySalary(theEmployee->getSalary(),EmployeeID);

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
    KeyBySalary *keyToInsert = new KeyBySalary(theEmployee->getSalary(),EmployeeID);
    (this->EmployeesBySalary)->insert(*keyToInsert, *theEmployee);
    ((theEmployee->getEmployer().data)->getcomEmpBySalary()).insert(*keyToInsert, theEmployee);

    // HighestEarner
    if (theEmployee >  HighestEarner)
    {
        (HighestEarner = theEmployee);
    }
    if (theEmployee > theEmployee->getEmployer().data->getHighestEarnerInCom())
    {
        theEmployee->getEmployer().data->setHighestEarnerInCom(theEmployee);
    }
    delete keyToRemove;
    return SUCCESS;
}

StatusType DataStructure::HireEmployee(int EmployeeID, int NewCompanyID)
{
    if (EmployeeID <= 0|| NewCompanyID<=0)
    {
        return INVALID_INPUT;
    }
    AVLNode<Company*, int> *theCompany = Companies->find((this->Companies)->getRoot(), NewCompanyID);
    AVLNode<Employee, int> *theEmployee = Employees->find((this->Employees)->getRoot(), EmployeeID);
    AVLNode<Company*, int> *employer = Companies->find((this->Companies)->getRoot(), NewCompanyID);
    if (!theCompany ||!theEmployee||employer->data->getCompanyID() == theCompany->data->getCompanyID())
    {
        return FAILURE;
    }
    int newGrade = theEmployee->data.getGrade();
    int newSalary = theEmployee->data.getSalary();

    RemoveEmployee(EmployeeID);
    AddEmployee(EmployeeID,NewCompanyID,newSalary,newGrade);
    return SUCCESS;

}

StatusType DataStructure::AcquireCompany(int acquirer_id, int target_id, double factor)
{
    if (acquirer_id <= 0||target_id<=0||target_id == acquirer_id ||factor<1.00)
    {
        return INVALID_INPUT;
    }
    //step 1: get the 2 companies
    AVLNode<Company*, int> *acquire_com = Companies->find((this->Companies)->getRoot(), acquirer_id);
    AVLNode<Company*, int> *target_com = Companies->find((this->Companies)->getRoot(), target_id);
    if(!target_com || !acquire_com || acquire_com->data->getValue() < (target_com->data->getValue()*10))
    {
        return FAILURE;
    }

    // step 2: get the info from the companies
    AVLTree<Employee*,KeyBySalary> acq_comp_by_sal = acquire_com->data->getcomEmpBySalary(); //of acquire
    AVLTree<Employee*,int> acq_comp_by_id = acquire_com->data->getcomEmpByID();
    int acq_val = acquire_com->data->getValue();
    int acq_num_of_emp = acquire_com->data->getValue();
    Employee* acq_highest = acquire_com->data->getHighestEarnerInCom();

    AVLTree<Employee*,KeyBySalary> tar_comp_by_sal = target_com->data->getcomEmpBySalary(); // of target
    AVLTree<Employee*,int> tar_comp_by_id = target_com->data->getcomEmpByID();
    int tar_val = target_com->data->getValue();
    int tar_num_of_emp = target_com->data->getValue();
    Employee* tar_highest = target_com->data->getHighestEarnerInCom();

    //step 3: combine employees
    AVLTree<Employee*,KeyBySalary> *merged_emp_by_sal = tar_comp_by_sal.combineTree(&tar_comp_by_sal, &acq_comp_by_sal);
    AVLTree<Employee*,int> *merged_emp_by_id = tar_comp_by_id.combineTree(&tar_comp_by_id, &acq_comp_by_id);

    //step 4: set other datas
    int merged_value = (acquire_com->data->getValue() + target_com->data->getValue()) * factor;
    int merged_num_of_employees = acquire_com->data->getNumEmployees() + target_com->data->getNumEmployees();
    Employee* merged_highest_emp;

    if((acquire_com->data->getHighestEarnerInCom())&&(target_com->data->getHighestEarnerInCom()))
    {
        if (*(acquire_com->data->getHighestEarnerInCom()) > *(target_com->data->getHighestEarnerInCom()))
        {
            merged_highest_emp = acquire_com->data->getHighestEarnerInCom();
        }
        else{
            merged_highest_emp = target_com->data->getHighestEarnerInCom();
      }
    }
    else if(target_com->data->getHighestEarnerInCom())
        {
            merged_highest_emp = target_com->data->getHighestEarnerInCom();
        }
    else if(acquire_com->data->getHighestEarnerInCom())
        {
            merged_highest_emp = acquire_com->data->getHighestEarnerInCom();
        }
    
    // step 5: delete the target company
    // step 5.1: delete comEmpBySalary and comEmpByID and set numEmployees = 0 (target)
    target_com->data->setcomEmpBySalary(nullptr);
    target_com->data->setcomEmpByID(nullptr);
    target_com->data->setHighestEarnerInCom(nullptr);
    target_com->data->setcomEmpBySalary(nullptr);
    target_com->data->setcomEmpByID(nullptr);
    target_com->data->setNumEmployees(0);
    

    //step 5.2: delete comEmpBySalary and comEmpByID and set numEmployees = 0 from CompaniesWithEmp (target)
    AVLNode<Company*, int> *target_com_with_emps = CompaniesWithEmp->find((this->Companies)->getRoot(), target_id);
    if (target_com_with_emps)
    {
        target_com_with_emps->data->setcomEmpBySalary(nullptr);
        target_com_with_emps->data->setcomEmpByID(nullptr);
        target_com_with_emps->data->setHighestEarnerInCom(nullptr);
        target_com_with_emps->data->setcomEmpBySalary(nullptr);
        target_com_with_emps->data->setcomEmpByID(nullptr);
        target_com_with_emps->data->setNumEmployees(0);
        this->CompaniesWithEmp->remove(target_id);
    }
    


    //step 5.3: remove the target company
    this->RemoveCompany(target_id);

    //step 6.1: old data acquire company (acquire)
    acquire_com->data->setcomEmpBySalary(nullptr);
    acquire_com->data->setcomEmpByID(nullptr);
    acquire_com->data->setHighestEarnerInCom(nullptr);
    acquire_com->data->setcomEmpBySalary(nullptr);
    acquire_com->data->setcomEmpByID(nullptr);
    acquire_com->data->setNumEmployees(0);

    //step 6.2: comEmpBySalary and comEmpByID and set numEmployees = 0 from CompaniesWithEmp (acquire)
    AVLNode<Company*, int> *acquire_com_with_emps = CompaniesWithEmp->find((this->Companies)->getRoot(), acquirer_id);
    if (acquire_com_with_emps)
    {
        acquire_com_with_emps->data->setcomEmpBySalary(nullptr);
        acquire_com_with_emps->data->setcomEmpByID(nullptr);
        acquire_com_with_emps->data->setHighestEarnerInCom(nullptr);
        acquire_com_with_emps->data->setcomEmpBySalary(nullptr);
        acquire_com_with_emps->data->setcomEmpByID(nullptr);
        acquire_com_with_emps->data->setNumEmployees(0);
        this->CompaniesWithEmp->remove(acquirer_id);
    }
    
    //step 6.3: remove acquire ccompany
    this->RemoveCompany(acquirer_id);

    // step 7: add again the acquire company
    this->AddCompany(acquirer_id, merged_value);

    //step 8: get the acquire company
    AVLNode<Company*, int> *merged_comp = Companies->find((this->Companies)->getRoot(), acquirer_id);

    //step 9: set data of acquire in companies
    merged_comp->data->setHighestEarnerInCom(merged_highest_emp);
    merged_comp->data->setcomEmpBySalary(merged_emp_by_sal);
    merged_comp->data->setcomEmpByID(merged_emp_by_id);
    merged_comp->data->setNumEmployees(merged_num_of_employees);

    //step 10: set data of acquire in CompaniesWithEmp
    if (merged_comp->data->getNumEmployees())
    {
        this->CompaniesWithEmp->insert(acquirer_id, merged_comp->data);
    }
    
    return SUCCESS;
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
    *Employees = (int*)malloc(sizeof(int)*(this->Employees->getNumOfNode()));
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
    (*NumOfEmployees)++;
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
