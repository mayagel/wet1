
#include "library1.h"
#include "Avltree.h"
#include "DS.h"

 void *Init()
 {
    DataStructure *DS = new DataStructure();
    return (void *)DS;
 }
 StatusType AddCompany(void *DS, int CompanyID, int Value)
 {
    if (!DS)
    {
        return INVALID_INPUT;
    }
    return ((DataStructure *)DS)->AddCompany(CompanyID, Value);
 }

