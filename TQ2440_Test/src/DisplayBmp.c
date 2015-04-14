
/*
**--------------File Info---------------------------------------------------------------------------------
** File name:               DisplayBmp.C
** Descriptions:            The File System application function

** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#include "DisplayBmp.h"
#include "ff.h"
#include "LCD_TFT.h"

U8 tmp_buffer[2048]={0}; //512̫С,1024̫��,�������ջ���
U8 tmp_buffer2[1024]={0};
FIL file1;


extern void PutPixel(U32 x,U32 y, U32 c );


U16 X1R5G5B5_R5G6B5(U16 input)
{
    U16  r, g, b, rgb;
    input &= 0x7FFF;//ȥ��X1
    r = (input>>0)  & 0x1F;
    g = (input>>5)  & 0x1F;
    b = (input>>10) & 0x1F;
    rgb = (b<<11) + (g<<6) + (r<<0);

    return rgb;
}



void  DispImage(char *file,U16 StartX,U16 StartY,U32 hno,U32 lno)
{
    U32  no;
    U32  biBitCount;
    
    unsigned int br;
    int result;
	int i;
    unsigned long offset = 0;
	unsigned long offset_setp = 0;
	unsigned char * buffer_point = 0;
    unsigned int  n;

    //���ļ�
    result = f_open(&file1,file,FA_READ);
    if( result == FR_OK )//�򿪳ɹ�
    {
		
        result = f_read(&file1,tmp_buffer,54,&br);//��ȡ54�ֽ��ļ�ͷ

        hno    =  *(tmp_buffer+0x12);//�õ�ͼ����
        lno    =  *(tmp_buffer+0x16);//�õ�ͼ����
		
        biBitCount = *(tmp_buffer+0x1C);//������ر�����
        offset = *(tmp_buffer+0x0A);//�õ�ͼ�����ݵ�ƫ����

		if( ((hno*(biBitCount/8))%4) == 0 )
		{
		   offset_setp = hno * (biBitCount / 8);
		}
		else
		{
		   	offset_setp = 	 hno * (biBitCount / 8) + (4 - (hno * (biBitCount / 8) )%4 ) ;
		}

		offset = offset +   (lno-1) * offset_setp - 1;
    }
    no = 0;
	f_close(&file1);

	result = f_open(&file1,file,FA_READ);
//	Uart_Printf("\n hno:%d",hno);
//	Uart_Printf("\n lno:%d",lno);
//	Uart_Printf("\n biBitCount:%d",biBitCount);
//	Uart_Printf("\n offset_setp:%d",offset_setp);
    for(no=lno; no>0; no--) // 1024����,75��
    {
        
		br = 0;
		result = f_lseek(&file1,offset);
		offset -=  offset_setp;
		
		Uart_Printf("\n here !!! ");
		Uart_Printf("\n hno*(biBitCount / 8):%d",hno*(biBitCount / 8));
        result = f_read(&file1,tmp_buffer,hno*(biBitCount / 8),&br);//��ȡ 256 ��������,ÿ����3�ֽ�
		Uart_Printf("\n res:%d",result);
		Uart_Printf("\n br:%d",br);
		for(i=0;i<360;i++)
		Uart_Printf("%d ",tmp_buffer[i]);
		Uart_Printf("\n hdgsdgsd !!! ");
        buffer_point = tmp_buffer;
        for(n=0; n<hno; n++)//ת��������320����
        {
            unsigned short color = 0;
			
            switch(biBitCount)
            {
                case 24:
                    color |= ( *(buffer_point++) >> 3 ) << 11;
                    color |= ( *(buffer_point++) >> 3 );
                    color |= ( *(buffer_point++) >> 2 ) << 5;
					
                    PutPixel(StartX + n, (StartY + lno) - no + 1,color);
                    break;
                    
                case 16:
                    color |= (*(buffer_point++));
                    color |= (*buffer_point++) << 8;
                    color = X1R5G5B5_R5G6B5(color);
                    PutPixel(StartX + n, StartY + 239 - no + 1,color);
                    break;

                default:
                    break;
                    
            }
        }
    }
    f_close(&file1);
}










