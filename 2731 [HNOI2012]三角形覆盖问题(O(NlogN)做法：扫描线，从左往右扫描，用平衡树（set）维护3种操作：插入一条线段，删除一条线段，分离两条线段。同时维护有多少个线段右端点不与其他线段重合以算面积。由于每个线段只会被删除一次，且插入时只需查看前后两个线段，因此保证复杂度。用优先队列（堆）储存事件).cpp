#include <cstdio>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;
const int N=10005,oo=1e8;

int n;
ll ans,now,cnt,X;

struct tria{
	int x,y,d; bool exist;
	int ti;
	int l() const{
		return y;
	}
	int r() const{
		return y+d-(X-x);
	}
	ll calc() const{
		return r()-l()-(ti==-1?0:ti-X);
	}
} a[N];
struct event{
	int type; // 0: insert 1: delete 2: sperate
	tria *num; int x;
	void work();
};
struct cmp{
	bool operator () (const event &a,const event &b){
		return a.x>b.x||a.x==b.x&&a.type<b.type;
	}
};
priority_queue<event,vector<event>,cmp> q;
struct cmptri{
	bool operator () (const tria *a,const tria *b){
		return a->l()<b->l();
	}
};
set<tria*,cmptri> s;
typedef set<tria*>::iterator iter;
void event::work(){
	if(type==0){
		iter it=s.upper_bound(num);
		if(it!=s.begin()){
			it--;
			if((*it)->r()>=num->r())
				return;
		}
		it=s.lower_bound(num);
		while(it!=s.end()&&(*it)->r()<=num->r()){
			if((*it)->ti==-1)
				cnt--;
			now-=(*it)->calc();
			s.erase(it++);
		}
		q.push((event){1,num,num->x+num->d});
		if(it!=s.end()&&num->r()>(*it)->l()){
			q.push((event){2,num,num->ti=X+num->r()-(*it)->l()});
		}
		else{
			cnt++;
			num->ti=-1;
		}
		it=s.insert(num).first;
		num->exist=true;
		now+=num->calc();
		if(it!=s.begin()){
			it--;
			if((*it)->r()>num->l()){
				now-=(*it)->calc();
				if((*it)->ti==-1)
					cnt--;
				q.push((event){2,*it,(*it)->ti=X+(*it)->r()-num->l()});
				now+=(*it)->calc();
			}
		}
		return;
	}
	iter it=s.find(num);
	if(it==s.end()||*it!=num) return;
	if(type==1){
		(*it)->exist=false;
		s.erase(it);
		cnt--;
		return;
	}
	if(type==2){
		if((*it)->ti==X){
			(*it)->ti=-1;
			cnt++;
		}
		return;
	}
	puts("Unknown type!");
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].d);
		q.push((event){0,a+i,a[i].x});
	}
	while(!q.empty()){
		event cur=q.top(); q.pop();
		X=cur.x;
		cur.work();
		if(!q.empty()){
			ll tmp=now-cnt*(q.top().x-cur.x);
			ans+=(now+tmp)*(q.top().x-cur.x);
			now=tmp;
		}
	}
	printf("%.1lf\n",ans/2.);
}
