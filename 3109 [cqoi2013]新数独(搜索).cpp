#include <cstdio>
#include <cstdlib>
int Num,num,map[9][9],fx[9],fy[9],fz[3][3];
bool sign[2][9][9];
const int order[9][2]={1,1, 0,1, 1,0, 0,0, 1,2, 0,2, 2,1, 2,0, 2,2};
inline bool check(int x,int y,int c){
	return
		!(fx[x]&1<<c)
	&&	!(fy[y]&1<<c)
	&&	!(fz[x/3][y/3]&1<<c)
	&&	(x%3==0||!map[x-1][y]||(map[x-1][y]<c)^sign[1][x][y])
	&&	(x%3==2||!map[x+1][y]||(c<map[x+1][y])^sign[1][x+1][y])
	&&	(y%3==0||!map[x][y-1]||(map[x][y-1]<c)^sign[0][x][y])
	&&	(y%3==2||!map[x][y+1]||(c<map[x][y+1])^sign[0][x][y+1]);
}
void square();
void search(){
	if(num==9){
		Num++;
		square();
		Num--;
		num=9;
		return;
	}
	int x=order[Num][0]*3+order[num][0],
		y=order[Num][1]*3+order[num][1];
	for(int c=1;c<=9;c++)
		if(check(x,y,c)){
			map[x][y]=c;
			fx[x]^=1<<c;
			fy[y]^=1<<c;
			fz[x/3][y/3]^=1<<c;
			num++;
			search();
			num--;
			fx[x]^=1<<c;
			fy[y]^=1<<c;
			fz[x/3][y/3]^=1<<c;
			map[x][y]=0;
		}
	map[x][y]=0;
}
void square(){
	if(Num==9){
		for(int i=0;i<9;i++){
			for(int j=0;j<8;j++) printf("%d ",map[i][j]);
			printf("%d\n",map[i][8]);
		}
		exit(0);
	}
	num=0; search();
}
inline bool gc(){
	loop:
	switch(getchar()){
		case '<': case '^': return 0;
		case '>': case 'v': return 1;
		default: goto loop;
	}
}
int main(){
	for(int i=0;i<9;i++){
		if(i%3) for(int j=0;j<9;j++)
				sign[1][i][j]=gc();
		for(int j=0;j<9;j++) if(j%3)
				sign[0][i][j]=gc();
	}
	Num=0; square();
}
