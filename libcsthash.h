
#pragma  once
#include "rbtree.h"

struct real_node{

	char identify[100];  /*����ʾ��*/
	int  vnode_count; /*��������Ŀ*/
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
