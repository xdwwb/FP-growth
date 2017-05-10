#include <time.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "test.h"
#include "Arules.h"

using namespace std;

int main(int argc, char** argv) {

	clock_t begin = clock();
	double support = 0;
	double confidence = 0;

	//����������
	if (argc != 4) {
		cerr << "Argument number is wrong, please check your input!" << endl;
		//system("pause");
		return 0;
	}

	//���ղ���
	ifstream in(argv[1]);
	support = atof(argv[2]);
	confidence = atof(argv[3]);


	//������
	if (!(support >= 0 && support <= 1)) {
		cerr << "The argument of support is out of the right range, please input again!" << endl;
		//system("pause");
		return 0;
	}
	if (!(confidence >= 0 && confidence <= 1)) {
		cerr << "The argument of confidence is out of the right range, please input again!" << endl;
		//system("pause");
		return 0;
	}
	if (!in) {
		cerr << "The input file path is wrong, please input again!" << endl;
		//system("pause");
		return 0;
	}

	test t;
	clog << "------------------------------------------------------" << endl;
	clog << "Welcome to use Arules to mine association rules!" << endl;
	clog << "Author: Weibing Wang" << endl;
	clog << "Data: 2017-04-25" << endl;
	clog << "------------------------------------------------------" << endl;
	clog << "Minimun Support: " << support << endl;
	clog << "Minimum Confidence: " << confidence << endl;
	
	Arules arules(in, support, confidence);
	clog << "Minimum Support Count: " << arules.getMin_sup_count() << endl;
	clog << "Transactions Size: " << arules.getTransactionSize() << endl;
	clog << "Arules is mining......" << endl;
	arules.run();
	clog << "Mined done!" << endl;
	clog << "Frequent Item Set Size: " << arules.getFrequentItemSetSize() << endl;
	clog << "Association Rules Size: " << arules.getRulesSize() << endl;

	ofstream out("rules.csv");
	arules.saveAssociation(out);
	//arules.save(out);
	clog << "Mining result have been saved to file \"rules.csv\"" << endl;

	//clog << "OK!" << endl;
	in.close();
	out.close();
	//system("type rules.csv");
	//system("pause");
	clog << "Use time: "<<clock() - begin <<"ms"<< endl;
	return 0;
}