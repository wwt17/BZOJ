#include <iostream>
#include <bitset>
using namespace std;
const int N=1024;
typedef bitset<N> type;
int n,m,cnt;
bool ok[N];
type cur,a[N];
int main(){
	iostream::sync_with_stdio(false);
	cin>>n>>m;
	cnt=n;
	for(int k=1;k<=m;k++){
		int b;
		cin>>cur>>b;
		cur[n]=b;
		for(int i=0;i<n;i++) if(cur[i])
			if(ok[i]) cur^=a[i];
			else{
				ok[i]=true;
				cnt--;
				a[i]=cur;
				break;
			}
		if(!cnt){
			cout<<k<<endl;
			for(int i=n-1;i>=0;i--){
				for(int j=i+1;j<n;j++) if(a[i][j])
					a[i]^=a[j];
				cout<<(a[i][n]?"?y7M#":"Earth")<<endl;
			}
			return 0;
		}
	}
	cout<<"Cannot Determine"<<endl;
}
