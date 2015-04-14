#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"
#include "menu.h"
#include "LCD_TFT.h"

// ����ѡ��
U8   func_ptr,func1_ptr;   // ����ָ��,�ӹ���ָ��
U8   disp_ptr;             // ��һ��ʾ��ָ��
U8   sel_ptr;              // ��ǰѡ����ָ��
U16  para_val,edit_val;
U8   Menu_times_count;     // �˵�����������
extern U16  column;			   // �ļ�����

U8 state_ptr,bit_ptr;
U8 bitedit;
U8 menu_ptr; //�˵�ָ��
U8 para_ptr; //����ָ��
U8 board_input = 0;
U8 num = 1;
U8 last_disp_ptr = 0;
U8 last_sel_ptr;
ULONG time;
char const menu[][20] = {
    "     ��Ϸѡ��     ",};

char  menu0[256][20] = {
0,
};



extern int joy;



void display_menu(void)
{
    U16  i,j,dot;
    U16  cur_disp;
    char  buff[22];
    char  *p;
	char namebuf[20];
	char buf1[20] = {"�궷��.nes"};
	char buf2[20] = {"��������.NES"};
	char buf3[20] = {"��Ӱսʿ.nes"};
	char buf4[20] = {"����.nes"};
	char buf5[20] = {"���ݹ�.nes"};
	char buf6[20] = {"�����߹�.nes"};
	char buf7[20] = {"����֮��.nes"};
	char buf8[20] = {"�Զ�.nes"};
	char buf9[20] = {"������.nes"};
	char buf10[20] = {"����˹����.nes"};
	char buf11[20] = {"��·����.nes"};
	char buf12[20] = {"����.nes"};
	char buf13[20] = {"�����.nes"};
	char buf14[20] = {"����������2.nes"};
	char buf15[20] = {"����è.nes"};
	char buf16[20] = {"�����.nes"};
	char buf17[20] = {"��ɫ����.nes"};
	char buf18[20] = {"��Ϸ��.nes"};
	char buf19[20] = {"ð�յ�.nes"};
	char buf20[20] = {"�Ͼ����.nes"};
	char buf21[20] = {"����ս��.nes"};
	char buf22[20] = {"��ֻС��.nes"};
	char buf23[20] = {"ɳ������.NES"};
	char buf24[20] = {"δ��սʿ.nes"};
	char buf25[20] = {"С������.nes"};
	char buf26[20] = {"ԽҰ����.nes"};
//	char buf4[20] = {"δ��սʿ.nes"};
	
    if (menu_ptr == 0)  // ��һ��˵� ----- �ļ�ѡ��
    {

		memset(namebuf,0,20);
    	strncpy(namebuf,menu0[sel_ptr],20);
		for(i=0;i<20;i++)
    	{
        	if(namebuf[i] == ' ')
       	 	{
          	  namebuf[i] = 0;
        	}
    	}
		
		if(strcmp(namebuf,buf1) == 0)
		Paint_Bmp(270,0,210,272,hundouluo);
		else if(strcmp(namebuf,buf2) == 0)
		Paint_Bmp(270,0,210,272,mali);
		else if(strcmp(namebuf,buf3) == 0)
		Paint_Bmp(270,0,210,272,chiyingzhanshi);
		else if(strcmp(namebuf,buf4) == 0)
		Paint_Bmp(270,0,210,272,bingfeng);
		else if(strcmp(namebuf,buf5) == 0)
		Paint_Bmp(270,0,210,272,chaiwugong);
		else if(strcmp(namebuf,buf6) == 0)
		Paint_Bmp(270,0,210,272,chenglongtiguan);
		else if(strcmp(namebuf,buf7) == 0)
		Paint_Bmp(270,0,210,272,chenglongzhi);
		else if(strcmp(namebuf,buf8) == 0)
		Paint_Bmp(270,0,210,272,chidou);
		else if(strcmp(namebuf,buf9) == 0)
		Paint_Bmp(270,0,210,272,chongqigou);
	/*	else if(strcmp(namebuf,buf10) == 0)
		Paint_Bmp(270,0,210,272,eluosi);   */
		else if(strcmp(namebuf,buf11) == 0)
		Paint_Bmp(270,0,210,272,gonglusaiche);
		else if(strcmp(namebuf,buf12) == 0)
		Paint_Bmp(270,0,210,272,gongfu);
		else if(strcmp(namebuf,buf13) == 0)
		Paint_Bmp(270,0,210,272,huojianche);
		else if(strcmp(namebuf,buf14) == 0)
		Paint_Bmp(270,0,210,272,kelami);
		else if(strcmp(namebuf,buf15) == 0)
		Paint_Bmp(270,0,210,272,kuailemao);
		else if(strcmp(namebuf,buf16) == 0)
		Paint_Bmp(270,0,210,272,luokeren);
		else if(strcmp(namebuf,buf17) == 0)
		Paint_Bmp(270,0,210,272,lvsebing);
		else if(strcmp(namebuf,buf18) == 0)
		Paint_Bmp(270,0,210,272,maxituan);
		else if(strcmp(namebuf,buf19) == 0)
		Paint_Bmp(270,0,210,272,maoxiandao);
		else if(strcmp(namebuf,buf20) == 0)
		Paint_Bmp(270,0,210,272,qie);
		else if(strcmp(namebuf,buf21) == 0)
		Paint_Bmp(270,0,210,272,zhonghuadaxian);
		else if(strcmp(namebuf,buf22) == 0)
		Paint_Bmp(270,0,210,272,threepig);
		else if(strcmp(namebuf,buf23) == 0)
		Paint_Bmp(270,0,210,272,shamantuo);
		else if(strcmp(namebuf,buf24) == 0)
		Paint_Bmp(270,0,210,272,weilaizhanshi);
		else if(strcmp(namebuf,buf25) == 0)
		Paint_Bmp(270,0,210,272,xiaomeiren);
	/*	else if(strcmp(namebuf,buf26) == 0)
		Paint_Bmp(270,0,210,272,yueye);	  */
		 
		else 
		Lcd_Clear(270,0,210,272,0);

		time ++;
        set_cursor(0xff,0xff);       // ��겻��ʾ
        p = (char *)menu[0];
        Lcd_printf(0,0,p,Red,Black);
		Lcd_printf(0,16,"====================",Red,Black);
        j = 32;
		if ( last_sel_ptr != sel_ptr)
		//Uart_Printf("last_disp_ptr %d  disp_ptr %d  ", last_disp_ptr, disp_ptr);
		Lcd_Clear(0,32,16,272,0);
		last_sel_ptr = sel_ptr;

		if ( last_disp_ptr != disp_ptr)
		//Uart_Printf("last_disp_ptr %d  disp_ptr %d  ", last_disp_ptr, disp_ptr);
		Lcd_Clear(0,0,160,272,0);
		last_disp_ptr = disp_ptr;
       	cur_disp = disp_ptr;
//		if(time == 10)
//		{
//	   	Lcd_Clear(0,0,160,272,0);
//		time = 0;
//		}
        p = (char *)menu0[0];
	//	Uart_Printf(" %d ", disp_ptr);
	//	Uart_Printf("sel_ptr: %d \n", sel_ptr);
        for (i = 0; i < 14; i++)
        {
			memset(buff,' ',21);
            buff[22] = 0;
            strncpy((char*)(buff+2), (char *)(p + cur_disp * 20),19);
            if (cur_disp == sel_ptr)      // ��ǰ��ѡ��Ĺ������ü�ͷָʾ
            {
                buff[0] = '=';
                buff[1] = '>';
            }
			else
            {
                buff[0] = ' ';
                buff[1] = ' ';
            }
		//	Uart_Printf("%s \n", buff);
            Lcd_printf(0,j,buff,Red,Black);
            cur_disp++;
            j = j + 16;
        }
    }
}



void process_key(U8 keycode)
{
    U16 const bit_val[] = {1,10,100,1000,10000};
	U8 last_keycode;
	

    if (keycode == 0) 
        return;
	
	    switch(menu_ptr)
	    {
	        case 0:  // �˵�ѡ��
			    if (keycode == KEY_ESC)
		            {
		                menu_ptr = 0;
		                func_ptr = 0;
		            }
		            if (keycode == KEY_ENTER)
		            {   
		                func_ptr = sel_ptr;            
		                menu_ptr = 2;
		                sel_ptr = 0;
		                disp_ptr = 0;
						Lcd_ClearScr(0);
						Glib_Buttom();
	                    App_Main();				
		            }                
		            if (keycode == KEY_UP)   // ѡ����һ����
		            {
		                if (sel_ptr > 0) sel_ptr--;					   	
		                if (sel_ptr < disp_ptr)	 disp_ptr--;
					
		            }    

		            if (keycode == KEY_DN)  // ѡ����һ����
		            {
						//Lcd_Clear(0,0,160,272,Green);
		                if (sel_ptr < (column - 1)) sel_ptr++; // 					                        
		                if (sel_ptr > disp_ptr + 13) disp_ptr++;
					
		            }    
		            break;
	            
	        default:
	            break;
	    }

}


U8 ReadMenuKey( int *xdata, int *ydata)
{
    U8 KeyCode;
    

   // ɨ���ֵ
    KeyCode = 0;

    if(*xdata>180 && *xdata<240 && *ydata>50 && *ydata<110)  
		{
			
			KeyCode = 4;  //up

			
		}

	else if(*xdata>180 && *xdata<240 && *ydata>185 && *ydata<240)  
		{
			
			KeyCode = 5;   //down 
		    
		}  
	else if(*xdata>180 && *xdata<240 && *ydata>110 && *ydata<140)  
		{
			
			KeyCode = 2;   
			
		} 

	 *xdata = 0;
	 *ydata = 0;

	 return KeyCode;


}

