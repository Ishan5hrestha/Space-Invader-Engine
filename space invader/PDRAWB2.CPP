#include<dos.h>
#include <iostream.h>
#include <time.h>
#include <math.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y)) 	//this copied code helps to print in required printing place
#define pi 3.141926

int resx,resy;
int steps=5;
int x,y;
int mag=1;
int delaya=10;
int bgcolor=0;

int inkey()
{
int c;
if(kbhit())
c=getch();
return c;
}

int timey(int c)  //time mechanaism yet to develop
{
	return c;
}

void floodFill(int x,int y,int oldcolor,int newcolor)
{
	if(getpixel(x,y)==oldcolor)
	{
		putpixel(x,y,newcolor);
		floodFill(x+1,y,oldcolor,newcolor);
		floodFill(x,y+1,oldcolor,newcolor);
		floodFill(x-1,y,oldcolor,newcolor);
		floodFill(x,y-1,oldcolor,newcolor);
	}
}


class frame
{
	int c[100][5]; 		//all the line coordinates
	int cmax,fmax;      //max coordinates used  and maax floods
	int flood[20][20];	//flood fills
	int i;

	public:
	void initialise()
	{ cmax=0;
	  fmax=0;
	}

	void input(int x,int y, int sx, int sy, int color)
	{
		c[cmax][0]=x-resx/2;
		c[cmax][1]=y-resy/2;
		c[cmax][2]=sx-resx/2;
		c[cmax][3]=sy-resy/2;
		c[cmax][4]=color;
		cmax++;
	}

	void input(int x,int y, int color)
	{
	 flood[fmax][0]=x-resx/2;
	 flood[fmax][1]=y-resy/2;
	 flood[fmax][2]=color;
	 fmax++;
	}

	void display()
	{
		for(i=0;i<cmax;i++)
		{
			setcolor(c[i][4]);
			line(c[i][0]+resx/2,c[i][1]+resy/2,c[i][2]+resx/2,c[i][3]+resy/2);
		}
		for(i=0;i<fmax;i++)
		{
			setfillstyle(SOLID_FILL, getmaxcolor());
			floodFill(flood[i][0]+resx/2,flood[i][1]+resy/2,getpixel(flood[i][0]+resx/2,flood[i][1]+resy/2),flood[i][2]);
		}
	}

	void store(FILE *fp)
	{
		fprintf(fp,"%d %d ",cmax,fmax);
		for(i=0;i<cmax;i++)
		fprintf(fp,"%d %d %d %d %d ",c[i][0],c[i][1],c[i][2],c[i][3],c[i][4]);
		for(i=0;i<fmax;i++)
		fprintf(fp,"%d %d %d ",flood[i][0],flood[i][1],flood[i][2]);
	}
};

void drawer(int k)
{
int i;
setcolor(6);
line(resx/2,resy,resx/2,0);
line(0,resy/2,resx,resy/2);
setcolor(15);
line(x,y-5,x,y+5);
line(x-5,y,x+5,y);
//putpixel(x,y,0);
if(k==1)
{
	setcolor(5);
	for(i=resx/2-200;i<=resx/2+200;i+=10) line(i,0,i,resy);
	for(i=resy/2-200;i<=resy/2+200;i+=10) line(0,i,resx,i);
}
}


void main()
{
      //	int error=0;
	FILE *fp;
	int gd=DETECT,gm;//IBM8514HI,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	setbkcolor(0);
	setcolor(15);
	frame f[20];
	int graph=0;
	char command[10];
	for(int i=0;i<20;i++) f[i].initialise();	//making all cmax 0
	int frm=0;   	//present frame
     //	int cord=0;     //present frame's coordinate number
	int color=15;   //present color
	char ch,name[20];
	int sx,sy;
	int s=-1;


//	cout<<"Enter File Name: ";
  //	cin>>name;



	fp=fopen("ship","w");
	resx=getmaxx();
	resy=getmaxy();
	x=resx/2;y=resy/2;

	getch();



	//Main loop begins
for(;ch!=27;)
{
	setbkcolor(bgcolor);
	delay(delaya);
	cleardevice();
	drawer(graph);

	ch=inkey();
	switch(tolower(ch))
	{
		case 'w':y-=steps;
			 break;
		case 's':y+=steps;
			 break;
		case 'a':x-=steps;
			 break;
		case 'd':x+=steps;
			 break;
		case '+':mag++;
			 break;
		case '-':mag--;
			 break;
		case ' ':if(s==-1){sx=x; sy=y;}
			 s=s*-1;
			 if(s==-1) f[frm].input(x,y,sx,sy,color);
			 break;
		case 'x':color=(color+1) %16;
			 setcolor(color);
			 break;
		case 'f':f[frm].input(x,y,color);
			 break;

		case '.':delaya+=10;
			 break;
		case ',':delaya-=10;
			 if (delaya<0) delaya=0;
			 break;
		case '`':cin>>command;
			 if(strcmp(command,"next")==0) frm++;
			 if(strcmp(command,"save")==0)
			 {
			  fprintf(fp,"%d ",frm);
			  for(i=0;i<=frm;i++) f[i].store(fp);
			  cleardevice();
			  cout<<"SUCCESS";
			  getch();
			  }
			  if(strcmp(command,"graph_on")==0) graph=1;
			  if(strcmp(command,"graph_off")==0) graph=0;
			  if(strcmp(command,"bgcolor")==0) bgcolor=(bgcolor+1)%15;
			  if(strcmp(command,"bgreset")==0) bgcolor=0;
			  if(strcmp(command,"+")==0) steps++;
			  if(strcmp(command,"-")==0) steps--;

			 break;
		default :break;
	}//switch case

	if(frm>0) f[frm-1].display();
	f[frm].display();
	if(s==1) line(x,y,sx,sy);
	gotoxy(1,1);
	cout<<x*10<<y*10<<color<<"\n";
	cout<<"Frame: "<<frm<<" ";
	cout<<"Delay: "<<delaya;

}	//for loop

	fclose(fp);
	getch();
}