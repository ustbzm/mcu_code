
#include "gui.h"
#include "string.h"

uint8_t gram[4][8];


void gui_main_windows(void){
	
	lcd_show_strings(1,0,(uint8_t*) "ENV1.0");
}

void gui_memset_gram(uint8_t value){
  uint8_t   i = 0 ,j =0;  		
	for(i=0;i<4;i++){
		for(j=0;j<8;j++){
			//gram[i][j]=value;
		}
	}
}

void gui_show_gram(void)   
{  
   uint8_t   i = 0 ,j =0;  
	for(i=0;i<4;i++){
		for(j=0;j<8;j++){
			show_char(i, j,'B');
		}
	}
} 

void clear_gram(void){
	memset(gram,0,sizeof(gram));
}

void ui_drew_point(uint8_t x,uint8_t y,fill_type fill_type){
	uint8_t xaddr_byte=(x >> 8) ;
	uint8_t yaddr_byte=(y >> 8) ;
	
	uint8_t bit_pos;
	
	bit_pos =x-( xaddr_byte << 8);
	
	if(fill_type == FILL_TYPE_DEFUALT)
		gram[xaddr_byte][yaddr_byte] |= (0x80 >> bit_pos);
	
	else if(fill_type == FILL_TYPE_CLEAR)
		gram[xaddr_byte][yaddr_byte] &= ~(0x80 >> bit_pos);
	
	else if(fill_type == FILL_TYPE_INVERSE)
		gram[xaddr_byte][yaddr_byte] ^= (0x80 >> bit_pos);
}

void ui_drew_line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,fill_type fill_type){
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	
	delta_x=x2-x1; //璁＄畻鍧愭爣澧為噺
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //璁剧疆鍗曟鏂瑰悜
	else if(delta_x==0)incx=0;//鍨傜洿绾�
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//姘村钩绾�
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //閫夊彇鍩烘湰澧為噺鍧愭爣杞�
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//鐢荤嚎杈撳嚭
	{  
		ui_drew_point(uRow,uCol,fill_type);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 	
}

void ui_drew_rectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,fill_type fill){
	uint8_t dy;
	if(fill){
		for(dy=y1;dy<=y2;dy++){
			ui_drew_line(x1,dy,x2,dy,FILL_TYPE_DEFUALT);
		}
		
	}else{
		ui_drew_line(x1,y1,x2,y1,FILL_TYPE_DEFUALT);
		ui_drew_line(x1,y1,x1,y2,FILL_TYPE_DEFUALT);
		ui_drew_line(x2,y2,x1,y2,FILL_TYPE_DEFUALT);
		ui_drew_line(x2,y2,x2,y1,FILL_TYPE_DEFUALT);
	}
	
}

