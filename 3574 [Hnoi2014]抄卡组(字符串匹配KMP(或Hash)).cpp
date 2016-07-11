#include <cstdio>
#include <cstring>

const int N=100005,L=11<<20;

int n;

char *curmem,*s[N],mem[L],tmp[L];
int tmplen,len[N];

int next[L];

bool work(){
	curmem=mem;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]=curmem);
		curmem+=(len[i]=strlen(s[i]))+1;
	}
	bool found;
	tmplen=0;
	for(int i=1;i<=n;i++){
		found=false;
		for(int j=0;s[i][j];j++)
			if(s[i][j]=='*'){
				found=true;
				break;
			}
		if(!found){
			strcpy(tmp,s[i]);
			tmplen=strlen(tmp);
			break;
		}
	}
	if(found){
		tmplen=0;
		for(int i=1;i<=n;i++){
			for(int j=0;s[i][j]!='*';j++){
				if(j<tmplen){
					if(s[i][j]!=tmp[j])
						return false;
				}
				else
					tmp[tmplen++]=s[i][j];
			}
		}
		tmplen=0;
		for(int i=1;i<=n;i++){
			for(int j=0;s[i][len[i]-1-j]!='*';j++){
				if(j<tmplen){
					if(s[i][len[i]-1-j]!=tmp[j])
						return false;
				}
				else
					tmp[tmplen++]=s[i][len[i]-1-j];
			}
		}
	}
	else
		for(int i=1;i<=n;i++)
			for(int l=0,r,t=0;l<len[i];l=r){
				for(;l<len[i]&&s[i][l]=='*';l++);
				if(l==len[i]) break;
				for(r=l;r<len[i]&&s[i][r]!='*';r++);
				if(l==0){
					if(r>tmplen) return false;
					for(;t<r;t++) if(tmp[t]!=s[i][t]) return false;
					if(r==len[i]&&r!=tmplen) return false;
				}
				else
					if(r==len[i]){
						if(t>tmplen-(r-l)) return false;
						for(int j=r-l;j;j--)
							if(tmp[tmplen-j]!=s[i][len[i]-j]) return false;
					}
					else{
						char *x=s[i]+l-1;
						int lenx=r-l;
						next[1]=0;
						for(int j=2,k=0;j<=lenx;j++){
							for(;k&&x[k+1]!=x[j];k=next[k]);
							if(x[k+1]==x[j]) k++;
							next[j]=k;
						}
						int k=0;
						for(;t<tmplen;t++){
							for(;k&&x[k+1]!=tmp[t];k=next[k]);
							if(x[k+1]==tmp[t]) k++;
							if(k==lenx)
								break;
						}
						if(k!=lenx) return false;
						t++;
					}
			}
	return true;
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		puts(work()?"Y":"N");
}
