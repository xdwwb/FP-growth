#include "test.h"

test::test() {
	FPTreeTest();//�Ѿ��ɹ�
}

inline void test::FPTreeTest() {
	vector<ItemSet> T;
	T.push_back(ItemSet(1));
	T.back().insert(Item(5));
	T.back().insert(Item(1));
	T.back().insert(Item(4));
	T.back().insert(Item(2));

	T.push_back(ItemSet(1));
	T.back().insert(Item(4));
	T.back().insert(Item(1));
	T.back().insert(Item(3));
	T.back().insert(Item(5));
	T.back().insert(Item(2));

	T.push_back(ItemSet(1));
	T.back().insert(Item(3));
	T.back().insert(Item(1));
	T.back().insert(Item(2));
	T.back().insert(Item(5));

	T.push_back(ItemSet(1));
	T.back().insert(Item(2));
	T.back().insert(Item(1));
	T.back().insert(Item(4));

	T.push_back(ItemSet(1));
	T.back().insert(Item(4));

	T.push_back(ItemSet(1));
	T.back().insert(Item(4));
	T.back().insert(Item(2));

	T.push_back(ItemSet(1));
	T.back().insert(Item(1));
	T.back().insert(Item(4));
	T.back().insert(Item(5));

	T.push_back(ItemSet(1));
	T.back().insert(Item(2));
	T.back().insert(Item(3));

	FPtree fptree(T,3);
	//���Գɹ�
}
