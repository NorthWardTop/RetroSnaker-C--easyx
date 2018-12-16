
//-----------------------------------------------------定义蛇
typedef enum ch			//蛇头方向
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
}CH;

typedef struct coor		//坐标
{
	int x;
	int y;
}COOR;

typedef struct snake	//蛇----
{
	COOR scr[843];		//蛇所有节的位置（坐标）
	CH dir;				//蛇头方向
	int len;		//蛇当前长度

}SNAKE;

typedef struct food
{
	COOR fd;		//食物的坐标
	int eat;		//食物是否被吃
}FOOD;

