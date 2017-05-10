#include "test.h"

test::test() {
	FPTreeTest();//已经成功
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
	//测试成功
}
