/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#4
* List.c 
* C source code file for List ADT program
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include"List.h"
#include"Matrix.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    void* pointer;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int cur;
} ListObj;

typedef ListObj* List;

Node newNode(void* pointer){
    Node n = malloc(sizeof(NodeObj));
    assert( n != NULL );
    n->pointer = pointer;
    n->prev = NULL;
    n->next = NULL;
    return n;
}


List newList(void){
    List L = malloc(sizeof(ListObj));
    assert( L != NULL );
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cur=-1;
    return L;
}

void freeNode(Node* pN){
    if (pN!=NULL && *pN!=NULL) {
        free(*pN);
        *pN = NULL;
    }
}

void freeList(List *pL) {
    Node node = (*pL)->front;
    while(node!=NULL) {
        Node cur = node;
        node = node->next;
        freeNode(&cur);
    }
    free(*pL);
    *pL = NULL;
}

int length(List L){
    if(L==NULL){
	printf("List Error: length() called on NULL List\n");
	exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L){
    return L->cur;
}

void* front(List L){
    if(L==NULL){
	printf("List Error: front() called on NULL List\n");
	exit(EXIT_FAILURE);
    }
    return L->front->pointer;
}

void* back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   return L->back->pointer;
}

void* get(List L){
    if(L==NULL){
	printf("List Error: get() called on NULL List\n");
	exit(EXIT_FAILURE);
    }
    return L->cursor->pointer;
}


void clear(List L){
   if (L ==NULL){
      printf("List Error: calling equals() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   if(L != NULL){
	    while(length(L)>0){
	        deleteBack(L);
	    }
    }
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->cur= -1;
}

void set(List L, void* x){
    if (L == NULL){
        printf("List Error: calling set() on NULL List\n");
        exit(EXIT_FAILURE);
        }
    if (length(L) <= 0 ){
        printf("List Error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("index Error\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->pointer = x;
}

void moveFront(List L){
    if(L==NULL){
	printf("List Error: moveFront() called on NULL List\n");
	exit(EXIT_FAILURE);
    }
    if(length(L)>0){
        L->cursor = L->front;
        L->cur = 0;
    }
}

void moveBack(List L){
    if(L==NULL){
	printf("List Error: moveBack() called on NULL List\n");
	exit(EXIT_FAILURE);
    }
    if(length(L)>0){
        L->cursor = L->back;
        L->cur = length(L)-1;
    }
}

void movePrev(List L){
    if(L->cursor!=NULL && L->cursor!=L->front){
        L->cursor = L->cursor->prev;
        L->cur--;
    }
    else if(L->cursor!=NULL && L->cursor==L->front){
        L->cursor = NULL;
        L->cur = -1;
    }
}

void moveNext(List L){
    if(L->cursor!=NULL && L->cursor!=L->back){
        L->cursor = L->cursor->next;
        L->cur++;
    }
    else if(L->cursor!=NULL && L->cursor==L->back){
        L->cursor = NULL;
        L->cur = -1;
    }
}

void prepend(List L, void* data){
    Node node = newNode(data);
    if(length(L)==0){
        L->front = L->back = node;
    }else{ 
        L->front->prev = node;
        node->next = L->front;
        L->front = node;
    }
    if(L->cur != -1){
	L->cur++;
    }
    L->length++;
}

void append(List L, void* data){	
	if(L->length > 0){
		Node node = newNode(data);
		L->back->next = node;
		node->prev = L->back;
		node->next = NULL;
		L->back = node;
		L->length++;
	} else {
		Node node = newNode(data);
		L->front = node;
		L->back = node;
		L->cursor = node;
		L->cur = 0;
		node->prev = NULL;
		node->next = NULL;
		L->length++;
	}
}

void insertBefore(List L, void* data){
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List\n");
      exit(EXIT_FAILURE);
   }
    Node node = newNode(data);
    if(L->cursor == L->front){
        node->next = L->cursor;
        L->cursor->prev = node;
        L->front = node;
    }else{
        node->next = L->cursor;
        node->prev = L->cursor->prev;
        L->cursor->prev->next = node;
        L->cursor->prev = node;
    }
    L->cur++;
    L->length++;
}

void insertAfter(List L, void* data){
  if(L==NULL){
	printf("List Error: insertAfter() called on NULL List\n");
	exit(EXIT_FAILURE);
    }
    Node node = newNode(data);
    Node next = L->cursor->next;
    if(L->cursor == L->back){
        L->cursor->next = node;
        node->prev = L->cursor;
        L->back = node;
    }else{
        L->cursor->next = node;
        node->prev = L->cursor;
        node->next = next;
        next->prev = node;
    }
    L->length++;
}

void deleteFront(List L){
    if(L==NULL){
        printf("List Error: deleteFront() called on NULL List\n");
        exit(EXIT_FAILURE);
    }

	Node x = L->front;

	if(L->length > 0){
		if(L->length == 1){
			L->front = NULL;
			L->back = NULL;
			L->cursor = NULL;
			L->cur = -1;
		} else {
			L->front = L->front->next;
			L->front->prev = NULL;
			L->cur--;
		}
			L->length--;
	}

	freeNode(&x);
}

void deleteBack(List L){
    if(L==NULL){
        printf("List Error: deleteFront() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
	if(L->length >0){

	Node x = L->back;
	if(L->length == 1){
		L->back = NULL;
		L->front = NULL;
		L->cursor = NULL;
		L->cur = -1;
	} else {
		if(L->cur == L->length -1){
			L->cur = -1;
			L->cursor = NULL;
		}
			L->back = L->back->prev;
			L->back->next = NULL;
	}
	L->length--;

	freeNode(&x);
	}
}

void delete(List L){
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == L->front){
        deleteFront(L);
    }else if(L->cursor == L->back){
        deleteBack(L);
    }else{
        Node N = L->cursor->prev;
        Node M = L->cursor->next;
        N->next = M;
        M->prev = N;
        freeNode(&(L->cursor));
        L->length--;
    }
    L->cur = -1;
}