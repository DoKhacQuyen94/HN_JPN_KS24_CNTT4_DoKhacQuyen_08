#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[100];
    int age;
    struct Student* left, *right;
}Student;
Student* creatStudent(int id, char name[], int age) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}
Student *insertStudent(Student* root,int id, char name[], int age) {
    if (root==NULL) {
        return creatStudent(id,name,age);
    }
    if (id<root->id) {
        root->left = insertStudent(root->left,id,name,age);
    }else if (id > root->id) {
        root->right = insertStudent(root->right,id,name,age);
    }else {
        printf("ID %d da ton tai\n",id);
    }
    return root;
}
void inorder(Student* root) {
    if (root!=NULL) {
        inorder(root->left);
        printf("ID: %d\n",root->id);
        printf("Name: %s\n",root->name);
        printf("Age: %d\n",root->age);

        inorder(root->right);

    }
}
Student* searchStudent(Student* root,int id) {
    if (root==NULL || root->id==id) {
        return root;
    }
    if (id<root->id) {
        return searchStudent(root->left,id);
    }else if (id > root->id) {
        return searchStudent(root->right,id);
    }
}
void displayMenu() {
    printf("1. Them sinh vien\n");
    printf("2. Hien thi sinh vien\n");
    printf("3. Tim kiem sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Thoat\n");
    printf("Nhap lua chon cua ban: ");
}

int main() {
    int choice;
    Student* root = NULL;
    int id,age;
    char name[100];
    int StudentID= 1;
    do {
        displayMenu();
        scanf("%d",&choice);
        getchar();

        switch(choice) {
            case 1:
                printf("Nhap ten: ");
                fgets(name,sizeof(name),stdin);
                printf("Nhap tuoi: ");
                scanf("%d",&age);
                getchar();
                root = insertStudent(root,StudentID,name,age);
                ++StudentID;
                break;
            case 2:
                printf("\n Danh sach sinh vien \n");
                if (root == NULL) {
                    printf("Danh sach rong\n");

                }else {
                    inorder(root);
                }
                break;
            case 3:
                printf("Nhap Id can tim: ");
                scanf("%d",&id);
                Student* found = searchStudent(root,id);
                if (found) {
                    printf("Tim thay Id: %d\n", found->id);
                }else {
                    printf("Khong tim thay Id: %d\n", id);
                }
                break;
            case 4:
                break;
            case 5:
                printf("Ban da thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
    }while (choice!=5);
    return 0;
}