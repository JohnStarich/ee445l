#include <stdint.h>
#include <stdio.h>
#include "ST7735.h"

extern uint32_t Hours_current,Mins_current,Secs_current;

void Graphics_DrawCircle(int x0, int y0, int radius, int color)
{
  int x = radius;
  int y = 0;
  int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

  while( y <= x )
  {
    ST7735_DrawPixel( x + x0,  y + y0, color); // Octant 1
    ST7735_DrawPixel( y + x0,  x + y0, color); // Octant 2
    ST7735_DrawPixel(-x + x0,  y + y0, color); // Octant 4
    ST7735_DrawPixel(-y + x0,  x + y0, color); // Octant 3
    ST7735_DrawPixel(-x + x0, -y + y0, color); // Octant 5
    ST7735_DrawPixel(-y + x0, -x + y0, color); // Octant 6
    ST7735_DrawPixel( x + x0, -y + y0, color); // Octant 7
    ST7735_DrawPixel( y + x0, -x + y0, color); // Octant 8
    y++;
    if (decisionOver2<=0)
    {
      decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
    }
    else
    {
      x--;
      decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
    }
  }
}

int abs(int val){
	if(val < 0){ return ~val + 1;}
	else return val;
}

int sgn(int num){
	if(num < 0) { return -1;}
	else if(num > 0) {return 1;}
	else return 0;
}

void Graphics_DrawLine(int x1, int y1, int x2, int y2, int color){

	int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;

  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
    for(i=0;i<dxabs;i++)
    {
      y+=dyabs;
      if (y>=dxabs)
      {
        y-=dxabs;
        py+=sdy;
      }
      px+=sdx;
      ST7735_DrawPixel(px,py,color);
    }
  }
  else /* the line is more vertical than horizontal */
  {
    for(i=0;i<dyabs;i++)
    {
      x+=dxabs;
      if (x>=dyabs)
      {
        x-=dyabs;
        px+=sdx;
      }
      py+=sdy;
      ST7735_DrawPixel(px,py,color);
    }
  }
}
