#include <iostream>
#include <string>
#include "CustomMemoryManager.h"
using namespace std;

const int MAX_SIZE = 10;

void initializeData(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks);
void displayStatus(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int totalWaste);
void displayPartitions(CustomBlock blocks[], int numBlocks);
void resetData(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks);

void customBestFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks);
void customFirstFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks);
void customNextFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks);
void customWorstFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks);

int main() {

	int numProcesses, numBlocks;
	CustomProcess processes[MAX_SIZE];
	CustomBlock blocks[MAX_SIZE];
	cout << "Enter number of processes: ";
	cin >> numProcesses;
	cout << "Enter number of partitions ";
	cin >> numBlocks;

	initializeData(processes, blocks, numProcesses, numBlocks);

	customBestFit(processes, blocks, numProcesses, numBlocks);
	resetData(processes, blocks, numProcesses, numBlocks);
	customFirstFit(processes, blocks, numProcesses, numBlocks);
	resetData(processes, blocks, numProcesses, numBlocks);
	customNextFit(processes, blocks, numProcesses, numBlocks);
	resetData(processes, blocks, numProcesses, numBlocks);
	customWorstFit(processes, blocks, numProcesses, numBlocks);

	return 0;
}

void initializeData(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks) {

	int temp;
	cout << "Enter size for: \n";
	for (int i = 0; i < numProcesses; i++) {
		cout << "CustomProcess " << i << " = ";
		cin >> temp;
		processes[i] = CustomProcess(i, temp, false);
	}

	cout << "Enter size for: \n";
	for (int j = 0; j < numBlocks; j++) {
		cout << "Partition " << j << " = ";
		cin >> temp;
		blocks[j] = CustomBlock(j, temp, false);
	}
}

void displayStatus(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int totalWaste) {

	cout << "CustomProcess ID/Size\t\tBlock ID/Size\tWaste\tStatus\n";
	for (int i = 0; i < numProcesses; i++) {
		cout << processes[i].id << " / " << processes[i].size << "\t\t\t" <<
			(processes[i].block_id >= 0 ? (to_string(processes[i].block_id) + " / " + to_string(blocks[processes[i].block_id].size)) : "- / -")
			<< "\t\t" << (processes[i].block_id >= 0 ? to_string(processes[i].waste) : "-") << "\t"
			<< (processes[i].run ? "run" : "wait") << endl;
	}
	cout << "total waste: " << totalWaste << endl;
}

void displayPartitions(CustomBlock blocks[], int numBlocks) {
	cout << "---------------Status of Partitions---------------\n";
	cout << "Partition ID/SIZE\tCustomProcess Assigned\tJob ID\n";
	for (int i = 0; i < numBlocks; i++) {
		cout << blocks[i].id << " / " << blocks[i].size << "\t\t\t" << (blocks[i].isUsed ? "yes" : "no") << "\t\t\t"
			<< (blocks[i].isUsed ? to_string(blocks[i].process_id) : "-") << endl;
	}
	cout << endl;
}

void resetData(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks) {

	for (int i = 0; i < numProcesses; i++)
		processes[i].reset();
	for (int j = 0; j < numBlocks; j++)
		blocks[j].reset();
}

void customBestFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks) {

	int lowest, temp, totalWaste(0);
	cout << "\n---------------CUSTOM BEST FIT---------------\n";
	for (int i = 0; i < numProcesses; i++) {
		lowest = 9999;
		for (int j = 0; j < numBlocks; j++) {
			if (!blocks[j].isUsed) {
				temp = blocks[j].size - processes[i].size;
				if (temp >= 0)
					if (lowest > temp) {
						processes[i].block_id = blocks[j].id;
						processes[i].run = true;
						lowest = temp;
						processes[i].waste = lowest;
					}
			}
		}
		totalWaste += processes[i].waste;
		if (processes[i].run) {
			blocks[processes[i].block_id].isUsed = true;
			blocks[processes[i].block_id].process_id = processes[i].id;
		}
	}
	displayStatus(processes, blocks, numProcesses, totalWaste);
	displayPartitions(blocks, numBlocks);
}

void customFirstFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks) {

	int totalWaste = 0;
	cout << "\n---------------CUSTOM FIRST FIT---------------\n";
	for (int i = 0; i < numProcesses; i++) {
		for (int j = 0; j < numBlocks; j++) {
			if (!blocks[j].isUsed && blocks[j].size >= processes[i].size) {
				blocks[j].process_id = processes[i].id;
				blocks[j].isUsed = true;
				processes[i].block_id = blocks[j].id;
				processes[i].run = true;
				processes[i].waste = blocks[j].size - processes[i].size;
				totalWaste += processes[i].waste;
				break;
			}
		}
	}
	displayStatus(processes, blocks, numProcesses, totalWaste);
	displayPartitions(blocks, numBlocks);
}

void customNextFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks) {

	int totalWaste(0), j(0);
	cout << "\n---------------CUSTOM NEXT FIT---------------\n";
	for (int i = 0; i < numProcesses; i++) {
		while (j < numBlocks) {
			if (!blocks[j].isUsed && blocks[j].size >= processes[i].size) {
				blocks[j].process_id = processes[i].id;
				blocks[j].isUsed = true;
				processes[i].block_id = blocks[j].id;
				processes[i].run = true;
				processes[i].waste = blocks[j].size - processes[i].size;
				totalWaste += processes[i].waste;
				break;
			}
			j++;
		}
	}
	displayStatus(processes, blocks, numProcesses, totalWaste);
	displayPartitions(blocks, numBlocks);
}

void customWorstFit(CustomProcess processes[], CustomBlock blocks[], int numProcesses, int numBlocks) {

	int largest, temp;
	cout << "\n---------------CUSTOM WORST FIT---------------\n";
	for (int i = 0; i < numProcesses; i++) {
		largest = -9999;
		for (int j = 0; j < numBlocks; j++) {
			if (!blocks[j].isUsed) {
				temp = blocks[j].size - processes[i].size;
				if (temp >= 0)
					if (largest < temp) {
						processes[i].block_id = blocks[j].id;
						processes[i].run = true;
						largest = temp;
					}
			}
		}

		if (processes[i].run) {
			blocks[processes[i].block_id].isUsed = true;
			blocks[processes[i].block_id].process_id = processes[i].id;
			blocks[processes[i].block_id].size -= largest;
			if (largest > 0) {
				blocks[numBlocks] = CustomBlock(numBlocks, largest, false);
				cout << "**New Partition made with waste from partition " << blocks[processes[i].block_id].id << " with id of "
					<< numBlocks << "**\n";
				numBlocks++;
			}
		}
	}
	displayStatus(processes, blocks, numProcesses, 0);
	displayPartitions(blocks, numBlocks);
}
