#include "HistoryLog.h"

HistoryLog::HistoryLog() {};

HistoryLog::~HistoryLog() {
	Record* temp;
	while (!isEmpty())
	{
		Record* temp = new Record;
		temp = top;
		top = top->next;
		temp->next = nullptr;
		delete temp;
	}
};

bool HistoryLog::isEmpty() {
	return top == nullptr;
}

bool HistoryLog::insertRecord(ItemType &item) {
	Record* newRecord = new Record;
	newRecord->item = item;
	newRecord->next = top;
	top = newRecord;
	return true;
}

bool HistoryLog::deleteRecord(ItemType &item) {
	if (!isEmpty()) {
		item = top->item;
		Record* temp = new Record;
		temp = top;
		top = top->next;
		temp->next = nullptr;
		delete temp;
		return true;
	}
	return false;
}

void HistoryLog::display() {
	if (!isEmpty()) {
		Record* current = top;
		int count{ 1 };
		while (current->next != nullptr) {
			cout << " " << count << " - " << "G" << '\n';
			current = current->next;
			count++;
		}
		cout << " " << count << " - " << "G" << '\n';
	}
}

ItemType HistoryLog::get(int index) {
	if (!isEmpty()) {
		Record* current = top;
		int count{ 1 };
		while (current->next != nullptr) {
			if (index == count) {
				return (current->item);
			}
			current = current->next;
			count++;
		}
		cout << "Invalid Choice!\n";

	}
}
