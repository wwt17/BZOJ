const base=10000;
type num=array[0..500] of integer;
var n:longint;
function h(n:longint):num;
 var i:longint;
 procedure mult(a:longint);
  var i,x:longint;
  begin
   x:=0;
   for i:=1 to h[0] do
    begin
     x:=h[i]*a+x;
     h[i]:=x mod base;
     x:=x div base;
    end;
   if x>0 then
    begin
     inc(h[0]);
     h[h[0]]:=x;
    end;
  end;
 procedure divi(a:longint);
  var i,x:longint;
  begin
   x:=0;
   for i:=h[0] downto 1 do
    begin
     x:=x*base+h[i];
     h[i]:=x div a;
     x:=x mod a;
    end;
   while h[h[0]]=0 do dec(h[0]);
  end;
 begin
  fillchar(h,sizeof(h),0);
  h[0]:=1;h[1]:=1;
  for i:=1 to n do
   begin
    mult(4*i-2);
    divi(i+1);
   end;
 end;
procedure print(a:num);
 var i:longint;
 begin
  write(a[a[0]]);
  for i:=a[0]-1 downto 1 do
   begin
    if a[i]<1000 then write(0);
    if a[i]< 100 then write(0);
    if a[i]<  10 then write(0);
    write(a[i]);
   end;
  writeln;
 end;
begin
 readln(n);
 print(h(n));
end.
