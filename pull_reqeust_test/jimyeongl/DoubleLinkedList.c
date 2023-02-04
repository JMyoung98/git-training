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
	else if(pre ==NULL) {				//����Ʈ�� �����Ͱ� �ִ� ���¿��� ù��° �ڸ��� ���ڸ� ��������
		DL->head->llink = newNode;		//head�� ����Ű�� ù��° ����� ���ʸ�ũ�ʵ忡 ����� �ּ� ����
		newNode->rlink = DL -> head;	//�� ����� ������ ��ũ�ʵ忡 ù��°����� �ּ� ����
		newNode->llink = NULL;			//�� ��尡 ù��尡 �Ǿ� �Ǳ⶧���� ���� ������ �ʵ�� NULL
		DL->head = newNode;				//��尡 �� ��带 ����Ű���� ����
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
	if (DL->head == NULL)return;	//���� ����Ʈ�� ��� ���� ���� �ߴ�
	else if (old == NULL)return;	//������ ��尡 ���� ��� ���� �ߴ�
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