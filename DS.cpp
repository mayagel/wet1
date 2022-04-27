#include "DS.h"
#include "stdio.h"
#include <cstddef>

    // StatusType AddCompany(void *DS, int CompanyID, int Value);
    // StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade);
    // StatusType RemoveEmployee(void *DS, int EmployeeID);
    // StatusType RemoveCompany(void *DS, int CompanyID);
    // StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees);
    // StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade);
    // StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease);
    // StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade);
    // StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID);
    // StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor);
    // StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID);
    // StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees);
    // StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees);
    // StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int
    // MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
    // // void try();

StatusType DataStructure::AddCompany(int CompanyID, int Value)
{

    if (CompanyID<=0 || Value <= 0)
    {
        return INVALID_INPUT;
    }
    Company *newCompany = new Company(CompanyID, Value);
    if (!newCompany)
    {
        return ALLOCATION_ERROR;
    }
    if (this->Companies->find((this->Companies)->getRoot(), CompanyID))
    {
        delete newCompany;
        return FAILURE;
    }
    else
    {
        this->Companies->insert(CompanyID,*(newCompany));
        return SUCCESS;
    }
}

StatusType DataStructure::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if (CompanyID<=0 || Salary <=0 || Grade <0)
    {
        return INVALID_INPUT;
    }
    if(!(Companies->find((this->Companies)->getRoot(), CompanyID))||Employees->find((this->Employees)->getRoot(), EmployeeID)) 
    {
        return FAILURE;
    }

    AVLNode<Company, int>* employer = Companies->find((this->Companies)->getRoot(), CompanyID);
    Employee *newEmployee = new Employee(EmployeeID,CompanyID,Salary,Grade,employer);

    //insert to trees
    (this->Employees)->insert(EmployeeID,*newEmployee);
    (this->EmployeesBySalary)->insert(/*KeyBySalary*/,*newEmployee);
    ((employer->data).getcomEmpBySalary())->insert(/*KeyBySalary*/,*newEmployee);
    ((employer->data).getcomEmpByID())->insert(EmployeeID,*newEmployee);

    //HighestEarner
    if(newEmployee > this->HighestEarner)
    {
        (employer->data).setHighestEarner(newEmployee);
    }
    if(newEmployee > (employer->data).getHighestEarnerInCom())
    {
        (employer->data).setHighestEarnerInCom(newEmployee);
    }
    if((employer->data).getNumEmployees()==0)
    {
        this->CopaniesWithEmp->insert(CompanyID,employer->data);
    }
    (employer->data).setNumEmployees();
    return SUCCESS;
       
}

// StatusType CarDealershipManager::RemoveCarType(int type)
// {
//     if (type <= 0)
//     {
//         return INVALID_INPUT;
//     }
//     CarType *wanted_car = new CarType(type, 1);
//     if (!wanted_car)
//     {
//         return ALLOCATION_ERROR;
//     }

//     if (!all_types || !this->all_types->search(*wanted_car))
//     {

//         delete wanted_car;
//         return FAILURE;
//     }
//     *wanted_car = *this->all_types->search(*wanted_car);
//     CarModel *best_to_remove = new CarModel();

//     *best_to_remove = *wanted_car->getBestSell();
//     best_to_remove->changeBest();
//     best_models_sells->remove(best_models_sells, *best_to_remove);
//     delete best_to_remove;

//     AvlNode<CarModel> *model_to_del = this->all_types->search(*wanted_car)->getmodelsTree();
//     del_tree(positive_models, model_to_del);
//     del_tree(negative_models, model_to_del);
//     this->all_types->remove(all_types, *wanted_car);

//     this->zero_types->remove(zero_types, *wanted_car);
//     this->bestSell = *(*this->best_models_sells->maxNode(best_models_sells));

//     delete wanted_car;
//     return SUCCESS;
// }

// void deleteTypeNode(AvlNode<CarType> *to_del)
// {
//     delete to_del->getData();
//     to_del->setData();
// }

// StatusType CarDealershipManager::SellCar(int typeID, int modelID)
// {
//     if (modelID < 0 || typeID <= 0)
//     {
//         return INVALID_INPUT;
//     }
//     CarType *demo_wanted_type = new CarType(typeID, modelID);
//     if (!demo_wanted_type)
//     {
//         return ALLOCATION_ERROR;
//     }
//     CarType *wanted_type = this->all_types->search(*demo_wanted_type);
//     // delete demo_wanted_type->getmodelsTree();
//     // delete demo_wanted_type->getBestSell();
//     delete demo_wanted_type;
//     if (!wanted_type)
//     {
//         return FAILURE;
//     }
//     CarModel *demo_wanted_model = new CarModel(typeID, modelID);
//     demo_wanted_model->makeDemo();
//     if (!demo_wanted_model)
//     {
//         return ALLOCATION_ERROR;
//     }
//     CarModel *the_model = wanted_type->getmodelsTree()->search(*demo_wanted_model);
//     //CarModel *the_model=new CarModel( wanted_type->getmodelsTree()->search(*demo_wanted_model));
//     delete demo_wanted_model;
//     if (!the_model)
//     {
//         return FAILURE;
//     }
//     //wanted_car is inside Zero-types
//     if (the_model->getGrade() == 0)
//     {
//         // if the best of the wanted type is the model to remove from zero tree
//         // we delete his bestSell first
//         // if (zero_types->search(*wanted_type)->getBestSell() == zero_types->search(
//         //                                                                      *wanted_type)
//         //                                                            ->getmodelsTree()
//         //                                                            ->search(*the_model))
//         // {
//         //     delete zero_types->search(*wanted_type)->getBestSell();
//         // }

//         //get the models tree of the wanted type and then remove the model from this tree
//         (zero_types->search(
//                        *wanted_type)
//              ->getmodelsTree())
//             ->remove(zero_types->search(*wanted_type)->getmodelsTree(), *the_model); //was true
//         delete (zero_types->search(*wanted_type)->getmodelsTree())->search(*the_model);

//         the_model->higherGrade();
//         CarModel *the_model1 = new CarModel(*the_model);
//         //CarModel *the_model1=new CarModel( wanted_type->getmodelsTree()->search(*demo_wanted_model));
//         positive_models->insert(*the_model1);
//         //     if (!this->bestSell || this->bestSell->getGrade() < the_model->getGrade())
//         //     {
//         //         this->bestSell = the_model;

//         //         //update bestSells tree
//         if (the_model->getSells() > wanted_type->getBestSell()->getSells())
//         {
//             CarModel *best_to_remove = new CarModel();
//             *best_to_remove = *wanted_type->getBestSell();
//             best_to_remove->changeBest();
//             CarModel *best_to_remove2 = best_models_sells->search(*best_to_remove);
//             best_models_sells->remove(best_models_sells, *best_to_remove);
//             delete best_to_remove2; //was true
//             delete best_to_remove;  //added
//             //   CarModel *best_to_insert = new CarModel(*the_model);
//             //*best_to_insert = *the_model;
//             CarModel best_to_insert = *the_model;
//             best_to_insert.changeBest(); //changed stuff here
//             best_models_sells->insert(best_to_insert);
//             // delete best_to_insert;
//         }

//         //         //update best sell of this type
//         CarModel *best_of_type = wanted_type->getBestSell();
//         if (wanted_type->getBestSell()->getSells() < the_model->getSells())
//         {
//             delete best_of_type;
//             CarModel *to_insert8 = new CarModel(the_model->getCarType(), the_model->getModelId());
//             to_insert8->setSells(the_model->getSells());
//             // to_insert8->setGrade(the_model->getGrade());
//             // *to_insert8 = *the_model;
//             // delete wanted_type->getBestSell();
//             wanted_type->setBestSell(to_insert8);
//         }
//         //update BestSell of DS
//         this->bestSell = *(*this->best_models_sells->maxNode(best_models_sells));
//         return SUCCESS;
//         //     }
//     }
//     //wanted_car is inside negative models
//     if (the_model->getGrade() < 0)
//     {
//         if (the_model->getGrade() + 10 < 0)
//         {
//             negative_models->remove(negative_models, *the_model); //was true
//             the_model->higherGrade();
//             CarModel *the_model1 = new CarModel(*the_model);
//             negative_models->insert(*the_model1);
//             if (!this->bestSell || this->bestSell->getGrade() < the_model->getGrade())
//             {
//                 this->bestSell = the_model;
//             }

//             //update bestSells
//             if (the_model->getSells() > wanted_type->getBestSell()->getSells())
//             {

//                 CarModel *best_to_remove = new CarModel();
//                 *best_to_remove = *wanted_type->getBestSell();
//                 best_to_remove->changeBest();
//                 best_models_sells->remove(best_models_sells, *best_to_remove);
//                 delete best_to_remove;
//                 CarModel *best_to_insert2 = new CarModel();
//                 *best_to_insert2 = *the_model;
//                 best_to_insert2->changeBest();
//                 best_models_sells->insert(*best_to_insert2);
//             }
//             //update best sell of this type
//             CarModel *best_of_type = wanted_type->getBestSell();
//             if (best_of_type->getSells() < the_model->getSells())
//             {
//                 delete wanted_type->getBestSell();
//                 best_of_type = the_model;
//             }

//             //update BestSell of DS
//             this->bestSell = *(*this->best_models_sells->maxNode(best_models_sells));
//             return SUCCESS;
//         }
//         else if (the_model->getGrade() == 0)
//         {
//             negative_models->remove(negative_models, *the_model); //was true
//             the_model->higherGrade();
//             CarType *the_type = zero_types->search(*wanted_type);
//             CarModel *the_model1 = new CarModel(*the_model);
//             the_type->getmodelsTree()->insert(*the_model1);
//             if (!this->bestSell || this->bestSell->getGrade() < the_model->getGrade())
//             {
//                 this->bestSell = the_model;
//             }
//             //update bestSells
//             if (the_model->getSells() > wanted_type->getBestSell()->getSells())
//             {

//                 CarModel *best_to_remove = new CarModel();
//                 *best_to_remove = *wanted_type->getBestSell();
//                 best_to_remove->changeBest();
//                 best_models_sells->remove(best_models_sells, *best_to_remove);
//                 delete best_to_remove;
//                 CarModel *best_to_insert3 = new CarModel();
//                 *best_to_insert3 = *the_model;
//                 best_to_insert3->changeBest();
//                 best_models_sells->insert(*best_to_insert3);
//             }

//             //update best sell of this type
//             CarModel *best_of_type = wanted_type->getBestSell();
//             if (best_of_type->getSells() < the_model->getSells())
//             {
//                 delete wanted_type->getBestSell();
//                 best_of_type = the_model;
//             }

//             //update BestSell of DS
//             this->bestSell = *(*this->best_models_sells->maxNode(best_models_sells));
//             return SUCCESS;
//         }
//         else
//         {
//             negative_models->remove(negative_models, *the_model); //was true
//             the_model->higherGrade();
//             CarModel *the_model1 = new CarModel(*the_model);
//             positive_models->insert(*the_model1);
//             if (!this->bestSell || this->bestSell->getGrade() < the_model->getGrade())
//             {
//                 this->bestSell = the_model;
//             }
//             //update bestSells
//             if (the_model->getSells() > wanted_type->getBestSell()->getSells())
//             {

//                 CarModel *best_to_remove = new CarModel();
//                 *best_to_remove = *wanted_type->getBestSell();
//                 best_to_remove->changeBest();
//                 best_models_sells->remove(best_models_sells, *best_to_remove);
//                 delete best_to_remove;
//                 CarModel *best_to_insert4 = new CarModel();
//                 *best_to_insert4 = *the_model;
//                 best_to_insert4->changeBest();
//                 best_models_sells->insert(*best_to_insert4);
//             }
//             //update best sell of this type
//             CarModel *best_of_type = wanted_type->getBestSell();
//             if (best_of_type->getSells() < the_model->getSells())
//             {
//                 delete wanted_type->getBestSell();
//                 best_of_type = the_model;
//             }
//             //update BestSell of DS
//             this->bestSell = *(*this->best_models_sells->maxNode(best_models_sells));
//             return SUCCESS;
//         }
//     }

//     //if the grade is positive no need to update to trees
//     else
//     {

//         //  if (zero_types->search(*wanted_type)->getBestSell() == positive_models->search(*the_model))
//         //  {
//         // delete zero_types->search(*wanted_type)->getBestSell();
//         // } //not sure

//         // //get the models tree of the wanted type and then remove the model from this tree
//         // (zero_types->search(
//         //                *wanted_type)
//         //      ->getmodelsTree())
//         //     ->remove(zero_types->search(*wanted_type)->getmodelsTree(), *the_model); //was true
//         // // delete (zero_types->search(*wanted_type)->getmodelsTree())->search(*the_model);

//         // the_model->higherGrade();
//         // CarModel *the_model1 = new CarModel(*the_model);
//         // //CarModel *the_model1=new CarModel( wanted_type->getmodelsTree()->search(*demo_wanted_model));
//         // positive_models->insert(*the_model1);

//         positive_models->remove(positive_models, *the_model);
//         the_model->higherGrade();
//         CarModel *the_model1 = new CarModel(*the_model);
//         positive_models->insert(*the_model1);
//     }
//     //update bestSells
//     if (the_model->getSells() > wanted_type->getBestSell()->getSells())
//     {

//         CarModel *best_to_remove = new CarModel();
//         *best_to_remove = *wanted_type->getBestSell();
//         best_to_remove->changeBest();
//         CarModel *best_to_remove2 = best_models_sells->search(*best_to_remove);
//         best_models_sells->remove(best_models_sells, *best_to_remove);
//         delete best_to_remove2;
//         delete best_to_remove;
//         CarModel best_to_insert5 = *the_model;
//         // *best_to_insert5 = *the_model;
//         best_to_insert5.changeBest();
//         best_models_sells->insert(best_to_insert5);

//         // CarModel *best_to_remove = new CarModel();
//         //     *best_to_remove = *wanted_type->getBestSell();
//         //     best_to_remove->changeBest();
//         //     CarModel *best_to_remove2 = best_models_sells->search(*best_to_remove);
//         //     best_models_sells->remove(best_models_sells, *best_to_remove);
//         //     delete best_to_remove2; //was true
//         //     delete best_to_remove;  //added
//         //     //   CarModel *best_to_insert = new CarModel(*the_model);
//         //     //*best_to_insert = *the_model;
//         //     CarModel best_to_insert = *the_model;
//         //     best_to_insert.changeBest(); //changed stuff here
//         //     best_models_sells->insert(best_to_insert);
//         // delete best_to_insert;
//     }
//     //update best sell of this type
//     CarModel *best_of_type = wanted_type->getBestSell();
//     if (wanted_type->getBestSell()->getSells() < the_model->getSells())
//     {
//         // delete wanted_type->getBestSell();
//         // best_of_type = the_model;
//         delete best_of_type;
//         CarModel *to_insert8 = new CarModel(the_model->getCarType(), the_model->getModelId());
//         to_insert8->setSells(the_model->getSells());
//         // to_insert8->setGrade(the_model->getGrade());
//         // *to_insert8 = *the_model;
//         // delete wanted_type->getBestSell();
//         wanted_type->setBestSell(to_insert8);
//     }
//     //update BestSell of DS
//     this->bestSell = *(*this->best_models_sells->maxNode(best_models_sells));
//     return SUCCESS;
// }
// StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
// {
//     if (modelID < 0 || typeID <= 0)
//     {
//         return INVALID_INPUT;
//     }
//     CarType *demo_wanted_type = new CarType(typeID, modelID);
//     if (!demo_wanted_type)
//     {
//         return ALLOCATION_ERROR;
//     }
//     CarType *wanted_type = this->all_types->search(*demo_wanted_type);
//     // delete demo_wanted_type->getmodelsTree();
//     // delete demo_wanted_type->getBestSell();
//     delete demo_wanted_type;
//     if (!wanted_type)
//     {
//         return FAILURE;
//     }
//     CarModel *demo_wanted_model = new CarModel(typeID, modelID);
//     demo_wanted_model->makeDemo();
//     if (!demo_wanted_model)
//     {
//         return ALLOCATION_ERROR;
//     }
//     CarModel *the_model = wanted_type->getmodelsTree()->search(*demo_wanted_model);
//     delete demo_wanted_model;
//     if (!the_model)
//     {
//         return FAILURE;
//     }

//     //wanted_car is inside Zero-types
//     if (the_model->getGrade() == 0)
//     {
//         // if the best of the wanted type is the model to remove from zero tree
//         // we delete his bestSell first
//         // if (zero_types->search(*wanted_type)->getBestSell() == zero_types->search(
//         //                                                                      *wanted_type)
//         //                                                            ->getmodelsTree()
//         //                                                            ->search(*the_model))
//         // {
//         //     delete zero_types->search(*wanted_type)->getBestSell();
//         // }
//         (zero_types->search(
//                        *wanted_type)
//              ->getmodelsTree())
//             ->remove(zero_types->search(*wanted_type)->getmodelsTree(), *the_model); //
//         the_model->lowerGrade(t);
//         CarModel *the_model1 = new CarModel(*the_model);
//         negative_models->insert(*the_model1);
//         return SUCCESS;
//     }

//     //wanted_car is inside positive models
//     if (the_model->getGrade() > 0)
//     {

//         if (the_model->getGrade() - (100 / t) > 0)
//         {
//             positive_models->remove(positive_models, *the_model); //was true
//             the_model->lowerGrade(t);
//             CarModel *the_model1 = new CarModel(*the_model);
//             positive_models->insert(*the_model1);

//             return SUCCESS;
//         }
//         else if (the_model->getGrade() - (100 / t) == 0)
//         {
//             positive_models->remove(positive_models, *the_model); //was true
//             the_model->lowerGrade(t);
//             CarType *the_type = zero_types->search(*wanted_type);
//             the_type->getmodelsTree()->insert(*the_model);
//             return SUCCESS;
//         }
//         else
//         {
//             positive_models->remove(positive_models, *the_model); //was true
//             the_model->lowerGrade(t);
//             CarModel *the_model1 = new CarModel(*the_model);
//             negative_models->insert(*the_model1);
//             return SUCCESS;
//         }
//     }

//     //if the grade is negative no need to update to trees
//     else
//     {

//         the_model->lowerGrade(t);
//         negative_models->remove(negative_models, *the_model); //was true
//         CarModel *the_model1 = new CarModel(*the_model);
//         negative_models->insert(*the_model1);
//     }
//     return SUCCESS;
// }

// StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int *models)
// {

//     CarType *demo_type = new CarType(typeID, 1);
//     if (!demo_type)
//     {
//         return ALLOCATION_ERROR;
//     }
//     if (typeID < 0)
//     {
//         // delete demo_type->getmodelsTree();
//         // delete demo_type->getBestSell();
//         delete demo_type;
//         return INVALID_INPUT;
//     }
//     CarType *the_type = all_types->search(*demo_type);
//     if (!the_type)
//     {
//         // delete demo_type->getmodelsTree();
//         // delete demo_type->getBestSell();
//         delete demo_type;
//         return FAILURE;
//     }
//     if (typeID == 0 && !bestSell)
//     {
//         // delete demo_type->getmodelsTree();
//         // delete demo_type->getBestSell();
//         delete demo_type;
//         return FAILURE;
//     }
//     if (typeID == 0)
//     {
//         // delete demo_type->getmodelsTree();
//         // delete demo_type->getBestSell();
//         delete demo_type;
//         *models = this->bestSell->getModelId();
//         return SUCCESS;
//     }
//     *models = the_type->getBestSell()->getModelId();
//     // delete demo_type->getmodelsTree();
//     // delete demo_type->getBestSell();
//     delete demo_type;
//     return SUCCESS;
// }

// int insert_to_arr(int numOfModels, int *types, int *models, AvlNode<CarModel> *current, int *counter)
// {
//     if (numOfModels == 0)
//     {
//         return 0;
//     }
//     if (current->getLeft())
//     {
//         numOfModels = insert_to_arr(numOfModels, types, models, current->getLeft(), counter);
//     }
//     if (numOfModels == 0)
//     {
//         return 0;
//     }
//     if (**current)
//     {
//         types[*counter] = (*(*current))->getCarType();
//         models[*counter] = (*(*current))->getModelId();
//         numOfModels -= 1;
//         (*counter)++;
//     }

//     if (numOfModels == 0)
//     {
//         return 0;
//     }
//     if (current->getRight())
//     {
//         numOfModels = insert_to_arr(numOfModels, types, models, current->getRight(), counter);
//     }
//     if (numOfModels == 0)
//     {
//         return 0;
//     }

//     return numOfModels;
// }

// int type_in_order(int numOfModels, int *types, int *models, AvlNode<CarType> *current, int *counter)
// {
//     AvlNode<CarModel> *zero_root = (*(*(current)))->getmodelsTree();
//     numOfModels = insert_to_arr(numOfModels, types, models, zero_root, counter);
//     if (numOfModels == 0)
//     {
//         return 0;
//     }

//     if (current->getLeft())
//     {
//         numOfModels = type_in_order(numOfModels, types, models, current->getLeft(), counter);
//     }
//     if (numOfModels == 0)
//     {
//         return 0;
//     }
//     if (current->getRight())
//     {
//         numOfModels = type_in_order(numOfModels, types, models, current->getRight(), counter);
//     }
//     if (numOfModels == 0)
//     {
//         return 0;
//     }
//     return numOfModels;
// }

// StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models)
// {

//     int *counter = new int(0);
//     if (!counter)
//     {
//         return ALLOCATION_ERROR;
//     }
//     if (numOfModels <= 0)
//     {
//         delete counter;
//         return INVALID_INPUT;
//     }
//     AvlNode<CarModel> *neg_root = negative_models;
//     numOfModels = insert_to_arr(numOfModels, types, models, neg_root, counter);
//     if (numOfModels == 0)
//     {
//         delete counter;
//         return SUCCESS;
//     }

//     numOfModels = type_in_order(numOfModels, types, models, this->zero_types, counter);
//     if (numOfModels == 0)
//     {
//         delete counter;
//         return SUCCESS;
//     }

//     AvlNode<CarModel> *pos_root = positive_models;
//     numOfModels = insert_to_arr(numOfModels, types, models, pos_root, counter);
//     if (numOfModels > 0)
//     {
//         delete counter;
//         return FAILURE;
//     }
//     delete counter;
//     return SUCCESS;
// }
