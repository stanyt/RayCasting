#include<graphics.h>
#include <conio.h>

int main(void) {
	IMAGE _1;

	loadimage(&_1, "./Image/שǽ.jpg");
	int width = _1.getwidth(), height = _1.getheight();

	initgraph(width, height);
	// ��ȡָ����ʾ��������ָ��
	DWORD* pMem = GetImageBuffer();


	// ֱ�Ӷ���ʾ��������ֵ
	for (int i = 0; i < width; i++)
		putpixel(i, i, pMem[i]);

	_getch();
	closegraph();
	return 0;
}