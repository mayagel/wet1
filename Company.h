#ifndef _CARMODEL
#define _CARMODEL
#include "Avltree.h"
#include "Employee.h"

//namespace data_structure
//{
class CarModel
{
private:
    int CompanyID;
    int Value;
    int numEmployees;
    Avltree<Employee>* comEmpBySalary;
    Avltree<Employee>* comEmpByID;
    Employee* HighestEarnerInCom;


    bool best;
    bool demo;
    int carType;
    int modelId;
    int modelSells;
    int modelGrade;

public:
    CarModel() = default;
    CarModel(int carType, int modelId) : best(false), demo(false), carType(carType), modelId(modelId), modelSells(0), modelGrade(0){};
    // CarModel(int carType, int modelId, int grade, i) : best(false), demo(false), carType(carType), modelId(modelId), modelSells(0), modelGrade(grade){};

    CarModel(const CarModel &cd)
    {
        best = cd.best;
        demo = cd.demo;
        carType = cd.carType;
        modelId = cd.modelId;
        modelSells = cd.modelSells;
        modelGrade = cd.modelGrade;
    }
    ~CarModel() = default;
    //CarModel &operator++();//function that increases modelSells by 1 and add 10 to grade
    void higherGrade();
    void changeBest() { best = !best; }
    void makeDemo() { demo = true; }
    void lowerGrade(int t);                      //decreases 100/t from grade
    bool operator<(const CarModel &model) const; //based on grade and if equal then based on carType
    bool operator>(const CarModel &model) const; //based on grade and if equal then based on carType
    CarModel &operator=(const CarModel &car);
    int getCarType() { return carType; };
    int getGrade() { return modelGrade; };
    int getModelId() { return modelId; };
    int getSells() { return modelSells; };
    void setSells(int t) { modelSells = t; }
    void setGrade(int t) { modelGrade = t; }
    //  bool operator==(const CarModel &model);
};
//}

#endif