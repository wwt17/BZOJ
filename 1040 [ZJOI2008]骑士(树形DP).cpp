#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
struct knight{
	knight *p; int goin; long long f[2];
	inline void renew(const knight* x){
		f[0]+=max(x->f[0],x->f[1]);
		f[1]+=x->f[0];
		goin--;
	}
} no[1000001],*i,*j;
int N; long long f[2][2],tmp,Ans;
queue<knight*> q;
int main(){
	scanf("%u",&N);
	for(i=no;i<no+N;i++){
		static int P;
		scanf("%u%u",&i->f[1],&P);
		i->p=no+--P;
		no[P].goin++;
	}
	for(i=no;i<no+N;i++) if(!i->goin) q.push(i);
	while(!q.empty()){
		i=q.front();
		q.pop();
		i->p->renew(i);
		if(!i->p->goin) q.push(i->p);
	}
	for(i=no;i<no+N;i++) if(i->goin){
		i->goin--;
		f[0][0]=i->f[0];
		f[0][1]=f[1][0]=0;
		f[1][1]=i->f[1];
		for(j=i->p;j!=i;j=j->p){
			for(int b=0;b<2;b++){
				tmp=f[b][0];
				f[b][0]=max(tmp,f[b][1])+j->f[0];
				f[b][1]=tmp+j->f[1];
			}
			j->goin--;
		}
		Ans+=max(f[1][0],max(f[0][0],f[0][1]));
	}
	printf("%lld\n",Ans);
}
