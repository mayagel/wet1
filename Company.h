#ifndef _CARMODEL
#define _CARMODEL
#include "Avltree.h"
#include "Employee.h"
// #include "SalaryKey.h"
/*
Yagel 27.04 2:23
**/
#include <iostream>



class Company
{
private:
    int CompanyID;
    int Value;
    int numEmployees;
    AVLTree<Employee, KeyBySalary> *comEmpBySalary; 
    AVLTree<Employee, int> *comEmpByID;    
    Employee *HighestEarnerInCom;
public:
    Company() = default;
    Company(int compId, int value) : CompanyID(compId), Value(value), numEmployees(0){
        comEmpBySalary = new AVLTree<Employee, KeyBySalary>();
        comEmpByID = new AVLTree<Employee, int>();
        HighestEarnerInCom = nullptr;
        
    };
    // Company(int carType, int modelId, int grade, i) : best(false), demo(false), carType(carType), modelId(modelId), modelSells(0), modelGrade(grade){};

    Company(const Company &comp)
    {
        CompanyID = comp.CompanyID;
        Value = comp.Value;
        numEmployees = comp.numEmployees;
        comEmpBySalary = new AVLTree<Employee, KeyBySalary>();
        if (comp.comEmpBySalary)
        {
            *comEmpBySalary = *comp.comEmpBySalary;
        }
        
        comEmpByID = new AVLTree<Employee, int>();
        if (comp.comEmpByID)
        {
            *comEmpByID = *comp.comEmpByID;
        }
        
        HighestEarnerInCom = new Employee();
        if (comp.HighestEarnerInCom)
        {
            *HighestEarnerInCom = *comp.HighestEarnerInCom;
        }
        

    }
    ~Company() = default;
    // CarModel &operator++();//function that increases modelSells by 1 and add 10 to grade
    // void higherGrade();
    // void changeBest() { best = !best; }
    // void makeDemo() { demo = true; }
    // void lowerGrade(int t);                      // decreases 100/t from grade
    bool operator<(const Company &c) const; // based on grade and if equal then based on carType
    bool operator>(const Company &c) const; // based on grade and if equal then based on carType
    Company &operator=(const Company &c);
    // int getCarType() { return carType; };
    // int getGrade() { return modelGrade; };
    // int getModelId() { return modelId; };
    // int getSells() { return modelSells; };
    // void setSells(int t) { modelSells = t; }
    // void setGrade(int t) { modelGrade = t; }
    // //  bool operator==(const CarModel &model);
};
//}

#endif