#include <stdlib.h>
#include <dos.h>
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
int univx,univy,univz;
int mag=1;
int delaya=10;

int inkey()
{
int c;
if(kbhit())
c=getch();
return c;
}

int timey()  //time mechanaism yet to develop
{
	time_t t;
	t = time(NULL);
	return (t%60);
}


void rotate(int px,int py,int ox,int oy,int degree)
{
	univx= (float)cos(pi/180*degree)*(px-ox) - sin(pi/180*degree)*(py-oy)+ox;
	univy= (float)sin(pi/180*degree)*(px-ox) + cos(pi/180*degree)*(py-oy)+oy;
}


class object
{
	int frames;
	int c[5][20][5]; 		//all the line coordinates
	int cmax[5],fmax[5];      //max coordinates used  and maax floods
	int flood[5][10][3];	//flood fills
	int colrad;
	int health;
	int i,j;
	int x,y;

	public:

	void initialise(int a,int b)
	{x=a;y=b;colrad=20;health=5;}

	void returninfo()
	{univx=x;univy=y;univz=colrad;}

	int returnhp()
	{return(health);}

	void hp(int h)
	{health=health+h;}

	void read(FILE *fp)
	{
		fscanf(fp,"%d ",&frames);
		for(i=0;i<=frames;i++)
		{
			fscanf(fp,"%d %d ",&cmax[i],&fmax[i]);
			for(j=0;j<cmax[i];j++)
			fscanf(fp,"%d %d %d %d %d ",&c[i][j][0],&c[i][j][1],&c[i][j][2],&c[i][j][3],&c[i][j][4]);
			for(j=0;j<fmax[i];j++)
			fscanf(fp,"%d %d %d ",&flood[i][j][0],&flood[i][j][1],&flood[i][j][2]);
		}
	}


	void display(int fno)
	{       if(x<resx || x>0 || y<resy || y>0)
		{
		for(i=0;i<cmax[fno];i++)
		{
			if (fno>frames) break;
			setcolor(c[fno][i][4]);
			line(c[fno][i][0]+x,c[fno][i][1]+y,c[fno][i][2]+x,c[fno][i][3]+y);
		}
		for(i=0;i<fmax[fno];i++)
		{
			floodfill(flood[fno][i][0]+x,flood[fno][i][1]+y,flood[fno][i][2]);
		}
		}

	}

	void move(int xm,int ym)
	{x=x+xm;y=y+ym;	}

	int outside()
	{
	 if(x<0 || x>640 || y>480 || y<0) return 1; //screen size is 480
	 else return 0;
	}



/*
	void rotateo(int degree)  	//rotate object
	{
	int i,fno;
	int a;
	for(fno=0;fno<=frames;fno++)
	{
		for(i=0;i<cmax[fno];i++)
		{
			rotate(c[fno][i][0],c[fno][i][1],0,0,degree);
			c[fno][i][0]=univx;
			c[fno][i][1]=univy;
			rotate(c[fno][i][2],c[fno][i][3],0,0,degree);
			c[fno][i][2]=univx;
			c[fno][i][3]=univy;
		}
		for(i=0;i<fmax[fno];i++)
		{
			rotate(flood[fno][i][0],flood[fno][i][1],0,0,1);
	     a		flood[fno][i][0]=univx;
			flood[fno][i][1]=univy;
		}
	}    //for
	}    //void

*/
};


int collision(object a,object b)//r1r2 is collision radius and x1x2y1y2 is center of sprite
	{
	float d,x1,y1,x2,y2,r1,r2;
	a.returninfo();
	x1=univx; y1=univy; r1=univz;
     //	gotoxy(1,1);
     //	cout<<x1<<y1<<r1;
	b.returninfo();
	x2=univx; y2=univy; r2=univz;
     //	gotoxy(2,2);
     //	cout<<x2<<y2<<r2;
	d=pow((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1),0.5);
     //	gotoxy(3,3);
     //	cout<<d;
     //	if (d<r1+r2) {cout<<"Collision";getch();}
	if(d<r1+r2) return 1;
	else return 0;
	}


void mus(int fr,int leng,int del)
{
sound(fr);
delay(leng);
nosound();
delay(del);
}



 void main()
{
	FILE *fp;
       //	int c=261.63,d=293.66,e=329.63,f=349.23,g=392.00,a=440.00,b=493.88,23.37;
	int earthhp,score;;
	int i,j,t;
	int gd=DETECT,gm;//IBM8514HI,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	setbkcolor(1);
	setcolor(5);
		object bg;
		object ship;
		object bullet[7];
		object asteroid;
		object blast;
	int shoot=0,bn=0;
	char ch;
	int hs=0;;
	resx=getmaxx();
	resy=getmaxy();
	t=timey();

	//loading part

	fp=fopen("bg.txt","r");
	bg.read(fp);
	fclose(fp);
	fp=fopen("ship.txt","r");
	ship.read(fp);
	fclose(fp);
	fp=fopen("asteroid.txt","r");
	asteroid.read(fp);
	fclose(fp);
	fp=fopen("bullet.txt","r");
	for(i=0;i<7;i++)
	{
		bullet[i].read(fp);
		rewind(fp);
	}
	fp=fopen("blast.txt","r");
	blast.read(fp);
	fclose(fp);

	//main menu
	mainmenu:
	int as=1;//as asteroid speed
	int ss=5;//ship speed


	setbkcolor(1);
	fp=fopen("music.txt","r");

	for(;ch!=' ';)
	{
	if (ch==27) goto end;
	cleardevice();
	bg.initialise(resx/2,resy/2);
	bg.display(0);
	setcolor(5);
	settextstyle(1,0,5);
	outtextxy(150,100,"SPACE DEFENDER");
	if(timey()%2==0)
	{
		gotoxy(17,32);
		printf("Press space to start");
	}
	gotoxy(23,35);
	cout<<"Developed by";
	gotoxy(24,34);
	cout<<"Ishan Shrestha";
	gotoxy(25,34);
	cout<<"Gaurav Acharya";

	//for sound
	if(fscanf(fp,"%d %d",&univx,&univy)!=EOF) mus(univx,univy,100);
	else rewind(fp);

	ch=inkey();
	}
	fclose(fp);
	nosound();

	cleardevice();
	setcolor(3);
	settextstyle(1,0,5);
	outtextxy(175,100,"GET PSYCHED");
	gotoxy(14,20);
	cout<<"Defend the earth from the asteroid fall.";
	gotoxy(15,19);
	cout<<"Use A and D to navigate and SPACE to fire.";
	delay(4000);

	restartgame:
	//initialisation part

	fp=fopen("highscore.txt","r");
	fscanf(fp,"%d",&hs);
	fclose(fp);


	bg.initialise(resx/2,resy/2);
	ship.initialise(resx/2,resy-50);
	asteroid.initialise(100,100);
	blast.initialise(resx/2,resy/2);
	score=0;
	earthhp=10;
	getch();
	t=timey();

for(;ch!=27;)
{
	cleardevice();
	ch=inkey();

	//Background
	setbkcolor(0);
	bg.display(0);

	//user input
	if (ch=='d') ship.move(ss,0);
	if (ch=='a') ship.move(-ss,0);
	if (ch==' ')
	{
		ship.returninfo();
		bullet[bn].initialise(univx,univy);
		sound(1000);
		bn=(bn+1)%7;
	}

	//processing
	bg.move(0,1);
	if (bg.outside()==1) bg.initialise(resx/2,0);


	asteroid.move(0,as);
	//difficulty
	if(abs(timey()-t)>20) { as++;ss+=3;t=timey();}


	if (asteroid.outside()==1)
	{
		earthhp-=asteroid.returnhp();
		asteroid.initialise(rand()%100*6,0);
		sound(100);
	}
	if (asteroid.returnhp()<1)
	{
		 asteroid.initialise(rand()%100*6,0);
		 score++;
		 sound(500);
	}

	if (collision(asteroid,ship)==1)
	{
		sound(100);
		ship.hp(-asteroid.returnhp());
		asteroid.initialise(rand()*6%100,0);
	}


	for(i=0;i<7;i++)
	{
		 bullet[i].move(0,-5);
		 if (collision(asteroid,bullet[i])==1)
		 {
			sound(300);
			asteroid.hp(-1);
			bullet[i].initialise(-10,10);
		 }
	}

	//screenstop
	ship.returninfo();
	if (univx>630) ship.move(-1,0);
	if (univx<10) ship.move(1,0);



	if(earthhp<1) goto earthdead;
	if(ship.returnhp()<1) goto shipdead;



	//display
	ship.display(0);
	asteroid.display(5-asteroid.returnhp());
	for(i=0;i<7;i++) bullet[i].display(0);


	//draw hp
	gotoxy(1,1);
	cout<<"Earth HP";
	if(earthhp>6) setcolor(GREEN);
	if(earthhp<7) setcolor(YELLOW);
	if(earthhp<4) setcolor(RED);
	rectangle(100,10,25*earthhp+100,15);
	setfillstyle(1,getcolor());
	floodfill(101,11,getcolor());

	gotoxy(2,1);
	cout<<"Ship HP";
	univx=ship.returnhp();
	if(univx>3) setcolor(GREEN);
	if(univx<4) setcolor(YELLOW);
	if(univx<3) setcolor(RED);
	rectangle(100,20,50*univx+100,25);
	setfillstyle(1,getcolor());
	floodfill(101,21,getcolor());

	gotoxy(3,1);
	cout<<"Score: "<<score;

	delay(20);
	nosound();

}

	goto end;
	//Game Over


	earthdead:
		sound(50);

		for(i=0;i<5;i++)
	{
		cleardevice();
		blast.display(i);
		delay(500);
	}
	delay(500);
	nosound();
	cleardevice();
	setcolor(RED);
	settextstyle(7,0,0);
	outtextxy(100,100,"You failed to defend the planet!!!");
	gotoxy(20,35);
	cout<<"SCORE: "<<score;
		if(score>hs)
	{
		hs=score;
		gotoxy(20,30);
		cout<<"New High Score: "<<score;
		fp=fopen("highscore.txt","w");
		fprintf(fp,"%d",hs);
		fclose(fp);
	}
	delay(2000);

	getch();
	goto mainmenu;

	shipdead:
	 sound(50);
	for(i=0;i<6;i++)
	{
		cleardevice();
		blast.display(i);
		delay(500);
	}
	delay(500);
	nosound();

	cleardevice();
	setcolor(RED);
	settextstyle(7,0,0);
	outtextxy(250,200,"YOU DIED");
	gotoxy(20,35);
	cout<<"SCORE: "<<score;
	if(score>hs)
	{
		hs=score;
		gotoxy(20,30);
		cout<<"New High Score: "<<score;
		fp=fopen("highscore.txt","w");
		fprintf(fp,"%d",hs);
		fclose(fp);
	}
	delay(2000);
	getch();
	goto mainmenu;
	end:
	nosound();


}