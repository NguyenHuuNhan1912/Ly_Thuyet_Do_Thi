//Thu vien danh sach (List library)
#include <stdio.h>
#define idx 100
//Khai bao cau truc danh sach(List)
typedef struct{
    int data[idx];
    int size;
}List;
//Ham tao rosizeg danh sach
void makenull_List(List *l){
    l->size=0;
}
//Ham them phan tu vao danh sach
void push_List(List *l, int x){
    l->data[l->size]=x;
    l->size++;
}
//Ham lay phan tu trong danh sach
int get_List(List l, int i){
    return l.data[i];
}
//Ham in danh sach
void print_List(List l){
    for(int i=0;i<l.size;i++){
        printf("\nList[%d] = %d\n",(i+1),l.data[i]);
    }
}
//Ham nhap danh sach
List read_List(){
    List L;
    makenull_List(&L);
    printf("\nDanh sach ban co bao nhieu phan tu: ");
    scanf("%d",&(L.size));
    printf("\nNhap gia tri cac phan tu\n");
    for(int i=0;i<L.size;i++){
        printf("\nNhap phan tu thu %d: ",(i+1));
        scanf("%d",&(L.data[i]));
    }
    return L;
}
