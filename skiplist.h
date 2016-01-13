#ifndef _SKIP_LIST__H__
#define _SKIP_LIST__H__

#define SKIPLIST_MAXLEVEL 32
//#define SKIPLIST_P 0.25 
#define SKIPLIST_P 0.5

typedef struct tagSL_Node SL_Node;
struct tagSL_Node {
	int key;
	void* obj;
	SL_Node* forward[1];
};

typedef struct tagSkipList SkipList;
struct tagSkipList {
	int level;
	int size;
	SL_Node* header;
};

// Create a Skiplist
SkipList* SL_Create();

// Insert a node to skiplist
int SL_Insert(SkipList* sl, int key, void* obj);

// Find value by key
void* SL_Find(SkipList* sl, int key);

// Remove a node 
int SL_Remove(SkipList* sl, int key);

// Clear skiplist
void SL_Clear(SkipList* sl);

// Get the number of skiplist node
int SL_Size(SkipList* sl);

// Show the the level of skiplist
int Sl_Level(SkipList* sl);

#endif

