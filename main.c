#include <stdio.h>
#include "skiplist.h"
#include "util.h"

void printSL(SkipList* sl) 
{
	int i;
	int level = sl->level;
	SL_Node* p;

	Log_Debug("\n=====================SKIPLIST INFO BEGIN=====================\n");
	for (i = level; i >= 0; i--) {
		Log_Debug("Level %d:", i);

		p = sl->header;
		while (p->forward[i]) {
			Log_Debug("%4d", p->forward[i]->key);
			p = p->forward[i];
		}
		Log_Debug("\n");
	}
	Log_Debug("\n======================SKIPLIST INFO END======================\n");
}

// insert test
void Stub_Test01()
{
	int i;
	SkipList* sl;
	
	sl = SL_Create();
	
	for (i = 0; i < 20; i++) {
		SL_Insert(sl, i, NULL);
	}

	printSL(sl);
	Log_Debug("skiplist level:%d\n", Sl_Level(sl));
	Log_Debug("skiplist size:%d\n", SL_Size(sl));
}

// find test
void Stub_Test02()
{
	int i;
	SkipList* sl;
	
	sl = SL_Create();
	
	for (i = 0; i < 20; i++) {
		SL_Insert(sl, i, (void*)(long)i);
	}

	printSL(sl);
	Log_Debug("skiplist level:%d\n", Sl_Level(sl));
	Log_Debug("skiplist size:%d\n", SL_Size(sl));

	void* p;
	for (i = 0; i < 20; i++) {
		p = SL_Find(sl, i);
		Log_Debug("key=%d,value=%p\n", i, p);
	}
}

// remove test
void Stub_Test03()
{
	int i;
	SkipList* sl;
	
	sl = SL_Create();
	
	for (i = 0; i < 20; i++) {
		SL_Insert(sl, i, (void*)(long)i);
	}

	printSL(sl);
	Log_Debug("skiplist level:%d\n", Sl_Level(sl));
	Log_Debug("skiplist size:%d\n", SL_Size(sl));

	for (i = 0; i < 20; i++) {
		SL_Remove(sl, i);
		printSL(sl);
		Log_Debug("skiplist level:%d\n", Sl_Level(sl));
		Log_Debug("skiplist size:%d\n", SL_Size(sl));
	}
}

// clear test
void Stub_Test04()
{
	int i;
	SkipList* sl;
	
	sl = SL_Create();
	
	for (i = 0; i < 20; i++) {
		SL_Insert(sl, i, (void*)(long)i);
	}

	printSL(sl);
	Log_Debug("skiplist level:%d\n", Sl_Level(sl));
	Log_Debug("skiplist size:%d\n", SL_Size(sl));

	SL_Clear(sl);
	printSL(sl);
	Log_Debug("skiplist level:%d\n", Sl_Level(sl));
	Log_Debug("skiplist size:%d\n", SL_Size(sl));
}

int main() 
{	
	// Stub_Test01();

	// Stub_Test02();

	// Stub_Test03();

	Stub_Test04();

	return 0;
}
