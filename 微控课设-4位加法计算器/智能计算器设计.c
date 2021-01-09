#include<reg52.h>			
typedef unsigned char uint8;
typedef unsigned int uint16;

sbit rw=P2^5;
sbit rs=P2^6;
sbit e=P2^7;
sbit led=P3^7;

uint8 key,num,ei,eii,p;
uint8 fuhao;//���������Ǹ����ţ��ǼӼ����ǳ˳���
uint8 flag;	//������û�а��·��ż��������ͳ��
long a,b,c,d;	//�����������ݵĵ�һ���͵ڶ��������ڵ�������
uint8 k; //����С���������ʾ��λ��

uint8 dat1[]={1,2,3,0x2b-0x30, 4,5,6,0x2d-0x30, 7,8,9,0x2a-0x30,
									0,0x01-0x30,0x3d-0x30,0x2b-0x30 };//������ʾ������
uint8 dat2[]="9999 revo rewsna";
uint8 dat3[]="Hi welcome into";
uint8 dat4[]="counter by yumo";
void delay(uint16 i)
{
	while(i--);
}
void lcdwrc(uint8 c)//д������
{
	delay(1000);
	rs=0;//ѡ��������
	rw=0;//ѡ��д��
	e=0;//ʹ��
	
	P0=c;//��������
	e=1;//дʱ��
	delay(1000);//����ʱ��
	e=0;
}
void lcdwrd(uint8 dat)//д������
{
	delay(1000);
	rs=1;//ѡ����������
	rw=0;//ѡ��д��
	e=0;
	
	P0=dat;//д������
	e=1;//д��ʱ��
	delay(1000);
	e=0;
	rs=0;
}

void lcdinit()//LCD��ʼ��
{
	delay(1500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	lcdwrc(0x08);
	lcdwrc(0x01);
	lcdwrc(0x06);
	lcdwrc(0x0c);
	key=0;
	num=0;
	flag=0;
	fuhao=0;
	a=0;
	b=0;
	c=0;
	d=0;
	led=0;
}

show()
{
	for(eii=0;eii<15;eii++)
	{
		
		lcdwrd(dat3[eii]);
	}	
	lcdwrc(0xc0);//д�����ʹ�䵽�ڶ��е�һ���ַ�
	for(p=0;p<15;p++)
	{
		
		lcdwrd(dat4[p]);
	}	
	return 1;
}
void keyscan()
{
	P1=0xfe;   //���һ��Ϊ0��Ȼ���ж�����һ�а���
	if(P1!=0xfe)
	{
		delay(1000);
		if(P1!=0xfe)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=0;break;	  //1
				case 0xd0: num=1;break;	  //2
				case 0xb0: num=2;break;	  //3
				case 0x70: num=3;break;	  //��
			}
		}
		while(P1!=0xfe);
		if(num==0||num==1||num==2)	 //ȷ�ϵ�һ�е���1,2,3
		{
			if(flag==0)	 //û�а��·��ż�
			{
				led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				led=1;
				delay(1000);
				led=0;
				delay(1000);
				led=1;
				b=b*10+dat1[num];
			}		
		}
		if(num==3)
		{
			led=0;
			flag=1;
			fuhao=1;//�Ӻ�+	
		}
		lcdwrd(0x30+dat1[num]);
	}

	P1=0xfd;				//��ڶ���Ϊ0���ж�����һ�а���
	if(P1!=0xfd)
	{
		delay(1000);
		if(P1!=0xfd)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=4;break;	  //4
				case 0xd0: num=5;break;	  //5
				case 0xb0: num=6;break;	  //6
				case 0x70: num=7;break;	  //����
			}	
		}
		while(P1!=0xfd);
		if(num==4||num==5||num==6)
		{
			if(flag==0)	 //û�а��·��ż�
			{
				led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				led=1;
				b=b*10+dat1[num];
			}			
		}
		else
		{
			led=0;
			flag=1;
			fuhao=2;//�������
		}
		lcdwrd(0x30+dat1[num]);
	}

	P1=0xfb;		 //�������Ϊ0���ж���һ�а���
	if(P1!=0xfb)
	{
		delay(1000);
		if(P1!=0xfb)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=8;break;	  //7
				case 0xd0: num=9;break;	  //8
				case 0xb0: num=10;break;  //9
				case 0x70: num=11;break;  //��*
			}	
		}
		while(P1!=0xfb);
		if(num==8||num==9||num==10)
		{
			if(flag==0)	 //û�а��·��ż�
			{
				led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				led=1;
				b=b*10+dat1[num];
			}			
		}
		else
		{
			led=0;
			flag=1;
			fuhao=3;//����˺�*
		}
		lcdwrd(0x30+dat1[num]);
	}

	P1=0xf7;		 //�������Ϊ0���ж���һ�а���
	if(P1!=0xf7)
	{
		delay(1000);
		if(P1!=0xf7)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=12;break;  //0
				case 0xd0: num=13;break;  //���rst
				case 0xb0: num=14;break;  //�Ⱥ�=
				case 0x70: num=15;break;  //��/
			}	
		}
		while(P1!=0xf7);
		switch(num)
		{
			case 12: 
					if(flag==0)	 //û�а��·��ż�
					{
						led=1;
						a=a*10+dat1[num];
						lcdwrd(0x30);	
					}
					else
					{
						led=1;
						b=b*10+dat1[num];
						lcdwrd(0x30);
					}
					break;			
			case 13: 
					lcdwrc(0x01);	//����ָ��			
					a=0;
					b=0;
			    c=0;
					flag=0;
					fuhao=0;
					break;
			case 15:
				
					led=0;
					flag=1;
					fuhao=4;
					lcdwrd(0x2f);//����/
					break;					
			case 14: 					//����ǵ��ں�
					if(fuhao==1)//��
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//���ù�����ƣ���Ļ���ƶ�
						c=a+b;
						
						if(c==0)
						{
							lcdwrc(0x4f+0x80);
							lcdwrc(0x04);
							lcdwrd(0x30);
						}
						while((c!=0)&&(c<=9999))	 //һλһλ��ʾ
						{
							
							lcdwrd(0x30+c%10);//��ʾ��������һλ��0x4f��λ��
							c=c/10;//ȡǰ��Ľ������	
						}						
						if(c>9999)
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}			
						}						
						lcdwrd(0x3d); //��ʾ���ں�=
						a=0;
						b=0;
						c=0;
						flag=0;
						fuhao=0;//ȫ�����Ϊ0
					}					
					if(fuhao==2)   //��
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//���ù�����ƣ���Ļ���ƶ�
						if(a>b)
							c=a-b;
						else
							c=b-a;
						
						if((c==0))//�����λ��Ӱ����ʾ
						{
							lcdwrc(0x4f+0x80);
							lcdwrc(0x04);
							lcdwrd(0x30);
						}
						while((c!=0)&&(c<=9999))	 //һλһλ��ʾ
						{
							lcdwrd(0x30+c%10);//��ʾ��������һλ��0x4f��λ��
							c=c/10;//ȡǰ��Ľ������	
						}
						if(c>9999) 
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}								
						}					
						if(a<b)	lcdwrd(0x2d); //��ʾ-��
						lcdwrd(0x3d); //��ʾ���ں�=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//ȫ�����Ϊ0
					}					
					if(fuhao==3)//�˷�		
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//���ù�����ƣ���Ļ���ƶ�
						c=a*b;
						while((c!=0)&(c<=9999))	 //һλһλ��ʾ
						{
							lcdwrd(0x30+c%10);//��ʾ��������һλ��0x4f��λ��
							c=c/10;//ȡǰ��Ľ������	
						}
						if (c>9999) 
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}					
						}
						if(a==0||b==0)
						{
							lcdwrd(0x30);
						}
						lcdwrd(0x3d); //��ʾ���ں�=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//ȫ�����Ϊ0	
					}				
					if(fuhao==4)//����
					{
						k=0;
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//���ù�����ƣ���Ļ���ƶ�
						c=(long)(((float)a/b)*10000);//ǿ��ת��Ϊlong��
						while((c!=0)&&(c<=99990000))	 //һλһλ��ʾ
						{
							k++;
							lcdwrd(0x30+c%10);//��ʾ��������һλ��0x4f��λ��
							c=c/10;//ȡǰ��Ľ������
							if(k==4)//���������λ��Ч����
							{
								lcdwrd(0x2e);//��ʾһ����
								//k=0;//����K=0����ôÿ����λ����һ��С���㣬�������ϵĶ��ž������ԭ��
							}		
						}
						if(c>99990000) 
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}		
						}
						if(0<(a/b)<0.1001)
						{
							//lcdwrd(0x2e);
							
						}
						if((a/b)<1)	  //���a��bС�Ļ���ô���Ľ�����λ��0
						{
							lcdwrd(0x30);	
						}
						if(b==0)//�����Ϊ��������Ϊ0���������ʾERROR
						{
							lcdwrc(0x4f+0x80);
							lcdwrc(0x04);
							lcdwrd(0x52);
							lcdwrd(0x4f);
							lcdwrd(0x52);												
							lcdwrd(0x52);
							lcdwrd(0x45);
						}
						lcdwrd(0x3d); //��ʾ�Ⱥ�
						a=0;
						b=0;
						flag=0;
						fuhao=0;//ȫ�����Ϊ0
					}
					break;
		}
	}
}
void main()
{
	lcdinit();
	show();//���Ի�����
	while(1)
	{		
		keyscan();	
	}
}
