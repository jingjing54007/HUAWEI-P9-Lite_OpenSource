/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCsCallCtx.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��09��03��
  ��������   : TAF X CALL�����Ĺ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafCsCallCtx.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : TAF_CSCALL_InitCtx
 ��������  : ��ʼ��XCALL��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CSCALL_InitCtx(VOS_VOID)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_InitCtx();
#endif

}

/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





