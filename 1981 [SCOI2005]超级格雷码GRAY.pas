var
 up:array[1..16] of boolean;
 da:array[1..16] of integer;
 n,B,i:longint;
procedure test(k:integer);
 begin
  if k>n then halt;
  if up[k]
   then begin
         if da[k]=B-1
          then begin up[k]:=false;test(k+1);end
          else inc(da[k]);
        end
   else begin
         if da[k]=0
          then begin up[k]:=true;test(k+1);end
          else dec(da[k]);
        end;
 end;
begin
 readln(n,B);
 fillchar(da,sizeof(da),0);
 fillchar(up,sizeof(up),true);
 while true do
  begin
   for i:=1 to n do
   if da[i]<10
    then write(da[i])
    else write(chr(55+da[i]));
   writeln;
   test(1);
  end;
end.
