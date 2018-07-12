/******************************Copyright(C) Nubo*******************************
File name  : NuboLib.h
Description: Nubo create lib source
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __NuboLIB_H
#define __NuboLIB_H

/*�ݴ��*/
#define ERRR(conf, ret)      do              \
                            {                \
                                if (conf)    \
                                {            \
                                    ret;     \
                                }            \
                            } while(0) 
                            
#define ABS(i, j)       (((i) > (j)) ? ((i) - (j)) : ((j) - (i)))       //��ȡ����ֵ
//
                                
void memcpy(void *dest, const void *src, unsigned int num); //�ڴ濼��
char memcmp(void *dest,  const void *src, unsigned int num);    //�ڴ�Ƚ�
void memmove(void *dest,  const void *src, unsigned int num);   //�ڴ��ƶ�
void memset(void *dest, unsigned char const val, unsigned int num); //�ڴ����� 
void* memfind(void *dest, unsigned int dLen, void *src, unsigned int sLen);                         
void memcharget(void *dest, unsigned char *len, void const *src, unsigned int size);

#endif //NuboLib.h end
