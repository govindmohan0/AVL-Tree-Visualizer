#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<alloc.h>
#include<graphics.h>
char element[100];
int check=1;
int diff;
int x=320,y=20;
int temp=0,criticaldata=0;

//structure for creating binary tree
struct avl
{
long int data;
struct avl *parent,*lc,*rc;
};
struct avl *critical,*nodemain,*node,*par1,*start;

//function to calculate height and balance factor
int heightcalc(struct avl *node1)
{
if(node1==NULL)
   return 0;
else
{
int lheight=heightcalc(node1->lc);
int rheight=heightcalc(node1->rc);
if(lheight>rheight)
   return lheight+1;
else
   return rheight+1;
}
}//end height calc

//function for insertion in binary tree
void insert(int ele,struct avl *par)
{
 while(par!=NULL)
 {
 if(ele<par->data)
 {
 par1=par;
 par=par->lc;
 }
 else if(ele>=par->data)
 {
 par1=par;
 par=par->rc;
 }
 }//end while
 node=(struct avl *)malloc(sizeof(struct avl));
 node->data=ele;
 node->parent=par1;
 node->lc=NULL;
 node->rc=NULL;
 if(check==1)
 {
 start=node;
 check++;
 goto a;
 }
 if(ele<par1->data)
 {
 par1->lc=node;
 }
 else if(ele>=par1->data)
 {
 par1->rc=node;
 }
a:}//end insert

//function to display the tree
void display(struct avl *p,int q,int r,int s,int t)
{
char *word;
s=s/2;
if(p==NULL)
return;
itoa(p->data,word,10);
setfillstyle(SOLID_FILL,GREEN);
if(p->lc!=NULL)
{
setfillstyle(SOLID_FILL,GREEN);
fillellipse(q-s,r+t,15,15);
circle(q-s,r+t,15);
line(q,r,q-s,r+t);
}
if(p->rc!=NULL)
{
setfillstyle(SOLID_FILL,GREEN);
fillellipse(q+s,r+t,15,15);
circle(q+s,r+t,15);
line(q,r,q+s,r+t);
}
if(p->data==criticaldata)
setfillstyle(SOLID_FILL,RED);
fillellipse(q,r,15,15);
circle(q,r,15);
setcolor(WHITE);
outtextxy(q-9,r-2,word);
display(p->lc,q-s,r+t,s,t);
display(p->rc,q+s,r+t,s,t);
}
void startdisplay()
{ int x1=320,y1=20;
display(start,x1,y1,getmaxx()/2,70);
getch();
clrscr();
cleardevice();
}

//function for LL rotation
void LLrotation(struct avl *print)
{
struct avl *x=print;
struct avl *y=print->lc;
y->parent=print->parent;
if(print->data<print->parent->data)
print->parent->lc=y;
else
print->parent->rc=y;
if(print==start)
{start=y;
start->parent=NULL;
}
x->lc=y->rc;
y->rc=x;
x->parent=y;
}//end LL

//function for RR rotation
void RRrotation(struct avl *print)
{
struct avl *x=print;
struct avl *y=print->rc;
y->parent=print->parent;
if(print->data<print->parent->data)
print->parent->lc=y;
else
print->parent->rc=y;
if(print==start)
{start=y;
start->parent=NULL;
}
x->rc=y->lc;
y->lc=x;
x->parent=y;
}//end RR

//function for LR rotation
void LRrotation(struct avl *print)
{
struct avl *x=print;
struct avl *y=print->lc;
struct avl *z=y->rc;
z->parent=print->parent;
if(print->data<print->parent->data)
x->parent->lc=z;
else
x->parent->rc=z;
if(print==start)
{start=z;
start->parent=NULL;
}
y->rc=z->lc;
z->lc=print->lc;
x->lc=z->rc;
z->rc=x;
x->parent=z;
y->parent=z;
}//end LR

//function for RL rotation
void RLrotation(struct avl *print)
{
struct avl *x=print;
struct avl *y=print->rc;
struct avl *z=y->lc;
z->parent=print->parent;
if(print->data<print->parent->data)
x->parent->lc=z;
else
x->parent->rc=z;
if(print==start)
{
start=z;
start->parent=NULL;
}
y->lc=z->rc;
z->rc=y;
x->rc=z->lc;
z->lc=x;
x->parent=z;
y->parent=z;
}//end RL

//main function
void main()
{
int gd=DETECT,gm;
char choice1[1];
int choice=0,x,y;
long int convert;
initgraph(&gd,&gm,"c:\\tc\\bgi");
cout<<"\n";
//cleardevice();
start=(struct avl *)malloc(sizeof(struct avl));
start->lc=NULL;
start->rc=NULL;
start->parent=NULL;
start=NULL;
cout<<"Enter the choice: \n";
cout<<"1.Insert\n2.Quit \n";
cin>>choice1;
fflush(stdin);
choice=atoi(choice1);
while(choice!=2)
{
switch(choice)
{
case 1:
	cout<<"Enter the element to be inserted(between 0 t0 30000):";
	cin>>element;
	fflush(stdin);
	convert=atold(element);
	if(convert==0)
	  {
	  cout<<"Enter the valid input";
	  cleardevice();
	  goto back;
	  }
	if(!(convert>=0&&convert<=30000))
	{
	printf("Enter the value with in the range \n");
	goto back;
	}
	insert(convert,start);
	cleardevice();
	 outtext("Before Rotation");
	startdisplay();
	cleardevice();
	while(node!=NULL)
	{
	x=heightcalc(node->lc);
	y=heightcalc(node->rc);
	nodemain=node;
	critical=node;
	diff=x-y;
	if(diff==2||diff==-2)
	     {
	     criticaldata=critical->data;
	     cleardevice();
	     startdisplay();
	     criticaldata=0;
	     cleardevice();
	     goto a;
	      }
	node=node->parent;
	}
	a:switch(diff)
	{
	case 2:
	x=heightcalc(nodemain->lc->lc);
	y=heightcalc(nodemain->lc->rc);
	diff=x-y;
	if(diff>0)
	    {
	    outtextxy(100,100,"LL Rotation");
	    getch();
	    cleardevice();
	    LLrotation(critical);
	    cleardevice();
	    }
	    else if(diff<0)
	    {
	    outtextxy(100,100,"LRrotation");
	    getch();
	    cleardevice();
	    LRrotation(critical);
	    cleardevice();
	    }
	   outtext("After Rotation");
	  startdisplay();
	  break;
	case -2:
	x=heightcalc(nodemain->rc->lc);
	y=heightcalc(nodemain->rc->rc);
	diff=x-y;
	if(diff>0)
	    {
	  outtextxy(100,100,"RLrotation");
	    getch();
	    cleardevice();
	    RLrotation(critical);
	    cleardevice();
	    }
	    else if(diff<0)
	    {
	  outtextxy(100,100,"RRrotation");
	    getch();
	    cleardevice();
	    RRrotation(critical);
	    cleardevice();
	    }
	     outtext("After Rotation");
	    startdisplay();
	break;
       }
case 2:
	break;
default:cout<<"Enter the correct value:\n";
	break;
}//end switch
back:cout<<"Enter the choice: \n";
cout<<"1.Insert\n2.Quit \n";
cin>>choice1;
choice=atoi(choice1);
fflush(stdin);
}//end while choice
getch();
cleardevice();
closegraph();
}
