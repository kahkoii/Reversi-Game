#pragma once
#include <iostream>
#include "MoveHistory.h"
using namespace std;

typedef MoveHistory ItemType;

class HistoryLog
{
private:
	struct Record
	{
		ItemType item;   // to store data
		Record* next;  // to point to next node
	};

	Record* top;
	int totalMoves;

public:
	HistoryLog();
	~HistoryLog();
	bool isEmpty();
	bool insertRecord(ItemType &item);
	bool deleteRecord(ItemType &item);
	void display();
	ItemType get(int index);
};

