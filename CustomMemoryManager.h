#ifndef CUSTOM_MEMORY_MANAGER_H
#define CUSTOM_MEMORY_MANAGER_H

struct CustomProcess {
	int id;
	int size;
	bool run;
	int block_id;
	int waste;
	CustomProcess() {};
	CustomProcess(int i, int s, bool r) : id(i), size(s), run(r), block_id(-1), waste(0) {};
	void reset() { run = false; block_id = -1; waste = 0; }
};

struct CustomBlock {
	int id;
	int size;
	bool isUsed;
	int process_id;
	CustomBlock() {};
	CustomBlock(int i, int s, bool u) : id(i), size(s), isUsed(u), process_id(-1) {};
	void reset() { isUsed = false; process_id = -1; }
};

#endif
