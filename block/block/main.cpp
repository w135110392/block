#include<graphics.h>

#include<time.h>
#include<conio.h>
#include <stdio.h>
#define screenWidth 550
#define screenHeight 660
#define unit_size  20
#define BLOCK_COUNT 5   //定义5种形状
#define block_width 5   //定义一个5行5列的数组 表示形状的范围
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
}blockdir_t; //当前方块的朝向
typedef enum{
	movedown,
	moveleft,
	moveright,
	

}movedir_t;//移动的方向

int score=0;
int rank=0; 
int nextIndex=-1;   //下一种方块种类
int BlockIndex = -1; //当前方块种类

int color[BLOCK_COUNT] = {
	GREEN, CYAN, MAGENTA, BROWN, YELLOW
};
int visit[30][15];
int markcolor[30][15];//表示对应位置的颜色


//5种形状 5种颜色

int block[BLOCK_COUNT * 4][block_width][block_height] = {
	// |  型方块
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

			// L 形方块
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

			// 田 形方块
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

			// T 形方块
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

			// Z 形方块
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


//启动页面
void welcome(){
	initgraph(screenWidth, screenHeight);
	//设置窗口标题
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "俄罗斯方块");
	//设置标题
	settextstyle(40, 0, "楷体");
	setcolor(WHITE);
	outtextxy(115, 200, "梦回情怀，重温经典！");


	//设置副标题
	settextstyle(22, 0, "楷体");
	setcolor(GREEN);
	outtextxy(220, 300, "编程,梦开始的地方！");
	Sleep(3000);
}
//初始化游戏环境
void initGamescene(){
	char str[16];
	setcolor(WHITE);
	cleardevice();
	rectangle(29,29,334,633);
	rectangle(27, 27, 336, 635);
	rectangle(370, 50, 515, 195);

	//右上角内容
	settextstyle(24,0,"楷体");
	setcolor(LIGHTGRAY);
	outtextxy(405,215,"下一个");
	setcolor(RED);
	outtextxy(405, 280, "分数:");
	sprintf_s(str,"%d",score);
	outtextxy(415, 310, str);
	outtextxy(405, 375, "等级:");
	sprintf_s(str, "%d", rank);
	outtextxy(425, 405, str);
	
	settextstyle(22, 0, "楷体");

	setcolor(LIGHTBLUE);
	outtextxy(390, 475, "操作说明:");
	outtextxy(390, 500, "↑: 旋转");
	outtextxy(390, 525, "↓: 下降");
	outtextxy(390, 550, "←: 左移");
	outtextxy(390, 575, "→: 右移");
	outtextxy(390, 600, "空格: 暂停");
}
//清除方块
void clerblock(void){
	setcolor(BLACK);
	settextstyle(23,0,"楷体");
	for (int i = 0; i <block_height; i++){
		for (int j = 0; j < block_width;j++){
			int x = 391 + j*unit_size;
			int y = 71+i*unit_size;
			outtextxy(x,y,"■");
		
		}
		
	}
}

//右上角画下一个方块
void drawblock(int x,int y){
	setcolor(color[nextIndex]);
	settextstyle(23, 0, "楷体");
	
		for (int i = 0; i < block_height; i++){
			for (int j = 0; j < block_width; j++){
				if (block[nextIndex * 4][i][j] == 1){
					int x2 = x + j*unit_size;
					int y2= y + i*unit_size;
					outtextxy(x2, y2, "■");
				}
			}
		}
}
void drawblock(int x,int y,int blockIndex ,blockdir_t dir){
	setcolor(color[blockIndex]);
	settextstyle(23, 0, "楷体");
	int id = blockIndex * 4 + dir; //表示20种的哪一个
	for (int i = 0; i < block_height; i++){
		for (int j = 0; j < block_width; j++){
			if (block[id][i][j] == 1){
				int x2 = x + j*unit_size;
				int y2 = y + i*unit_size;
				outtextxy(x2, y2, "■");
			}
		}
	}


}
//产生新方块
void nextblock(){
	clerblock(); //不停产生 先清除方块
	//随机选择一种方块
	srand((unsigned)time(NULL));//时间函数返回值 作为随机种子
	nextIndex= rand()%BLOCK_COUNT;//随机选一种方块  序号 下一个要画的方块  取余取余取余.................注意
	drawblock(391,71);
}

//降落方块
/*
	用数组来表示游戏区域  30行15列


*/
//是否可以移动
int moveable(int x0, int y0, movedir_t moveDir, blockdir_t blockdir){
	//计算当前方块的左上角在30*15的游戏区域的位置（行列）
	int x = (y0 - min_y) / unit_size;//行等于 纵坐标 除以每个单元大小  得到第几行
	int y = (x0 - min_x) / unit_size;//列等予 横坐标 除以每个单元的大小  得到第几列
	int id = BlockIndex * 4 + blockdir; //第几种方块的那个朝向  就是 总状态中的第几种状态
	int ret = 1;

	if (movedown==moveDir ){
					for (int i = 0; i < block_height;i++){
						for (int j = 0; j < block_width;j++){
							if (block[id][i][j]==1&&
								(x + i + 1 >= 30 || visit[x + i + 1][y + j] == 1)){                       //表示行超出或者等于30 的时候                                                            
								                                                                //表示在游戏区域内 已经有方块
								                                                                   //不能移动的时候 设一个值
									ret = 0;
							}
						
						}
					}


				}
				
	else if (moveleft==moveDir  ){

					for (int i = 0; i < block_height; i++){
						for (int j = 0; j < block_width; j++){
							if (block[id][i][j] == 1 && 
								(y+j==0|| visit[x + i][y + j - 1] == 1)){        //表示行超出或者等于30 的时候 (y + j == 0 && x +                                                             i>0 && y+j-1>= 0 && y +j-1<15 && 
							                                                        //表示在游戏区域内 已经有方块
								                                                      //不能移动的时候 设一个值
									ret = 0;
							}

						}
					}




				}
	else if (moveright == moveDir){
					for (int i = 0; i < block_height; i++){
						for (int j = 0; j < block_width; j++){
							if (block[id][i][j] == 1 &&
								(y + j + 1 >= 15 || visit[x + i][y + j + 1] == 1)){      //表示行超出或者等于30 的时候 (x+ i >= 0 && x + i<30 && y +                                                                          j + 1 >= 0 && y + j + 1<15&& 
								                                                            //表示在游戏区域内 已经有方块
									ret = 0;                    //不能移动的时候 设一个值
								
							}

						}
					}

	
				}

	return ret;
}
//检测游戏是否结束
void failcheck(){

	if (!moveable(start_x,start_y,movedown,BLOCK_UP)){
		setcolor(WHITE);
		settextstyle(80,0,"楷体");
		outtextxy(75,300,"游戏结束.");
		Sleep(1000);
		system("pause");
		closegraph();
		exit(0);
	}

}
//清除上一次生成的方块
void clearblock(int x, int y, blockdir_t Dir){
	setcolor(BLACK);
	int id = BlockIndex * 4 + Dir;
	y += start_y;
	for (int i = 0; i < 5;i++){
		for (int j = 0; j < 5; j++){
			if (block[id][i][j]==1){
				outtextxy(x+unit_size*j,y+unit_size*i,"■");
			
			}
		}
	}

}

//判断当前方块在指定方向 是否可以改变到指定方向 还没有转到此方向
int rotatable(int x,int y,blockdir_t dir){
	int id = BlockIndex * 4 + dir;
	int xIndex = (y - min_y) / unit_size; //具体的行
	int yIndex = (x - min_x) / unit_size;  //具体的列

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
	blockdir_t blockDir = BLOCK_UP; //当前方块朝向
	int cutspeed = speed;
	//检测游戏是否结束
	failcheck();
	//持续向下降落
	while (1){
	
	    //实现控制
		if (_kbhit()){
			int key = _getch();
					if (key == key_space){
						//暂停
						_getch();
					}
				}
				//清除上一次画的方块
		      clearblock(x,k, blockDir);


				if (_kbhit()){
					int key = _getch();
					if (key_up==key){ //变形
						blockdir_t nextDir = (blockdir_t)((blockDir + 1) % 4);
						if (rotatable(x,y+k,nextDir)){
							blockDir = nextDir;
						
						}
						
					}
					else if (key_down == key){
						//加速度
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
				//绘制当前方块
				drawblock(x, y+k,BlockIndex, blockDir);
				
				wait(cutspeed); //等待速度
	          //方块的固化处理
				if (!moveable(x,y+k,movedown,blockDir)){
				
					mark(x, y + k, BlockIndex, blockDir);
					break;
				}
	
	}

}
//产生新方块
void newblock(){
	BlockIndex = nextIndex;
	//绘制顶部的方块 
	drawblock(start_x, start_y);
	Sleep(100);
	//产生右上角的方块
	nextblock();
	//方块降落
	move();

}

void down(int x){
	for (int i = x; i >0;i--){
		for (int j = 0; j < 15;j++){
		//消除第i行的第j列的方格消除
			if (visit[i-1][j]){
				visit[i][j] =1;
				markcolor[i][j] = markcolor[i - 1][j];
				setcolor(markcolor[i][j]);
				outtextxy(20*j + min_x,  20*i + min_y, "■");

			}
			else{
				visit[i][j] = 0;
				setcolor(BLACK);
				outtextxy( 20*j + min_x, 20 *i+ min_y, "■");
			
			}
		
		}
	}
			setcolor(BLACK);
			for (int j = 0; j < 15;j++){
			visit[0][j] = 0;
			outtextxy( 20*j + min_x,  min_y, "■");
			}
	}
	


void addscore(int clearlines){
	char str[10];
	score += clearlines*10;
	setcolor(RED);
	outtextxy(405, 280, "分数:");
	sprintf_s(str, "%d", score);
	outtextxy(415, 310, str);
}
void updateGrade(){
	char str[3];
	//更新等级的提示 100分一级
	rank = score / 30 ;  //升一级
	outtextxy(405, 375, "等级:");
	sprintf_s(str, "%d", rank);
	outtextxy(425, 405, str);

	//更新速度
	speed = 500-rank*30;
	if (speed<=100){
		speed = 100;
	
	}

}
void  check(void){
	int i, j;
	int clearlines = 0;
	
	for (i = 29; i >= 0;i--){
		// 检查第i行有没有满
		for (j = 0; j < 15 && visit[i][j]; j++){
		}
			//执行到此处时，有两种情况：
			// 1. 第i行没有满，即表示有空位 此时 j<15
			// 2. 第i行已满了，此时 j>=15
			if (j>=15){
				down(i); //消除第i行 并把上面的行下移
				i++;
				clearlines++;
			}
		}
		//更新分数
	addscore(clearlines);
	//更新等级(更新等级提示，更新等级速度)
	updateGrade();

	}
int main(){
	welcome();
	initGamescene();
	nextblock();
	Sleep(500);
	//初始化访问数组
	
	memset(visit, 0, sizeof(visit)); //整个数组数值设为0

	while (1){
		newblock();
		check();  //消除方块
	
	}
	system("pause");
	closegraph();
	return 0;
}