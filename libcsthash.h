
#pragma  once
#include "rbtree.h"

struct real_node{

	char identify[100];  /*结点标示串*/
	int  vnode_count; /*虚拟结点数目*/
};

struct virtual_node{
	int hash;
	real_node * rnode;
};

typedef util_rbtree_t cst_hash;

cst_hash * cst_hash_new();

void cst_hash_destory(cst_hash * hs);

int cst_hash_create_node(cst_hash * hs, const char * identify, int vcount);

int cst_hash_destory_node(cst_hash * hs, const char * identify, int vcount);

real_node * cst_hash_search_node(cst_hash * hs, const char * identify);
