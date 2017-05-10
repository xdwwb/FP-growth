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
	int id;//��ı��
	int count;//��ļ���
	map<int, Node*> children;//ָ���ӽڵ�ָ��
	Node* sibling;//��һ���ֵܽڵ�ָ��
	Node* parent;//��ĸ�ڵ�ָ��

	bool isRoot() {
		if (this->parent == NULL)
			return true;
		else
			return false;
	}
};

