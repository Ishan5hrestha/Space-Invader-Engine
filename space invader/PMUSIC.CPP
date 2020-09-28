#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<iostream.h>


int inkey()
{
int c;
if(kbhit())
c=getch();
return c;
}



void main()
{
FILE *fp;
int t,mul=1,i=0;
char ch;
int note[100],dur,max;
int c=261.63,cs=227.18,d=293.66,ds=311.13,e=329.63,f=349.23,fs=369.99,g=392.00,gs=415.3,a=440.00,as=466.16,b=493.88,c5=523.37;

clrscr();
fp=fopen("music.txt","r" );
for(i=0;fscanf(fp,"%d",&note[i])!=EOF;i++);
max=i;

for(i=0;i<max;i++)
{
printf("%d",note[i]);


switch(ch)
{
	case 'a': sound(c*mul);dur++;break;
	case 's': sound(d*mul);break;
	case 'd': sound(e*mul);break;
	case 'f': sound(f*mul);break;
	case 'g': sound(g*mul);break;
	case 'h': sound(a*mul);break;
	case 'j': sound(b*mul);break;
	case -10: nosound();note[i]=dur*1000+c*mul;break;
}
}
nosound();
getch();
fclose(fp);
}
*/