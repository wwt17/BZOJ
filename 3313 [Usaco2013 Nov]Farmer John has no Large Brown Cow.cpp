#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
const int N=100,M=30;
int n,m,k,u,Ans,num[N],cnt[M],ans[M];
string a[N][M],s[M][N],tmp;
int main(){
	iostream::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=0;i<n;i++){
		cin>>tmp>>tmp>>tmp>>tmp;
		for(m=0;cin>>tmp,tmp!="cow.";m++){
			a[i][m]=tmp;
			for(u=0;u<cnt[m]&&s[m][u]!=tmp;u++);
			if(u==cnt[m]) s[m][cnt[m]++]=tmp;
		}
	}
	for(int j=0;j<m;j++) sort(s[j],s[j]+cnt[j]);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			num[i]=num[i]*cnt[j]+(lower_bound(s[j],s[j]+cnt[j],a[i][j])-s[j]);
	sort(num,num+n);
	int v=0;
	for(int i=0;i<n;i++){
		if(k<=num[i]-v){ Ans=v+k-1; break; }
		k-=num[i]-v;
		v=num[i]+1;
	}
	Ans=v+k-1;
	for(int j=m;j--;){
		ans[j]=Ans%cnt[j];
		Ans/=cnt[j];
	}
	for(int j=0;j<m;j++){
		cout<<s[j][ans[j]];
		if(j<m-1) cout<<' '; else cout<<endl;
	}
}
