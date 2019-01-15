/*
Author: Marc-Andre Descoteaux // v00847029 // mdesco18@uvic.ca
Project: CSC360 A1.1
Date: 2019-01-09

//I know its named like Java; just used to it right now
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail = NULL;
int size = 0;

struct Node* createNode(int x){
	
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->data = x;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

int isEmpty(){
	if(size == 0){
		return 1;
	}else{
		return 0;
	}
}

int getSize(){
	
	return size;
}

//push_front
void insertAtHead(struct Node* newNode){
	
	assert(newNode != NULL);
	
	if(isEmpty()){
		tail = newNode;
	}else if(head != NULL){
		head->prev = newNode;
		newNode->next = head;
	}
	
	head = newNode;
	size++;
}
//push_back
void insertAtTail(struct Node* newNode){
	
	assert(newNode != NULL);
	
	if(isEmpty()){
		head = newNode;
	}else if(head != NULL){
		tail->next = newNode;
		newNode->prev = tail;
	}
	
	tail = newNode;
	size++;
}

void insertAfterNode(struct Node* inNode, struct Node* newNode){
	
	assert(newNode != NULL);
	assert(inNode != NULL);
	
	struct Node* temp = inNode->next;
	
	inNode->next = newNode;
	newNode->next = temp;
	newNode->prev = inNode;
	
	
	if(inNode == tail) tail = newNode;
	else temp->prev = newNode;
	size++;
}

void insertBeforeNode(struct Node* inNode, struct Node* newNode){
	
	assert(newNode != NULL);
	assert(inNode != NULL);
	
	struct Node* temp = inNode->prev;
	
	newNode->prev = temp;
	inNode->prev = newNode;
	newNode->next = inNode;
	
	
	if(inNode == head) head = newNode;
	else temp->next = newNode;
	
	size++;
}

struct Node* getNodeAtPos(int i){
	struct Node* curr = head;
	for(int j = 0; j < i; j++){
		curr = curr->next;
	}
	return curr;
}

void emplace_front(int i, struct Node* newNode){
	
	insertAfterNode(getNodeAtPos(i), newNode);
}

void emplace_back(int i, struct Node* newNode){
	
	insertBeforeNode(getNodeAtPos(i), newNode);
}

void deleteNode(struct Node* inNode){
	
	assert(inNode != NULL);
	
	struct Node* temp_a = inNode->next;
	struct Node* temp_b = inNode->prev;
	
	if(inNode == head){
		head = temp_a;
		head->prev = NULL;
	}else if(inNode == tail){
		tail = temp_b;
		tail->next = NULL;
	}else{
		temp_a->prev = temp_b;
		temp_b->next = temp_a;
	}
	
	size--;
	free(inNode);
}

void clear(){
	
	for(struct Node* curr = head; curr != NULL; curr = curr->next){
		deleteNode(curr);
	}
	assert(isEmpty());
}

struct Node* peekFront(){
	return head;
}

struct Node* peekBack(){
	return tail;
}

struct Node* popFront(){
	struct Node* temp = head;
	deleteNode(head);
	return temp;
}

struct Node* popBack(){
	struct Node* temp = tail;
	deleteNode(tail);
	return temp;
}

void setVal(struct Node* inNode, int x){
	
	inNode->data = x;
}

int getVal(struct Node* inNode){
	
	return inNode->data;
}

void reverse(){

	for(struct Node* curr = head; curr != NULL; curr = curr->next){
		curr->prev = curr->next;
	}
	
	struct Node* oldNode = head;
	struct Node* curr = head;
	curr->next = NULL;
	curr = curr->prev;
	for(;curr != NULL; curr = curr->prev){
		curr->next = oldNode;
		oldNode = curr;
	}
	
	oldNode = head;
	head = tail;
	tail = oldNode;
}

void printList(){
	int i = 0;
	for(struct Node* curr = head; curr != NULL; curr = curr->next){
		if(curr == head) printf("---Head---\n");
		printf("Node %d: %d\n", i, curr->data);
		if(curr == tail) printf("---Tail---\n");
		i++;
	}
}

void printBackwards(){
	int i = size-1;
	for(struct Node* curr = tail; curr != NULL; curr = curr->prev){
		if(curr == tail) printf("---Tail---\n");
		printf("Node %d: %d\n", i, curr->data);
		if(curr == head) printf("---Head---\n");
		i--;	
	}
}

void checkSize(){
	
	int i = 0;
	for(struct Node* curr = head; curr != NULL; curr = curr->next){ i++; };
	
	assert(size == i);
	
	printf("List size is %d and correctly set.\n", size);
}

int main(){
	
	printf("\nThis is my Doubly Linked List Implementation\nRunning test...\n");
	
	insertAtHead(createNode(6));
	insertAtTail(createNode(4));
	insertAfterNode(head, createNode(0));
	insertAtTail(createNode(3));
	insertBeforeNode(tail, createNode(3));
	insertBeforeNode(tail, createNode(5));
	insertAfterNode(tail, createNode(5));
	deleteNode(head);
	deleteNode(getNodeAtPos(3));
	insertAtTail(createNode(2));
	insertAtTail(createNode(4));
	insertBeforeNode(head, createNode(6));
	insertBeforeNode(getNodeAtPos(4), createNode(5)); 
	insertAfterNode(getNodeAtPos(7), createNode(9));
	printList();
	printBackwards();
	checkSize();
	
	printf("\nTesting reverse...\n");
	
	reverse();
	printList();
	printBackwards();
	
	printf("\nDone.");
}