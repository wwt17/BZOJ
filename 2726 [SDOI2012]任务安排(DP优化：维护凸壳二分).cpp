/*
sf(j)=sF[n]-sF[j]
f[i]=min{ f[j] + (S+sT[i]-sT[j])*(sF[n]-sF[j]) }
    =min{ f[j]-sT[j]*sf(j) + (S+sT[i])*sf(j) }

X[j]=sf(j)
Y[j]=f[j]-sT[j]*sf(j)

f[i]=min{ (S+st[i])*X[j] + 1*Y[j] }
*/
#include <cstdio>
typedef long long ll;
const int N=300005;
int n;
ll s,t[N],c[N],x[N],y[N],f[N];
int top,q[N];
ll calc(int i,int j){
	return f[j]+(s+t[i]-t[j])*(c[n]-c[j]);
}
bool mini(ll &a,const ll b){
	return b<a?(a=b,true):false;
}
double cross(int a,int b,int c){
	return 1.*(x[b]-x[a])*(y[c]-y[a])-1.*(x[c]-x[a])*(y[b]-y[a]);
}
int main(){
	scanf("%d%lld",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",t+i,c+i);
		t[i]+=t[i-1];
		c[i]+=c[i-1];
	}
	x[0]=c[n];
	y[0]=0;
	q[top=1]=0;
	for(int i=1;i<=n;i++){
		int l=0,r=top;
		while(r-l>1){
			int mid=l+r>>1;
			if(calc(i,q[mid])>calc(i,q[mid+1]))
				l=mid;
			else
				r=mid;
		}
		f[i]=calc(i,q[r]);
		x[i]=c[n]-c[i];
		y[i]=f[i]-t[i]*x[i];
		for(;top>=2&&cross(q[top-1],q[top],i)>=0;top--);
		q[++top]=i;
	}
	printf("%lld\n",f[n]);
}
