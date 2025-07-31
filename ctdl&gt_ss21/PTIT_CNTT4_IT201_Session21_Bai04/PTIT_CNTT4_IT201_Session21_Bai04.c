#include <stdio.h>
#include <stdlib.h>
// xay dung cau truc do thi
typedef struct Graph{
    int V;
    int **matrix;
}Graph;
// xd ham khoi tao
Graph *createGraph(int V){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    // cap phat bo nho cho mang 2 chieu
    graph->matrix = (int **)malloc(V*sizeof(int *));
    for(int i = 0; i < V; i++) {
        // cap phat bo nho cho tung mang con
        graph->matrix[i] = (int *)calloc(V,sizeof(int));
    }
    return graph;
}

// xay dung ham ket noi 2 dinh
void addEdge(Graph *graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;
}


// in ma tran
void printGraphTrix(Graph *graph) {
    printf("[\n");
    for(int i = 0; i < graph->V; i++) {
        for(int j = 0; j < graph->V; j++) {
            printf("%d ", graph->matrix[i][j]);
            if (j != graph->V - 1 ) {
                printf(",");
            }
        }

        printf("\n");
    }
    printf("]\n");
}

void printGraph(Graph *graph) {
    for(int i = 0; i < graph->V; i++) {
        printf("%d: ", i);
        for(int j = 0; j < graph->V; j++) {
            if(graph->matrix[i][j] == 1) {
                printf("%d " , j);
            }

        }
        printf("\n");
    }
}
void add(Graph* graph, int start, int end) {
    graph->matrix[start][end] = 1;
}
int main(void) {
    Graph *graph = createGraph(3);
    int start,end;
    printf("Nhap gia tri start: ");
    scanf("%d", &start);
    printf("Nhap gia tri end: ");
    scanf("%d", &end);
    add(graph, start, end);
    printGraphTrix(graph);
    return 0;
}
