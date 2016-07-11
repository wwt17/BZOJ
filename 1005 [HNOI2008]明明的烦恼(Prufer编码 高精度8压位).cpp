//M=没有度数限制的点个数 
//T=Sigma{degree[i]-1}
//Ans=M^(n-2-T)*C(n-2,T)*T!/Pi{(degree[i]-1)!}
#include <cstdio>
#include <vector>
namespace Huge_Num{
	using std::vector;
	struct Huge{
		#define BASE 100000000
		vector<int> data;
		Huge(){
		}
		Huge(const int x){
			data.push_back(x);
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
}
using namespace Huge_Num;
Huge Ans=1; int N,i,T,M,D[1000];
int main(){
	scanf("%u",&N);
	for(i=0;i<N;i++){
		scanf("%d",D+i);
		if(D[i]==-1) M++;
		else T+=--D[i];
	}
	if(T>N-2) { puts("0"); goto end; }
	for(i=1;i<=N-2-T;i++) Ans*=M;
	for(;i<=N-2;i++) Ans*=i;
	for(i=0;i<N;i++)
		for(D[i];D[i]>0;Ans/=D[i]--);
	Ans.print(),putchar('\n');
	end:;
}
