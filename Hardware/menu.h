#ifndef __MENU_H
#define __MENU_H


typedef struct
{
	uint8_t CurrentNum;	//当前界面序号
	uint8_t Enter;		//确认键
	uint8_t Next;		//下一个
	void (*Current_Operation)(void);//执行函数
}Menu_table_t;

extern uint8_t taskIndex;
extern Menu_table_t taskTable[];

void Menu_Interface(void);
void Function_Interface1(void);
void Function_Interface2(void);
void Function_Interface3(void);
void Function_Interface4(void);
void Function_Interface5(void);
void Function_Interface6(void);
void Function_Interface7(void);
void Function_Interface8(void);
void Function_Interface9(void);
void Function_Interface10(void);
void Function_Interface11(void);
void Function_Interface12(void);
void Function_Interface13(void);
void Function_Interface14(void);
void Function_Interface15(void);
void Function_Interface16(void);
void Function_Interface17(void);

#endif
