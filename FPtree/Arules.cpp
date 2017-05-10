#include <sstream>
#include <iomanip>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include "Arules.h"
#include "FPtree.h"

void Arules::readFromFile(ifstream &in)
{
	string line, value;
	while (getline(in, line)) {
		istringstream linestream(line);
		set<int> itemset;
		while (getline(linestream, value, ',')) {
			istringstream valuestream(value);
			int num;
			valuestream >> num;
			itemset.insert(num);
		}
		//T.push_back(itemset);
		T.push_back(set<int>());
		T.back().swap(itemset);
	}
	this->min_sup_count = T.size()*min_sup;
}

void Arules::readTransactions(ifstream & in)
{
	string line, value;
	while (getline(in, line)) {
		istringstream linestream(line);
		set<int> itemset;
		while (getline(linestream, value, ',')) {
			int num = dict[value];//查询，如若失败，则插入，值为0
			if (num == 0) {
				num = dict.size();//查询失败，则重新编号
				dict[value] = num;
			}
			itemset.insert(num);
		}
		//T.push_back(itemset);
		T.push_back(set<int>());
		T.back().swap(itemset);
	}
	this->min_sup_count = T.size()*min_sup;
}

void Arules::patternGrow(vector<ItemSet> &T, set<int> &suffix)
{
	//注意：程序如何结束，还需要考虑！
	if (T.empty())
		return;
	FPtree fptree(T, this->min_sup_count);
	if (fptree.firstNode.empty())
		return;

	map<Item, Node*>::reverse_iterator r_itr;
	for (r_itr = fptree.firstNode.rbegin();r_itr != fptree.firstNode.rend();r_itr++) {
		//生成新的频繁模式
		set<int> pattern(suffix);
		assert(r_itr->first.priority>=min_sup_count);
		pattern.insert(r_itr->first.id);
		
		//差点忽略掉，致命的错误！
		if (Fk.size() <= pattern.size())
			Fk.resize(pattern.size()+1);

		Fk[pattern.size()][pattern] = r_itr->first.priority;

		//pattern作为新的后缀
		vector<ItemSet> Tplus;//新的事务数据
		Node* rightward = r_itr->second;
		while (rightward!= NULL) {
			if (rightward->parent->isRoot())//上一顶点为根，不会生成路径
			{
				rightward = rightward->sibling;//指向兄弟顶点
				continue;
			}
			//构建新的项集
			ItemSet temp(rightward->count);
			Node* upward = rightward->parent;
			while (!(upward->isRoot())) {
				temp.insert(Item(upward->id,upward->count));
				upward = upward->parent;
			}
			if (!temp.empty())
				Tplus.push_back(temp);
			rightward = rightward->sibling;
		}
		patternGrow(Tplus, pattern);
	}
}



vector<set<int>>& Arules::gen_postCondition(vector<set<int>>& Cm, vector<set<int>>& Hm)
{
	assert(!Hm.empty());
	assert(Hm[0].size() >= 1);

	int m = Hm.size();
	for (int i = 0;i < Hm.size();i++) {
		for (int j = i + 1;j < Hm.size();j++) {
			assert(Hm[i] != Hm[j]);
			if (equal(Hm[i].begin(), --Hm[i].end(), Hm[j].begin())) {
				set<int> itemset(Hm[i]);
				itemset.insert(*Hm[j].rbegin());
				Cm.push_back(set<int>());
				Cm.back().swap(itemset);
			}
		}
	}
	return Cm;
	// TODO: 在此处插入 return 语句
}

void Arules::run()
{
	genFrequentPattern();
	generateRules();
}

void Arules::genFrequentPattern()
{
	//使用更复杂的事务数据表示形式
	vector<ItemSet> Tplus;
	for (int i = 0;i < T.size();i++) {
		Tplus.push_back(ItemSet(1));
		set<int>::iterator itr;
		for (itr = T[i].begin();itr != T[i].end();itr++) {
			Tplus.back().insert(Item(*itr));
		}
	}
	patternGrow(Tplus,set<int>());
}

void Arules::generateRules()
{
	for (int k = 2;k < Fk.size();k++) {
		map<set<int>, int>::iterator itr;
		for (itr = Fk[k].begin();itr != Fk[k].end();itr++) {
			int m = 1;
			vector<int> C1(itr->first.begin(), itr->first.end());
			vector<set<int>> Hm;
			//生成一个项作为后件的规则
			for (int i = 0;i < C1.size();i++) {
				set<int> post;
				post.insert(C1[i]);
				set<int> pre(itr->first);
				pre.erase(C1[i]);
				double confidence = (double)itr->second / (double)Fk[k - 1][pre];
				if (confidence >= this->min_conf) {
					Rule r;
					r.pre = pre;
					r.post = post;
					r.conf = confidence;
					r.supp = (double)itr->second / (double)(this->T.size());
					r.lift = confidence / ((double)Fk[1][post] / (double)(this->T.size()));
					rules.push_back(r);
					Hm.push_back(post);
				}
			}
			vector<set<int>> Cm;
			while (k > m + 1 && !Hm.empty()) {
				m++;
				Cm = gen_postCondition(Cm, Hm);
				//set<set<int>> temp(Cm.begin(),Cm.end());
				//Cm.assign(temp.begin(),temp.end());
				Hm.clear();
				for (int i = 0;i < Cm.size();i++) {
					set<int> post(Cm[i]);
					vector<int> dif_set;
					set_difference(itr->first.begin(), itr->first.end(), post.begin(), post.end(), back_inserter(dif_set));
					set<int> pre(dif_set.begin(), dif_set.end());

					assert(pre.size() == k - m);
					double confidence = (double)itr->second / (double)Fk[k - m][pre];
					if (confidence >= this->min_conf) {
						Rule r;
						r.pre = pre;
						r.post = post;
						r.conf = confidence;
						r.supp = (double)itr->second / (double)(this->T.size());
						assert(m == post.size());
						r.lift = confidence / ((double)Fk[m][post] / (double)(this->T.size()));
						rules.push_back(r);
						Hm.push_back(post);
					}//end if
				}//end for
				Cm.clear();

			}//end while
		}//end for
	}//end for
}
void Arules::save(ofstream & out)
{
	out << "support\tconfidence\tlift\trule\n";
	for (int i = 0;i < this->rules.size();i++) {
		rules[i].save(out);
	}
}
void Arules::saveAssociation(ofstream & out)
{
	map<int, string> dictionary;
	map<string, int>::iterator itr_dict;
	for (itr_dict = dict.begin();itr_dict != dict.end();itr_dict++) {
		dictionary[itr_dict->second] = itr_dict->first;
	}

	out << setw(8) << setiosflags(ios::left) << "support" << "\t" << setw(8) << "confidence" << "\t" << setw(8) << "lift" << "\t" << setw(8) << "rule" << endl;
	for (int i = 0;i < this->rules.size();i++) {
		rules[i].saveAssociation(out, dictionary);
	}
}
///end function

void Rule::save(ofstream& out)
{
	out << this->supp << "\t\t" << this->conf << "\t\t" << this->lift << "\t\t";
	out << "{";
	set<int>::iterator itr_pre, itr_post;
	for (itr_pre = this->pre.begin();itr_pre != this->pre.end();itr_pre++) {
		out << *itr_pre;
		if (itr_pre != --this->pre.end())
			out << ",";
	}
	out << "=>";
	for (itr_post = this->post.begin();itr_post != this->post.end();itr_post++) {
		out << *itr_post;
		if (itr_post != --this->post.end())
			out << ",";
	}
	out << "}";
	out << endl;
}

void Rule::saveAssociation(ofstream & out, map<int, string> &dictionary)
{
	out << setprecision(2) << this->supp << "\t\t" << this->conf << "\t\t" << this->lift << "\t\t";
	out << "{ ";
	set<int>::iterator itr_pre, itr_post;
	for (itr_pre = this->pre.begin();itr_pre != this->pre.end();itr_pre++) {
		out << dictionary[*itr_pre];
		if (itr_pre != --this->pre.end())
			out << ", ";
	}
	out << " => ";
	for (itr_post = this->post.begin();itr_post != this->post.end();itr_post++) {
		out << dictionary[*itr_post];
		if (itr_post != --this->post.end())
			out << ", ";
	}
	out << " }";
	out << endl;
}
