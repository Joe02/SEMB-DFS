//0 to 68

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_NODES 2000
#define N_TO_REACH 86
    
typedef struct
{
    int label;
    bool visited;
} Vertex;

//stack variables

int stack[N_NODES];
int top = -1;
int counter = -1;
int bestSolution = 999999;
int lineCounter = 0;
//graph variables

//array of vertices
Vertex lstVertices[N_NODES];

//adjacency matrix
int adjMatrix[N_NODES][N_NODES];

//vertex count
int vertexCount = 0;

//stack functions

void push(int item)
{
    stack[++top] = item;
}

int pop()
{
    return stack[top--];
}

int peek()
{
    return stack[top];
}

bool isStackEmpty()
{
    return top == -1;
}

//graph functions

//add vertex to the vertex list
void addVertex(int label)
{
    Vertex vertex;
    vertex.label = label;
    vertex.visited = false;
    lstVertices[vertexCount++] = vertex;
}

//add edge to edge array
void addEdge(int start, int end)
{
    adjMatrix[start][end] = 1;
    // adjMatrix[end][start] = 1;
}

//display the vertex
void displayVertex(int vertexIndex)
{
    printf("%03d ", lstVertices[vertexIndex].label);
}

//get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex, int baseCount)
{
    int i;

    for (i = 0; i < vertexCount; i++)
    {
        if (adjMatrix[vertexIndex][i] == 1)
        {
            if (lstVertices[i].visited == false) {
                return i;
            }
            
            if (lstVertices[i].label == N_TO_REACH) {
                // printf("baseCount=%d, best=%d", baseCount+1, bestSolution);
                if (baseCount+1 < bestSolution) {
                    bestSolution = baseCount+1;
                    if (baseCount == 0) {
                        displayVertex(0);
                    }
                    displayVertex(i);
                }
            }
        }
    }

    return -1;
}

void depthFirstSearch()
{
    int i;

    //mark first node as visited
    lstVertices[0].visited = true;

    // //display the vertex
    // displayVertex(0);

    //push vertex index in stack
    push(0);
    int pathName = 1;
    printf("Caminho %d\n", pathName);
    while (!isStackEmpty())
    {
        //get the unvisited vertex of vertex which is at top of the stack
        // printf("top=%d\n", top);
        int unvisitedVertex = getAdjUnvisitedVertex(peek(), top);

        //no adjacent vertex found
        if (unvisitedVertex == -1)
        {
            pop();
            if (top == 0) {
                pathName++;
                printf("\n\nCaminho %d\n", pathName);
            }
        }
        else
        {
            lineCounter++;
            if (lstVertices[unvisitedVertex].label == N_TO_REACH) {
                
                if (top+1 < bestSolution) {
                    bestSolution = top+1;
                }
            }
            if (top == 0) {
                displayVertex(0);
            }
            if (lineCounter > 20) {
                lineCounter = 0;
                printf(" -> \n->");
            }
            lstVertices[unvisitedVertex].visited = true;
            displayVertex(unvisitedVertex);
            push(unvisitedVertex);
        }
    }

    //stack is empty, search is complete, reset the visited flag
    for (i = 0; i < vertexCount; i++)
    {
        lstVertices[i].visited = false;
    }
}

int main()
{
    int i, j;
    for (i = 0; i < N_NODES; i++)
    {
        for (j = 0; j < N_NODES; j++) // matrix to 0
            adjMatrix[i][j] = 0;
    }
    // now create edge from 0 to N_TO_REACH label vertex
    ///JJJ Goes from start to finish directly.
    //addEdge(0, N_TO_REACH); // Creates relation 0 -> N_TO_REACH
    addEdge(0, 28);
    addEdge(0, 29);
    addEdge(0, 33);
    addEdge(29, 30);
    addEdge(30, 32);
    addEdge(30, 67);
    addEdge(32, 35);
    addEdge(35, 62);
    addEdge(62, 73);
    addEdge(73, 95);
    addEdge(73, 93);
    addEdge(76, 93);
    addEdge(95, 96);
    addEdge(96, 97);
    addEdge(67, 68);
    addEdge(68, 100);
    addEdge(100, 99);
    addEdge(98, 99);
    addEdge(69, 65);
    addEdge(70, 65);
    addEdge(70, 63);
    addEdge(70, 71);
    addEdge(36, 65);
    addEdge(72, 71);
    addEdge(72, 94);
    addEdge(75, 94);
    addEdge(75, 74);
    addEdge(75, 60);
    addEdge(61, 60);
    addEdge(61, 38);
    addEdge(83, 73);
    addEdge(83, 76);
    addEdge(59, 76);
    addEdge(59, 40);
    addEdge(41, 40);
    addEdge(41, 23);
    addEdge(58, 40);
    addEdge(58, 43);
    addEdge(57, 43);
    addEdge(57, 77);
    addEdge(92, 77);
    addEdge(92, 78);
    addEdge(92, 91);
    addEdge(90, 91);
    addEdge(80, 90);
    addEdge(80, 89);
    addEdge(88, 89);
    addEdge(88, 82);
    addEdge(88, 87);
    addEdge(87, 86);
    addEdge(87, 83);
    addEdge(93, 76);
    addEdge(76, 59);
    addEdge(40, 58);
    addEdge(58, 43);
    addEdge(43, 57);
    addEdge(77, 92);
    addEdge(92, 91);
    addEdge(91, 90);
    addEdge(90, 80);
    addEdge(80, 89);
    addEdge(89, 88);
    addEdge(88, 87);
    addEdge(87, 86);
    
    addVertex(0);
    addVertex(1);
    addVertex(2);
    addVertex(3);
    addVertex(4);
    addVertex(5);
    addVertex(6);
    addVertex(7);
    addVertex(8);
    addVertex(9);
    addVertex(10);
    addVertex(11);
    addVertex(12);
    addVertex(13);
    addVertex(14);
    addVertex(15);
    addVertex(16);
    addVertex(17);
    addVertex(18);
    addVertex(19);
    addVertex(20);
    addVertex(21);
    addVertex(22);
    addVertex(23);
    addVertex(24);
    addVertex(25);
    addVertex(26);
    addVertex(27);
    addVertex(28);
    addVertex(29);
    addVertex(30);
    addVertex(31);
    addVertex(32);
    addVertex(33);
    addVertex(34);
    addVertex(35);
    addVertex(36);
    addVertex(37);
    addVertex(38);
    addVertex(39);
    addVertex(40);
    addVertex(41);
    addVertex(42);
    addVertex(43);
    addVertex(44);
    addVertex(45);
    addVertex(46);
    addVertex(47);
    addVertex(48);
    addVertex(49);
    addVertex(50);
    addVertex(51);
    addVertex(52);
    addVertex(53);
    addVertex(54);
    addVertex(55);
    addVertex(56);
    addVertex(57);
    addVertex(58);
    addVertex(59);
    addVertex(60);
    addVertex(61);
    addVertex(62);
    addVertex(63);
    addVertex(64);
    addVertex(65);
    addVertex(66);
    addVertex(67);
    addVertex(68);
    addVertex(69);
    addVertex(70);
    addVertex(71);
    addVertex(72);
    addVertex(73);
    addVertex(74);
    addVertex(75);
    addVertex(76);
    addVertex(77);
    addVertex(78);
    addVertex(79);
    addVertex(80);
    addVertex(81);
    addVertex(82);
    addVertex(83);
    addVertex(84);
    addVertex(85);
    addVertex(86);
    addVertex(87);
    addVertex(88);
    addVertex(89);
    addVertex(90);
    addVertex(91);
    addVertex(92);
    addVertex(93);
    addVertex(94);
    addVertex(95);
    addVertex(96);
    addVertex(97);
    addVertex(98);
    addVertex(99);
    addVertex(100);

    depthFirstSearch();
    if (bestSolution != 999999) {
        printf("\n\n\nCusto do melhor caminho partindo de 0 até %d == %d\n", N_TO_REACH, bestSolution);
    } else {
        printf("\n\n\nEsse problema não tem soluções :(\n");
    }
    
    return 0;
}