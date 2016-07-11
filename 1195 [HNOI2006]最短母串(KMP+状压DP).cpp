#include <cstdio>
#include <cstring>
const int N=12,L=55;
int n;
char s[N][L];
int len[N],next[N][L],g[N][N],f[1<<N][N];
char t[N*L],tt[N*L];
int lent,lentt;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%s",s[i]);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) if(j!=i&&strstr(s[j],s[i])!=NULL){
			for(j=i;j+1<n;j++) strcpy(s[j],s[j+1]);
			n--;
			break;
		}
	for(int i=0;i<n;i++){
		len[i]=strlen(s[i]);
		next[i][1]=0;
		for(int j=2;j<=len[i];j++){
			int k=next[i][j-1];
			for(;k&&s[i][k]!=s[i][j-1];k=next[i][k]);
			if(s[i][k]==s[i][j-1]) k++;
			next[i][j]=k;
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) if(i!=j){
			int J=0;
			for(int I=0;I<len[i];I++){
				for(;J&&s[j][J]!=s[i][I];J=next[j][J]);
				if(s[j][J]==s[i][I]) J++;
			}
			g[i][j]=J;
		}
	for(int st=(1<<n)-2;st;st--)
		for(int i=0;i<n;i++) if(st>>i&1){
			lent=N*L;
			for(int j=0;j<n;j++) if(!(st>>j&1)){
				lentt=0;
				for(int k=j,ss=st|1<<j,e=g[i][j];;e=g[k][f[ss][k]],k=f[ss][k],ss|=1<<k){
					strcpy(tt+lentt,s[k]+e);
					lentt+=len[k]-e;
					if(ss==(1<<n)-1) break;
				}
				tt[lentt]=0;
				if(lentt<lent||lentt==lent&&strcmp(tt,t)<0){
					strcpy(t,tt);
					lent=lentt;
					f[st][i]=j;
				}
			}
		}
	lent=N*L;
	for(int j=0;j<n;j++){
		lentt=0;
		for(int k=j,ss=1<<j,e=0;;e=g[k][f[ss][k]],k=f[ss][k],ss|=1<<k){
			strcpy(tt+lentt,s[k]+e);
			lentt+=len[k]-e;
			if(ss==(1<<n)-1) break;
		}
		tt[lentt]=0;
		if(lentt<lent||lentt==lent&&strcmp(tt,t)<0){
			strcpy(t,tt);
			lent=lentt;
		}
	}
	puts(t);
}
