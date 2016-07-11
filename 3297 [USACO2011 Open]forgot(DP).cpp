#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int l,nw,lw[1000];
string p,w[1000],*f[1024];
inline bool cmp(int k,string* A,string* B){
	if(!A) return false;
	if(!B) return true;
	string::iterator i=A->begin(),j=B->begin();
	for(;;){
		if(k==l) return A==&p;
		if(*i<*j) return true;
		if(*i>*j) return false;
		k++;
		if(++i==A->end()){
			A=f[k];
			i=A->begin();
		}
		if(++j==B->end()){
			B=f[k];
			j=B->begin();
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>l>>nw>>p;
	for(int i=0;i<nw;i++) cin>>w[i];
	sort(w,w+nw);
	for(int i=0;i<nw;i++) lw[i]=w[i].length();
	f[l]=&p;
	for(int j=l-1;j>=0;j--){
		for(int i=0;i<nw;i++) if(f[j+lw[i]]){
			for(int k=0;k<lw[i];k++)
				if(p[j+k]!='?'&&p[j+k]!=w[i][k])
					goto out;
			if(cmp(j,w+i,f[j]))
				f[j]=w+i;
			out:;
		}
	}
	int j=0;
	for(string* s=f[0];s!=&p;j+=s->length(),s=f[j])
		cout<<*s;
	cout<<endl;
}
