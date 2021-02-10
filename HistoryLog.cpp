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
	newRecord->next = nullptr;
	newRecord->next = top;
	top = newRecord;
	return true;
}

bool HistoryLog::deleteRecord(int index) {
	if (!isEmpty()) {
		Record* temp = new Record;
		temp = top;
		top = top->next;
		temp->next = nullptr;
		delete temp;
		cout << "\nHistory successfully deleted from log!\n";
		return true;
	}
	cout << "\Invalid choice!\n";
	return false;
}

void HistoryLog::display() {
	if (!isEmpty()) {
		Record* current = top;
		int count{ 1 };
		while (current->next != nullptr) {
			char w = current->item.GetWinner();
			if (w == 'n') cout << " " << count << " - No Winner\n";
			else if (w == 'w') cout << " " << count << " - White\n";
			else if (w == 'b') cout << " " << count << " - Black\n";
			else cout << " " << count << " - Tie\n";
			current = current->next;
			count++;
		}
		char w = current->item.GetWinner();
		if (w == 'n') cout << " " << count << " - No Winner\n";
		else if (w == 'w') cout << " " << count << " - White\n";
		else if (w == 'b') cout << " " << count << " - Black\n";
		else cout << " " << count << " - Tie\n";
	}
}

ItemType HistoryLog::get(int index) {
	if (!isEmpty()) {
		Record* current = top;
		int count{ 1 };
		while (true) {
			if (index == count) {
				return (current->item);
			}
			else if (current->next != nullptr) {
				current = current->next;
				count++;
			}
			else {
				cout << "Invalid Choice!\n";
				break;
			}
		}
	}
}
