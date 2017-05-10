#include "FPtree.h"

FPtree::FPtree(vector<ItemSet>& T, int minsup)
{
	//统计频率
	map<int, int>dic;
	for (int i = 0;i < T.size();i++) {
		ItemSet::iterator itr;
		for (itr = T[i].begin();itr != T[i].end();itr++) {
			dic[itr->id] += T[i].count;//计数增加
		}
	}
	//修改优先级别
	for (int i = 0;i < T.size();i++) {
		ItemSet::iterator itr;
		ItemSet temp(T[i].count);

		for (itr = T[i].begin();itr != T[i].end();itr++) {
			int frequency = dic[itr->id];
			if (frequency < minsup)
				continue;
			temp.insert(Item(itr->id,frequency));//频率作为优先级
		}
		//注意，temp可能为空了！
		T[i].swap(temp);//这时候，按照优先级排好序了
	}
	//构建id的索引头字典
	map<Item, Node*> lastNode;
	map<int, int>::iterator itr_dic;
	for (itr_dic = dic.begin();itr_dic != dic.end();itr_dic++) {
		if (itr_dic->second >= minsup) {
			firstNode[Item(itr_dic->first, itr_dic->second)] = NULL;
			lastNode[Item(itr_dic->first, itr_dic->second)] = NULL;
		}
	}

	//构建fp树
	root = new Node(0,0,NULL);
	for (int i = 0;i < T.size();i++) {
		ItemSet::iterator itr;
		Node* current = root;
		for (itr = T[i].begin();itr != T[i].end();itr++) {
			int id = itr->id;
			Node* child = current->children[id];
			//如果没有这个孩子，需要构建,初始化计数值
			if (child == NULL) {
				child = new Node(id,T[i].count,current);
				current->children[id] = child;
				if (firstNode[*itr] == NULL) {
					firstNode[*itr] = child;
					lastNode[*itr] = child;
				}
				else {
					lastNode[*itr]->sibling = child;
					lastNode[*itr] = child;
				}
			}
			else
			{
				//否则更新计数值
				child->count += T[i].count;
			}
			current = child;
		}
	}

}


FPtree::~FPtree()
{
	delete root;
	map<Item, Node*>::iterator itr;
	for (itr = firstNode.begin();itr != firstNode.end();itr++) {
		Node* current = itr->second;
		while (current!=NULL) {
			Node* pre = current;
			current = current->sibling;
			delete pre;
		}
	}
}