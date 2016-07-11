#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
const int B=50;
int n;
char s[B+1];
ll ans,C[B][B];
int cnt[10];
int main(){
	scanf("%s",s);
	n=strlen(s);
	std::reverse(s,s+n);
	for(int i=0;i<n;i++) s[i]-='0';
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			C[i][j]=j?C[i-1][j-1]+C[i-1][j]:1;
	for(int i=0;i<n;i++) cnt[s[i]]++;
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<s[i];j++) if(cnt[j]){
			cnt[j]--;
			ll now=1,tot=0;
			for(int k=0;k<10;k++){
				tot+=cnt[k];
				now*=C[tot][cnt[k]];
			}
			ans+=now;
			cnt[j]++;
		}
		cnt[s[i]]--;
	}
	printf("%lld\n",ans);
}
