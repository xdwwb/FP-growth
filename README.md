# FPtree
An implement for FP-tree algorithm which used to mine frequent item set and association rules.
## Introduction
### Usage(in command line)
FPtree f supp conf

f: inupt file name, supp: minimum support threshold, conf: confidence.
### Input file format
item1,item2,item3

item1,item3

item2,item3,item4,item5

### Source code Introduction
#### Item.h, Item.cpp
Item class and ItemSet class is used to describe transaction data for more convenient usage.
#### FPtree.h, FPtree.cpp
Node class is the node struct for FPtree. FPtree class is used to construct FP-tree.
#### Arules.h, Arules.cpp
class Arules, which is the most important class for this procedure, is used to mine frequent item set and association rules.
#### test.h ,test.cpp
class test is used to test FP-tree class.
#### main.cpp
main function, which is used to process input ,output and call the function of Arules class.
