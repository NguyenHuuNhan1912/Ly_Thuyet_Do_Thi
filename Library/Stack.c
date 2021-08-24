//Thu vien ngan xep (Stack)

#include <stdio.h>
#define MAX 100
//Khai bao cau truc ngan xep
typedef struct{
	int Elements[MAX];
	int Top_idx;//Chi so o cuoi mang
}Stack;
//Ham lam rong stack
void makenull_Stack(Stack *s){
	s->Top_idx=MAX;
}
//Ham kiem tra stack co rong hay khong
int empty_Stack(Stack s){
	return (s.Top_idx == MAX);
}
//Ham kiem tra stack co day hay chua
int full_Stack(Stack s){
	return (s.Top_idx == 0);
}
//Ham them phan tu vao stack
void push_Stack(int x, Stack *s){
	if(full_Stack(*s)) printf("Stack day khong the them duoc\n");
	else{
		s->Top_idx=s->Top_idx-1;// nhung no chay len tren
		s->Elements[s->Top_idx]=x;
	}
}
void read_Stack(Stack *s){
	int n,x;
	printf("Nhap so phan tu cua ngan xep: "); scanf("%d",&n);
	for(int i=1;i<=n;i++){
		printf("Nhap phan tu thu %d: ",i);
		scanf("%d",&x);
		push_Stack(x,s);
	}
}
//Ham in phan tu trong stack
// void print_Stack(Stack s){
// 	while(s.Top_idx!=MAX){
// 		printf("%d ",s.Elements[s.Top_idx]);
// 		s.Top_idx=s.Top_idx+1;
// 	}
// }
// Ham lay phan tu trong stack
int get_Stack(Stack *s){
	int x;
	x=s->Elements[s->Top_idx];
	s->Top_idx++;
	return x;
}
void print_Stack(Stack s){
	while(s.Top_idx!=MAX){
		printf("%d ",get_Stack(&s));
	}
}
// int main(){
// 	Stack S;
// 	makenull_Stack(&S);
// 	read_Stack(&S);
// 	printf("Danh sach vua nhap la\n");
// 	print_Stack(S);
// 	return 0;
// }
