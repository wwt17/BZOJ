#include <cstdio>
#define size 60
#define lenP 60
#define P 10000007
#define ll unsigned long long
int len,Pow[size][lenP+1];
ll C[size][size];
void initC(){
    for (int i=0;i<=len;++i){
        C[i][0]=1;
        for (int j=1;j<=i;++j)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
}
void initPow(){
    for (int i=1;i<=len;++i){
        Pow[i][0]=1;Pow[i][1]=i;
        for (int j=2;j<=lenP;++j)
            Pow[i][j]=(ll)Pow[i][j-1]*Pow[i][j-1]%P;
    }
}
int power(int a,ll b){
    if (!a) return 1;
    ll ret=1;
    for (int j=1;b;b>>=1,++j) if (b&1)
        ret=ret*Pow[a][j]%P;
    return ret;
}
bool f[size];
int main(){
    ll N,Ans=1;
    scanf("%llu",&N);
    for (len=0;N;N>>=1) f[++len]=N&1;
    initC();
    initPow();
    int sum=0;
    for (int i=len;i;--i) if (f[i]){
        for (int j=i-1;j>=0;--j)
            Ans=Ans*power(sum+j,C[i-1][j])%P;
        ++sum;
    }
    printf("%d\n",(int)(Ans*sum%P));
}
