/******************************Copyright(C) Nubo*******************************
File name  : Thread.h
Description: Thread implementation function 
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __THREAD_H
#define __THREAD_H
#include "NbType.h"

#define THREAD_NUM_MAX 20

/*********************************�������Ͷ���********************************/
typedef enum
{
    ONCEDELAY   = 0,    //������ʱ����
    MANY        = 1,    //���
    FOREVER     = 2,    //����
    RESULT      = 3,    //�����
}ThreadCon_t;           //�߳�פ������
 
typedef enum
{
    NO_EXIST_STATE = 0, //��������������   
    RUNNING_STATE,      //����̬   
    PENDING_STATE       //����̬ 
}ThreadState_t;

typedef void (*fun1)(void); 
typedef u8 (*fun2)(void);
 
/*********************************��������********************************/
void Thread_Init(void);     //�̳߳�ʼ������
u32 Thread_Login(ThreadCon_t con, u16 cnt, u32 frep, void * fun);   //�߳�ע��
void Thread_Logout(void *fun);  //�߳�ע��
void Thread_Process(void);      //�߳�����
void Thread_RunCheck(void); //�߳�����ʱ��˶�
void Thread_Hang(void * fun);   //�̹߳���
void Thread_Wake(void * fun);   //�̻߳���    
ThreadState_t Thread_Query(void *fun);//��ѯ�̵߳�ǰ״̬   //Jay Add 2015.11.17

#endif //Thread.h end
