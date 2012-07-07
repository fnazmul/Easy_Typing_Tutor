#include <dos.h>

REGS r,o;
int mouse=0;
int xPos,yPos;

//#define	NO_BTN		0
//#define	LEFT_BTN		1
//#define	RIGHT_BTN	2
//#define	BOTH_BTN    3

int	mousePresent(){
	r.x.ax=0;
	int86(0x33,&r,&r);
	if(r.x.ax){
		mouse=1;
		return	1;
	}
	return	0;
}

int showMouse()
{
	if(mouse){
		r.x.ax=1;
		int86(0x33,&r,&o);
		return	1;
	}
	return	0;
}

int	hideMouse()
{
	if(mouse){
		r.x.ax=2;
		int86(0x33,&r,&r);
		return	1;
	}
	return	0;
}


int	getNumberOfButtons()
{
	if(mousePresent()){
		   r.x.ax=0;
		   int86(0x33,&r,&r);
		   return	r.x.bx;
	}
	return	0;
}


int	getMouseX()
{
	if(mouse){
		r.x.ax=3;
		int86(0x33,&r,&r);
		xPos=r.x.cx;
		yPos=r.x.dx;
		return	r.x.cx;
	}
	return	-1;
}

int	getMouseY()
{
	if(mouse){
		r.x.ax=3;
		int86(0x33,&r,&r);
		xPos=r.x.cx;
		yPos=r.x.dx;
		return	r.x.dx;
	}
	return	-1;
}

int	getMouseButton()
{
	if(mouse){
		r.x.ax=3;
		int86(0x33,&r,&r);
		return	r.x.bx;
	}
	return	0;
}

int	mouseClicked()
{
   if(mouse)
   {
	if(getMouseButton()==1)
		return 1;
	else return 0;
		//return	getMouseButton();
   }
   return	0;
}

int	mouseReleased()
{
   if(mouse){
		return	!getMouseButton();
   }
   return	1;
}


int	setMouseLocation(int x,int y)
{
	if(mouse){
		r.x.ax=4;
		r.x.cx=x;
		r.x.dx=y;
		int86(0x33,&r,&r);
		return	1;
	}
	return	0;
}


int mouseMoved()
{
	if(mouse){
		r.x.ax=3;
		int86(0x33,&r,&r);
		if(xPos!=r.x.cx || yPos!=r.x.dx)
			return	1;
		return 0;
	}
	return	0;
}
int restrictMouse(int x1,int y1,int x2,int y2)
{

	r.x.ax=7;
	r.x.cx=x1;
	r.x.dx=x2;
	int86(0x33,&r,&o);

	r.x.ax=8;
	r.x.cx=y1;
	r.x.dx=y2;
	int86(0x33,&r,&o);
}