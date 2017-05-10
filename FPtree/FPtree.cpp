#include "FPtree.h"

FPtree::FPtree(vector<ItemSet>& T, int minsup)
{
	//ͳ��Ƶ��
	map<int, int>dic;
	for (int i = 0;i < T.size();i++) {
		ItemSet::iterator itr;
		for (itr = T[i].begin();itr != T[i].end();itr++) {
			dic[itr->id] += T[i].count;//��������
		}
	}
	//�޸����ȼ���
	for (int i = 0;i < T.size();i++) {
		ItemSet::iterator itr;
		ItemSet temp(T[i].count);

		for (itr = T[i].begin();itr != T[i].end();itr++) {
			int frequency = dic[itr->id];
			if (frequency < minsup)
				continue;
			temp.insert(Item(itr->id,frequency));//Ƶ����Ϊ���ȼ�
		}
		//ע�⣬temp����Ϊ���ˣ�
		T[i].swap(temp);//��ʱ�򣬰������ȼ��ź�����
	}
	//����id������ͷ�ֵ�
	map<Item, Node*> lastNode;
	map<int, int>::iterator itr_dic;
	for (itr_dic = dic.begin();itr_dic != dic.end();itr_dic++) {
		if (itr_dic->second >= minsup) {
			firstNode[Item(itr_dic->first, itr_dic->second)] = NULL;
			lastNode[Item(itr_dic->first, itr_dic->second)] = NULL;
		}
	}

	//����fp��
	root = new Node(0,0,NULL);
	for (int i = 0;i < T.size();i++) {
		ItemSet::iterator itr;
		Node* current = root;
		for (itr = T[i].begin();itr != T[i].end();itr++) {
			int id = itr->id;
			Node* child = current->children[id];
			//���û��������ӣ���Ҫ����,��ʼ������ֵ
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
				//������¼���ֵ
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