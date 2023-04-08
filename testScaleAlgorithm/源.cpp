#include<graphics.h>
#include <conio.h>

int main(void) {
	IMAGE _1;

	loadimage(&_1, "./Image/砖墙.jpg");
	int width = _1.getwidth(), height = _1.getheight();

	initgraph(width, height);
	// 获取指向显示缓冲区的指针
	DWORD* pMem = GetImageBuffer();


	// 直接对显示缓冲区赋值
	for (int i = 0; i < width; i++)
		putpixel(i, i, pMem[i]);

	_getch();
	closegraph();
	return 0;
}