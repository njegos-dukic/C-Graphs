#pragma once

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#define MAX 50
// const int MAX = 50;

typedef struct NODE
{
	int value;
	struct NODE* next;
} node;

extern node* spanningTree;

void readMatrixFromTXT(const char* path, int matrix[MAX][MAX], int* brojCvorova);
void printMatrix(int matrix[MAX][MAX], int count);
int findIndexOfTheNode(node* graph, int count, int value);
void createGraphNodes(node* graph, int count);
void addNodeToList(node* head, int newNodeValue);
void createGraphFromMatrix(node* graph, int matrix[MAX][MAX], int count);
void enqueue(node* element, node queue[], int count, int izlaz, int* ulaz);
int dequeue(node* element, node queue[], int count, int* izlaz, int ulaz);
void printBFS(node* graph, int startValue, int numberOfElements); 
void dfsVisit(node* graph, int numberOfElements, int startValue, char visit[]);
void printDFS(node* graph, int startValue, int numberOfElements);