#include<graphics.h>

#include<time.h>
#include<conio.h>
#include <stdio.h>
#define screenWidth 550
#define screenHeight 660
#define unit_size  20
#define BLOCK_COUNT 5   //����5����״
#define block_width 5   //����һ��5��5�е����� ��ʾ��״�ķ�Χ
#define block_height 5
#define start_x 130
#define start_y  30
#define  key_up 72
#define  key_right 77
#define  key_left  75
#define  key_down  80
#define  key_space 32
int  speed = 500;
int min_y = 30;
int min_x = 30;
typedef enum {
	BLOCK_UP,
	BLOCK_RIGHT,
	BLOCK_DOWN,
	BLOCK_LEFT
}blockdir_t; //��ǰ����ĳ���
typedef enum{
	movedown,
	moveleft,
	moveright,
	

}movedir_t;//�ƶ��ķ���

int score=0;
int rank=0; 
int nextIndex=-1;   //��һ�ַ�������
int BlockIndex = -1; //��ǰ��������

int color[BLOCK_COUNT] = {
	GREEN, CYAN, MAGENTA, BROWN, YELLOW
};
int visit[30][15];
int markcolor[30][15];//��ʾ��Ӧλ�õ���ɫ


//5����״ 5����ɫ

int block[BLOCK_COUNT * 4][block_width][block_height] = {
	// |  �ͷ���
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0 },
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 1, 1, 1, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 1, 1, 1, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			// L �η���
			{ 0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 1, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 1, 1, 1, 0,
			0, 1, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 0, 0, 1, 0,
			0, 1, 1, 1, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			// �� �η���
			{ 0, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			// T �η���
			{ 0, 0, 0, 0, 0,
			0, 1, 1, 1, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 0, 0, 1, 0,
			0, 0, 1, 1, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 1, 1, 1, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, 0, 0, 0 },

			// Z �η���
			{ 0, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 1, 1, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 1, 1, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 1, 1, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0 },

			{ 0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 1, 1, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, 0, 0, 0 }
};


//����ҳ��
void welcome(){
	initgraph(screenWidth, screenHeight);
	//���ô��ڱ���
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "����˹����");
	//���ñ���
	settextstyle(40, 0, "����");
	setcolor(WHITE);
	outtextxy(115, 200, "�λ��黳�����¾��䣡");


	//���ø�����
	settextstyle(22, 0, "����");
	setcolor(GREEN);
	outtextxy(220, 300, "���,�ο�ʼ�ĵط���");
	Sleep(3000);
}
//��ʼ����Ϸ����
void initGamescene(){
	char str[16];
	setcolor(WHITE);
	cleardevice();
	rectangle(29,29,334,633);
	rectangle(27, 27, 336, 635);
	rectangle(370, 50, 515, 195);

	//���Ͻ�����
	settextstyle(24,0,"����");
	setcolor(LIGHTGRAY);
	outtextxy(405,215,"��һ��");
	setcolor(RED);
	outtextxy(405, 280, "����:");
	sprintf_s(str,"%d",score);
	outtextxy(415, 310, str);
	outtextxy(405, 375, "�ȼ�:");
	sprintf_s(str, "%d", rank);
	outtextxy(425, 405, str);
	
	settextstyle(22, 0, "����");

	setcolor(LIGHTBLUE);
	outtextxy(390, 475, "����˵��:");
	outtextxy(390, 500, "��: ��ת");
	outtextxy(390, 525, "��: �½�");
	outtextxy(390, 550, "��: ����");
	outtextxy(390, 575, "��: ����");
	outtextxy(390, 600, "�ո�: ��ͣ");
}
//�������
void clerblock(void){
	setcolor(BLACK);
	settextstyle(23,0,"����");
	for (int i = 0; i <block_height; i++){
		for (int j = 0; j < block_width;j++){
			int x = 391 + j*unit_size;
			int y = 71+i*unit_size;
			outtextxy(x,y,"��");
		
		}
		
	}
}

//���Ͻǻ���һ������
void drawblock(int x,int y){
	setcolor(color[nextIndex]);
	settextstyle(23, 0, "����");
	
		for (int i = 0; i < block_height; i++){
			for (int j = 0; j < block_width; j++){
				if (block[nextIndex * 4][i][j] == 1){
					int x2 = x + j*unit_size;
					int y2= y + i*unit_size;
					outtextxy(x2, y2, "��");
				}
			}
		}
}
void drawblock(int x,int y,int blockIndex ,blockdir_t dir){
	setcolor(color[blockIndex]);
	settextstyle(23, 0, "����");
	int id = blockIndex * 4 + dir; //��ʾ20�ֵ���һ��
	for (int i = 0; i < block_height; i++){
		for (int j = 0; j < block_width; j++){
			if (block[id][i][j] == 1){
				int x2 = x + j*unit_size;
				int y2 = y + i*unit_size;
				outtextxy(x2, y2, "��");
			}
		}
	}


}
//�����·���
void nextblock(){
	clerblock(); //��ͣ���� ���������
	//���ѡ��һ�ַ���
	srand((unsigned)time(NULL));//ʱ�亯������ֵ ��Ϊ�������
	nextIndex= rand()%BLOCK_COUNT;//���ѡһ�ַ���  ��� ��һ��Ҫ���ķ���  ȡ��ȡ��ȡ��.................ע��
	drawblock(391,71);
}

//���䷽��
/*
	����������ʾ��Ϸ����  30��15��


*/
//�Ƿ�����ƶ�
int moveable(int x0, int y0, movedir_t moveDir, blockdir_t blockdir){
	//���㵱ǰ��������Ͻ���30*15����Ϸ�����λ�ã����У�
	int x = (y0 - min_y) / unit_size;//�е��� ������ ����ÿ����Ԫ��С  �õ��ڼ���
	int y = (x0 - min_x) / unit_size;//�е��� ������ ����ÿ����Ԫ�Ĵ�С  �õ��ڼ���
	int id = BlockIndex * 4 + blockdir; //�ڼ��ַ�����Ǹ�����  ���� ��״̬�еĵڼ���״̬
	int ret = 1;

	if (movedown==moveDir ){
					for (int i = 0; i < block_height;i++){
						for (int j = 0; j < block_width;j++){
							if (block[id][i][j]==1&&
								(x + i + 1 >= 30 || visit[x + i + 1][y + j] == 1)){                       //��ʾ�г������ߵ���30 ��ʱ��                                                            
								                                                                //��ʾ����Ϸ������ �Ѿ��з���
								                                                                   //�����ƶ���ʱ�� ��һ��ֵ
									ret = 0;
							}
						
						}
					}


				}
				
	else if (moveleft==moveDir  ){

					for (int i = 0; i < block_height; i++){
						for (int j = 0; j < block_width; j++){
							if (block[id][i][j] == 1 && 
								(y+j==0|| visit[x + i][y + j - 1] == 1)){        //��ʾ�г������ߵ���30 ��ʱ�� (y + j == 0 && x +                                                             i>0 && y+j-1>= 0 && y +j-1<15 && 
							                                                        //��ʾ����Ϸ������ �Ѿ��з���
								                                                      //�����ƶ���ʱ�� ��һ��ֵ
									ret = 0;
							}

						}
					}




				}
	else if (moveright == moveDir){
					for (int i = 0; i < block_height; i++){
						for (int j = 0; j < block_width; j++){
							if (block[id][i][j] == 1 &&
								(y + j + 1 >= 15 || visit[x + i][y + j + 1] == 1)){      //��ʾ�г������ߵ���30 ��ʱ�� (x+ i >= 0 && x + i<30 && y +                                                                          j + 1 >= 0 && y + j + 1<15&& 
								                                                            //��ʾ����Ϸ������ �Ѿ��з���
									ret = 0;                    //�����ƶ���ʱ�� ��һ��ֵ
								
							}

						}
					}

	
				}

	return ret;
}
//�����Ϸ�Ƿ����
void failcheck(){

	if (!moveable(start_x,start_y,movedown,BLOCK_UP)){
		setcolor(WHITE);
		settextstyle(80,0,"����");
		outtextxy(75,300,"��Ϸ����.");
		Sleep(1000);
		system("pause");
		closegraph();
		exit(0);
	}

}
//�����һ�����ɵķ���
void clearblock(int x, int y, blockdir_t Dir){
	setcolor(BLACK);
	int id = BlockIndex * 4 + Dir;
	y += start_y;
	for (int i = 0; i < 5;i++){
		for (int j = 0; j < 5; j++){
			if (block[id][i][j]==1){
				outtextxy(x+unit_size*j,y+unit_size*i,"��");
			
			}
		}
	}

}

//�жϵ�ǰ������ָ������ �Ƿ���Ըı䵽ָ������ ��û��ת���˷���
int rotatable(int x,int y,blockdir_t dir){
	int id = BlockIndex * 4 + dir;
	int xIndex = (y - min_y) / unit_size; //�������
	int yIndex = (x - min_x) / unit_size;  //�������

	if (!moveable(x, y, movedown, dir)){
		return 0;
	}
	
	
	for (int i = 0; i < 5;i++){
		for (int j = 0; j < 5; j++){

			if (block[id][i][j] == 1 && 
				(yIndex + j < 0 || yIndex + j>15 || visit[xIndex + i][yIndex + j] == 1)){
				return 0;
			
			}
		}
	}
	return 1;

}
void wait(int interval){
	int count = interval / 10;
	for (int i = 0; i < count; i++){

		Sleep(10);
		if (_kbhit()){
			return;
		}
	}

};
void mark(int x,int y,int blockindex,blockdir_t dir){
	int id = blockindex * 4 + dir;
	int x2 = (y - min_y)/20;
	int y2 = (x - min_x) / 20;
	for (int i = 0; i < 5;i++){
		for (int j = 0; j < 5;j++){
		
			if (block[id][i][j]==1){
			
				visit[x2+i][y2+j] = 1;
				markcolor[x2 + i][y2 + j] = color[blockindex];
			
			}
		}
	}

}
void move(){
	int x = start_x;
	int y = start_y;
	int k = 0;
	blockdir_t blockDir = BLOCK_UP; //��ǰ���鳯��
	int cutspeed = speed;
	//�����Ϸ�Ƿ����
	failcheck();
	//�������½���
	while (1){
	
	    //ʵ�ֿ���
		if (_kbhit()){
			int key = _getch();
					if (key == key_space){
						//��ͣ
						_getch();
					}
				}
				//�����һ�λ��ķ���
		      clearblock(x,k, blockDir);


				if (_kbhit()){
					int key = _getch();
					if (key_up==key){ //����
						blockdir_t nextDir = (blockdir_t)((blockDir + 1) % 4);
						if (rotatable(x,y+k,nextDir)){
							blockDir = nextDir;
						
						}
						
					}
					else if (key_down == key){
						//���ٶ�
						cutspeed = 30;
			
					}
					else if (key==key_left){
						if (moveable(x,y+k+20,moveleft,blockDir)){
							x -= unit_size;
						}
						
			
					}
					else if (key==key_right){
						if (moveable(x, y + k + 20, moveright, blockDir)){
							x += unit_size;
						}
						
			
					}
				}
				 k += 20;
				//���Ƶ�ǰ����
				drawblock(x, y+k,BlockIndex, blockDir);
				
				wait(cutspeed); //�ȴ��ٶ�
	          //����Ĺ̻�����
				if (!moveable(x,y+k,movedown,blockDir)){
				
					mark(x, y + k, BlockIndex, blockDir);
					break;
				}
	
	}

}
//�����·���
void newblock(){
	BlockIndex = nextIndex;
	//���ƶ����ķ��� 
	drawblock(start_x, start_y);
	Sleep(100);
	//�������Ͻǵķ���
	nextblock();
	//���齵��
	move();

}

void down(int x){
	for (int i = x; i >0;i--){
		for (int j = 0; j < 15;j++){
		//������i�еĵ�j�еķ�������
			if (visit[i-1][j]){
				visit[i][j] =1;
				markcolor[i][j] = markcolor[i - 1][j];
				setcolor(markcolor[i][j]);
				outtextxy(20*j + min_x,  20*i + min_y, "��");

			}
			else{
				visit[i][j] = 0;
				setcolor(BLACK);
				outtextxy( 20*j + min_x, 20 *i+ min_y, "��");
			
			}
		
		}
	}
			setcolor(BLACK);
			for (int j = 0; j < 15;j++){
			visit[0][j] = 0;
			outtextxy( 20*j + min_x,  min_y, "��");
			}
	}
	


void addscore(int clearlines){
	char str[10];
	score += clearlines*10;
	setcolor(RED);
	outtextxy(405, 280, "����:");
	sprintf_s(str, "%d", score);
	outtextxy(415, 310, str);
}
void updateGrade(){
	char str[3];
	//���µȼ�����ʾ 100��һ��
	rank = score / 30 ;  //��һ��
	outtextxy(405, 375, "�ȼ�:");
	sprintf_s(str, "%d", rank);
	outtextxy(425, 405, str);

	//�����ٶ�
	speed = 500-rank*30;
	if (speed<=100){
		speed = 100;
	
	}

}
void  check(void){
	int i, j;
	int clearlines = 0;
	
	for (i = 29; i >= 0;i--){
		// ����i����û����
		for (j = 0; j < 15 && visit[i][j]; j++){
		}
			//ִ�е��˴�ʱ�������������
			// 1. ��i��û����������ʾ�п�λ ��ʱ j<15
			// 2. ��i�������ˣ���ʱ j>=15
			if (j>=15){
				down(i); //������i�� ���������������
				i++;
				clearlines++;
			}
		}
		//���·���
	addscore(clearlines);
	//���µȼ�(���µȼ���ʾ�����µȼ��ٶ�)
	updateGrade();

	}
int main(){
	welcome();
	initGamescene();
	nextblock();
	Sleep(500);
	//��ʼ����������
	
	memset(visit, 0, sizeof(visit)); //����������ֵ��Ϊ0

	while (1){
		newblock();
		check();  //��������
	
	}
	system("pause");
	closegraph();
	return 0;
}