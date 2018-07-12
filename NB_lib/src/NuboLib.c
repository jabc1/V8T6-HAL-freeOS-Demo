/******************************Copyright(C) Nubo*******************************
File name  : NuboLib.c
Description: Nubo create lib source
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#include "NuboLib.h"

/*******************************************************************************
�� �� ����  memcpy
����˵����  �ڴ濼��
��    ����  dest:   Ŀ���ڴ��ַ
            src:    Դ�ڴ��ַ
            num:    �����ڴ��С
�� �� ֵ��  ��
*******************************************************************************/
void memcpy(void *dest,  const void *src, unsigned int num)
{
    char *pd, *ps;
    
    if (dest != src)    //Ŀ����Դ����ͬһλ��
    {
        for (pd = (char*)dest, ps = (char*)src; num > 0; num--)
        {
            *pd++ = *ps++;
        }
    }
}
                                                                                
/*******************************************************************************
�� �� ����  memcmp
����˵����  �ڴ�Ƚ�
��    ����  dest:   Ŀ���ڴ��ַ
            src:    Դ�ڴ��ַ
            num:    �Ƚ��ڴ��С
�� �� ֵ��  1(��ͬ)/0
*******************************************************************************/
char memcmp(void *dest,  const void *src, unsigned int num)
{
    char *pd, *ps;
    
    if (dest != src)    //Ŀ����Դ����ͬһλ��
    {
        for (pd = (char*)dest, ps = (char*)src; num > 0; num--)
        {
            if (*pd++ != *ps++)
            {
                return 1;
            }
        }
    }
        
    return 0;
}

/*******************************************************************************
�� �� ����  memset
����˵����  �ڴ�����
��    ����  dest:   Ŀ���ڴ��ַ
            val:    Ŀ��ֵ
            num:    �Ƚ��ڴ��С
�� �� ֵ��  ��
*******************************************************************************/
void memset(void *dest, unsigned char const val, unsigned int num)
{
    char *pd;
    
    for (pd = (char*)dest; num > 0; num--)
    {
        *pd++ = val;
    }
}

/*******************************************************************************
�� �� ����  memmove
����˵����  �ڴ��ƶ�
��    ����  dest:   Ŀ���ڴ��ַ
            src:    Դ�ڴ��ַ
            num:    �ƶ��ڴ��С
�� �� ֵ��  ��
*******************************************************************************/
void memmove(void *dest,  const void *src, unsigned int num)
{
    char *pd, *ps;
    
    if (dest < src)
    {
        for (pd = (char*)dest, ps = (char*)src; num > 0; num--)
        {
            *pd++ = *ps++;
        }
    }
    else if (dest > src)
    {
        for (pd = (char*)((unsigned int)dest + num), ps = (char*)((unsigned int)src + num);
                num > 0; num--)
        {
            *(--pd) = *(--ps);
        }
    }
}

/*******************************************************************************
�� �� ��:   memfind
����˵��:   �ڴ����
��    ��:   dest:   ����Ŀ��
            dLen��   Ŀ����Ч����
            src:    ����Դ
            sLen:   Դ���ݴ�С
�� �� ֵ:   NULL(δ�ҵ�)/Ŀ��λ��Դ�ĵ�ַ
*******************************************************************************/
void* memfind(void *dest, unsigned int dLen, void *src, unsigned int sLen)
{
    char *pDest, *pSrc;
    unsigned int i;
    
    for (pDest = dest, pSrc = src; sLen > 0; sLen--, pSrc++)
    {
        if (*pDest == *pSrc++)  //Դ���ҵ���Ŀ����ͬ����
        {
            for (i = 1; i < dLen && pDest[i] == *pSrc++; i++) //�ȽϺ��������Ƿ����
            {}
            if (i == dLen)  //Դ���ҵ�����Ŀ����ȫ��ȵ�����Ƭ
            {
                return (pSrc - i);
            }
        }
    }
    
    return 0;
}

/*****************************************************************************
�� �� ��:   memcharget
����˵��:   �ڴ��ַ�����ȡ
��    ��:   dest:   Ŀ��洢��ַ
            len:    ���س���
            src:    �ڴ����Դ
            size:   ����Դ��С
�� �� ֵ:   ��
*****************************************************************************/
void memcharget(void *dest, unsigned char *len, void const *src, unsigned int size)
{
    char *pDest;
    char const *pSrc;
    
    for (*len = 0, pDest = dest, pSrc = src; size > 0; size--)
    {
        *pDest++ = *pSrc++;
        *len += 1;
        if (*pSrc == '\0')
        {
            return;
        }
    }
    *len = 0;
}

///*****************************************************************************
//�� �� ��:   Char_hex
//����˵��:   �ַ���ת16����
//��    ��:   dest:   Ŀ��洢��ַ
//            len:    ���س���
//            src:    Դ�ַ�����
//            size:   Դ�ַ����ݴ�С
//�� �� ֵ:   1:ת���ɹ�/0: �ַ������з�16���������ַ�
//*****************************************************************************/
//char Char_hex(void *dest, unsigned char *len, void const *src, unsigned int size)
//{
//  char *pDest = dest;
//  char const *pSrc = src;
//  int i;
//  
//  for (*len = 0; size > 0; size--)
//  {
//      if (*pSrc >= 'a')
//      {
//          i = *pSrc - 'a' + 10;
//      }
//      else if (*pSrc >= 'A')
//      {
//          i = *pSrc - 'A' + 10;
//      }
//      else if (*pSrc >= '0' && *pSrc <= '9')
//      {
//          i = *pSrc - '0';
//      }
//      else
//      {
//          return 0;
//      }
//      
//      if (i > 15)
//      {
//          return 0;
//      }
//      if (size%2)
//      {
//          *pDest = i<<4;
//      }
//      else
//      {
//          *pDest += i;
//          pDest++;
//          (*len)++;
//      }
//      pSrc++;
//  }

//  return 1;
//}

/**************************Copyright Nubo 2018-01-03*************************/
