#pragma once
#include <set>
#include <map>
#include "Item.h"
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Rule;

class Arules {
public:

	Arules(ifstream &_in, double _min_sup, double _min_conf) :min_sup(_min_sup), min_conf(_min_conf) {
		this->readTransactions(_in);
		//this->readFromFile(_in);
	}

	void run();

	void genFrequentPattern();

	void generateRules();

	void save(ofstream &out);

	void saveAssociation(ofstream &out);


private:

	double min_sup;//��С֧�ֶ�

	double min_conf;//��С���Ŷ�

	int min_sup_count;//��С֧�ֶȼ���

	map<string, int> dict;//Item���ַ�����ʾ�����ֱ�ʾ��ӳ�䣻

	vector<set<int>> T;//��������ļ���

	vector<map<set<int>, int>> Fk;//Ƶ����ļ���

	vector<Rule> rules;//���ھ򵽵Ĺ�������ļ���

	void readFromFile(ifstream &in);

	void readTransactions(ifstream &in);

	void patternGrow(vector<ItemSet>& T, set<int>& suffix);


	vector<set<int>>& gen_postCondition(vector<set<int>>& Cm, vector<set<int>> &Hm);

public:
	double getMinConfidence() {
		return this->min_conf;
	}

	int getMin_sup_count() {
		return this->min_sup_count;
	}

	size_t getTransactionSize() {
		return T.size();
	}

	size_t getFrequentItemSetSize() {
		size_t size=0;
		for (int i = 0;i < Fk.size();i++) {
			size += Fk[i].size();
		}
		return size;
	}

	size_t getRulesSize() {
		return rules.size();
	}
};

class Rule {

public:

	set<int> pre;//precondition ����ǰ��

	set<int> post;//postcondition ������

	double conf;//confidence ���Ŷ�

	double supp;//support ֧�ֶ�

	double lift;//lift ������

	void save(ofstream &out);

	void saveAssociation(ofstream & out, map<int, string> &dictionary);

};