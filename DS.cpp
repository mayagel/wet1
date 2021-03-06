#include "DS.h"
#include "stdio.h"
#include <cstddef>

StatusType DataStructure::AddCompany(int CompanyID, int Value)
{
    if (CompanyID <= 0 || Value <= 0)
    {
        return INVALID_INPUT;
    }
    if (this->Companies->find(Companies->getRoot(), CompanyID))
    {
        return FAILURE;
    }
    Company *newCompany = new Company(CompanyID, Value);
    if (!newCompany)
    {
        return ALLOCATION_ERROR;
    }
    this->Companies->insert(CompanyID, newCompany);
    // delete newCompany;

    return SUCCESS;
}

StatusType DataStructure::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if (CompanyID <= 0 || Salary <= 0 || Grade < 0 || EmployeeID <= 0)
    {
        return INVALID_INPUT;
    }
    if (!(Companies->find((this->Companies)->getRoot(), CompanyID)) || Employees->find((this->Employees)->getRoot(), EmployeeID))
    {
        return FAILURE;
    }

    AVLNode<Company *, int> *employer = Companies->find((this->Companies)->getRoot(), CompanyID);

    Employee *newEmployee = new Employee(EmployeeID, CompanyID, Salary, Grade, employer->data);
    // Employee *newEmployeeBySal = new Employee(EmployeeID, CompanyID, Salary, Grade, employer);
    KeyBySalary *keyToInsert = new KeyBySalary(Salary, EmployeeID);

    // insert to trees
    (this->Employees)->insert(EmployeeID, newEmployee);
    (this->EmployeesBySalary)->insert(*keyToInsert, newEmployee);
    ((employer->data)->getcomEmpBySalary2())->insert(*keyToInsert, newEmployee);
    ((employer->data)->getcomEmpByID2())->insert(EmployeeID, newEmployee);

    // HighestEarner
    if (this->Employees->getNumOfNode() == 1)
    {
        (HighestEarner = newEmployee);
    }
    else if (*newEmployee > *HighestEarner)
    {
        (HighestEarner = newEmployee);
    }
    if (employer->data->getNumEmployees() == 0)
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

    delete keyToInsert;
    // numOfEmployees++
    (employer->data)->incNumEmployees();
    return SUCCESS;
}

StatusType DataStructure::RemoveEmployee(int EmployeeID)
{
    if (EmployeeID <= 0)
    {
        return INVALID_INPUT;
    }
    if (!(this->Employees->find((this->Employees)->getRoot(), EmployeeID)))
    {
        return FAILURE;
    }
    AVLNode<Employee *, int> *EmployeeByID = this->Employees->find((this->Employees)->getRoot(), EmployeeID);
    KeyBySalary *tempKey = new KeyBySalary(EmployeeByID->data->getSalary(), EmployeeID);
    AVLTree<Employee *, KeyBySalary> *compBySal = &(EmployeeByID->data->getEmployer().getcomEmpBySalary()); // of target

    EmployeeByID->data->getEmployer().decNumEmployees();
    EmployeeByID->data->getEmployer().getcomEmpByID().remove(EmployeeID);
    EmployeeByID->data->getEmployer().getcomEmpBySalary().remove(*tempKey);
    // Employee->data.getEmployer().data->decNumEmployees();
    if (EmployeeByID->data->getEmployer().getNumEmployees() == 0)
    {
        this->CompaniesWithEmp->remove(EmployeeByID->data->getEmployer().getCompanyID());
    }

    this->EmployeesBySalary->remove(*tempKey);
    
    //hiest earner
    if(EmployeeID == HighestEarner->getEmployeeID())
    {
       HighestEarner = goLeft(EmployeesBySalary->getRoot());
    }
    if(EmployeeID == EmployeeByID->data->getEmployer().getHighestEarnerInCom()->getEmployeeID())
    {
        if(EmployeeByID->data->getEmployer().getNumEmployees() != 0)
        {
            EmployeeByID->data->getEmployer().setHighestEarnerInCom(goLeft(compBySal->getRoot()));
        }
    }
    delete EmployeeByID->data;

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
    AVLNode<Company *, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
    if (!theCompany || theCompany->data->getNumEmployees() != 0)
    {
        return FAILURE;
    }
    // delete theCompany->data->getcomEmpBySalary2();
    // delete theCompany->data->getcomEmpByID2();
    delete theCompany->data;
    this->Companies->remove(CompanyID);
    return SUCCESS;
}

StatusType DataStructure::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees)
{
    if (CompanyID <= 0 || Value == nullptr || NumEmployees == nullptr)
    {
        return INVALID_INPUT;
    }
    if (!this->Companies->find((Companies)->getRoot(), CompanyID))
    {
        return FAILURE;
    }
    AVLNode<Company *, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
    *Value = theCompany->data->getValue();
    *NumEmployees = theCompany->data->getcomEmpByID().getNumOfNode();
    return SUCCESS;
}

StatusType DataStructure::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    if (EmployeeID <= 0 || EmployerID == nullptr || Salary == nullptr || Grade == nullptr)
    {
        return INVALID_INPUT;
    }
    if (!Employees->find((this->Employees)->getRoot(), EmployeeID))
    {
        return FAILURE;
    }
    AVLNode<Employee *, int> *theEmployee = Employees->find((this->Employees)->getRoot(), EmployeeID);
    *EmployerID = theEmployee->data->getEmployerID();
    *Salary = theEmployee->data->getSalary();
    *Grade = theEmployee->data->getGrade();
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
    AVLNode<Company *, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
    theCompany->data->incValue(ValueIncrease);
    return SUCCESS;
}

StatusType DataStructure::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    if (EmployeeID <= 0 || SalaryIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    if (!Employees->find((this->Employees)->getRoot(), EmployeeID))
    {
        return FAILURE;
    }
    Employee *theEmployee = Employees->find((this->Employees)->getRoot(), EmployeeID)->data;
    KeyBySalary *keyToRemove = new KeyBySalary(theEmployee->getSalary(), EmployeeID);

    // remove
    theEmployee->getEmployer().getcomEmpBySalary().remove(*keyToRemove);
    this->EmployeesBySalary->remove(*keyToRemove);

    // upgrade
    theEmployee->addToSalary(SalaryIncrease);
    if (BumpGrade > 0)
    {
        theEmployee->incGrade();
    }

    // insert
    KeyBySalary *keyToInsert = new KeyBySalary(theEmployee->getSalary(), EmployeeID);
    (this->EmployeesBySalary)->insert(*keyToInsert, theEmployee);
    (theEmployee->getEmployer().getcomEmpBySalary()).insert(*keyToInsert, theEmployee);

    // HighestEarner
    if ((*theEmployee) > (*HighestEarner))
    {
        (HighestEarner = theEmployee);
    }
    if ((*theEmployee) > (*theEmployee->getEmployer().getHighestEarnerInCom()))
    {
        theEmployee->getEmployer().setHighestEarnerInCom(theEmployee);
    }
    delete keyToRemove;
    delete keyToInsert;
    return SUCCESS;
}

StatusType DataStructure::HireEmployee(int EmployeeID, int NewCompanyID)
{
    if (EmployeeID <= 0 || NewCompanyID <= 0)
    {
        return INVALID_INPUT;
    }
    AVLNode<Company *, int> *theCompany = Companies->find((this->Companies)->getRoot(), NewCompanyID);
    AVLNode<Employee *, int> *theEmployee = Employees->find((this->Employees)->getRoot(), EmployeeID);
    if (!theCompany || !theEmployee || theEmployee->data->getEmployerID() == theCompany->data->getCompanyID())
    {
        return FAILURE;
    }

    int newGrade = theEmployee->data->getGrade();
    int newSalary = theEmployee->data->getSalary();

    RemoveEmployee(EmployeeID);
    AddEmployee(EmployeeID, NewCompanyID, newSalary, newGrade);
    return SUCCESS;
}

StatusType DataStructure::AcquireCompany(int acquirer_id, int target_id, double factor)
{
    if (acquirer_id <= 0 || target_id <= 0 || target_id == acquirer_id || factor < 1.00)
    {
        return INVALID_INPUT;
    }

    // step 1: get the 2 companies
    AVLNode<Company *, int> *acquire_com = Companies->find((this->Companies)->getRoot(), acquirer_id);
    AVLNode<Company *, int> *target_com = Companies->find((this->Companies)->getRoot(), target_id);
    if (!target_com || !acquire_com || acquire_com->data->getValue() < (target_com->data->getValue() * 10))
    {
        return FAILURE;
    }
    // step 2: get the info from the companies
    AVLTree<Employee *, KeyBySalary> *acq_comp_by_sal = &(acquire_com->data->getcomEmpBySalary()); // of acquire
    AVLTree<Employee *, int> *acq_comp_by_id = &(acquire_com->data->getcomEmpByID());
    // int acq_val = acquire_com->data->getValue();
    // int acq_num_of_emp = acquire_com->data->getValue();
    // Employee* acq_highest = acquire_com->data->getHighestEarnerInCom();

    AVLTree<Employee *, KeyBySalary> *tar_comp_by_sal = &(target_com->data->getcomEmpBySalary()); // of target
    AVLTree<Employee *, int> *tar_comp_by_id = &(target_com->data->getcomEmpByID());
    // int tar_val = target_com->data->getValue();
    // int tar_num_of_emp = target_com->data->getValue();
    // Employee* tar_highest = target_com->data->getHighestEarnerInCom();

    // step 3: combine employees
    AVLTree<Employee *, KeyBySalary> *merged_emp_by_sal = tar_comp_by_sal->combineTree(tar_comp_by_sal, acq_comp_by_sal);
    AVLTree<Employee *, int> *merged_emp_by_id = tar_comp_by_id->combineTree(tar_comp_by_id, acq_comp_by_id);
    // delete tar_comp_by_id;
    // delete tar_comp_by_sal;
    // delete acq_comp_by_id;
    // delete acq_comp_by_sal;
    // step 4: set other datas
    int merged_value = (acquire_com->data->getValue() + target_com->data->getValue()) * factor;
    int merged_num_of_employees = acquire_com->data->getNumEmployees() + target_com->data->getNumEmployees();
    Employee *merged_highest_emp;

    if ((acquire_com->data->getHighestEarnerInCom()) && (target_com->data->getHighestEarnerInCom()))
    {
        if (*(acquire_com->data->getHighestEarnerInCom()) > *(target_com->data->getHighestEarnerInCom()))
        {
            merged_highest_emp = acquire_com->data->getHighestEarnerInCom();
        }
        else
        {
            merged_highest_emp = target_com->data->getHighestEarnerInCom();
        }
    }
    else if (target_com->data->getHighestEarnerInCom())
    {
        merged_highest_emp = target_com->data->getHighestEarnerInCom();
    }
    else
    {
        merged_highest_emp = acquire_com->data->getHighestEarnerInCom();
    }
    // step 5: delete the target company
    // step 5.1: delete comEmpBySalary and comEmpByID and set numEmployees = 0 (target)
    // target_com->data->getcomEmpByID().setNullDataInTree(target_com->data->getcomEmpByID().getRoot());
    // target_com->data->getcomEmpBySalary().setNullDataInTree(target_com->data->getcomEmpBySalary().getRoot());
    // delete acq_comp_by_sal;
    // delete tar_comp_by_id;
    target_com->data->setcomEmpBySalary(nullptr);
    target_com->data->setcomEmpByID(nullptr);
    target_com->data->setHighestEarnerInCom(nullptr);
    target_com->data->setNumEmployees(0);

    // step 5.2: delete comEmpBySalary and comEmpByID and set numEmployees = 0 from CompaniesWithEmp (target)
    AVLNode<Company *, int> *target_com_with_emps = CompaniesWithEmp->find((this->CompaniesWithEmp)->getRoot(), target_id);
    if (target_com_with_emps)
    {
        this->CompaniesWithEmp->remove(target_id);
    }

    // step 5.3: remove the target company
    this->RemoveCompany(target_id);
    AVLNode<Company *, int> *new_acquire_com = Companies->find((this->Companies)->getRoot(), acquirer_id);

    // //step 6.1: old data acquire company (acquire)
    // acquire_com->data->setcomEmpBySalary(nullptr);
    // acquire_com->data->setcomEmpByID(nullptr);
    // acquire_com->data->setHighestEarnerInCom(nullptr);
    // acquire_com->data->setcomEmpBySalary(nullptr);
    // acquire_com->data->setcomEmpByID(nullptr);
    // acquire_com->data->setNumEmployees(0);

    // //step 6.2: comEmpBySalary and comEmpByID and set numEmployees = 0 from CompaniesWithEmp (acquire)
    // AVLNode<Company*, int> *acquire_com_with_emps = CompaniesWithEmp->find((this->Companies)->getRoot(), acquirer_id);
    // if (acquire_com_with_emps)
    // {
    //     acquire_com_with_emps->data->setcomEmpBySalary(nullptr);
    //     acquire_com_with_emps->data->setcomEmpByID(nullptr);
    //     acquire_com_with_emps->data->setHighestEarnerInCom(nullptr);
    //     acquire_com_with_emps->data->setcomEmpBySalary(nullptr);
    //     acquire_com_with_emps->data->setcomEmpByID(nullptr);
    //     acquire_com_with_emps->data->setNumEmployees(0);
    //     this->CompaniesWithEmp->remove(acquirer_id);
    // }

    // //step 6.3: remove acquire ccompany
    // this->RemoveCompany(acquirer_id);

    // // step 7: add again the acquire company
    // this->AddCompany(acquirer_id, merged_value);

    // step 8: get the acquire company
    //  AVLNode<Company*, int> *merged_comp = Companies->find((this->Companies)->getRoot(), acquirer_id);

    // step 9: set data of acquire in companies
    inOrderUpdateEmployer(merged_emp_by_id->getRoot(), new_acquire_com);
    inOrderUpdateEmployerBySal(merged_emp_by_sal->getRoot(), new_acquire_com);
    new_acquire_com->data->setValue(merged_value);
    new_acquire_com->data->setHighestEarnerInCom(merged_highest_emp);
    new_acquire_com->data->setcomEmpBySalary(merged_emp_by_sal);
    new_acquire_com->data->setcomEmpByID(merged_emp_by_id);
    new_acquire_com->data->setNumEmployees(merged_num_of_employees);

    // NEED TO CHANGE
    // step 10: set data of acquire in CompaniesWithEmp
    if (new_acquire_com->data->getNumEmployees())
    {
        this->CompaniesWithEmp->insert(acquirer_id, new_acquire_com->data);
    }
    delete tar_comp_by_id;
    delete tar_comp_by_sal;
    delete acq_comp_by_id;
    delete acq_comp_by_sal;
    return SUCCESS;
}

StatusType DataStructure::GetHighestEarner(int CompanyID, int *EmployeeID)
{
    if (CompanyID == 0 || EmployeeID == nullptr)
    {
        return INVALID_INPUT;
    }
    if (CompanyID > 0)
    {
        AVLNode<Company *, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
        if (!theCompany || theCompany->data->getNumEmployees() == 0)
        {
            return FAILURE;
        }
        *EmployeeID = theCompany->data->getHighestEarnerInCom()->getEmployeeID();
    }
    else
    {
        if (Employees->getNumOfNode() == 0)
        {
            return FAILURE;
        }
        *EmployeeID = HighestEarner->getEmployeeID();
    }
    return SUCCESS;
}

StatusType DataStructure::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
{
    if (Employees == nullptr || NumOfEmployees == nullptr || CompanyID == 0)
    {
        return INVALID_INPUT;
    }
    if (CompanyID > 0)
    {
        AVLNode<Company *, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
        if (!theCompany || theCompany->data->getNumEmployees() == 0)
        {
            return FAILURE;
        }
        *Employees = (int *)malloc(sizeof(int) * (theCompany->data->getcomEmpBySalary().getNumOfNode()));
        *NumOfEmployees = 0;
        inOrderBySalary(theCompany->data->getcomEmpBySalary().getRoot(), Employees, NumOfEmployees);
    }
    else
    {
        if (this->Employees->getNumOfNode() == 0)
        {
            return FAILURE;
        }
        *Employees = (int *)malloc(sizeof(int) * (this->Employees->getNumOfNode()));
        *NumOfEmployees = 0;
        inOrderBySalary(EmployeesBySalary->getRoot(), Employees, NumOfEmployees);
    }
    return SUCCESS;
}

StatusType DataStructure::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
{
    if(Employees == nullptr || this->Employees->getNumOfNode() < 1 || NumOfCompanies <= 0)
    {
        return INVALID_INPUT;
    }
    if(this->CompaniesWithEmp->getNumOfNode() < NumOfCompanies)

    {
        return FAILURE;
    }
    *Employees = (int *)malloc(sizeof(int) * NumOfCompanies);
    int index = 0;
    // int* NumOfCompaniesPtr = &NumOfCompanies;
    subInOrder(CompaniesWithEmp->getRoot(), Employees, &index, &NumOfCompanies);
    return SUCCESS;
}

StatusType DataStructure::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if (TotalNumOfEmployees == nullptr || NumOfEmployees == nullptr || CompanyID == 0 ||
        MinEmployeeID < 0 || MaxEmployeeId < 0 || MinSalary < 0 || MinGrade < 0 || MinEmployeeID > MaxEmployeeId)
    {
        return INVALID_INPUT;
    }
    *TotalNumOfEmployees = 0;
    *NumOfEmployees = 0;
    if (CompanyID > 0)
    {
        AVLNode<Company *, int> *theCompany = Companies->find((this->Companies)->getRoot(), CompanyID);
        if (!theCompany || theCompany->data->getNumEmployees() == 0)
        {
            return FAILURE;
        }

        int newMinEmployeeID = findMinKey(theCompany->data->getcomEmpByID().getRoot(), MinEmployeeID);
        int newMaxEmployeeId = findMaxKey(theCompany->data->getcomEmpByID().getRoot(), MaxEmployeeId);
        nodeToNodeInOrder(theCompany->data->getcomEmpByID().getRoot(), MinEmployeeID, MaxEmployeeId,newMinEmployeeID, newMaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
    }
    else
    {
        if (Employees->getNumOfNode() == 0)
        {
            return FAILURE;
        }
        int newMinEmployeeID = findMinKey(Employees->getRoot(), MinEmployeeID);
        int newMaxEmployeeId = findMaxKey(Employees->getRoot(), MaxEmployeeId);
        nodeToNodeInOrder(Employees->getRoot(), MinEmployeeID, MaxEmployeeId, newMinEmployeeID, newMaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
    }

    return SUCCESS;
}

// private
void DataStructure::inOrderBySalary(AVLNode<Employee *, KeyBySalary> *start, int **Employees, int *NumOfEmployees)
{
    if (start == nullptr)
        return;
    inOrderBySalary(start->getLeft(), Employees, NumOfEmployees);
    (*Employees)[(*NumOfEmployees)] = start->data->getEmployeeID();
    (*NumOfEmployees)++;
    inOrderBySalary(start->getRight(), Employees, NumOfEmployees);
}

void DataStructure::inOrderBySalary2(AVLNode<Employee, KeyBySalary> *start, int **Employees, int *NumOfEmployees)
{
    if (start == nullptr)
        return;
    inOrderBySalary2(start->getLeft(), Employees, NumOfEmployees);
    (*Employees)[*NumOfEmployees] = start->data.getEmployeeID();
    (*NumOfEmployees)++;
    inOrderBySalary2(start->getRight(), Employees, NumOfEmployees);
}

void DataStructure::subInOrder(AVLNode<Company *, int> *subtree, int **Employees, int *index, int *NumOfCompanies)
{
    if (subtree == nullptr)
    {
        return;
    }
    subInOrder(subtree->left, Employees, index, NumOfCompanies);
    if ((*index) < (*NumOfCompanies))
    {
        (*Employees)[(*index)] = subtree->data->getHighestEarnerInCom()->getEmployeeID();
        (*index) += 1;
        subInOrder(subtree->right, Employees, index, NumOfCompanies);
    }
    return;
}

void DataStructure::nodeToNodeInOrder(AVLNode<Employee *, int> *subtree, int oldmin, int oldmax, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if (subtree == nullptr)
        return;
    if (subtree->data->getEmployeeID() > MinEmployeeID)
        nodeToNodeInOrder(subtree->left, oldmin, oldmax, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
    if ((subtree->data->getEmployeeID() >= oldmin) && (subtree->data->getEmployeeID() <= oldmax))
    {
        (*TotalNumOfEmployees)++;
        if ((subtree->data->getSalary() >= MinSalary) && (subtree->data->getGrade() >= MinGrade))
        {
            (*NumOfEmployees)++;
        }
    }
    if (subtree->data->getEmployeeID() <= MaxEmployeeId)
        nodeToNodeInOrder(subtree->right,  oldmin, oldmax,MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);

    return;
}

void DataStructure::nodeToNodeInOrderEmployeeBySalary(AVLNode<Employee, KeyBySalary> *subtree,int oldmin, int oldmax, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if (subtree == nullptr)
        return;
    if (subtree->data.getEmployeeID() > MinEmployeeID)
        nodeToNodeInOrderEmployeeBySalary(subtree->left,oldmin,oldmax, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
    if ((subtree->data.getEmployeeID() >= oldmin) && (subtree->data.getEmployeeID() >= oldmax))
    {
        (*TotalNumOfEmployees)++;
        if ((subtree->data.getSalary() >= MinSalary) && (subtree->data.getGrade() >= MinGrade))
        {
            (*NumOfEmployees)++;
        }
    }
    if (subtree->data.getEmployeeID() <= MaxEmployeeId)
        nodeToNodeInOrderEmployeeBySalary(subtree->right,oldmin,oldmax, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);

    return;
}

int DataStructure::findMinKey(AVLNode<Employee *, int> *subtree, int MinMaxEmployeeID)
{

    if (subtree->data->getEmployeeID() == MinMaxEmployeeID)
    {
        return subtree->data->getEmployeeID();
    }
    if (subtree->left == nullptr)
    {
        return subtree->data->getEmployeeID();
    }
    if (subtree->data->getEmployeeID() < MinMaxEmployeeID)
    {
        if(subtree->right)
        return findMinKey(subtree->right, MinMaxEmployeeID);
        else
        return subtree->data->getEmployeeID();
    }
    return findMinKey(subtree->left, MinMaxEmployeeID);
}

int DataStructure::findMaxKey(AVLNode<Employee *, int> *subtree, int MinMaxEmployeeID)
{

    if (subtree->data->getEmployeeID() == MinMaxEmployeeID)
    {
        return subtree->data->getEmployeeID();
    }
    if (subtree->right == nullptr)
    {
        return subtree->data->getEmployeeID();
    }
    if (subtree->data->getEmployeeID() < MinMaxEmployeeID)
    {
        return findMaxKey(subtree->right, MinMaxEmployeeID);
    }
    if(subtree->left)
    return findMaxKey(subtree->left, MinMaxEmployeeID);
    else
    return subtree->data->getEmployeeID();
}

void DataStructure::inOrderUpdateEmployer(AVLNode<Employee *, int> *subtree, AVLNode<Company *, int> *newEmployer)
{
    if (subtree == nullptr)
        return;
    inOrderUpdateEmployer(subtree->getLeft(), newEmployer);
    subtree->data->setEmployerID(newEmployer->data->getCompanyID());
    subtree->data->setEmployer(newEmployer->data);
    inOrderUpdateEmployer(subtree->getRight(), newEmployer);
}

void DataStructure::inOrderUpdateEmployerBySal(AVLNode<Employee *, KeyBySalary> *subtree, AVLNode<Company *, int> *newEmployer)
{
    if (subtree == nullptr)
        return;
    inOrderUpdateEmployerBySal(subtree->getLeft(), newEmployer);

    subtree->data->setEmployer(newEmployer->data);
    subtree->data->setEmployerID(newEmployer->data->getCompanyID());
    inOrderUpdateEmployerBySal(subtree->getRight(), newEmployer);
}

Employee* DataStructure::goLeft(AVLNode<Employee *, KeyBySalary> *subtree)
{
    if(subtree->left == nullptr)
    {
        return subtree->data;
    }
    return goLeft(subtree->left);
}