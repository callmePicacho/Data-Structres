/*
#include<iostream>
#include<stdlib.h>
#include<string>
#include<cmath>
#define MAXTABLESIZE 1000000
using namespace std;
typedef struct Node Cell;
struct Node{
	bool exist;
	string acc;   // 账号
	string pas;  // 密码 
};

typedef struct HashTBL *HashTable; 
struct HashTBL{
	int TableSize;
	Cell *users;
};

int Hash(int key,int p){
	return key%p;
}

int NextPrime(int N){
	int p = N%2?N+2:N+1;
	int i;
	while(p <= MAXTABLESIZE) {  
		for(i=(int)sqrt(p);i>2;i--)
			if(!(p%i))
				break;
		if(i==2 && p%4==3) // 保证平方探测都能找到 
			break;
		p +=2;
	}
	return p;
}

// 初始化 
HashTable Create(int TableSize){
	HashTable H;
	H = (HashTable)malloc(sizeof(struct HashTBL));
	H->TableSize = NextPrime(TableSize);
	H->users = new Node[H->TableSize];
	for(int i=0;i<H->TableSize;i++)
		H->users[i].exist = false;
	return H;
}

int Find(HashTable H,string key){
	int NewPos,CurrentPos;
	int CNum = 0;
	NewPos = CurrentPos = Hash(atoi(key.c_str()),H->TableSize);
	while(H->users[NewPos].exist && H->users[NewPos].acc != key){
		if(++CNum %2){
			NewPos =( CurrentPos + (CNum+1)/2*(CNum+1)/2 )%H->TableSize;
		}else{
			NewPos = CurrentPos - CNum/2*CNum/2;
			while(NewPos < 0)
				NewPos += H->TableSize;
		}
	}
	return NewPos;
}

void Insert(HashTable H,string key,string pas,char flag){
	int pos;
	pos = Find(H,key);
	if(H->users[pos].exist){  // 已经存在 
		if(flag == 'L'){   // 登陆 
			if(pas == H->users[pos].pas)   // 密码正确，登陆成功 
				cout<<"Login: OK"<<endl;
			else   // 密码错误，登陆失败 
				cout<<"ERROR: Wrong PW"<<endl;
		}else if(flag == 'N'){  // 注册失败 
			cout<<"ERROR: Exist"<<endl;
		} 
	}else{  // 不存在 
		if(flag == 'L')   // 登陆失败 
			cout<<"ERROR: Not Exist"<<endl;
		else if(flag == 'N'){ // 注册成功 
			cout<<"New: OK"<<endl; 
			H->users[pos].exist = true;
			H->users[pos].pas = pas;
			H->users[pos].acc = key;
		}
	}
}

int main(){
	HashTable H;
	int N;
	char command;
	string account;
	string password;
	cin>>N;
	H = Create(N);
	for(int i=0;i<N;i++){
		cin>>command>>account>>password;
		Insert(H,account,password,command);
	} 
	return 0;
}*/


#include<cstdio>
#include<iostream>
#include<map>
#include<string>
using namespace std;
int main(){
	int N;
	char command;
	string qq;
	string ps;
	map<string,string> m;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		getchar();
		scanf("%c",&command);
		cin>>qq>>ps;
		if(command == 'N'){     // 新用户 
			if(m.find(qq)!=m.end())    // qq号已经存在 
				printf("ERROR: Exist");
			else{    // 注册成功 
				printf("New: OK");
				m[qq] = ps;
			}
		}else if(command == 'L'){  // 老用户 
			if(m.find(qq)==m.end())  // 没找到 
				printf("ERROR: Not Exist"); 
			else if(m[qq] == ps)   // 密码正确 
				printf("Login: OK");
			else   
				printf("ERROR: Wrong PW");
		}
		printf("\n");
	} 
	return 0;
}
