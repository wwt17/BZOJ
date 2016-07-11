#include <iostream>
#include <set>
#include <utility>
using namespace std;
long long r,n,m;
typedef pair<int,int> ii;
set<ii> S;
void Cal(int d){
	long long r=::r/d;
	n=1,m=1;
	while(m*m<r) m++;
	while(n<m){
		while(n<m&&n*n+m*m>r) m--;
		if(n>=m) break;
		if(n*n+m*m==r){
			int a=m*m-n*n,b=2*m*n;
			S.insert(ii(a*d,b*d));
			S.insert(ii(b*d,a*d));
		}
		n++;
	}
}
int main(){
	cin>>r; int d;
	for(d=1;d*d<r;d++) if(!(r%d))
		Cal(r/d),Cal(d);
	if(d*d==r) Cal(d);
	cout<<(S.size()+1)*4<<endl;
}
