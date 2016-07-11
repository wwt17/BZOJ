#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N=12*8*55+5,M=12+55+5;

int n,m;
bool cho[N];
int cnt[M];
struct node{
	int x,y;
	node *l,*r,*u,*d;
} V[N][M];

void addm(){
	++m;
	V[0][m].x=0;
	V[0][m].y=m;
	V[0][m].u=V[0][m].d=&V[0][m];
	V[0][m].l=V[0][0].l;
	V[0][m].r=&V[0][0];
	V[0][m].l->r=&V[0][m];
	V[0][m].r->l=&V[0][m];
}
void addn(){
	++n;
	V[n]->x=n;
	V[n]->y=0;
	V[n]->l=V[n]->r=V[n];
	V[n]->u=V[0]->u;
	V[n]->d=V[0];
	V[n]->u->d=V[n];
	V[n]->d->u=V[n];
}
void addnode(int x,int y){
	V[x][y].x=x;
	V[x][y].y=y;
	V[x][y].l=V[x][0].l;
	V[x][y].r=&V[x][0];
	V[x][y].l->r=&V[x][y];
	V[x][y].r->l=&V[x][y];
	V[x][y].u=V[0][y].u;
	V[x][y].d=&V[0][y];
	V[x][y].u->d=&V[x][y];
	V[x][y].d->u=&V[x][y];
	cnt[y]++;
}

void remove(node *b){
	if(b==V[0]) return;
	b->l->r=b->r;
	b->r->l=b->l;
	for(node *i=b->d;i!=b;i=i->d){
		for(node *j=i->r;j!=i;j=j->r){
			j->u->d=j->d;
			j->d->u=j->u;
			cnt[j->y]--;
		}
	}
}

void resume(node *b){
	if(b==V[0]) return;
	for(node *i=b->u;i!=b;i=i->u){
		for(node *j=i->l;j!=i;j=j->l){
			j->u->d=j;
			j->d->u=j;
			cnt[j->y]++;
		}
	}
	b->l->r=b;
	b->r->l=b;
}

void print();

void dance(){
	int best=N;
	node *b=NULL;
	for(node *j=V[0]->r;j!=V[0];j=j->r){
		if(cnt[j->y]<best){
			best=cnt[j->y];
			b=j;
		}
	}
	if(!b){
		print();
		scanf("\n");
		exit(0);
	}
	remove(b);
	for(node *i=b->d;i!=b;i=i->d){
		cho[i->x]=true;
		for(node *j=i->r;j!=i;j=j->r)
			remove(&V[0][j->y]);
		dance();
		for(node *j=i->l;j!=i;j=j->l)
			resume(&V[0][j->y]);
		cho[i->x]=false;
	}
	resume(b);
}

int fig[8][12][4][4]={
	{
		{//A
			{1,1},
			{1},
		},
		{//B
			{1,1,1,1},
		},
		{//C
			{1,1,1},
			{1},
		},
		{//D
			{1,1},
			{1,1},
		},
		{//E
			{1},
			{1},
			{1,1,1},
		},
		{//F
			{1,1,1,1},
			{0,1},
		},
		{//G
			{1,1,1},
			{1,0,1},
		},
		{//H
			{1,1,1},
			{1,1},
		},
		{//I
			{1,1,1},
			{0,0,1,1},
		},
		{//J
			{0,1},
			{1,1,1},
			{0,1},
		},
		{//K
			{1},
			{1,1},
			{0,1,1},
		},
		{//L
			{1,1,1,1},
			{1},
		}
	}
};

int id[12][12];
char map[12][12];
bool used[12];

struct data{
	int d,c,i,j;
} way[N];

void print(){
	for(int i=1;i<=n;i++) if(cho[i]){
		for(int x=0;x<4;x++) for(int y=0;y<4;y++) if(fig[way[i].d][way[i].c][x][y])
			map[way[i].i+x][way[i].j+y]='A'+way[i].c;
	}
	for(int i=1;i<=10;i++){
		for(int j=1;j<=i;j++)
			putchar(map[i][j]);
		putchar('\n');
	}
}

int main(){
	V[0]->l=V[0]->r=V[0]->u=V[0]->d=V[0];
	for(int i=1;i<=10;i++){
		scanf("%s",map[i]+1);
		for(int j=1;j<=i;j++)
			if(map[i][j]!='.')
				used[map[i][j]-'A']=true;
			else{
				addm();
				id[i][j]=m;
			}
	}
	for(int c=0;c<12;c++) if(!used[c]){
		addm();
		for(int i=0;i<4;i++) for(int j=0;j<4;j++){
			fig[1][c][3-i][j]=
			fig[2][c][i][3-j]=
			fig[3][c][3-i][3-j]=
			fig[4][c][j][i]=
			fig[5][c][3-j][i]=
			fig[6][c][j][3-i]=
			fig[7][c][3-j][3-i]=
			fig[0][c][i][j];
		}
		for(int d=0;d<8;d++){
			for(int i=1-3;i<=10;i++) for(int j=1-3;j<=10;j++){
				bool ok=true;
				for(int x=0;x<4;x++) for(int y=0;y<4;y++) if(fig[d][c][x][y]){
					if(i+x<=0||i+x>10||j+y<=0||j+y>i+x||map[i+x][j+y]!='.'){
						ok=false;
						break;
					}
				}
				if(!ok) continue;
				addn();
				for(int x=0;x<4;x++) for(int y=0;y<4;y++) if(fig[d][c][x][y])
					addnode(n,id[i+x][j+y]);
				addnode(n,m);
				way[n]=(data){d,c,i,j};
			}
		}
	}
	dance();
	puts("No solution");
	scanf("\n");
}
