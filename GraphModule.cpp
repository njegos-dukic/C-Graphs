#include "GraphModule.h"

void readMatrixFromTXT(const char* path, int matrix[MAX][MAX], int* numberOfNodes)
{
	FILE* inputFile;
	char ch;
	int next = 0, i = 0, j = 0;
	int numberOfVertices = 0;

	fopen_s(&inputFile, path, "r");

	if (inputFile == NULL)
	{
		printf("Can't open file.\n");
		exit(1);
	}

	else
		while (ch = fgetc(inputFile))
		{
			if (isdigit(ch))
				next = (next * 10) + (ch - '0');

			else if (ch == ' ' || ch == '\n' || ch == EOF)
			{
				matrix[i][j] = next;
				next = 0;
				j++;

				if (ch == '\n' || ch == EOF)
				{
					i++;
					j = 0;

					if (ch == EOF)
					{
						numberOfVertices++;
						break;
					}
				}
				numberOfVertices++;

			}
		}
	*numberOfNodes = sqrt(numberOfVertices);
}

void printMatrix(int matrix[MAX][MAX], int count)
{
	printf("Adjacency matrix: \n\n   ");
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
			printf("%d ", matrix[i][j]);

		printf("\n   ");
	}
}

int findIndexOfTheNode(node* graph, int count, int value)
{
	for (int i = 0; i < count; i++)
		if ((graph + i)->value == value)
			return i;
}

void createGraphNodes(node* graph, int count)
{
	int value;
	printf("\n");
	char c;
	printf("Do you want to enter the values for each node [Y/N]: ");
	scanf_s("%c", &c, 1);
	
	while ((getchar()) != '\n');

	if (c == 'y' || c == 'Y')
		printf("\n");

	else
		printf("\nNodes initialized as: [1, %d].\n", count);
	
	for (int i = 0; i < count; i++)
	{
		if (c == 'y' || c == 'Y')
		{
			printf("Input value of node %d: ", i + 1);
			scanf_s("%d", &value);

			if (findIndexOfTheNode(graph, i, value) == i)
				(graph + i)->value = value;

			else
			{
				printf("  -- Specified node already exists.");
				Sleep(2500);
				system(" ");
				printf("\33[2K"); 	// Deletes current line.
				printf("\033[A"); 	// Moves cursor one line up.
				printf("\33[2K"); 	// Deletes line.
				printf("\r");		// Moves cursor to the beggining of the line.
				i--;
			}
		}
		else
			(graph + i)->value = i + 1;
	}

	return;
}

void addNodeToList(node* head, int newNodeValue)
{
	node* toAdd = (node*)calloc(sizeof(node), 1);
	toAdd->value = newNodeValue;

	if (head == NULL)
	{
		head = toAdd;
		return;
	}

	while (head->next != NULL)
		head = head->next;

	head->next = toAdd;

	return;
}

void createGraphFromMatrix(node* graph, int matrix[MAX][MAX], int count)
{
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (matrix[i][j] == 1)
				addNodeToList(graph + i, (graph + j)->value);
}

void enqueue(node* element, node queue[], int count, int output, int* input)
{
	if (((*input + 1) % count) == output)
		return;

	(*input) = (*input + 1) % count;
	queue[*input] = *element;

	return;
}

int dequeue(node* element, node queue[], int count, int* output, int input)
{
	if (input == *output)
		return 0;

	(*output) = (*output + 1) % count;
	*element = queue[*output];

	return 1;
}

void printBFS(node* graph, int startValue, int numberOfElements)
{
	if (findIndexOfTheNode(graph, numberOfElements, startValue) == numberOfElements)
	{
		printf("\nNode is not in graph.\n");
		return;
	}

	printf("\nBFS starting from %d:\n\n", startValue);

	node queue[MAX] = { 0 };
	int input = 0, output = 0;
	node nd;
	char visit[MAX] = { 0 };

	visit[findIndexOfTheNode(graph, numberOfElements, startValue)] = 1;
	enqueue(graph + findIndexOfTheNode(graph, numberOfElements, startValue), queue, numberOfElements, output, &input);
	while (dequeue(&nd, queue, numberOfElements, &output, input))
	{
		printf("   Visiting node: %d\n", nd.value);
		node* current = graph + findIndexOfTheNode(graph, numberOfElements, nd.value);
		current = current->next;
		while (current != NULL)
		{
			int nextToVisit = findIndexOfTheNode(graph, numberOfElements, current->value);

			if (!visit[nextToVisit])
			{
				visit[nextToVisit] = 1;
				enqueue(graph + nextToVisit, queue, numberOfElements, output, &input);
			}

			current = current->next;
		}
	}

}

void dfsVisit(node* graph, int numberOfElements, int startValue, char visit[])
{
	visit[findIndexOfTheNode(graph, numberOfElements, startValue)] = 1;
	node* current = graph + findIndexOfTheNode(graph, numberOfElements, startValue);
	printf("   Visiting node: %d\n", current->value);
	current = current->next;

	while (current != NULL)
	{
		if (!visit[findIndexOfTheNode(graph, numberOfElements, current->value)])
		{
			printf("   %d - %d\n", startValue, current->value);
			dfsVisit(graph, numberOfElements, current->value, visit);
		}
		current = current->next;
	}
}

void printDFS(node* graph, int startValue, int numberOfElements)
{
	if (findIndexOfTheNode(graph, numberOfElements, startValue) == numberOfElements)
	{
		printf("\nnd ne postoji u grafu.\n");
		return;
	}

	printf("\nDFS starting from: %d:\n\n", startValue);
	char visit[MAX] = { 0 };
	dfsVisit(graph, numberOfElements, startValue, visit);
}