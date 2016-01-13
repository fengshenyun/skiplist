#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"
#include "util.h"


int SL_RandomLevel() 
{
    int level = 0;
    while ((random()&0xFFFF) < (SKIPLIST_P * 0xFFFF))
        level += 1;
    return (level < (SKIPLIST_MAXLEVEL-1)) ? level : (SKIPLIST_MAXLEVEL-1);
}

SL_Node* SL_CreateNode(int level, int key, void* obj) 
{
	SL_Node* sln;

	sln = (SL_Node *)zmalloc(sizeof(SL_Node) + level * sizeof(SL_Node *));
	sln->key = key;
	sln->obj = obj;
	
	return sln;
}

SkipList* SL_Create()
{
	int i;
	SkipList* sl;

	sl = (SkipList *)zmalloc(sizeof(SkipList));
	sl->level = 0;
	sl->size = 0;

	sl->header = SL_CreateNode(SKIPLIST_MAXLEVEL, 0, NULL);
	for (i = 0; i < SKIPLIST_MAXLEVEL; i++) {
		sl->header->forward[i] = NULL;
	}

	return sl;
}

int SL_Insert(SkipList* sl, int key, void* obj)
{
	int i;
	int level;
	SL_Node* p = NULL;
	SL_Node* sln = NULL;
	SL_Node* update[SKIPLIST_MAXLEVEL];

	for (i = 0; i < SKIPLIST_MAXLEVEL; i++) {
		update[i] = sl->header;
	}

	for (i = 0; i <= sl->level; i++) {
		p = sl->header;
		while (p->forward[i] && (p->forward[i]->key < key)) {
			p = p->forward[i];
		}
		update[i] = p;
	}

	level = SL_RandomLevel();
	Log_Debug("new node level:%d\n", level);

	// update skiplist level
	if (level > sl->level) {
		sl->level = level;
	}

	sln = SL_CreateNode((level+1), key, obj);
	for (i = 0; i <= level; i++) {
		sln->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = sln;
	}

	sl->size ++;
	return 0;
}

void* SL_Find(SkipList* sl, int key)
{
	int i;
	int level = sl->level;
	SL_Node* p = sl->header;

	for (i = level; i >= 0; i--) {
		while (p->forward[i] && p->forward[i]->key < key) {
			p = p->forward[i];
		}

		if (p->forward[i] && p->forward[i]->key == key) {
			return p->forward[i]->obj;
		}
	}

	return NULL;
}

int SL_Remove(SkipList* sl, int key)
{
	int i;
	int level = -1;
	SL_Node* p = sl->header;
	SL_Node* update[SKIPLIST_MAXLEVEL];

	for (i = sl->level; i >=0; i--) {
		while (p->forward[i] && p->forward[i]->key < key) {
			p = p->forward[i];
		}

		if (p->forward[i] && p->forward[i]->key == key) {
			if (i > level) {
				level = i;
			}

			update[i] = p;
		}
	}

	if (-1 == level) {
		Log_Debug("No such key[%d] in skiplist\n", key);
		return 0;
	}

	p = update[0]->forward[0];
	for (i = 0; i <= level; i++) {
		update[i]->forward[i] = p->forward[i];
	}

	// update skiplist level
	for (i = sl->level; i >=0; i--) {
		if (sl->header->forward[i] == NULL) {
			sl->level --;
		} else {
			break;
		}
	}

	// update skiplist size
	sl->size --;

	// free memory
	zfree(p);
	return 0;
}

void SL_Clear(SkipList* sl)
{
	int i;
	SL_Node* cur = NULL;
	SL_Node* pre = NULL;

	cur = sl->header->forward[0];
	while (cur) {
		pre = cur;
		cur = cur->forward[0];

		// debug
		Log_Debug("node[%d] has been clear.\n", pre->key);
		
		// free skiplist node
		zfree(pre);
	}

	for (i = 0; i < SKIPLIST_MAXLEVEL; i++) {
		sl->header->forward[i] = NULL;
	}
}

int SL_Size(SkipList* sl)
{
	return sl->size;
}

int Sl_Level(SkipList* sl)
{
	return sl->level;
}

