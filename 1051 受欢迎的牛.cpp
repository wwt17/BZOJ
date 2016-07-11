/**************************************************************
    Problem: 1051
    User: wwt15
    Language: C++
    Result: Accepted
    Time:88 ms
    Memory:2012 kb
****************************************************************/
 
#include <cstdio>
#define size 10001
int dfn[size],low[size],cnt[size],sum[size],belong[size];
bool visited[size],instack[size];
int stack[size*4];
int tot,top,i,n,m,a,b,cnt0,val,cmp;
struct node { int num; node *next; } *son[size],*p;
int min(int a,int b) { return a<b?a:b; }
void tarjan(int v) {
    dfn[v]=low[v]=++tot;
    stack[++top]=v;
    instack[v]=visited[v]=true;
    for (node *p=son[v];p;p=p->next) {
        if (!visited[p->num]) {
            tarjan(p->num);
            low[v]=min(low[v],low[p->num]);
        } else if (instack[p->num])
            low[v]=min(low[v],dfn[p->num]);
    }
    if (low[v]==dfn[v]) {
        ++cmp;
        int u;
        do {
            u=stack[top--];
            belong[u]=cmp;
            instack[u]=false;
        } while (u^v);
    }
}
int main() {
    scanf("%d%d\n",&n,&m);
    for (i=1;i<=m;++i) {
        scanf("%d%d\n",&a,&b);
        p=new node;
        p->num=b;
        p->next=son[a];
        son[a]=p;
    }
    for (i=1;i<=n;++i) if (!visited[i]) tarjan(i);
    for (i=1;i<=n;++i) {
        for (p=son[i];p;p=p->next)
            if (belong[i]^belong[p->num]) ++cnt[belong[i]];
      ++sum[belong[i]];
    }
    for (i=1;i<=cmp;++i) if (!cnt[i]) { ++cnt0; val=sum[i]; }
    if (cnt0==1) printf("%d\n",val); else printf("0\n");
}
