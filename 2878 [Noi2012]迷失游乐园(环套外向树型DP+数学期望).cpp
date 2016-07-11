#include <cstdio>
const int N=100005,M=N,C=25;
int n,m;
inline double inv(int x){
	return x?1./x:1;
}
struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[M<<1],*newE=E;
struct node{
	node *pa;
	edge *son;
	double f,g;
	bool vis,oncir;
	int deg;
	void getcir();
	void dfs1(){
		for(edge *e=son;e;e=e->next) if(!e->ed->oncir&&e->ed!=pa){
			e->ed->pa=this;
			e->ed->dfs1();
			f+=e->w+e->ed->f;
		}
		if(!pa) deg++;
		f*=inv(deg-1);
		if(!pa) deg--;
	}
	void dfs2(){
		if(!pa) deg++;
		g+=f*(deg-1);
		if(!pa) deg--;
		for(edge *e=son;e;e=e->next) if(!e->ed->oncir&&e->ed!=pa){
			e->ed->g=(g-(e->w+e->ed->f))*inv(deg+(m==n-1||pa?0:2)-1)+e->w;
			e->ed->dfs2();
		}
	}
} V[N];
int cnt,last[C],next[C];
node *seq[C];
void node::getcir(){
	vis=1;
	for(edge *e=son;e;e=e->next) if(e->ed!=pa){
		if(e->ed->vis){
			if(!e->ed->oncir){
				for(node *v=this;v!=e->ed;v=v->pa)
					seq[++cnt]=v,v->oncir=1;
				seq[++cnt]=e->ed,e->ed->oncir=1;
			}
			continue;
		}
		e->ed->pa=this;
		e->ed->getcir();
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++,V[x].deg++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++,V[y].deg++;
	}
	if(m==n-1){
		V[1].dfs1();
		V[1].dfs2();
		double ans=0;
		for(int i=1;i<=n;i++) ans+=V[i].g/V[i].deg;
		printf("%.9lf\n",ans/n);
		return 0;
	}
	V[1].getcir();
	for(int i=1;i<=cnt;i++){
		seq[i]->pa=NULL;
		seq[i]->deg-=2;
		seq[i]->dfs1();
		seq[i]->deg+=2;
	}
	last[1]=cnt;
	for(int i=2;i<=cnt;i++) last[i]=i-1;
	next[cnt]=1;
	for(int i=1;i<cnt;i++) next[i]=i+1;
	for(int i=1;i<=cnt;i++){
		double now=0;
		now=seq[next[i]]->f;
		for(int j=next[i];;){
			for(edge *e=seq[j]->son;e;e=e->next) if(e->ed==seq[next[j]]){
				now+=e->w;
				break;
			}
			j=next[j];
			if(j==i) break;
			now=(seq[j]->f*(seq[j]->deg-2)+now)/(seq[j]->deg-1);
		}
		seq[i]->g+=now;
		now=seq[last[i]]->f;
		for(int j=last[i];j!=i;){
			for(edge *e=seq[j]->son;e;e=e->next) if(e->ed==seq[last[j]]){
				now+=e->w;
				break;
			}
			j=last[j];
			if(j==i) break;
			now=(seq[j]->f*(seq[j]->deg-2)+now)/(seq[j]->deg-1);
		}
		seq[i]->g+=now;
	}
	for(int i=1;i<=cnt;i++){
		seq[i]->deg-=2;
		seq[i]->dfs2();
		seq[i]->deg+=2;
	}
	double ans=0;
	for(int i=1;i<=n;i++) ans+=V[i].g/V[i].deg;
	printf("%.9lf\n",ans/n);
}
