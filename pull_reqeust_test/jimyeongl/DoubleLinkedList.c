#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

linkedList_h* createLinkedList_h(void) {
	linkedList_h* DL;
	DL = (linkedList_h*)malloc(sizeof(linkedList_h));
	DL->head = NULL;
	return DL;
}

void printList(linkedList_h* DL) {
	listNode* p;
	printf("DL = (");

	p = DL->head;
	while (p != NULL) {
		printf("%s", p->data);
		p = p->rlink;
		if (p != NULL)printf(", ");
	}
	printf(") \n");
}

void insertNode(linkedList_h* DL, listNode* pre, char* x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	
	if (DL->head == NULL) {
		newNode->rlink = NULL;
		newNode->llink = NULL;
		DL->head = newNode;
	}
	else if(pre ==NULL) {				//리스트에 데이터가 있는 상태에서 첫번째 자리에 문자를 넣으려면
		DL->head->llink = newNode;		//head가 가리키는 첫번째 노드의 왼쪽링크필드에 새노드 주소 연결
		newNode->rlink = DL -> head;	//새 노드의 오른쪽 링크필드에 첫번째노드의 주소 연결
		newNode->llink = NULL;			//새 노드가 첫노드가 되야 되기때문에 왼쪽 데이터 필드는 NULL
		DL->head = newNode;				//헤드가 새 노드를 가리키도록 연결
	}
	else {
		newNode->rlink = pre->rlink;
		pre->rlink = newNode;
		newNode->llink = pre;
		if (newNode->rlink != NULL)
			newNode->rlink->llink = newNode;
	}
}
void deleteNode(linkedList_h* DL, listNode* old) {
	if (DL->head == NULL)return;	//공백 리스트인 경우 삭제 연산 중단
	else if (old == NULL)return;	//삭제할 노드가 없을 경우 삭제 중단
	else {
		/*if(DL->head -> rlink == NULL)DL -> head = NULL;*/
		if (old->rlink == NULL) {
			if (old->llink == NULL) {
				DL->head = NULL;}
			else {
				old->llink->rlink = old->rlink;
			}
		}
		else if (old->llink == NULL) {	
			if (old->rlink == NULL) {
				DL->head = NULL;}
			else {
				old->rlink->llink = old->llink;
				DL->head = old->rlink;
			}
		}
		else {
			old->llink->rlink = old->rlink;
			old->rlink->llink = old->llink;
		}
		
		free(old);
	}
}

listNode* searchNode(linkedList_h* DL, char* x) {
	listNode* temp;
	temp = DL->head;
	while (temp != NULL) {
		if (strcmp(temp->data, x) == 0)return temp;
		else temp = temp->rlink;
	}
	return temp;
}