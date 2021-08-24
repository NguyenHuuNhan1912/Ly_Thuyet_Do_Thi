//Thu vien hang doi (Queue) (FIFO/LILO)
#include <stdio.h>
#include <stdbool.h>
#define idx 100
typedef int first;
typedef int last;
//Khai bao cau truc hang doi(Queue)
typedef struct{
    int data[idx];
    first front; //Luu chi so dau cua hang doi
    last rear;//Luu chi so cuoi cua hang doi
}Queue;
//Ham tao rong hang doi
void makenull_Queue(Queue *q){
    q->front=0;
    q->rear=-1;
}
//Kiem tra hang doi co rong hay khong
bool empty_Queue(Queue q){
    if(q.front>q.rear) return true;
    return false;
}
//Ham them phan tu vao cuoi hang doi
void push_Queue(Queue *q, int element){
    q->rear++;
    q->data[q->rear]= element;
}
//Ham lay phan tu o dau hang doi
int get_Queue(Queue *q){
    int save = q->data[q->front];
    q->front++; //Sau khi lay xong thi phai tang front
    return save;
}
//Ham nhap hang doi
Queue read_Queue(){
    Queue q;
    makenull_Queue(&q);
    int n,element;
    printf("\nBan muon them bao nhieu phan tu vao hang doi: "); scanf("%d",&n);
    printf("\nNhap cac gia tri can them vao hang doi\n");
    for(int i=0;i<n;i++){
        printf("\nNhap phan tu thu %d: ",(i+1));
        scanf("%d",&element);
        push_Queue(&q,element);
    }
    return q;
}
//Ham in hang doi
void print_Queue(Queue q){
    int p=1;
    for(int i=q.front;i<=q.rear;i++){
        printf("\nQueue[%d] = %d\n",p,q.data[i]);
        p++;
    }
}
