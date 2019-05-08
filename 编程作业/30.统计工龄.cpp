#include<iostream>
using namespace std;

void bucket_sort(int A[],int N){
	int count[55];
	for(int i=0;i<55;i++)
		count[i] = 0;
	for(int i=0;i<N;i++)
		count[A[i]]++;
	for(int i=0;i<55;i++)
		if(count[i])
			cout<<i<<":"<<count[i]<<endl;
}

int main(){
	int N;
	cin>>N;
	int A[N];
	for(int i=0;i<N;i++)
		cin>>A[i];
	bucket_sort(A,N);
	return 0;
}
