#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<map>
#include<ctime>
#include<set>
#include<queue>
#include<cmath>
#include<vector>
#include<bitset>
#include<functional>
#define x first
#define y second
#define mp make_pair
#define pb push_back
using namespace std;

typedef long long LL;
typedef long double ld;

const int MAX=200000+10;

int n;
ld a,c[MAX],s[MAX],pp[MAX];

int main()
{
    int i;
    scanf("%d%Lf",&n,&a);
    for(i=1;i<=n;++i)
    {
        scanf("%Lf",&c[i]);
        s[i]=c[i]+s[i-1];
    }
    for(i=1;i<=n;++i)
        pp[i]=pp[i-1]+1.0/i;
    int up=200000000/n;
    for(i=1;i<=n;++i)
    {
        int j=floor(i*a);
        if(j==0)
        {
            printf("%lf\n",0.0);
            continue;
        }
        else
        {
            ld ans=0;
            int kuai=min(max(up,1),j),dd=max(j/kuai,1),now=j;
            while(now)
            {
                int left=max(now-dd+1,1);
                ans+=(s[now]-s[left-1])*(pp[i-left]-pp[i-now-1])/(now-left+1);
                ans+=(s[now]-s[left-1])/(i-(now*3+left*4)/7);
                now=left-1;
                dd=max(dd-2,1);
            }
            if(i%5==0)
                --up;
            printf("%Lf\n",ans*c[i]/2);
        }
    }
    scanf("%u");
    return 0;
}
