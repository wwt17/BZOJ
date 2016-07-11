#include <cstdio>
const int N=25;
int t,n,p[N],sg[N],flag[100];
int main(){
	sg[0]=0;
	for(int i=1;i<N;i++){
		for(int j=0;j<100;j++) flag[j]=0;
		for(int j=0;j<i;j++)
			for(int k=0;k<=j;k++)
				flag[sg[j]^sg[k]]=1;
		for(sg[i]=0;flag[sg[i]];sg[i]++);
	}
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",&p[i]);
		int cnt=0,ii=-1,jj=-1,kk=-1;
		for(int i=0;i<n;i++) if(p[i])
			for(int j=i+1;j<n;j++)
				for(int k=j;k<n;k++){
					p[i]--;
					p[j]++;
					p[k]++;
					int g=0;
					for(int l=0;l<n;l++) if(p[l]&1) g^=sg[n-1-l];
					if(!g)
						if(!cnt++) ii=i,jj=j,kk=k;
					p[i]++;
					p[j]--;
					p[k]--;
				}
		printf("%d %d %d\n%d\n",ii,jj,kk,cnt);
	}
}
