#include<iostream>
using namespace std;
int main(){
	int n;
	int a[100000+5];
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	int left = 0;
	int tmpleft = 0;
	int right = n-1;
	int max =0;
	int tmpSum=0;
	for(int i=0;i<n;i++){
		tmpSum+=a[i];
		if(tmpSum<0){
			tmpSum=0;
			tmpleft = i+1;   // 开头的数就在这段被抛弃子序列的下一个 
		}else if(max < tmpSum){
			max = tmpSum;        
			left = tmpleft;   // 每次更新最大值也就确定了一段子序列，保存此时的开头 
			right = i;       // 结尾的数就在每次更新最大值时 
		}
	}
	if(max>=0)
		cout<<max<<" "<<a[left]<<" "<<a[right];
	else
		cout<<0<<" "<<a[0]<<" "<<a[n-1];
	return 0;
} 

