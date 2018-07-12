/******************************Copyright(C) Nubo*******************************
File name  : Thread.c
Description: Thread implementation function 
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#include "NuboLib.h"
#include "Thread.h"

//Private type of data define
#pragma pack(1)
struct thread_data
{
    u8 flag;            //���б�ʶ
    u8 con;             //��������
    u16 cnt;            //���д���
    u32 frep;           //��������
    u32 count_time ;    //�߳�ִ�еĵȴ�ʱ�� yanhuan adding 2015/10/27
    void *fun;          //���к���ָ��
};

struct thread_manage
{
    u16 runCnt;         //��ǰ�߳�������
    u16 hangCnt;        //�̹߳�����    
    struct thread_data thread[THREAD_NUM_MAX];
};
#pragma pack()

//Private Macro define
#define THREAD_TOTAL    (thread.runCnt + thread.hangCnt)    //�߳�����

//Private Variable define
static struct thread_manage   thread;

//Private function declaration
static u8 Thread_Check(u32 start, u32 end, void *fun);

/*******************************************************************************
�� �� ��:  Thread_Init
����˵��:  �߳����ݳ�ʼ��
��    ��:  ��
����  ֵ:  ��
*******************************************************************************/
void Thread_Init(void)
{
    *(u32*)&thread.runCnt = 0;   //�߳������ÿ�
}

/*******************************************************************************
�� �� ��:  Thread_Login
����˵��:  �߳�ע�� 
��    ��:  fun: �߳���
           ִ������
����  ֵ:  ע����, 
*******************************************************************************/
u32 Thread_Login(ThreadCon_t con, u16 cnt, u32 frep, void * fun)
{
    u32 i;
    
    ERRR(THREAD_TOTAL >= THREAD_NUM_MAX, return 0);     //�߳̿ռ�
    if (Thread_Check(0, THREAD_TOTAL, fun) == 0)        //�߳�û�г������̱߳���
    {
        memmove(&thread.thread[thread.runCnt+1], &thread.thread[thread.runCnt],     //����һ���ռ䣬���½��߳�
                    sizeof(struct thread_data)*(thread.hangCnt));   
        i = thread.runCnt;
        thread.runCnt++;
        thread.thread[i].flag = 0;
    }   
    else 
    {
        Thread_Wake(fun);   //�̻߳���
        i = Thread_Check(0, THREAD_TOTAL, fun) - 1;
    }   
   
    thread.thread[i].con = con;
    thread.thread[i].fun = fun;
    if (con == ONCEDELAY)   //������ʱ�߳�
    {
        if (0 == frep)
        {
            frep++;
        }
        cnt = 1;
        thread.thread[i].flag = 0;
    }
    thread.thread[i].cnt = cnt;
    thread.thread[i].frep = frep;
    thread.thread[i].count_time = 0; //yanhuan adding 2015/10/28
    
    return 1;
}

/*******************************************************************************
�� �� ��:  Thread_Logout
����˵��:  �߳�ע�� 
��    ��:  fun: �߳���
�� �� ֵ:  ��
*******************************************************************************/
void Thread_Logout(void * fun)
{
    u32 i = Thread_Check(0, THREAD_TOTAL, fun);

    if (i)    //�ҵ��߳�λ��
    {
        memmove(&thread.thread[i-1], &thread.thread[i], 
                    sizeof(struct thread_data)*(THREAD_TOTAL - i));
        
        if (i > thread.runCnt)  //�߳�λ�����пռ�
        {
            thread.hangCnt--;
        }
        else
        {
            thread.runCnt--; 
        }
    }
}

/*******************************************************************************
�� �� ��:  Thread_Hang
����˵��:  �̹߳��� 
��    ��:  fun:�߳���
����  ֵ:  ��
*******************************************************************************/
void Thread_Hang(void * fun)
{
    u32 i = Thread_Check(0, thread.runCnt, fun);

    if (i)    //�߳�λ�������߳̿ռ�
    {
        struct thread_data th;
        
        memcpy(&th, &thread.thread[i-1], sizeof(struct thread_data)); 
        memmove(&thread.thread[i-1], &thread.thread[i], 
                    sizeof(struct thread_data)*(thread.runCnt - i));
        memcpy(&thread.thread[--thread.runCnt], &th, sizeof(struct thread_data));
        thread.hangCnt++;
    }
}

/*******************************************************************************
�� �� ��:  Thread_Wake
����˵��:  �̻߳���
��    ��:  fun:�߳���
����  ֵ:  ��
ע    ��:  ������ֻ�ܶ������̵߳Ĳ��� 
*******************************************************************************/
void Thread_Wake(void * fun)
{
    u32 i = Thread_Check(thread.runCnt, THREAD_TOTAL, fun);

    if (i)    //�ҵ��߳�λ��
    {
        if ((i - thread.runCnt) > 1)    //i���ǽ��������߳�
        {
            struct thread_data th;
            memcpy(&th, &thread.thread[i-1], sizeof(struct thread_data)); 
            memmove(&thread.thread[thread.runCnt + 1], &thread.thread[thread.runCnt], //�ڳ��洢�ռ�
                        sizeof(struct thread_data)*(i - thread.runCnt));
            memcpy(&thread.thread[thread.runCnt], &th,  sizeof(struct thread_data));
        }
        thread.runCnt++;
        thread.hangCnt--;
    }
}

/*******************************************************************************
�� �� ��:  Thread_Process
����˵��:  �̴߳���
��    ��:  ��
����  ֵ:  ��
*******************************************************************************/
void Thread_Process(void)
{
    struct thread_data *pThread = NULL;
    
    for (pThread = &thread.thread[0]; pThread < &thread.thread[thread.runCnt]; pThread++)
    {
        if (pThread->flag)
        {
            void *fun = pThread->fun;;
            
            pThread->flag = 0;
            switch (pThread->con)
            {
                case ONCEDELAY: pThread->flag = 1;
                case MANY:      if (!pThread->cnt--)
                                {   
                                    Thread_Logout(fun);
                                    pThread --;
                                    break;
                                }
                     
                case FOREVER:   ((fun1)(fun))();
                     break;             
                case RESULT:    if (((fun2)(fun))() == 0)  //�߳����з���ʧ��
                                {
                                    Thread_Logout(fun);
                                    pThread --;
                                }
                    break;
                default : break;
            }
        }
    }
}
    
/*******************************************************************************
�� �� ��:  Thread_RunCheck
����˵��:  �߳����������˶�
��    ��:  ��
����  ֵ:  ��
*******************************************************************************/
void Thread_RunCheck(void)
{
    struct thread_data *pThread;

    for (pThread = &thread.thread[0]; pThread < &thread.thread[thread.runCnt]; pThread++)
    {
        if ((++pThread->count_time)>=(pThread->frep))//yanhuan modify 2015/10/28
        {
            pThread->count_time = 0;  
            pThread->flag = 1;
        }
    }
}

/*******************************************************************************
�� �� ��:   Thread_Check
����˵��:   �̺߳˶�
��    ��:   fun:     �߳���
            start:  ��ʼ�߳�λ��
            end:    ��ֹ�߳�λ��
����  ֵ:   0(û��)/(1~THREAD_UNM)�߳�����λ��
*******************************************************************************/
u8 Thread_Check(u32 start, u32 end, void *fun)
{
    u32 i; 
    
    for (i = start; i < end;)
    {
        if (thread.thread[i++].fun == fun)
        {
            return i;
        }
    }
    
    return 0;
}

/*******************************************************************************
�� �� ��:  ThreadState_t Thread_Query(void *fun)
����˵��:  �̲߳�ѯ����
��    ��:  fun���̺߳���ָ��
�� �� ֵ:  NO_EXIST_STATE:��������������;RUNNING_STATE��������������;PENDING_STATE���ڹ���������
*******************************************************************************/
ThreadState_t Thread_Query(void *fun)    //Jay Add 2015.11.17
{
    u8 Taskpos = Thread_Check(0, THREAD_TOTAL, fun);
    if(0 == Taskpos)
    {
        return NO_EXIST_STATE;
    }
    else if(Taskpos < thread.runCnt + 2)
    {
        return RUNNING_STATE;
    }
    else
    {
        return PENDING_STATE;
    }
}

/**************************Copyright Nubo 2018-01-03*************************/

