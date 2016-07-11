#include <cstdio>
#include <cstring>
char mem[2*1024*1024],*newc=mem,*cur=newc,*tmpcur;
struct segment{
	char *begin,*end;
	segment *last,*next;
	#define segsize(x) ((x).end-(x).begin)
	segment(
		char* _begin,char* _end,
		segment* _last,segment* _next):
		begin(_begin),end(_end),last(_last),next(_next){
		last->next=this;
		next->last=this;
	}
	~segment(){
		last->next=next;
		next->last=last;
	}
} nullmem(newc,newc,&nullmem,&nullmem),*null=&nullmem,*curseg=null,*tmpcurseg;
#define head null
int main(){
	int t,n;
	scanf("%u",&t);
	while(t--){
		switch(scanf("\n"),getchar()){
			case 'M'://Move k
				scanf("ove %u",&n);
				for(curseg=head->next;
					curseg!=null&&n>=segsize(*curseg);
					n-=segsize(*curseg),curseg=curseg->next);
				cur=curseg->begin+n;
				break;
			case 'I'://Insert n endl S
				scanf("nsert %u",&n);
				if(cur>curseg->begin){
					new segment(curseg->begin,cur,curseg->last,curseg);
					curseg->begin=cur;
				}
				cur=newc;
				while(n--){
					while((*newc=getchar())=='\n');
					newc++;
				}
				curseg=new segment(cur,newc,curseg->last,curseg);
				break;
			case 'D'://Delete n
				scanf("elete %u",&n);
				if(cur!=curseg->begin){
					new segment(curseg->begin,cur,curseg->last,curseg);
					curseg->begin=cur;
				}
				while(curseg!=null&&n>=segsize(*curseg)){
					n-=segsize(*curseg);
					curseg=curseg->next;
					delete curseg->last;
				}
				cur=curseg->begin+=n;
				break;
			case 'G'://Get n
				scanf("et %u",&n);
				tmpcur=cur; tmpcurseg=curseg;
				while(curseg!=null&&n>=curseg->end-cur){
					n-=curseg->end-cur;
					fwrite(cur,1,curseg->end-cur,stdout);
					curseg=curseg->next;
					cur=curseg->begin;
				}
				fwrite(cur,1,n,stdout);
				putchar('\n');
				curseg=tmpcurseg;
				cur=tmpcur;
				break;
			case 'P'://Prev
				scanf("rev");
				if(cur!=curseg->begin) cur--; else
					curseg=curseg->last,cur=curseg->end-1;
				break;
			case 'N'://Next
				scanf("ext");
				if(++cur==curseg->end)
					curseg=curseg->next,cur=curseg->begin;
				break;
		}
	}
}
