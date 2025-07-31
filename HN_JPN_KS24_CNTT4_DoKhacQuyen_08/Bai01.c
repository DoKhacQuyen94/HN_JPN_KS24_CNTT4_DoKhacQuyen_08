#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Operation {
    char url[100];
    char timestamp[50];
}Operation;

typedef struct Stack {
    Operation operation[1000];
    int top;
}Stack;
 typedef struct Node {
     Operation operation;
     struct Node* next;
     struct Node* prev;
 }Node;
typedef struct History {
    Node* head;
    Node* tail;

}History;
void initStack(Stack* stack) {
    stack->top = -1;
}
int isEmpty(Stack* stack) {
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}
int isFull(Stack* stack) {
    if (stack->top == 1000-1) {
        return 1;
    }
    return 0;
}
void push(Stack* stack, Operation operation) {
    if (isFull(stack) == 1) {
        printf("Stack day\n");
        return;
    }
    stack->operation[++stack->top] = operation;
}
Operation* pop(Stack* stack) {
    if (isEmpty(stack) == 1) {
        printf("Stack trong\n");
        return NULL;
    }
    return &stack->operation[stack->top--];
}
Operation* peek(Stack* stack) {
    if (isEmpty(stack) == 1) {
        printf("Stack trong\n");
        return NULL;
    }
    return &stack->operation[stack->top];
}
void clearStack(Stack* stack) {
    stack->top = -1;
}
void initHistory(History* history) {
    history->head = NULL;
    history->tail = NULL;
}
void getTime(char* buffer) {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 50, "%H:%M:%S", timeinfo);

}
void pushHistory(History* history, Operation operation) {
    if (operation.url[0] == '\0') {
        printf("Loi: URL trong, khong the them vao lic su");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    newNode->operation = operation;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (!history->head) {
        history->head = newNode;
        history->tail = newNode;
    }else {
        newNode->prev = history->tail;
        history->tail->next = newNode;
        history->tail = newNode;
    }

}
void displayHistory(History* history) {
    if (!history->head) {
        printf("Lich su trong\n");
        return;
    }
    Node* current = history->head;
    while (current) {
        if (current->operation.url[0] != '\0') {

            printf("Url: %s\n", current->operation.url);

        }else {
            printf("Url: Khong hop le\n");
        }
        if (current->operation.timestamp[0] != '\0') {
            printf("Timestamp: %s\n", current->operation.timestamp);
        }else {
            printf("TimeStamp: Khong hop le\n");
        }
        current = current->next;
    }
}

void clearHistory(History* history) {
    Node* current = history->head;
    while (current) {
        Node* temp =current;
        current = current->next;
        free(temp);
    }
    history->head = NULL;
    history->tail = NULL;
}

typedef struct WebHistory {
    Stack back;
    Stack forward;
    History history;
    char currentUrl[100];

}WebHistory;

void createWebHistory(WebHistory* webHistory) {
    initStack(&webHistory->back);
    initStack(&webHistory->forward);
    initHistory(&webHistory->history);
    webHistory->currentUrl[0] = '\0';
}

void visit(WebHistory* webHistory, char* url) {
    Operation operation;
    strncpy(operation.url, url, 99);
    operation.url[99]= '\0';
    getTime(operation.timestamp);
    if (operation.timestamp[0] == '\0') {
        strcpy(operation.timestamp, "00:00:00");
    }
    operation.timestamp[49]= '\0';
    push(&webHistory->back, operation);
    pushHistory(&webHistory->history, operation);
    clearStack(&webHistory->forward);
    strncpy(webHistory->currentUrl, url,99);
    webHistory->currentUrl[99]= '\0';
}
void backward(WebHistory* webHistory) {
    Operation *operation = pop(&webHistory->back);
    if (!operation) {
        return;
    }
    push(&webHistory->forward,*operation);
    Operation* nextOp = peek(&webHistory->back);
    if (nextOp) {
        strncpy(webHistory->currentUrl, nextOp->url, 99);
        webHistory->currentUrl[99]= '\0';
    }else {
        webHistory->currentUrl[99]= '\0';
    }

}
void forward(WebHistory* webHistory) {
    Operation* operation = pop(&webHistory->forward);
    if (!operation) {
        return;
    }
    push(&webHistory->back,*operation);
    strncpy(webHistory->currentUrl, operation->url, 99);
    webHistory->currentUrl[99] = '\0';
}
void current(WebHistory* webHistory) {
    if (webHistory->currentUrl[0] != '\0') {
        if (webHistory->currentUrl[0] != '\0') {
            printf("Trang hien tai: %s\n",webHistory->currentUrl);
        }else {
            printf("Khong co trang hien tai\n");
        }
    }
}
void displayMenu() {
    printf("\n====Menu====\n");
    printf("1. VISIT url\n");
    printf("2. BACKWARD\n");
    printf("3. FORWARD\n");
    printf("4. CURRENT\n");
    printf("5. HISTORY\n");
    printf("6. CLEAR HISTORY\n");
    printf("7. Thoat\n");
    printf("Nhap lua chon cua ban: ");
}


int main(void) {
    int choice;
    WebHistory webHistory;
    createWebHistory(&webHistory);

    char url[100];
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Nhap URL: ");
                fgets(url, 100, stdin);
                url[strcspn(url, "\n")] = '\0';
                if (url[0] == '\0') {
                    printf("URL khong hop le\n");
                    break;
                }
                visit(&webHistory,url);
                break;
            case 2:
                backward(&webHistory);
                break;
            case 3:
                forward(&webHistory);
                break;
            case 4:
                current(&webHistory);
                break;
            case 5:
                displayHistory(&webHistory.history);
                break;
            case 6:
                clearHistory(&webHistory.history);
                clearStack(&webHistory.back);
                clearStack(&webHistory.forward);
                webHistory.currentUrl[0] = '\0';
                printf("Da xoa lich su duyet web\n");

                break;
            case  7:
                clearHistory(&webHistory.history);
                clearStack(&webHistory.back);
                clearStack(&webHistory.forward);

                printf("Ban da thoat chuong trinh\n");
                break;
            default:
                printf("Lua cho sai vui long chon lai!\n");
        }
    }while (choice != 7);
    return 0;
}