#include<iostream>
#include<vector>
using namespace std;
int main(){
  int N;
  cin>>N;
  int tmp;
  int sum = 0;
  vector<int> A; // 存 N 
  vector<bool> flag;
  for(int i=0;i<N;i++){
  	cin>>tmp;
  	A.push_back(tmp);
  	flag.push_back(false);
  }
  for(int i=0;i<N;i++){
  	if(A[i]!=i && !flag[i]){   // 没被访问过的单元环 
  		int tmpSum = 0;  // 计交换次数
  		int j = i;
  		do{
  			tmpSum++;  // 每遇到一个数计数+1 
  			flag[j] = true; // 标记环 
  			if(!A[j])   // 如果遇到了 0，减去入环出环的两次 
  				tmpSum-=2;
  			j = A[j];
  		}while(j!=i);
  		tmpSum++;    // 前面减去了 0，所以交换次数是当前数个数+1 
  		sum += tmpSum;
  	}
  }
  cout<<sum<<endl;
  return 0;
}
