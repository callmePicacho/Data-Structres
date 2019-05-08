/*#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int Position;
#define NotFound -1 
using namespace std;

void BuildMatch(char *pattern,int *match){
	int i,j;
	int m = strlen(pattern);
	match[0] = -1;
	for(j=1;j<m;j++){
		i = match[j-1];
		while((i>=0) && (pattern[i+1] != pattern[j]))
			i = match[i];
		if(pattern[i+1] == pattern[j])
			match[j] = i+1;
		else
			match[j] = -1; 
	}
}

Position KMP(char* string,char *pattern){
	int n = strlen(string);
	int m = strlen(pattern);
	int s,p;
	if(n < m)
		return NotFound;
	int *match = (int *)malloc(sizeof(int) * m);
	BuildMatch(pattern,match);
	s = p = 0;
	while(s < n && p < m){
		if(string[s] == pattern[p]){
			s++;
			p++;
		}else if(p>0)
			p = match[p-1]+1;
		else
			s++;
	}
	return (p == m) ? (s-m) : NotFound;
}

int main(){
	char *string;
	char *pattern;
	Position p;
	int N;
	int i;
	string = (char *)malloc(sizeof(char) * 100005);
	pattern = (char *)malloc(sizeof(char) * 10005);
	scanf("%s %d",string,&N);
	for(i=0;i<N;i++){
		scanf("%s",pattern);
		p = KMP(string,pattern);
		if(p == NotFound)
			printf("Not Found\n");
		else
			printf("%s\n",p+string);
	}
	return 0;
}*/
#include<iostream>
#include<string.h>
#include<string>
typedef char *Position;
#define NotFound NULL 
using namespace std;

int main(){
	string str;
	string pat;
	Position p;
	int N;
	cin>>str>>N;
	for(int i=0;i<N;i++){
		cin>>pat;
		p = strstr(str.c_str(),pat.c_str());
		if(p == NotFound)
			cout<<"Not Found"<<endl;
		else
			cout<<p<<endl;
	}
	return 0;
}
