/*************************************************************************
*   ��Ȩ����(C) 1987-2004, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  GPIO.h
*
*   ��    �� :  liuwenhui
*
*   ��    �� :  GPIOģ��ӿ��ļ�����V7R1 BSP_GPIO.h��ֲ
*
*   �޸ļ�¼ :  2012��11��27��
*************************************************************************/
#ifndef _GPIO_BALONG_H_
#define _GPIO_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hi_gpio.h"
#include "osl_types.h"
#include "bsp_memmap.h"

/* GPIO״̬*/
#define GPIO_OK                     0
#define GPIO_ERROR                  -1


/* GPIO�Ƿ��ʼ����־*/
#define GPIO_DEF_NOT_RUNNING        0
#define GPIO_DEF_RUNNING            1

/*****************************************************************************
* �� �� ��  : bsp_gpio_init
*
* ��������  : GPIO��ʼ���ӿ�
*
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
s32 bsp_gpio_init(void);

/*****************************************************************************
* �� �� ��  : bsp_gpio_direction_input
*
* ��������  : ����GPIO���ŷ���Ϊ����
*
* �������  : UINT32 gpio    GPIO���ű��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
void bsp_gpio_direction_input(u32 gpio);

/*****************************************************************************
* �� �� ��  : bsp_gpio_direction_output
*
* ��������  : ����GPIO���ŵķ���Ϊ����������ø�����Ĭ�ϵ�ƽֵ
*
* �������  : UINT32 gpio       GPIO���ű��
*             UINT32 value      �����õ�ƽֵ,��0Ϊ�͵�ƽ��1Ϊ�ߵ�ƽ
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
void bsp_gpio_direction_output(u32 gpio, u32 value);

/*****************************************************************************
* �� �� ��  : bsp_gpio_direction_get
*
* ��������  : ��ѯGPIO ���ŵķ���
*
* �������  : UINT32 gpio        GPIO���ű��
*
* �� �� ֵ  : ����gpio���ŷ���,��0Ϊ���룬1Ϊ���
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
s32 bsp_gpio_direction_get(u32 gpio);

/*****************************************************************************
* �� �� ��  : bsp_gpio_set_value
*
* ��������  : ����GPIO ���ŵĵ�ƽֵ
*
* �������  : u32 gpio        GPIO���ű��
*			  u32 value      �ܽŸ�/�͵�ƽ
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
void bsp_gpio_set_value(u32 gpio,u32 value);

/*****************************************************************************
* �� �� ��  : bsp_gpio_get_value
*
* ��������  : ��ѯGPIO���ŵĵ�ƽֵ
*
* �������  : UINT32 gpio        GPIO���ű��
*
* �� �� ֵ  : ����GPIO���ŵĵ�ƽֵ
*
* �޸ļ�¼  : 2012��11��27��
*****************************************************************************/
s32 bsp_gpio_get_value(u32 gpio);

void rf_gpio_set_high(void);

void rf_gpio_set_low(void);

int ldo_gpio123_get_value(void);

int ldo_gpio124_get_value(void);

int bsp_rf_switch_init(void);

int bsp_ldo_gpio_init(void);

int bsp_rse_gpio_set(unsigned int flag, unsigned int mask, unsigned int value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define _GPIO_BALONG_H_ */