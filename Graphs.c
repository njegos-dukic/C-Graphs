#include "GraphModule.h"

int main()
{
	int graphMatrix[MAX][MAX] = { 0 };
	int numberOfNodes;
	readMatrixFromTXT(".\\Input.txt", graphMatrix, &numberOfNodes);
	printMatrix(graphMatrix, numberOfNodes);
	
	node* graph = (node*)calloc(sizeof(node), numberOfNodes);
	createGraphNodes(graph, numberOfNodes);
	createGraphFromMatrix(graph, graphMatrix, numberOfNodes);
	
	int start;
	printf("\nSpcify initial node: ");
	scanf_s("%d", &start);

	// system("cls");
	printBFS(graph, start, numberOfNodes);
	printDFS(graph, start, numberOfNodes);

	return 0;
}
