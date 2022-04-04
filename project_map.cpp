#include<iostream>
#include<graphics.h>
#include<windows.h>
#include<cmath> 
#include<string>
#include<cstring>
#include<conio.h>
#include<stdlib.h>
using namespace std;
#define filex1 0
#define filey1 0
#define filex2 47
#define filey2 25
#define algox1 47
#define algoy1 0
#define algox2 92
#define algoy2 25
#define fileMenux1 0
#define fileMenux2 100
#define newy1 20
#define newy2 54
#define openy1 55
#define openy2 83
#define savey1 83
#define savey2 108
#define algoMenux1 47
#define algoMenux2 150
#define DFSy1 30
#define DFSy2 54
#define BFSy1 55
#define BFSy2 79
#define TPLTy1 80
#define TPLTy2 104
#define timDuongy1 105
#define timDuongy2 133
#define dinhTruy1 134
#define dinhTruy2 162
#define dinhThaty1 163
#define dinhThaty2 187
#define canhCauy1 188
#define canhCauy2 212
#define hamiltony1 213
#define hamiltony2 237
#define eulery1 238
#define eulery2 262
#define topoSorty1 263
#define topoSorty2 287
#define FOR(i,a,b) for(int i=a;i<=b;i++)
struct Node{
	int x,y;
	char name[2];
};
struct DoThi{
	Node *node;
	int stt_Node;
	int **MT;	
	void delete_Data(){
		delete [] node;
		FOR(i,0,stt_Node) delete[] MT[i];
		delete[] MT;
	}
	void init_node(int mode, int del_index){
		if(mode==1){	//tang node
			Node *node2=new Node[stt_Node+1];
			for(int i=0;i<=stt_Node-1;++i){
				node2[i]=node[i];
			}
			delete []node;
			node=node2;
		}
		if(mode==-1){
			Node *node2=new Node[stt_node+1];
			for(int i=0;i<=del_index-1;++i){
				node2[i]=node[i];
			}
			for(int i=del_index;i<=stt_node;++i){
				node2[i]=node[i+1];
			}
			delete []node;
			node=node2;
		}
	}
	void reset_MT(int **MT1){
		FOR(i,0,stt_Node)
			FOR(j,0,stt_Node) 			
				MT1[i][j]=0;
	}
	void init_MT(int t,int ind){
		if(t==1){//TANG MT LEN 1
			int **MT2=new int *[stt_Node+1];
			FOR(i,0,stt_Node) MT2[i]=new int[stt_Node+1];
			reset_MT(MT2);
			FOR(i,0,stt_Node-1)
				FOR(j,0,stt_Node-1) 
					MT2[i][j]=MT[i][j];
				
			FOR(i,0,stt_Node-1) delete[] MT[i];
			delete[] MT;
			MT=MT2;
		}
		if(t==-1){//GIAM MT DI 1
			int **MT2=new int *[stt_Node+1];
			FOR(i,0,stt_Node) MT2[i]=new int[stt_Node+1];
			
			FOR(j,0,stt_Node+1) {
					MT[ind][j]=0;
					MT[j][ind]=0;
			}
			FOR(l1,0,stt_Node+1) FOR(l2,0,stt_Node+1) if(MT[l1][l2]!=0){
				int t1,t2;
				t1=(l1>ind?l1-1:l1);
				t2=(l2>ind?l2-1:l2);
				if(l1>ind||l2>ind){
					MT[t1][t2]=MT[l1][l2];
					MT[l1][l2]=0;
				}
			}
			
			reset_MT(MT2);
			FOR(i,0,stt_Node)
				FOR(j,0,stt_Node) 
					MT2[i][j]=MT[i][j];
			FOR(i,0,stt_Node+1) delete[] MT[i];
			delete[] MT;
			MT=MT2;
		}
		if(t==0){//KHOI TAO LAI MT KHI OPEN FILE
			FOR(i,0,ind) delete[] MT[i];
			delete[] MT;
			int **MT2=new int *[stt_Node+1];
			FOR(i,0,stt_Node) MT2[i]=new int[stt_Node+1];
			reset_MT(MT2);
			MT=MT2;
		}
	}
	~DoThi(){
		delete [] node;
		FOR(i,0,stt_Node) delete[] MT[i];
		delete[] MT;
	}
	
} dt;
void clearMainScreen(){
	bar(201,26,9999,550);
}
void createInfoScreen(){
	line(0,550,9999,550);
}
void createMatrix(){
	line (300,25,300,550);
}
void updateCusor(int length, char s[]){
	for(;length<10;length++) s[length]='\0';
}
string cusor(int x,int y,int maxLength){
	char a[maxLength+10]={};
	int length=-1;
	char temp='\0';
	while(kbhit()){
		char b= getch();
	}
	while(1){
		if(GetAsyncKeyState(0x01)){
			continue;
		}
		temp=getch();
		if(int (temp)==13)
			break;
		if(int(temp)==8){
			updateCusor(length,a);
			if(length==0){
				bar(x-1,y+4,x+12,y+20);
			}
			else if(length==1){
				bar(x-5,y+4,x+16,y+20);
				outtextxy(x,y,a);
			}
			length--;
			if (length<0){
				length =-1;
			}
			continue;
		}
		if(int (temp)>57||int (temp)<48||(int (temp)==48&&length==-1)){
			continue;
		}
		if (length==maxLength){
			a[length]=temp;
			outtextxy(x-5,y,a);
			continue;
		}
		if(length==-1){
			length++;
			a[length]=temp;
			outtextxy(x,y,a);
		}
		else {
			length++;
			a[length]=temp;
			outtextxy(x-5,y,a);
		}
}
	string temp1;
	for(int i=0;i<=maxLength;i++){
		temp1+=a[i];
	}
	cin.clear();
	outtextxy(100,100,a);
	return temp1;
}
class button{
		public:
		int x1,y1,x2,y2,textpos;
		char *name;
		button(int X1,int Y1,int X2,int Y2,int textPos,char* Name){
			x1=X1;
			y1=Y1;
			x2=X2;
			y2=Y2;
			textpos=textPos;
			name=Name;
		}
		create(){
		setfillstyle(1,WHITE);
		bar(x1+2,y1-2,x2-1,y2);
		outtextxy(textpos,y1-1,name);
		}
		highlight(){
		setfillstyle(1,LIGHTBLUE);
		bar(x1+2,y1-2,x2-1,y2);
		setbkcolor(LIGHTBLUE);
		setcolor(BLACK);
		outtextxy(textpos,y1-1,name);
		setbkcolor(WHITE);
		}
		deleteButton(){
		setfillstyle(1,WHITE);
		bar(x1+2,y1+1,x2-1,y2);
		}
		hover(){
		if (mousex() > x1 && mousex() < x2 && mousey() > y1 && mousey() < y2){
            return 1;
        }
        else{
            return 0;
        }
		}
};
void create(Node *&temp){
	POINT p;
	GetCursorPos(&p);
  	for(int i=20;i<=22;i++) circle(p.x-6, p.y-30, i);
  	temp->x=p.x-6;
  	temp->y=p.y-30;
  	string str=cusor(p.x-12,p.y-41,1);
	for(int i=0;i<=str.length();i++){
		temp->name[i]=str[i];
	}
}
bool hover(Node *temp){
   	if (sqrt(pow((mousex()-temp->x),2)+pow((mousey()-temp->y),2))<=20)
   		return true;
	else
	   	return false;
}	
void recreate(Node *temp){
	for(int i=20;i<=22;i++) circle(temp->x,temp->y, i);
	setcolor(15);
	for(int i=0;i<=20;i++) circle(temp->x,temp->y, i);
	setcolor(BLACK);
	if(temp->name[1]==NULL)
		outtextxy(temp->x-6,temp->y-11,temp->name);
	else
		outtextxy(temp->x-11,temp->y-11,temp->name);
}
void highlight(Node *temp){
	setcolor(3);
	for(int i=0;i<=19;i++)
		 circle(temp->x,temp->y, i);
	setcolor(9);
	for(int i=19;i<=20;i++)
		 circle(temp->x,temp->y, i);
	setcolor(0);
	for(int i=20;i<=22;i++)
		 circle(temp->x,temp->y, i);
	setbkcolor(3);
	if(temp->name[1]==NULL)
		outtextxy(temp->x-6,temp->y-11,temp->name);
	else
		outtextxy(temp->x-11,temp->y-11,temp->name);
	setbkcolor(15);
}
class link{
	public:
	Node *temp1, *temp2;
	int x1,y1,Ax,Bx,Ay,By,trongSo;
    void createLink(Node *temp1, Node *temp2){
		double deltax=(temp1->x>temp2->x)?1:-1;
		double deltay=(temp1->y>temp2->y)?1:-1;
		double degree=atan((abs(temp1->y-temp2->y)*1.0)/(abs(temp1->x-temp2->x)*1.0));
		x1=temp2->x+deltax*(cos(degree) *20.0);
		y1=temp2->y+deltay*(sin(degree) *20.0);
		line(temp1->x,temp1->y,x1,y1);
		recreate(temp1);
		int tdABx=x1+deltax*(cos(degree) *20.0);
		int tdABy=y1+deltay*(sin(degree) *20.0);
		Ax=tdABx-deltax*cos(90-degree)*10.0;
		Ay=tdABy+deltay*sin(90-degree)*10.0;
		Bx=tdABx+deltax*cos(90-degree)*10.0;
		By=tdABy-deltay*sin(90-degree)*10.0;
		int arr[8]={x1,y1,Ax,Ay,Bx,By,x1,y1};
		setfillstyle(1,0);
		fillpoly(4,arr);
		setfillstyle(1,15);
		//tao trong so
		int intx=(temp1->x+x1)/2;
		int inty=(temp1->y+y1)/2;
		trongSo=atoi(&cusor(intx,inty,2)[0]);
	}
	void highLightLink(){
		
	}
};

void createFile(){
	setfillstyle(1,WHITE);
	bar(0,0,47,25);
	setbkcolor(WHITE);
	setcolor(BLACK);
	settextstyle(3,0,2);
	outtextxy(7,1,"File");
	setcolor(LIGHTGRAY);
	line(0,25,2000,25);
	setcolor(0);
}
void fileHighlight(){
	setfillstyle(1,LIGHTCYAN);
	bar(0,0,46,25);
	setcolor(LIGHTBLUE);
	rectangle(0,0,46,25);
	setcolor(BLACK);
	setbkcolor(LIGHTCYAN);
	settextstyle(3,0,2);
	outtextxy(7,1,"File");
	setcolor(BLUE);
	line(0,25,46,25);
	setcolor(BLACK);
	setbkcolor(WHITE);
}
void createFileMenu(button a[3]){
	setcolor(BLACK);
	rectangle(-1,26,101,111);
	setcolor(LIGHTGRAY);
	rectangle(0,26,100,110);
	rectangle(0,26,102,112);
	setcolor(BLACK);
	for (int i =0;i<3;i++){
		a[i].create();
	}
}
void deleteFileMenu(){
	setfillstyle(1,WHITE);
	bar(0,26,103,114);
}
void createAlgo(){
	setfillstyle(1,15);
	bar(47,0,93,25);
	setcolor(LIGHTGRAY);
	line(47,25,2000,25);
	setcolor(BLACK);
	setbkcolor(WHITE);
	settextstyle(3,0,1);
	outtextxy(50,1,"Algo");
}
void algoHighlight(){
	setfillstyle(1,LIGHTCYAN);
	bar(46,0,92,25);
	setcolor(LIGHTBLUE);
	rectangle(46,0,92,25);
	setcolor(BLACK);
	setbkcolor(LIGHTCYAN);
	settextstyle(3,0,1);
	outtextxy(50,1,"Algo");
	setcolor(BLUE);
	line(46,25,92,25);
	setcolor(BLACK);
	setbkcolor(WHITE);
}
void createAlgoMenu(button a[10]){
	setcolor(BLACK);
	rectangle(46,25,151,289);
	setcolor(LIGHTGRAY);
	rectangle(46,25,150,288);
	rectangle(46,25,152,290);
	setcolor(BLACK);
	line(46,26,46,290);
	for (int i =0;i<10;i++){
		a[i].create();
	}
}
void deleteAlgoMenu(){
	setfillstyle(1,WHITE);
	bar(45,26,153,291);
}
bool Hover(int x1,int y1, int x2,int y2){
    if (mousex() > x1 && mousex() < x2 && mousey() > y1 && mousey() < y2)
        return 1;
	else
        return 0;
}
void menuInteraction(button file[3],button algo[10],bool &fileHovered,bool &algoHovered){
	while(1){
		if(Hover(filex1,filey1,filex2,filey2)||fileHovered==1){
		fileHighlight();
		createFileMenu(file);
		fileHovered=1;
		for(int i=0;i<3;i++){
			if(file[i].hover()){
			file[i].highlight();
		}
		}
	}
	else{
		createFile();
	}
	if(!Hover(filex1,filey1,filex2,filey2)&&!Hover(fileMenux1,newy1,fileMenux2,savey2+2)&&fileHovered==1){
		deleteFileMenu();
		fileHovered=0;
	}
	if(Hover(algox1,algoy1,algox2,algoy2)||algoHovered==1){
		algoHighlight();
		createAlgoMenu(algo);
		algoHovered=1;
		for(int i=0;i<10;i++){
			if(algo[i].hover()){
				algo[i].highlight();
				if(GetAsyncKeyState(0x01)){
					outtextxy(400,100,algo[i].name);	//Bat nhap chuot
					while(GetAsyncKeyState(0x01)){
					}
				}
			}
		}
	}
	else{
		createAlgo();
	}
	if(!Hover(algox1,algoy1,algox2,algoy2)&&!Hover(algoMenux1,DFSy1-10,algoMenux2,topoSorty2+2)&&algoHovered==1){
		deleteAlgoMenu();
		algoHovered=0;
	}
	if(algoHovered==0&&fileHovered==0){
		createFile();
		createAlgo();
		break;
	}
	delay(100);
}
}
int main(){
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_HIDE );
    initwindow(1000,700,"");
	floodfill(2,2,15);
    Node *arr[15]={};
    int arrPointer=0;	//dem so luong Node ton tai
    bool fileHovered=0, algoHovered=0;
	int chosenNode=-1;
    button file[3]={
	button(fileMenux1,30,fileMenux2,newy2,7,"New"),
	button(fileMenux1,openy1,fileMenux2,openy2,7,"Open"),
	button(fileMenux1,savey1,fileMenux2,savey2,7,"Save")
	};
	button algo[10]={
		button(algoMenux1,DFSy1,algoMenux2,DFSy2,50,"DFS"),
		button(algoMenux1,BFSy1,algoMenux2,BFSy2,50,"BFS"),
		button(algoMenux1,TPLTy1,algoMenux2,TPLTy2,50,"TPLT"),
		button(algoMenux1,timDuongy1,algoMenux2,timDuongy2,50,"Tim duong"),
		button(algoMenux1,dinhTruy1,algoMenux2,dinhTruy2,50,"Dinh tru"),
		button(algoMenux1,dinhThaty1,algoMenux2,dinhThaty2,50,"Dinh that"),
		button(algoMenux1,canhCauy1,algoMenux2,canhCauy2,50,"Canh cau"),
		button(algoMenux1,hamiltony1,algoMenux2,hamiltony2,50,"Hamilton"),
		button(algoMenux1,eulery1,algoMenux2,eulery2,50,"Euler"),
		button(algoMenux1,topoSorty1,algoMenux2,topoSorty2,50,"Topo Sort"),
	};
	createFile();
	createAlgo();
	createInfoScreen();
	createMatrix();
	while(1){
	if(mousey()<26||fileHovered||algoHovered){		//Lam viec voi menu
		menuInteraction(file,algo,fileHovered,algoHovered);
	}
	if(mousey()>46&&mousey()<570&&mousex()>220){	//Lam viec voi Node
		bool check=0;
		for(int i=0;i<arrPointer;i++){		// check Node hover
			if(hover(arr[i])){
				check=1;
				highlight(arr[i]);		//highlight Node
				if(GetAsyncKeyState(0x01)){		//neu Node duoc chon
					if(chosenNode!=-1&&chosenNode!=i){
						link temp;
						temp.createLink(arr[chosenNode],arr[i]);
						chosenNode=-1;
					}
					else if(chosenNode==-1){
					highlight(arr[i]);
					chosenNode=i;
				}	
				while(GetAsyncKeyState(0x01));
				}
				if(GetAsyncKeyState(0x0002)){		//neu Node duoc huy chon
					recreate(arr[i]);
					chosenNode=-1;
				}
				while(GetAsyncKeyState(0x0002));
			}
		}	
		if(GetAsyncKeyState(0x01)&&check==0&&chosenNode==-1){		//tao Node khi khong co nut dang hover
			Node *Node1=new Node;
			create(Node1);
			arr[arrPointer++]=Node1;	//them vao danh sach tat ca Node
		}
		if(check==0){	//kiem tra co Node nao dang duoc hover khong
			for(int j=0; j<arrPointer; j++){
				if(j==chosenNode) continue;
					recreate(arr[j]);
				}	
		}
		else check =0;
	}
		if(GetAsyncKeyState(0x01)){	//luoc bo nhap chuot trong hang cho
		continue;
	}
	delay(100);
}
    closegraph();
}

