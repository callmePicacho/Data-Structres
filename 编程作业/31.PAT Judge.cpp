#include<cstdio>
#include<algorithm>
#include<vector>

const int INIT = -2;  // 初始化 
const int NOPASS = -1;  // 未通过编译 
const int MAXID = 10005;  //最大ID 
using namespace std;

struct info{
	int id;    // id号 
	int ques[6];  // 每道题得分
	int sum;   // 总分 
	int solved;   // 答对题数 
};

// 定义sort 的排序规则 
bool cmp(info a,info b){
	if(a.sum != b.sum)
		return a.sum>b.sum;	
	if(a.solved != b.solved)
		return a.solved > b.solved;
	return a.id < b.id;
}


int main(){
	int N;  // 使用者总数
	int K;  // 问题总数
	int M;  // 提交总数 
	scanf("%d %d %d",&N,&K,&M);
	vector<info> user(N+1); // 使用者信息
	int Full[K+1];  // 记录问题总分 ,a[i] 表示第i道题的分数
	for(int i=1;i<=K;i++) 
		scanf("%d",&Full[i]);
	// 初始化信息 
	for(int i=1;i<N+1;i++){
		user[i].id = MAXID;  // 初始化成最大 
		user[i].sum = 0; 
		user[i].solved = 0;
		for(int j=1;j<K+1;j++) 
			user[i].ques[j] = INIT;
	}
	int use;  // 玩家编号 
	int question;  // 问题编号 
	int score;  // 得分 
	int listSum = 0; // 应该被输出总数 
	for(int i=0;i<M;i++){
		scanf("%d %d %d",&use,&question,&score);
		// 只要通过编译，该玩家就能被显示
		if(score >= 0 && user[use].id == MAXID){
			listSum++;
			user[use].id = use;
		} 
		// 分数有更大更新成更大 
		if(user[use].ques[question] < score){
			user[use].ques[question] = score;
		}
	}
	for(int i=1;i<N+1;i++)
		for(int j=1;j<K+1;j++){
			// 计算完全正确解题数 
			if(user[i].ques[j] == Full[j])
				user[i].solved++;
			// 计算总分 
			if(user[i].ques[j] != NOPASS && user[i].ques[j] != INIT)
				user[i].sum += user[i].ques[j];
		} 
	
	sort(user.begin()+1,user.end(),cmp);
	
	int preSum = user[1].sum;
	int preNum = 1;
	
	for(int i=1;i<=listSum;i++){ 
	    // 如果和上次分数不同，更新排名 
		if(preSum != user[i].sum){ 
			preNum = i;
			preSum = user[i].sum;
		} 
		printf("%d ",preNum);
		printf("%05d %d",user[i].id,user[i].sum);
		for(int j=1;j<K+1;j++){
			// 依旧初始化状态 
			if(user[i].ques[j] == INIT)
				printf(" -");
			else if(user[i].ques[j] == NOPASS)
				printf(" 0");
			else
				printf(" %d",user[i].ques[j]);
		}
		printf("\n");
	}
	return 0;
}
