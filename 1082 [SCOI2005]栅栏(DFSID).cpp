/*
ID: wwt14
TASK: fence8
LANG: C++
*/
#include <stdio.h>
#include <stdlib.h>
int N,R,i,j,board[51],l,r,mid,max[1024];
short rail[1024];
bool dfsid(int dep,int last,int waste) {
	if (!dep) return true;
	if (waste>max[mid]) return false;
	bool ret=false;
	int j=(rail[dep]==rail[dep+1])?last:N;
	for (;j;--j) if (board[j]>=rail[dep]) {
		board[j]-=rail[dep];
		ret=ret||dfsid(dep-1,j,waste+(board[j]<rail[1])*board[j]);
		board[j]+=rail[dep];
		if (ret) return true;
	}
	return false;
}
int compare(const void *a,const void *b)
	{ return *(int*)a-*(int*)b; }
int compare_short(const void *a,const void *b)
  { return *(short*)a-*(short*)b; }
int main() {
  scanf("%d\n",&N);
  for (i=1;i<=N;i++) scanf("%d\n",&board[i]);
  qsort(board+1,N,sizeof(int),compare);
  scanf("%d\n",&R);
  for (j=1;j<=R;j++) scanf("%d\n",&rail[j]);
  qsort(rail+1,R,sizeof(short),compare_short);
  for (i=1;i<=N;++i) max[0]+=board[i];
  for (j=1;j<=R;++j) max[j]=max[j-1]-rail[j];
  for (l=0,r=R;l<r;dfsid(mid,N,0)?l=mid:r=mid-1)
		mid=(l+r+1) >> 1;
  printf("%d\n",l);
}
