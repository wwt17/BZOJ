#include <cstdio>
#include <vector>
namespace Huge_Num{
	using namespace std;
	struct Huge{
		#define BASE 100000000
		vector<int> data;
		Huge(){
		}
		Huge(const int x){
			if(x) data.push_back(x);
		}
		bool operator<(const Huge &b){
			if(data.size()<b.data.size()) return true;
			if(data.size()>b.data.size()) return false;
			for(int i=data.size();i--;)
				if(data[i]<b.data[i]) return true; else
				if(data[i]>b.data[i]) return false;
			return false;
		}
		bool operator>(const Huge &b){
			if(data.size()>b.data.size()) return true;
			if(data.size()<b.data.size()) return false;
			for(int i=data.size();i--;)
				if(data[i]>b.data[i]) return true; else
				if(data[i]<b.data[i]) return false;
			return false;
		}
		void clear(){
			new(this) Huge;
		}
		Huge& operator++(){
			vector<int>::iterator i;
			for(i=data.begin();i!=data.end()&&*i==BASE-1;*i++=0);
			if(i==data.end()) data.push_back(1);
			else *i++;
			return *this;
		}
		void print(){
			if(!data.size()){ putchar('0'); return; }
			printf("%u",*(data.end()-1));
			for(vector<int>::iterator i=data.end()-1;data.begin()<i--;)
				printf("%08u",*i);
		}
		Huge& operator+=(const int b){
			int k=0;
			for(vector<int>::iterator i=data.begin();i!=data.end();i++){
				k+=*i+b;
				*i=k%BASE;
				k/=BASE;
			}
			if(k) data.push_back(k);
			return *this;
		}
		Huge& operator*=(const int b){
			long long k=0;
			for(vector<int>::iterator i=data.begin();i!=data.end();i++){
				k+=(long long)*i*b;
				*i=k%BASE;
				k/=BASE;
			}
			if(k) data.push_back(k);
			return *this;
		}
		Huge& operator/=(const int b){
			long long k=0;
			for(vector<int>::iterator i=data.end();i--!=data.begin();){
				k=k*BASE+*i;
				*i=k/b;
				k=k%b;
			}
			while(data.end()>data.begin()&&!*(data.end()-1)) data.pop_back();
			return *this;
		}
		Huge& operator+=(const Huge &b){
			int i,k=0;
			if(data.size()<=b.data.size()){
				for(i=0;i<data.size();i++){
					k+=data[i]+b.data[i];
					data[i]=k%BASE;
					k/=BASE;
				}
				for(;i<b.data.size();i++){
					data.push_back(b.data[i]);
					if(k){
						k+=data[i];
						data[i]=k%BASE;
						k/=BASE;
					}
				}
				if(k) data.push_back(k);
			}
			else{
				for(i=0;i<b.data.size();i++){
					k+=data[i]+b.data[i];
					data[i]=k%BASE;
					k/=BASE;
				}
				for(;i<data.size()&&k;i++){
					k+=data[i];
					data[i]=k%BASE;
					k/=BASE;
				}
				if(k) data.push_back(k);
			}
			return *this;
		}
		Huge operator+(const Huge &b){
			Huge c=*this;
			return c+=b;
		}
	};
	/*
	ostream& operator<<(ostream &out,Huge &a){
		if(!a.data.size()) return out<<'0';
		out<<*(a.data.end()-1);
		out.fill('0');
		out.width(8);
		for(vector<int>::iterator i=a.data.end()-1;a.data.begin()<i--;)
			out<<right<<*i;
		out.fill(' ');
		out.width(0);
		return out;
	}
	*/
}
using namespace Huge_Num;
//P(n+2+1,m) *n! *P(n+m+1,2)

//n!*( (n+1)*2*m*P(n+2,m-1) +P(n+1,2)*P(n+2+1,m) )
//(n+1)!*( 2*m*P(n+2,m-1) +n*P(n+2+1,m) )
//(n+1)!*P(n+2,m-1)*( 2*m +n*(n+2+1) )
int n,m,i;
Huge Ans=1,Ans2=1;
int main(){
	scanf("%u%u",&n,&m);
	for(i=n+1;i-1>0;i-=2) Ans*=i*(i-1);
	if(i>0) Ans*=i;
	for(i=n+2;i-1>n+3-m;i-=2) Ans*=i*(i-1);
	if(i>n+3-m) Ans*=i;
	Ans*=2*m+n*(n+3);
	Ans.print(),putchar('\n');
}
