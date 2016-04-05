#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<graphics.h>
#include<stdlib.h>
#define pi 3.14

int sopipe=50,pathdist=150,sofbird=40,dbtwpipe=8*50,bgcolor=0,pc=2,bc=14,speed=15;
void clr()
{
	setfillstyle(SOLID_FILL,bgcolor);
	bar(0,0,640,480);
}
void uppipe(float x1,float y2)
{
	setcolor(0);
	setfillstyle(SOLID_FILL,pc);
	bar(x1,0,x1+sopipe,y2-30);
	bar(x1-10,y2-30,x1+10+sopipe,y2);
}
void downpipe(float x1,float y2)
{
	setcolor(0);
	setfillstyle(SOLID_FILL,pc);
	bar(x1,480,x1+sopipe,y2+30);
	bar(x1-10,y2+30,x1+10+sopipe,y2);
}
void bird(float x,float y)
{
	int r=sofbird/2;
	//body
	setcolor(0);
	setfillstyle(SOLID_FILL,bc);
	sector(x,y,0,360,r,r);
	//wing
	setcolor(0);
	fillellipse(x-(0.5*r),y+(0.25*r),sofbird/2,2*sofbird/12);
	//eye
	setcolor(0);
	setfillstyle(SOLID_FILL,WHITE);
	sector(x+(0.5*r*cos(pi/4)),y-(0.5*r*sin(pi/4)),0,360,sofbird/3,sofbird/3);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,getcolor());
	sector(x+(0.75*r*cos(pi/6)),y-(0.75*r*sin(pi/6)),0,360,sofbird/5,sofbird/5);
	//lips
	setcolor(0);
	setfillstyle(SOLID_FILL,RED);
	fillellipse(x+r,y+(r/3),sofbird/2.5,sofbird/15);
	fillellipse(x+r,y+(r/3)+(sofbird/12),sofbird/2.5,sofbird/15);

}
void hurdle(float x,float y)
{
	uppipe(x,y);
	downpipe(x,y+pathdist);

}
void intro()
{
	char ch;
	settextstyle(1,0,3);
	outtextxy(160,80,"WELCOME TO FLAPPY BIRD");
	settextstyle(2,0,4);
	outtextxy(480,110,"By:-SANCHIT GUPTA");
	bird(320,200);
	setcolor(WHITE);
	settextstyle(3,0,2);
	outtextxy(240,280,"PRESS:- ");
	outtextxy(280,300,"1 - EASY");
	outtextxy(280,320,"2 - NORMAL");
	outtextxy(280,340,"3 - HARD");
	outtextxy(200,400,"To exit anytime press X");
	ch=getch();
	if(ch=='x'|| ch=='X')
		exit(0);
	else if(ch=='1')
	{
		pathdist=150;
		dbtwpipe=11*sopipe;
		speed=10;
	}
	else if(ch=='2')
	{
		pathdist=130;
		dbtwpipe=9*sopipe;
		speed=15;
	}
	else if(ch=='3')
	{
		pathdist=110;
		dbtwpipe=7*sopipe;
		speed=20;
	}
	clr();
}
int hit(int score)
{
      //	setfillstyle(SOLID_FILL,0);
       //	bar(0,0,640,480);
	char ch,scr[15];
	sprintf(scr,"YOUR SCORE IS: %d",score);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(160,120,480,360);
	settextstyle(3,0,4);
	outtextxy(163,140," YOU HAVE BEEN HIT ");
	settextstyle(3,0,3);
	outtextxy(180,200,scr);
	settextstyle(3,0,2);
	outtextxy(200,280,"PRESS:- ");
	outtextxy(240,300,"S - TO START AGAIN");
	outtextxy(240,320,"X - EXIT");
	ch=getch();
	if(ch=='x' || ch=='X')
		exit(0);
	else
		return 0;
	return 1;
}
void showscore(int score)
{
       char ch[50];
       setcolor(15);
       sprintf(ch,"SCORE: %d",score);
       outtextxy(480,0,ch);
}
int main(void)
{
   /* request auto detection */
   int i,p=1,xb,yb,k,j,y[10],gdriver = DETECT, gmode, errorcode,score=0;
   int xmax, ymax;
   char ch='o';
   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "C://TC//BGI");
   //randomize();
   /* read result of initialization */
   errorcode = graphresult();
   /* an error occurred */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

   setcolor(getmaxcolor());
   xmax = getmaxx();
   ymax = getmaxy();

   /* draw a diagonal line */
   //line(0, 0, xmax, ymax);
   //bird(320,240);
   // uppipe(320,200);
   // downpipe(320,200+pathdist);
    target:
    clr();
    score=0;
    intro();
    for(i=0;i<10;i++)
	y[i]=70+(10*(rand()%26));
   xb=160;
   yb=240;
   bird(xb,yb);
   getch();
   for(i=xmax;;i-=speed)
   {
	if(kbhit()!=0)
	{
		ch=getch();
		if(ch==' ')
			yb=yb-30;
		else
			exit(0);
	}
	else
		yb+=7;
	bird(xb,yb);
	//if(i<(xb+(sofbird/2)) && i>(xb-(sofbird/2)))
	//	score++;
	for(j=i,k=0;j<xmax;j+=(sopipe+dbtwpipe),k++)
	{
		if(k>=10)
			k=0;
		hurdle(j,y[k]);
		if(j<=(xb+(sofbird/2)) && j>=(xb-(sofbird/2)))
		{

			if((yb-(sofbird/2))>=y[k] && (yb+(sofbird/2))<=(y[k]+pathdist))
			{
				score++;

				continue;
			}
			else
			{
				p=hit(score/4);
				if(p==0)
					goto target;
			}

		}showscore(score/4);
	}

	delay(35);
	ch=='o';
       clr();
   }


   /* clean up */
   getch();
   closegraph();
   return 0;
}
