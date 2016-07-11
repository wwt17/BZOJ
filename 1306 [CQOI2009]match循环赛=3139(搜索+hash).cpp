#include <cstdio>
#include <cstring>
#include <algorithm>
using std::sort;
using std::pair;
using std::make_pair;
const size_t N=9,P=5000011,C=3*N;
template<size_t P,typename T,typename hash,typename equal_to>
struct hash_table{
	T* table[P]; hash _hash; equal_to _equal_to;
	void insert(T &x){
		size_t key=_hash(x);
		while(table[key]) if(++key==P) key=0;
		memcpy(table[key]=new T,&x,sizeof(T));
	}
	T* find(T &x){
		size_t key=_hash(x);
		while(table[key]){
			if(_equal_to(*table[key],x))
				return table[key];
			if(++key==P) key=0;
		}
		return NULL;
	}
};
int n,i,sum,Ans;
typedef pair<int[N],int> state;
int s[N];
struct hash{
	size_t operator()(const state &a){
		size_t ret=a.first[0];
		for(size_t i=a.first[0];i;i--)
			ret=(ret*C+a.first[i])%P;
		return ret;
	}
};
struct equal_to{
	bool operator()(const state &a,const state &b){
		if(a.first[0]!=b.first[0]) return false;
		for(size_t i=a.first[0];i;i--)
			if(a.first[i]!=b.first[i]) return false;
		return true;
	}
};
hash_table<P,state,hash,equal_to> memory;
unsigned search(const int i,const int j){
	unsigned Ans=0;
	if(j<=0){
		if(i<=0) return 1;
		if(s[i]) return 0;
		state S;
		S.first[0]=i-1;
		memcpy(S.first+1,s+1,sizeof(int)*(i-1));
		sort(S.first+1,S.first+i);
		state *tmp;
		if(tmp=memory.find(S))
			return tmp->second;
		S.second=search(i-1,i-2);
		memory.insert(S);
		return S.second;
	}
	if(s[i]>=1&&s[j]>=1){
		s[i]--,s[j]--;
		Ans+=search(i,j-1);
		s[i]++,s[j]++;
	}
	if(!sum) return Ans;
	sum--;
	if(s[i]>=3){
		s[i]-=3;
		Ans+=search(i,j-1);
		s[i]+=3;
	}
	if(s[j]>=3){
		s[j]-=3;
		Ans+=search(i,j-1);
		s[j]+=3;
	}
	sum++;
	return Ans;
}
int main(){
	scanf("%u",&n);
	sum=-(n-1)*n;
	for(i=1;i<=n;i++) scanf("%u",s+i),sum+=s[i];
	printf("%u\n",search(n,n-1));
}
