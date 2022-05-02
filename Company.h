#ifndef _Company
#define _Company
#include <iostream>
#include "Avltree.h"
#include "Employee.h"
#include "SalaryKey.h"
/*
Yagel 27.04 2:23
**/

class Employee;
class KeyBySalary;

class Company
{
private:
    int CompanyID;
    int Value;
    int numEmployees;
    AVLTree<Employee*,KeyBySalary> *comEmpBySalary; 
    AVLTree<Employee*,int> *comEmpByID;    
    Employee *HighestEarnerInCom;
public:
    Company() = default;
    Company(int compId, int value) : CompanyID(compId), Value(value), numEmployees(0){
        comEmpBySalary = new AVLTree<Employee*, KeyBySalary>();
        comEmpByID = new AVLTree<Employee*, int>();
        HighestEarnerInCom = nullptr;
        
    };
    // Company(int carType, int modelId, int grade, i) : best(false), demo(false), carType(carType), modelId(modelId), modelSells(0), modelGrade(grade){};

    Company(const Company &comp)
    {
        CompanyID = comp.CompanyID;
        Value = comp.Value;
        numEmployees = comp.numEmployees;
        comEmpBySalary = new AVLTree<Employee*, KeyBySalary>();
        if (comp.comEmpBySalary)
        {
            *comEmpBySalary = *comp.comEmpBySalary;
        }
        
        comEmpByID = new AVLTree<Employee*, int>();
        if (comp.comEmpByID)
        {
            *comEmpByID = *comp.comEmpByID;
        }
        
        if (comp.HighestEarnerInCom)
        {
            *HighestEarnerInCom = *comp.HighestEarnerInCom;
        }
        

    }
    ~Company() = default;
    bool operator<(const Company &c) const; 
    bool operator>(const Company &c) const; 
    Company &operator=(const Company &c);

    //geters
    AVLTree<Employee*,KeyBySalary>& getcomEmpBySalary() { return *comEmpBySalary; };
    AVLTree<Employee*,int>& getcomEmpByID() { return *comEmpByID; };

    AVLTree<Employee*,KeyBySalary>* getcomEmpBySalary2() { return comEmpBySalary; };
    AVLTree<Employee*,int>* getcomEmpByID2() { return comEmpByID; };

    int getCompanyID() {return CompanyID; };
    int getValue() {return Value; };
    int getNumEmployees() { return numEmployees; };
    Employee* getHighestEarnerInCom() {return HighestEarnerInCom; };

    
    
    //setters

    void setcomEmpBySalary(AVLTree<Employee*,KeyBySalary>* emp_by_sal ) { comEmpBySalary = emp_by_sal; };
    void setcomEmpByID(AVLTree<Employee*,int>* emp_by_id) { comEmpByID = emp_by_id; };
    void setHighestEarnerInCom(Employee* emp) {HighestEarnerInCom=emp; };
    void incNumEmployees(){numEmployees++;}
    void decNumEmployees(){numEmployees--;}
    void setNumEmployees(int num){numEmployees=num;}
    void setValue(int val){Value=val;}
    void incValue(int val){Value+=val;}
    // Employee *HighestEarner = nullptr;

   
};

#endif