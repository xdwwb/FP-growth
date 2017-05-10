#pragma once
#include <set>
using namespace std;

class Item
{
public:
	int id;
	int priority;

	Item(int _id,int _priority=0):id(_id),priority(_priority){}
	
	bool operator<(const Item &b)const {
		if (this->priority > b.priority)
			return true;
		else if (this->priority == b.priority) {
			//优先级相同时，比较id，这一点不容忽视！
			if (this->id < b.id)
				return true;
		}
		return false;
	}

};
class ItemSet :public set<Item> {
public:
	int count;
	ItemSet(int _count):count(_count) {

	}
};
