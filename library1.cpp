
#include "library1.h"
#include "Avltree.h"
#include "DS.h"

 void *Init()
 {
    DS *ds = new DS();
    return (void *)ds;
 }
 StatusType AddCompany(void *DS, int CompanyID, int Value)
 {
    if (!DS || CompanyID<=0 || Value <= 0)
    {
        return INVALID_INPUT;
    }
    return DS->AddCompany(CompanyID, Value);
 }

