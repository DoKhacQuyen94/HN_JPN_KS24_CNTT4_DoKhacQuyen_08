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
    for(int i = 0; i < graph->V; i++) {
        for(int j = 0; j < graph->V; j++) {
            printf("%d ", graph->matrix[i][j]);

        }
        printf("\n");
    }
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
void DFSUtil(Graph *graph, int src, int *visited){
    // b1: In ra dinh src va danh dau da di qua
    printf("%d ", src);
    visited[src] = 1;
    // b2: Ktra ca duong co the di tu ca dinh
    // sd vong lapj voi tat ca dinh trong do thi
    for(int i = 0; i < graph->V; i++) {
        // B3: neu co duong( matrix[src[i]] =1)
            // va dinh tiep theo chua duoc di qua
        if(graph->matrix[src][i] == 1 && visited[i] == 0) {
            //b4: di den dinh tiep theo va thuc hien lai toan bo logic
            DFSUtil(graph, i, visited);
        }

    }

};
void DFS(Graph *graph, int src) {
    int *visited = (int *)calloc(graph->V, sizeof(int));
    printf("Bat dau duyet DFS tu dinh %d: ",src);
    DFSUtil(graph, src, visited);
    printf("\n");
    free(visited);

}
int main(void) {
    int V;
    printf("Nhap dinh cua do thi: ");
    scanf("%d", &V);
    Graph *graph = createGraph(V);
    int src, dest;
    for(int i = 0; i < V; i++) {
        printf("Nhap so start: ");
        scanf("%d", &src);
        printf("Nhap so dest: ");
        scanf("%d", &dest);
        addEdge(graph, src, dest);
    }
    printGraphTrix(graph);
    return 0;
}
