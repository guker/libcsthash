#include "libcsthash.h"
#include "string.h"
#include "stdio.h"

int ap_hash(char * key)
{
    unsigned int hash = 0;
    for (int i= 0; *key; i++){
        if ((i & 1) == 0){
            hash ^= ((hash << 7) ^ (*key++) ^ (hash >> 3));
        }
        else{
            hash ^= (~((hash << 11) ^ (*key++) ^ (hash >> 5)));
        }
    }
    return (hash & 0x7FFFFFFF);
}


cst_hash * cst_hash_new(){
	 cst_hash * hs =  new cst_hash;
	 util_rbtree_init(hs);
	 return hs;
}

void cst_hash_destory(cst_hash * hs){
	util_rbtree_clear(hs);
	delete hs;
}

int cst_hash_create_node(cst_hash * hs, const char * identify, int vcount){

	if(vcount <=0){
		return -1;
	}

	real_node * rnode = new real_node;
	memset(rnode->identify, 0, sizeof(rnode->identify));
	strncpy(rnode->identify, identify, sizeof(rnode->identify));
	rnode->vnode_count = vcount;

	char item[256] = {0};
	for (int i = 0; i< vcount; i++){

		sprintf(item, "%s#%d", identify, i);
		int hash = ap_hash(item);
		if(util_rbtree_search(hs,hash)){
			continue;
		}
		virtual_node * vnode = new virtual_node;
		vnode->hash = hash;
		vnode->rnode = rnode;

		util_rbtree_node_t * rb_node = new util_rbtree_node_t;
		rb_node->data = vnode;
		rb_node->key = hash;

		util_rbtree_insert(hs, rb_node);
	}
	return 0;
}

int cst_hash_destory_node(cst_hash * hs, const char * identify, int vcount){

	char item[256] = {0};
	for (int i = 0; i< vcount; i++){

		sprintf(item, "%s#%d", identify, i);
		int hash = ap_hash(item);
		util_rbtree_node_t *rb_node = util_rbtree_search(hs, hash);
		if(!rb_node){
			continue;
		}

		virtual_node * vnode = (virtual_node *)rb_node->data;
		real_node * rnode = vnode->rnode;

		if(!strcmp(rnode->identify, identify) && vnode->hash == hash){
			util_rbtree_delete(hs, rb_node);
			delete rb_node;
			delete vnode;
		}

		if(i + 1 == vcount && rnode){
			delete rnode;
		}
	}	
	return 0;
}

real_node * cst_hash_search_node(cst_hash * hs, const char * identify){
	int hash = ap_hash((char*)identify);
	util_rbtree_node_t * rb_node = util_rbtree_lookup(hs, hash);
	if(rb_node){
		return ((virtual_node*)rb_node->data)->rnode;
	}
	return NULL;
}