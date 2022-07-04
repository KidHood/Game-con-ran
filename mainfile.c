#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
enum state{MENU = 0, INGAME, SETTING, GAMEOVER,INFOR} state;

int snake[10000];
int fruit = 12025; 
int length;
int vx=0,vy=-1;
int ct = 0;
int score=0;
int speed=50;
clock_t t;
int s_e;

void initgame(){
	s_e=120-speed;
	length=4;
	snake[0]=12015;
	snake[1]=12016;
	snake[2]=12017;
	snake[3]=12018;
	snake[4]=12019;
}

int getx(int a){
	return (a-10000)/100;
}

int gety(int a){
	return a%100;
}

void gotoxy(int x,int y){    
	static HANDLE  h = NULL;
	if(!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = {x,y};
	SetConsoleCursorPosition(h,c);
}

void textcolor(int color)
{
 	WORD wColor;
     

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void printScore(){
	int n=0;
	int tg = score;
	int a[5];
	for(n;n<5;n++){
		a[n] = tg%10;
		tg/=10;
	}
	textcolor(14);
	gotoxy(137,20);
	printf("%d",a[0]);
	gotoxy(137,19);
	printf("%d",a[1]);
	gotoxy(137,18);
	printf("%d",a[2]);
	gotoxy(137,17);
	printf("%d",a[3]);
	gotoxy(137,16);
	printf("%d",a[4]);
}
void printfBox(){
	textcolor(3);
	resizeConsole(1250,780);
	int i=0;
	for(i;i<137;i++)
		printf("#");
	int j=0;
	
	for(j;j<34;j++){
		i=0;
		printf("\n");
		for(i;i<137;i++){
			printf((i==0||i==136)?"#":" ");
		}
	}
	i = 0;
	printf("\n");
	for(i;i<137;i++)
		printf("#");
	textcolor(14);
	gotoxy(137,5);
	printf("S");
	gotoxy(137,6);
	printf("c");
	gotoxy(137,7);
	printf("o");
	gotoxy(137,8);
	printf("r");
	gotoxy(137,9);
	printf("e");
	
	gotoxy(137,20);
	printf("%d",0);
	gotoxy(137,19);
	printf("%d",0);
	gotoxy(137,18);
	printf("%d",0);
	gotoxy(137,17);
	printf("%d",0);
	gotoxy(137,16);
	printf("%d",0);
}

void gameover (){
	system("cls");
	textcolor(1);
	gotoxy(55,9);
	printf("Gameover");
	gotoxy(50,11);
	textcolor(11);
	printf("Choi gi ma duoc co %d diem kem coi the",score);
	textcolor(11);
	gotoxy(55,13);
	printf("Bam enter de ve menu");
	getchar();
	state = MENU;
}

int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void reCreatFruit(){
	int bl=1,i;
	while(bl){
	bl=0;
	fruit = 10000 + GetRandom(1,135)*100;
	fruit += GetRandom(1,32);
	for(i=0;i<length;i++){
		if(fruit==snake[i])
			bl=0;
	}
	
}
}

void menu (){
	resizeConsole(1000,500);
	textcolor(4);
	system("cls");
	gotoxy(50,3);
	printf("Game ran cua Van Thong");
	gotoxy(55,5);
	textcolor(9);
	printf("1.Vao game");
	gotoxy(55,6);
	printf("2.Tuy chinh");
	gotoxy(55,7);
	printf("3.Thong tin");
	int choice  = 1;
	int oldChoice = 1;
	int next;
	int key;
	textcolor(14);
	gotoxy(54,5);
	printf("%c",16);
	getch();
	while(state ==MENU){
		if(kbhit()){
			key = getch();
			if(key==80)
				choice++;
				if(choice==4) choice =1;
			if(key==72)
				choice--;
				if(choice==0) choice =3;
			switch (choice){
				case 1 :
				if(oldChoice!=choice){
				
				gotoxy(54,6);
				printf(" ");
				gotoxy(54,7);
				printf(" ");
				oldChoice = 1;
				
				gotoxy(54,5);
				textcolor(14);
				printf("%c",16);
				}
				break;
			case 2 :
				if(oldChoice!=choice){
			
				gotoxy(54,5);
				printf(" ");
				gotoxy(54,7);
				printf(" ");
		        gotoxy(54,6);
		       	textcolor(14);
				printf("%c",16);
				oldChoice = 2;
				}
				break;
			case 3 :
				if(oldChoice!=choice){
				
				
				gotoxy(54,6);
				printf(" ");
				gotoxy(54,5);
				printf(" ");
				gotoxy(54,7);
				textcolor(14);
				printf("%c",16);
				
				oldChoice = 3;
				}
				break;
			}
		if(key==13){
			switch(choice){
				case 1:
					state = INGAME;
					break;
				case 2:
					state = SETTING;
					break;
				case 3:
					state = INFOR;
					break;
			}
		}	
		}
	}
}

void setting(){
	system("cls");
	gotoxy(0,9);
	printf("An phim next or back de tang giam toc do");
	gotoxy(50,9);
	printf("Toc do hien tai la %d", speed);
	int key;
	while(state==SETTING){
		if(kbhit()){
			key = getch();
			switch(key){
				// nut trai 
				case 75:
					if(speed>1)
						speed--;
						gotoxy(50,9);
						printf("Toc do hien tai la %d",speed);
						break;
				case 77:
					if(speed<100)
						speed++;
						gotoxy(50,9);
						printf("Toc do hien tai la %d",speed);
					break;
				case 13:
					state=MENU;
					break;
			}
		}
	}
}

void information(){
	system("cls");
	gotoxy(45,9);
	printf("Game cua Thong di an cap tren mang ve code theo");
	gotoxy(45,11);
	printf("Moi thong tin chi tiet vui long tu tim hieu tren mang");
	gotoxy(55,13);
	printf("Bam enter de ve Menu");
	getchar();
	state=MENU;
}

void ingame (){
	system("cls");
	int key;
	initgame();
	printfBox();
	int j=1;	
	textcolor(14);
	gotoxy(getx(snake[0]),gety(snake[0]));
		printf("#");
		textcolor(2);
	for(j;j<length-1;j++){
		gotoxy(getx(snake[j]),gety(snake[j]));
		printf("o");
	}
	while(state==INGAME){
		if(kbhit()){
			key = getch();
			switch(key){
				// nut len
				case 72:
					if(vx!=0){
						vx=0;
						vy=-1;
				}
					break;
				//nut xuong
				case 80:
					if(vx!=0){
						vx=0;
						vy=1;
					}
					break;
				//nut trai
				case 75:
					if(vy!=0){
						vx=-1;
						vy=0;
					}
					break;
				//nut phai
				case 77:
					if(vy!=0){
						vx=1;
						vy=0;
					}
					break;
			}
		}
		if((clock()-t)>=s_e){
			if(snake[length-1]!=0){	
			gotoxy(getx(snake[length-1]),gety(snake[length-1]));
			printf(" ");
			}
			int i =length-1;
			for (i;i>0;i--){
				snake[i]=snake[i-1]; 
			}
			textcolor(2);
			gotoxy(getx(snake[0]),gety(snake[0]));
			printf("o");	
			snake[0] += vy;
			snake[0] += vx*100;
			if(snake[0]==fruit){	
				length+=1;
				score += (speed/10+5);
				printScore();
				textcolor(13);
				gotoxy(getx(fruit),gety(fruit));
				printf("o");
				reCreatFruit();	
			}
			if(gety(snake[0])==0) 
				snake[0] +=34;
			if(gety(snake[0])==35) 
				snake[0]-=34;
			if(getx(snake[0])==0) 
				snake[0] +=13400;
			if(getx(snake[0])==136) 
				snake[0] -=13500;
			textcolor(13);
			gotoxy(getx(fruit),gety(fruit));
			printf("0");
				textcolor(9);
			gotoxy(getx(snake[0]),gety(snake[0]));
			printf("#");
		
			for(i=1;i<length;i++){
				if(snake[0]==snake[i])
				state=GAMEOVER;
			}
				t = clock();
		}
	}

}
int main(){
	state = MENU;
	menu();
	while(1){
		switch(state) {
			case MENU:
				menu();
				break;
			case SETTING:
				setting();
				break;
			case INGAME:
				ingame();
				break;
			case GAMEOVER:
				gameover();
				break;
			case INFOR:
				information();
				break;
		}
	}
	return 0;
	}
