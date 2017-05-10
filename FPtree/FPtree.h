#pragma once
#include <map>
#include <set>
#include <vector>
#include "Item.h"
using namespace std;

class Node;

class FPtree
{
public:
	Node* root;
	map<Item, Node*> firstNode;
	FPtree(vector<ItemSet>& T, int minsup);
	~FPtree();
};

class Node {
public:
	Node(int _id,int _count,Node* _parent):id(_id),count(_count),parent(_parent) {}
	int id;//项的编号
	int count;//项的计数
	map<int, Node*> children;//指向孩子节点指针
	Node* sibling;//下一个兄弟节点指针
	Node* parent;//父母节点指针

	bool isRoot() {
		if (this->parent == NULL)
			return true;
		else
			return false;
	}
};

