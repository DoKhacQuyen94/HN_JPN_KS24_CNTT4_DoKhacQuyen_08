#include <stdio.h>
#include <stdlib.h>
//Yêu cầu: thêm phần tử vào cây


// B1: Xây ựng cấu trúc du lieu ca thiet
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;

}Node;

//B2: xd ham khoi tao
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// B3: xay dung ca phuong thu cay
//b3.1: xd ham preoder
void preorderDFS(Node* root) { // root->left->right
    // xay dung dieu kien dung
    if (root == NULL) {
        return;
    }
    // in ra node dang duoc set
    printf("%d ", root->data);
    //giai quyet bai toan voi cay con ben tay trai
    preorderDFS(root->left);
    // giai quyet bai toan ben tay phai
    preorderDFS(root->right);
}
//B3.2 xau dung ham inorder
void inorderDFS(Node* root) { // left->root->right
    // xd dieu kien dung
    if (root == NULL) {
        return;
    }
    // giai quyet bai toan cay con ben trai
    inorderDFS(root->left);
    //tin node duoc xet
    printf("%d ", root->data);
    // giai quyet bai toan ben phai
    inorderDFS(root->right);
}
//B3.3 xd ham postorder
void postorderDFS(Node* root) { /// left-right-root
    //xd dieu kien dung
    if (root == NULL) {
        return;
    }
    //giai quyet bai toan ben trai
    postorderDFS(root->left);
    // giai quyet bai toan ben phai
    postorderDFS(root->right);
    // in node  duoc xet
    printf("%d ", root->data);
}
typedef struct Queue {
    Node** arr;
    int capacity;
    int front;
    int rear;
}Queue;
// xd ham khoi tao ham doi
Queue* createQueue(int capacity) {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->arr = (Node**)malloc(sizeof(Node*) * capacity);
    newQueue->capacity = capacity;
    newQueue->front = 0;
    newQueue->rear = -1;
    return newQueue;
}
// xd ham kiem tra hang doi trong
int isEmpty(Queue* queue) {
    if (queue->rear < queue->front) {
        return 1;
    }
    return 0;
}
void enqueue(Queue* queue, Node* node) {
    if (queue->rear == queue->capacity-1) {
        return;
    }
    queue->rear++;
    queue->arr[queue->rear] = node;

}
// duyet theo tung tang
void levelorder(Node* root) {
    // ktra cay
    if (root == NULL) {
        return;
    }
    // khoi tao hang doi
    Queue* queue = createQueue(100);

    // dua node vao hang doi
    enqueue(queue, root);
    //thuc hien vong lap den khi hang doi trong
    while (!isEmpty(queue)){
        // lay node ra khoi hang doi va in ra
        Node* node = queue->arr[queue->front++];
        printf("%d ", node->data);
        // ktra va them con trai vao hang doi
        if (node->left != NULL) {
            enqueue(queue, node->left);
        }
        // ktra va them con phai vao hang doi
        if (node->right != NULL) {
            enqueue(queue, node->right);
        }
    }
}
void print(Node* root) {
    printf("node = {\n");
    printf("\tdata: ");
    inorderDFS(root);
    printf(",\n");
    printf("\tleft-> NULL\n");
    printf("\tright-> NULL\n");
    printf("}\n");
}
Node* dequeue(Queue* queue) {
    if (!isEmpty(queue)) {
        return queue->arr[queue->front++];
    }
}
Node* pushTree(Node* root,int value) {
    Node* newNode = createNode(value);
    if (root == NULL) {
        root = newNode;
        return root;
    }
    Queue* queue = createQueue(100);
    enqueue(queue, root);
    while (!isEmpty(queue)) {
        Node* node = dequeue(queue);
        if (node->left == NULL) {
            node->left = newNode;
            break;
        }else{
            enqueue(queue, node->left);
        }
        if (node->right == NULL) {
            node->right = newNode;
            break;
        }else {
            enqueue(queue, node->right);
        }
    }
    return root;
}
int countLeaves(Node* root) {
    int count = 0;
    if (root == NULL) {
        return 0;
    }
    Queue* queue = createQueue(100);
    enqueue(queue, root);
    while (!isEmpty(queue)) {
        Node *node = dequeue(queue);
        if (node->left == NULL && node->right == NULL) {
            count++;
        }
        if (node->left != NULL) {
            enqueue(queue, node->left);
        }
        if (node->right != NULL) {
            enqueue(queue, node->right);
        }
    }
    return count;
}
int main(void) {
    Node* root = NULL;
    int n;
    printf("Nhap so phan tu muon them: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        printf("Nhap gia tri muon them: ");
        scanf("%d", &x);
        root = pushTree(root, x);
    }
    printf("\n");
    printf("Levelorder:\n");
    levelorder(root);
    int count =countLeaves(root);
    printf("\nNumber of leaves: %d\n", count);



    return 0;
}