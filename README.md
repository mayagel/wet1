# wet1
wet1 for mivney

## instuctions (in general)
you can find the full instruction in the DS-WET1-2022-spring.pdf file
when we saw this file together we sugested to create 2 AVL tree.
1. for the all employees
2. for the company
every tree have nodes that is arrange by the ID (of the employee or the company depend on the tree)
one employee node will hold the next fileds:
(*** almog here you need to insert what you wrote in the IPAD)
one company node will hold the next fileds:
(*** almog here you need to insert what you wrote in the IPAD)

## sugestion of files and contain
1. AVL.h - hold the the AVL tree DS with the important function(like constuctore, find, insert, remove, select)
for example in the insert function we should insert "key" that will compare with the other "key nodes until it will find the right place for the new node. in our case the key is employeeID or companyID.
another value we should insert is the "data" whats means we should create object that will be the node himself, in our case, the data is object of employee of object of company
2. employee.cpp/.h - hold the object of one employee, will comtain the right fileds thats in almog IPAD and some function we will need to use if needed
3. company.cpp/.h - very similar to above
4. library.h - we got it from the Segel, dont touch this file is for th function we should use in the main file 
5. library.cpp - implementation of the method that we should create
6. DS.cpp - the whole DS that contains all the avl and data.
5. main.cpp - import all the above files and create obects and avltrees and with those Datas execute the function we need to do.
