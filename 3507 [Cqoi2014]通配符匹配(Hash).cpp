#include <cstdio>
const int N=105,L=100005,p=(int)1e9+9;
typedef long long ll;

int n;
char *S,*T,*tmp,s[L],t[L];
int mid[20];
ll power[L];

int main(){
	power[0]=1;
	for(int i=1;i<L;i++) power[i]=power[i-1]*26%p;
	scanf("%s",s+1);
	bool no=true;
	for(S=s+1;*S;S++) if(*S=='*') no=false;
	tmp=S;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int st,ed;
		#define match { puts("YES"); goto end; }
		#define fail { puts("NO"); goto end; }
		
		scanf("%s",t+1);
		for(T=t+1;*T;T++);
		
		if(no){
			if(S-s!=T-t) fail
			for(int j=1;j<S-s;j++)
				if(s[j]!='?'&&s[j]!=t[j])
					fail
			match
		}
		
		for(st=1;s[st]!='*';st++)
			if(s[st]!='?'&&s[st]!=t[st])
				fail
		for(ed=-1;S[ed]!='*';ed--)
			if(S[ed]!='?'&&S[ed]!=T[ed])
				fail
		
		S+=ed; S++;
		T+=ed; T++;
		*T=0;
		
		for(int j=st+1,l=st;j<S-s;){
			if(l>=T-t) fail
			*mid=0;
			ll g=0,h=0,H=0;
			int k;
			for(k=0;s[j+k]!='*';k++){
				if(l+k>=T-t) fail
				if(s[j+k]=='?'){
					mid[++*mid]=k;
					g=g*26%p;
					H=(H*26+(t[l+k]-'a'))%p;
				}
				else{
					g=(g*26+(s[j+k]-'a'))%p;
					H=H*26%p;
				}
				h=(h*26+(t[l+k]-'a'))%p;
			}
			if(l+k>T-t) fail
			while((g+H)%p!=h){
				if(l+1+k>T-t) fail
				h*=26;
				h-=(t[l]-'a')*power[k];
				h+=(t[l+k]-'a');
				h=(h%p+p)%p;
				H*=26;
				for(int x=1;x<=*mid;x++){
					H-=(t[l+mid[x]]-'a')*power[k-mid[x]];
					H+=(t[l+mid[x]+1]-'a')*power[k-mid[x]-1];
				}
				H=(H%p+p)%p;
				l++;
			}
			j+=k+1;
			l+=k;
		}
		match
		end:;
		S=tmp;
	}
}
