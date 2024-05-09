#ifndef __MYRTC_H
#define __MYRTC_H

extern uint16_t MyRTC_Time[];
extern uint8_t week_day;

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);
void Week_show(void);
void SecEXTI_Init(void);

#endif
