
//-----------------------------------------------------������
typedef enum ch			//��ͷ����
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
}CH;

typedef struct coor		//����
{
	int x;
	int y;
}COOR;

typedef struct snake	//��----
{
	COOR scr[843];		//�����нڵ�λ�ã����꣩
	CH dir;				//��ͷ����
	int len;		//�ߵ�ǰ����

}SNAKE;

typedef struct food
{
	COOR fd;		//ʳ�������
	int eat;		//ʳ���Ƿ񱻳�
}FOOD;

