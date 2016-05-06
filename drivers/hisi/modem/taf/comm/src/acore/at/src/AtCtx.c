

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtCtx.h"
#include "AtDataProc.h"
#include "AtMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CTX_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/***************************AT��ȫ�ֱ����� Begin******************************/
/* AT��������ε�PID��Ӧ��  */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
AT_MODEM_PID_TAB_STRU                   g_astAtModemPidTab[] =
{
    {I0_WUEPS_PID_USIM,         I1_WUEPS_PID_USIM,          I2_WUEPS_PID_USIM,      0},
    {I0_MAPS_STK_PID,           I1_MAPS_STK_PID,            I2_MAPS_STK_PID,        0},
    {I0_MAPS_PIH_PID,           I1_MAPS_PIH_PID,            I2_MAPS_PIH_PID,        0},
    {I0_MAPS_PB_PID,            I1_MAPS_PB_PID,             I2_MAPS_PB_PID,         0},
    {I0_UEPS_PID_GRM,           I1_UEPS_PID_GRM,            I2_UEPS_PID_GRM,        0},
    {I0_UEPS_PID_DL,            I1_UEPS_PID_DL,             I2_UEPS_PID_DL,         0},
    {I0_UEPS_PID_LL,            I1_UEPS_PID_LL,             I2_UEPS_PID_LL,         0},
    {I0_UEPS_PID_SN,            I1_UEPS_PID_SN,             I2_UEPS_PID_SN,         0},
    {I0_UEPS_PID_GAS,           I1_UEPS_PID_GAS,            I2_UEPS_PID_GAS,        0},
    {I0_WUEPS_PID_MM,           I1_WUEPS_PID_MM,            I2_WUEPS_PID_MM,        0},
    {I0_WUEPS_PID_MMC,          I1_WUEPS_PID_MMC,           I2_WUEPS_PID_MMC,       0},
    {I0_WUEPS_PID_GMM,          I1_WUEPS_PID_GMM,           I2_WUEPS_PID_GMM,       0},
    {I0_WUEPS_PID_MMA,          I1_WUEPS_PID_MMA,           I2_WUEPS_PID_MMA,       0},
    {I0_WUEPS_PID_CC,           I1_WUEPS_PID_CC,            I2_WUEPS_PID_CC,        0},
    {I0_WUEPS_PID_SS,           I1_WUEPS_PID_SS,            I2_WUEPS_PID_SS,        0},
    {I0_WUEPS_PID_TC,           I1_WUEPS_PID_TC,            I2_WUEPS_PID_TC,        0},
    {I0_WUEPS_PID_SMS,          I1_WUEPS_PID_SMS,           I2_WUEPS_PID_SMS,       0},
    {I0_WUEPS_PID_RABM,         I1_WUEPS_PID_RABM,          I2_WUEPS_PID_RABM,      0},
    {I0_WUEPS_PID_SM,           I1_WUEPS_PID_SM,            I2_WUEPS_PID_SM,        0},
    {I0_WUEPS_PID_ADMIN,        I1_WUEPS_PID_ADMIN,         I2_WUEPS_PID_ADMIN,     0},
    {I0_WUEPS_PID_TAF,          I1_WUEPS_PID_TAF,           I2_WUEPS_PID_TAF,       0},
    {I0_WUEPS_PID_VC,           I1_WUEPS_PID_VC,            I2_WUEPS_PID_VC,        0},
    {I0_WUEPS_PID_DRV_AGENT,    I1_WUEPS_PID_DRV_AGENT,     I2_WUEPS_PID_DRV_AGENT, 0},
    {I0_UEPS_PID_MTA,           I1_UEPS_PID_MTA,            I2_UEPS_PID_MTA,        0},
    {I0_DSP_PID_GPHY,           I1_DSP_PID_GPHY,            I2_DSP_PID_GPHY,        0},
    {I0_DSP_PID_SLEEP,          I1_DSP_PID_SLEEP,           I2_DSP_PID_SLEEP,       0},
    {I0_DSP_PID_APM,            I1_DSP_PID_APM,             I2_DSP_PID_APM,         0},
    {I0_WUEPS_PID_SLEEP,        I1_WUEPS_PID_SLEEP,         I2_WUEPS_PID_SLEEP,     0}
};
#endif

VOS_UINT32                              g_ulCtzuFlag = 0;

/* ATģ�鹫�������� */
AT_COMM_CTX_STRU                        g_stAtCommCtx;

/* ATģ����Modem��ص������� */
AT_MODEM_CTX_STRU                       g_astAtModemCtx[MODEM_ID_BUTT];

/* ATģ����Client��ص������� */
AT_CLIENT_CTX_STRU                      g_astAtClientCtx[AT_MAX_CLIENT_NUM];

/* ATģ�鸴λ��ص������� */
AT_RESET_CTX_STRU                       g_stAtResetCtx;

/***************************AT��ȫ�ֱ����� End******************************/

/*********************************������Ҫ������*************************************/
/* �Ƿ����Ȩ�ޱ�־(����DIAG/SHELL�ڵ�Ȩ��) */
AT_E5_RIGHT_FLAG_ENUM_U32               g_enATE5RightFlag;

/* ���� g_stATDislogPwd �е� DIAG�ڵ�״̬Ҫ���뱸��NV�б�; �����벻�ñ���
   �ʽ� g_stATDislogPwd �е��������, ��ʹ�����е� DIAG ��״̬;
   ���¶���NV��������������  */
VOS_INT8                                g_acATOpwordPwd[AT_OPWORD_PWD_LEN+1];

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/* ���ڵ�ǰ�Ƿ���Ȩ�޲���AT�˿� */
AT_RIGHT_OPEN_FLAG_STRU                 g_stAtRightOpenFlg;
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/* ʹ�ܽ�ֹSD��ʱ��Ҫ������ */
VOS_INT8                                g_acATE5DissdPwd[AT_DISSD_PWD_LEN+1];
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/*���֧����ʾ�ִ�*/
VOS_UINT8                               gaucAtCmdNotSupportStr[AT_NOTSUPPORT_STR_LEN+4];
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

AT_ABORT_CMD_CTX_STRU                   gstAtAbortCmdCtx;   /* ���ڱ����ϵ���Ϣ */

/*��¼���Ŵ������Ƿ�ʹ�� */
PPP_DIAL_ERR_CODE_ENUM                  gucPppDialErrCodeRpt;

AT_DIAL_CONNECT_DISPLAY_RATE_STRU       g_stDialConnectDisplayRate;

/* UE��������: ����Э��汾������ֵ */
AT_DOWNLINK_RATE_CATEGORY_STRU          g_stAtDlRateCategory;

VOS_UINT8                               ucAtS3          = 13;                   /* <CR> */
VOS_UINT8                               ucAtS4          = 10;                   /* <LF> */
VOS_UINT8                               ucAtS5          = 8;                    /* <DEL> */
VOS_UINT8                               ucAtS6          = 2;                    /* Number of seconds to wait before blind dialling:default value = 2 */
VOS_UINT8                               ucAtS7          = 50;                   /* Number of seconds in which connection must be established or call will be disconnected,
                                                                                   default value = 50(refer to Q)*/

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
AT_CMEE_TYPE                            gucAtCmeeType;                          /* E5������Ĭ�ϴ����� */
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

TAF_UINT32                              g_ulSTKFunctionFlag = TAF_FALSE;

/* ʹ��^NDISDUP���ŵı�־λ��Ϊ�˿����ϱ������Ϣʹ�� */
VOS_BOOL                                g_abAtNdisDialUp[AT_MAX_CLIENT_NUM];
VOS_BOOL                                g_abAtNdisDialDown[AT_MAX_CLIENT_NUM];

/*********************************CC Begin*************************************/
/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-10, begin */
/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-10, end */
/*********************************CC End*************************************/

/*********************************SMS Begin*************************************/
MN_MSG_CLASS0_TAILOR_U8                 g_enClass0Tailor         = MN_MSG_CLASS0_DEF;
/*********************************SMS End*************************************/

/*********************************NET Begin*************************************/
VOS_UINT16                              g_usReportCregActParaFlg = VOS_FALSE;
CREG_CGREG_CI_RPT_BYTE_ENUM             gucCiRptByte = CREG_CGREG_CI_RPT_TWO_BYTE;

/*********************************NET End*************************************/
#if (FEATURE_ON == FEATURE_LTE)
NVIM_RSRP_CFG_STRU                      g_stRsrpCfg;
NVIM_RSCP_CFG_STRU                      g_stRscpCfg;
NVIM_ECIO_CFG_STRU                      g_stEcioCfg;

LNAS_LMM_NV_NAS_RELEASE_STRU            g_stReleaseInfo;
#endif

AT_SS_CUSTOMIZE_PARA_STRU               g_stAtSsCustomizePara;

AT_TRACE_MSGID_TAB_STRU                 g_stAtTraceMsgIdTab[AT_CLIENT_ID_BUTT];

AT_CLIENT_CFG_MAP_TAB_STRU              g_astAtClientCfgMapTbl[] =
{
    AT_CLIENT_CFG_ELEMENT(PCUI),
    AT_CLIENT_CFG_ELEMENT(CTRL),
    AT_CLIENT_CFG_ELEMENT(PCUI2),
    AT_CLIENT_CFG_ELEMENT(MODEM),
    AT_CLIENT_CFG_ELEMENT(NDIS),
    AT_CLIENT_CFG_ELEMENT(UART),
#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CLIENT_CFG_ELEMENT(HSUART),
#endif
    AT_CLIENT_CFG_ELEMENT(SOCK),
    AT_CLIENT_CFG_ELEMENT(APPSOCK),
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_CLIENT_CFG_ELEMENT(HSIC1),
    AT_CLIENT_CFG_ELEMENT(HSIC2),
    AT_CLIENT_CFG_ELEMENT(HSIC3),
    AT_CLIENT_CFG_ELEMENT(HSIC4),
    AT_CLIENT_CFG_ELEMENT(HSIC_MODEM),
    AT_CLIENT_CFG_ELEMENT(MUX1),
    AT_CLIENT_CFG_ELEMENT(MUX2),
    AT_CLIENT_CFG_ELEMENT(MUX3),
    AT_CLIENT_CFG_ELEMENT(MUX4),
    AT_CLIENT_CFG_ELEMENT(MUX5),
    AT_CLIENT_CFG_ELEMENT(MUX6),
    AT_CLIENT_CFG_ELEMENT(MUX7),
    AT_CLIENT_CFG_ELEMENT(MUX8),
#endif
    AT_CLIENT_CFG_ELEMENT(APP),
    AT_CLIENT_CFG_ELEMENT(APP1),
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    AT_CLIENT_CFG_ELEMENT(APP2),
    AT_CLIENT_CFG_ELEMENT(APP3),
    AT_CLIENT_CFG_ELEMENT(APP4),
    AT_CLIENT_CFG_ELEMENT(APP5),
    AT_CLIENT_CFG_ELEMENT(APP6),
    AT_CLIENT_CFG_ELEMENT(APP7),
    AT_CLIENT_CFG_ELEMENT(APP8),
    AT_CLIENT_CFG_ELEMENT(APP9),
    AT_CLIENT_CFG_ELEMENT(APP10),
    AT_CLIENT_CFG_ELEMENT(APP11),
    AT_CLIENT_CFG_ELEMENT(APP12),
    AT_CLIENT_CFG_ELEMENT(APP13),
    AT_CLIENT_CFG_ELEMENT(APP14),
    AT_CLIENT_CFG_ELEMENT(APP15),
    AT_CLIENT_CFG_ELEMENT(APP16),
    AT_CLIENT_CFG_ELEMENT(APP17),
    AT_CLIENT_CFG_ELEMENT(APP18),
    AT_CLIENT_CFG_ELEMENT(APP19),
    AT_CLIENT_CFG_ELEMENT(APP20),
    AT_CLIENT_CFG_ELEMENT(APP21),
    AT_CLIENT_CFG_ELEMENT(APP22),
    AT_CLIENT_CFG_ELEMENT(APP23),
    AT_CLIENT_CFG_ELEMENT(APP24),
    AT_CLIENT_CFG_ELEMENT(APP25),
    AT_CLIENT_CFG_ELEMENT(APP26),
#endif
};

const VOS_UINT8                         g_ucAtClientCfgMapTabLen = AT_ARRAY_SIZE(g_astAtClientCfgMapTbl);

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE))

VOS_UINT8    gucCurrEncVoiceDataWriteFileNum       = 0;

#ifdef DMT
TAF_CHAR    *g_pacCurrEncVoiceDataWriteFilePath[] =
            {
                "",
                "D:\\modem_log\\Ecc_test\\Encrypted_call_data1.txt",
                "D:\\modem_log\\Ecc_test\\Encrypted_call_data2.txt",
                "D:\\modem_log\\Ecc_test\\Encrypted_call_data3.txt",
                "D:\\modem_log\\Ecc_test\\Encrypted_call_data4.txt",
                "D:\\modem_log\\Ecc_test\\Encrypted_call_data5.txt"
            };
#else
TAF_CHAR    *g_pacCurrEncVoiceDataWriteFilePath[] =
            {
                "",
                "/modem_log/ECC_TEST/Encrypted_call_data1.txt",
                "/modem_log/ECC_TEST/Encrypted_call_data2.txt",
                "/modem_log/ECC_TEST/Encrypted_call_data3.txt",
                "/modem_log/ECC_TEST/Encrypted_call_data4.txt",
                "/modem_log/ECC_TEST/Encrypted_call_data5.txt"
            };
#endif

#endif



#if ( VOS_WIN32 == VOS_OS_VER )

AT_USIMM_FILE_NUM_TO_ID_STRU g_aenAtSimFileNumToIdTab[]=
{
    {0x6F07, USIMM_GSM_EFIMSI_ID        },
    {0x6F46, USIMM_GSM_EFSPN_ID         },
    {0x6F31, USIMM_GSM_EFHPLMN_ID       },
    {0x6F53, USIMM_GSM_EFLOCIGPRS_ID    },
    {0x6f61, USIMM_GSM_EFOPLMNWACT_ID   },
    {0x6f62, USIMM_GSM_EFHPLMNACT_ID    },
    {0x6F7E, USIMM_GSM_EFLOCI_ID        }
};

VOS_UINT32 g_aenAtSimFileNumToIdTabLen = AT_ARRAY_SIZE(g_aenAtSimFileNumToIdTab);

AT_USIMM_FILE_NUM_TO_ID_STRU g_aenAtUsimFileNumToIdTab[]=
{
    {0x3F00, USIMM_MF_ID                },
    {0x2F00, USIMM_DIR_ID               },
    {0x2FE2, USIMM_ICCID_ID             },
    {0x2F05, USIMM_PL_ID                },
    {0x2F06, USIMM_ARR_ID               },
    {0x7FFF, USIMM_USIM_ID              },
    {0x6F05, USIMM_USIM_EFLI_ID         },
    {0x6F06, USIMM_USIM_EFARR_ID        },
    {0x6F07, USIMM_USIM_EFIMSI_ID       },
    {0x6F08, USIMM_USIM_EFKEYS_ID       },
    {0x6F09, USIMM_USIM_EFKEYSPS_ID     },
    {0x6F2C, USIMM_USIM_EFDCK_ID        },
    {0x6F31, USIMM_USIM_EFHPPLMN_ID     },
    {0x6F32, USIMM_USIM_EFCNL_ID        },
    {0x6F37, USIMM_USIM_EFACMMAX_ID     },
    {0x6F38, USIMM_USIM_EFUST_ID        },
    {0x6F39, USIMM_USIM_EFACM_ID        },
    {0x6F3B, USIMM_USIM_EFFDN_ID        },
    {0x6F3C, USIMM_USIM_EFSMS_ID        },
    {0x6F3E, USIMM_USIM_EFGID1_ID       },
    {0x6F3F, USIMM_USIM_EFGID2_ID       },
    {0x6F40, USIMM_USIM_EFMSISDN_ID     },
    {0x6F41, USIMM_USIM_EFPUCT_ID       },
    {0x6F42, USIMM_USIM_EFSMSP_ID       },
    {0x6F43, USIMM_USIM_EFSMSS_ID       },
    {0x6F45, USIMM_USIM_EFCBMI_ID       },
    {0x6F46, USIMM_USIM_EFSPN_ID        },
    {0x6F47, USIMM_USIM_EFSMSR_ID       },
    {0x6F48, USIMM_USIM_EFCBMID_ID      },
    {0x6F49, USIMM_USIM_EFSDN_ID        },
    {0x6F4B, USIMM_USIM_EFEXT2_ID       },
    {0x6F4C, USIMM_USIM_EFEXT3_ID       },
    {0x6F4D, USIMM_USIM_EFBDN_ID        },
    {0x6F4E, USIMM_USIM_EFEXT5_ID       },
    {0x6F4F, USIMM_USIM_EFCCP2_ID       },
    {0x6F50, USIMM_USIM_EFCBMIR_ID      },
    {0x6F55, USIMM_USIM_EFEXT4_ID       },
    {0x6F56, USIMM_USIM_EFEST_ID        },
    {0x6F57, USIMM_USIM_EFACL_ID        },
    {0x6F58, USIMM_USIM_EFCMI_ID        },
    {0x6F5B, USIMM_USIM_EFSTART_HFN_ID  },
    {0x6F5C, USIMM_USIM_EFTHRESHOL_ID   },
    {0x6F60, USIMM_USIM_EFPLMNWACT_ID   },
    {0x6F61, USIMM_USIM_EFOPLMNWACT_ID  },
    {0x6F62, USIMM_USIM_EFHPLMNwACT_ID  },
    {0x6F73, USIMM_USIM_EFPSLOCI_ID     },
    {0x6F78, USIMM_USIM_EFACC_ID        },
    {0x6F7B, USIMM_USIM_EFFPLMN_ID      },
    {0x6F7E, USIMM_USIM_EFLOCI_ID       },
    {0x6F80, USIMM_USIM_EFICI_ID        },
    {0x6F81, USIMM_USIM_EFOCI_ID        },
    {0x6F82, USIMM_USIM_EFICT_ID        },
    {0x6F83, USIMM_USIM_EFOCT_ID        },
    {0x6FAD, USIMM_USIM_EFAD_ID         },
    {0x6FB1, USIMM_USIM_EFVGCS_ID       },
    {0x6FB2, USIMM_USIM_EFVGCSS_ID      },
    {0x6FB3, USIMM_USIM_EFVBS_ID        },
    {0x6FB4, USIMM_USIM_EFVBSS_ID       },
    {0x6FB5, USIMM_USIM_EFEMLPP_ID      },
    {0x6FB6, USIMM_USIM_EFAAEM_ID       },
    {0x6FB7, USIMM_USIM_EFECC_ID        },
    {0x6FC3, USIMM_USIM_EFHIDDENKEY_ID  },
    {0x6FC4, USIMM_USIM_EFNETPAR_ID     },
    {0x6FC5, USIMM_USIM_EFPNN_ID        },
    {0x6FC6, USIMM_USIM_EFOPL_ID        },
    {0x6FC7, USIMM_USIM_EFMBDN_ID       },
    {0x6FC8, USIMM_USIM_EFEXT6_ID       },
    {0x6FC9, USIMM_USIM_EFMBI_ID        },
    {0x6FCA, USIMM_USIM_EFMWIS_ID       },
    {0x6FCB, USIMM_USIM_EFCFIS_ID       },
    {0x6FCC, USIMM_USIM_EFEXT7_ID       },
    {0x6FCD, USIMM_USIM_EFSPDI_ID       },
    {0x6FCE, USIMM_USIM_EFMMSN_ID       },
    {0x6FCF, USIMM_USIM_EFEXT8_ID       },
    {0x6FD0, USIMM_USIM_EFMMSICP_ID     },
    {0x6FD1, USIMM_USIM_EFMMSUP_ID      },
    {0x6FD2, USIMM_USIM_EFMMSUCP_ID     },
    {0x6FD3, USIMM_USIM_EFNIA_ID        },
    {0x6FD4, USIMM_USIM_EFVGCSCA_ID     },
    {0x6FD5, USIMM_USIM_EFVBSCA_ID      },
    {0x6FD6, USIMM_USIM_EFGBAP_ID       },
    {0x6FD7, USIMM_USIM_EFMSK_ID        },
    {0x6FD8, USIMM_USIM_EFMUK_ID        },
    {0x6FD9, USIMM_USIM_EFEHPLMN_ID     },
    {0x6FDA, USIMM_USIM_EFGBANL_ID      },
    {0x6FDB, USIMM_USIM_EFEHPLMNPI_ID   },
    {0x6FDC, USIMM_USIM_EFLRPLMNSI_ID   },
    {0x6FDD, USIMM_USIM_EFNAFKCA_ID     },
    {0x6FDE, USIMM_USIM_EFSPNI_ID       },
    {0x6FDF, USIMM_USIM_EFPNNI_ID       },
    {0x6FE2, USIMM_USIM_EFNCPIP_ID      },
    {0x6FE3, USIMM_USIM_EFEPSLOCI_ID    },
    {0x6FE4, USIMM_USIM_EFEPSNSC_ID     },
    {0x6FE6, USIMM_USIM_EFUFC_ID        },
    {0x6FE7, USIMM_USIM_EFUICCIARI_ID   },
    {0x6FE8, USIMM_USIM_EFNASCONFIG_ID  },
    {0x6FEC, USIMM_USIM_EFPWS_ID        },
    {0x5F3A, USIMM_USIM_DFPHONEBOOK_ID  },
    {0x4F22, USIMM_USIM_EFPSC_ID        },
    {0x4F23, USIMM_USIM_EFCC_ID         },
    {0x4F24, USIMM_USIM_EFPUID_ID       },
    {0x4F30, USIMM_USIM_EFPBR_ID        },
    {0x5F3B, USIMM_USIM_DFGSM_ACCESS_ID },
    {0x4F20, USIMM_USIM_EFKC_ID         },
    {0x4F52, USIMM_USIM_EFKCGPRS_ID     },
    {0x4F63, USIMM_USIM_EFCPBCCH_ID     },
    {0x4F64, USIMM_USIM_EFINVSCAN_ID    },
    {0x5F3C, USIMM_USIM_DFMEXE_ID       },
    {0x4F40, USIMM_USIM_EFMexE_ST_ID    },
    {0x4F41, USIMM_USIM_EFORPK_ID       },
    {0x4F42, USIMM_USIM_EFARPK_ID       },
    {0x4F43, USIMM_USIM_EFTPRK_ID       },
    {0x5F70, USIMM_USIM_DFSOLSA_ID      },
    {0x4F30, USIMM_USIM_EFSAI_ID        },
    {0x4F31, USIMM_USIM_EFSLL_ID        },
    {0x5F40, USIMM_USIM_DFWLAN_ID       },
    {0x4F41, USIMM_USIM_EFPSEUDO_ID     },
    {0x4F42, USIMM_USIM_EFUPLMNWLAN_ID  },
    {0x4F43, USIMM_USIM_EF0PLMNWLAN_ID  },
    {0x4F44, USIMM_USIM_EFUWSIDL_ID     },
    {0x4F45, USIMM_USIM_EFOWSIDL_ID     },
    {0x4F46, USIMM_USIM_EFWRI_ID        },
    {0x4F47, USIMM_USIM_EFHWSIDL_ID     },
    {0x4F48, USIMM_USIM_EFWEHPLMNPI_ID  },
    {0x4F49, USIMM_USIM_EFWHPI_ID       },
    {0x4F4A, USIMM_USIM_EFWLRPLMN_ID    },
    {0x4F4B, USIMM_USIM_EFHPLMNDAI_ID   },
    {0x5F50, USIMM_USIM_DFHNB_ID        },
    {0x4F81, USIMM_USIM_EFACSGL_ID      },
    {0x4F82, USIMM_USIM_EFCSGT_ID       },
    {0x4F83, USIMM_USIM_EFHNBN_ID       },
    {0x4F84, USIMM_USIM_EFOCSGL_ID      },
    {0x4F85, USIMM_USIM_EFOCSGT_ID      },
    {0x4F86, USIMM_USIM_EFOHNBN_ID      },
    {0X6F30, USIMM_GSM_EFPLMNSEL_ID     },
    {0x6F53, USIMM_GSM_EFLOCIGPRS_ID    },
    {0x6F20, USIMM_GSM_EFKC_ID          },
    {0x6F52, USIMM_GSM_EFKCGPRS_ID      },
    {0x4F34, USIMM_ATTGSM_EFACTINGHPLMN_ID},
    {0x7F66, USIMM_ATTUSIM_ID},
    {0x6FD2, USIMM_ATTUSIM_EFTERMINALTBL_ID},
    {0x4F34, USIMM_ATTUSIM_EFACTINGHPLMN_ID},
    {0x4F36, USIMM_ATTUSIM_EFRATMODE_ID},
    {0x4F40, USIMM_ATTUSIM_EFPRMENABLE_ID},
    {0x4F41, USIMM_ATTUSIM_EFPRMPARA_ID},
    {0x4F42, USIMM_ATTUSIM_EFPRMOMCLR_ID},
    {0x4F43, USIMM_ATTUSIM_EFPRMOMC_ID},
    {0x4F44, USIMM_ATTUSIM_EFPRMVERINFO_ID}
};

VOS_UINT32 g_aenAtUsimFileNumToIdTabLen = AT_ARRAY_SIZE(g_aenAtUsimFileNumToIdTab);
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : AT_InitUsimStatus
 ��������  : ��ʼ��USIM״̬
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��

*****************************************************************************/
VOS_VOID AT_InitUsimStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    pstUsimInfoCtx->enCardStatus = USIMM_CARD_SERVIC_BUTT;
    pstUsimInfoCtx->enCardType   = USIMM_CARD_TYPE_BUTT;

    pstUsimInfoCtx->ucIMSILen    = 0;
    PS_MEM_SET(pstUsimInfoCtx->aucIMSI, 0, sizeof(pstUsimInfoCtx->aucIMSI));

    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitPlatformRatList
 ��������  : ��ʼ��ƽ̨����
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_InitPlatformRatList(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRat   = VOS_NULL_PTR;
    VOS_UINT8                          *pucIsCLMode = VOS_NULL_PTR;

    pstSptRat = AT_GetSptRatFromModemId(enModemId);

    /* Ĭ������µ���ֻ֧��GSM */
    pstSptRat->ucPlatformSptGsm        = VOS_TRUE;
    pstSptRat->ucPlatformSptWcdma      = VOS_FALSE;
    pstSptRat->ucPlatformSptLte        = VOS_FALSE;
    pstSptRat->ucPlatformSptUtralTDD   = VOS_FALSE;

    pucIsCLMode  = AT_GetModemCLModeCtxAddrFromModemId(enModemId);
    *pucIsCLMode = VOS_FALSE;

    return;

}

/*****************************************************************************
 �� �� ��  : AT_InitCommPsCtx
 ��������  : ��ʼ��PS�򹫹�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��6��7��
    ��    ��   : z00214637
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�

  3.��    ��   : 2015��3��30��
    ��    ��   : A00165503
    �޸�����   : SPE Project: SPE����
*****************************************************************************/
VOS_VOID AT_InitCommPsCtx(VOS_VOID)
{
    AT_COMM_PS_CTX_STRU                *pstPsCtx = VOS_NULL_PTR;

    PS_MEM_SET(&g_stAtNdisDhcpPara, 0, sizeof(g_stAtNdisDhcpPara));
    PS_MEM_SET(&g_stAtAppPdpEntity, 0, sizeof(g_stAtAppPdpEntity));

    PS_MEM_SET(g_abAtNdisDialUp, VOS_FALSE, sizeof(g_abAtNdisDialUp));
    PS_MEM_SET(g_abAtNdisDialDown, VOS_FALSE, sizeof(g_abAtNdisDialDown));

    pstPsCtx = AT_GetCommPsCtxAddr();

#if (FEATURE_ON == FEATURE_IPV6)
    pstPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;

    pstPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum = 0;

    pstPsCtx->ulIpv6AddrTestModeCfg = 0;
#endif

    pstPsCtx->ucSharePdpFlag = VOS_FALSE;

    pstPsCtx->lSpePort       = AT_INVALID_SPE_PORT;
    pstPsCtx->ulIpfPortFlg   = VOS_FALSE;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitCommPbCtx
 ��������  : ��ʼ���绰������������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_InitCommPbCtx(VOS_VOID)
{
    AT_COMM_PB_CTX_STRU                *pstCommPbCntxt = VOS_NULL_PTR;

    pstCommPbCntxt = AT_GetCommPbCtxAddr();

    pstCommPbCntxt->usCurrIdx       = 0;
    pstCommPbCntxt->usLastIdx       = 0;
    pstCommPbCntxt->ulSingleReadFlg = VOS_FALSE;
    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitModemCcCtx
 ��������  : ��ʼ��������ص�������
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��04��11��
    ��    ��   : l00198894
    �޸�����   : C50���ⵥͬ��
  3.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID AT_InitModemCcCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);

    pstCcCtx->ulCurIsExistCallFlag = VOS_FALSE;
    pstCcCtx->enCsErrCause         = TAF_CS_CAUSE_SUCCESS;

    /* �����Զ�Ӧ�������ʼ�� */
    PS_MEM_SET(&(pstCcCtx->stS0TimeInfo), 0, sizeof(pstCcCtx->stS0TimeInfo));

    PS_MEM_SET(&(pstCcCtx->stEconfInfo), 0, sizeof(pstCcCtx->stEconfInfo));

    for (i = 0; i < TAF_CALL_MAX_ECONF_CALLED_NUM; i++)
    {
        pstCcCtx->stEconfInfo.astCallInfo[i].enCallState = TAF_CALL_ECONF_STATE_BUTT;
        pstCcCtx->stEconfInfo.astCallInfo[i].enCause     = TAF_CS_CAUSE_SUCCESS;
    }

    /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitModemSsCtx
 ��������  : ��ʼ��SS��ص�������
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��

*****************************************************************************/
VOS_VOID AT_InitModemSsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */
    pstSsCtx->usUssdTransMode      = AT_USSD_TRAN_MODE;
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */
    pstSsCtx->enCModType           = MN_CALL_MODE_SINGLE;
    pstSsCtx->ucSalsType           = AT_SALS_DISABLE_TYPE;
    pstSsCtx->ucClipType           = AT_CLIP_DISABLE_TYPE;
    pstSsCtx->ucClirType           = AT_CLIR_AS_SUBSCRIPT;
    pstSsCtx->ucColpType           = AT_COLP_DISABLE_TYPE;
    pstSsCtx->ucCrcType            = AT_CRC_DISABLE_TYPE;
    pstSsCtx->ucCcwaType           = AT_CCWA_DISABLE_TYPE;

    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

    pstSsCtx->stCbstDataCfg.enSpeed    = MN_CALL_CSD_SPD_64K_MULTI;
    pstSsCtx->stCbstDataCfg.enName     = MN_CALL_CSD_NAME_SYNC_UDI;
    pstSsCtx->stCbstDataCfg.enConnElem = MN_CALL_CSD_CE_T;

    PS_MEM_SET(&(pstSsCtx->stCcugCfg), 0, sizeof(pstSsCtx->stCcugCfg));

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitModemSmsCtx
 ��������  : ��ʼ������Ϣ��ص�������
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��03��04��
    ��    ��   : f62575
    �޸�����   : DTS2014030801193, +CSMP��ʼֵ����Ч

*****************************************************************************/
VOS_VOID AT_InitModemSmsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

    pstSmsCtx->enCmgfMsgFormat      = AT_CMGF_MSG_FORMAT_PDU;
    pstSmsCtx->ucCsdhType           = AT_CSDH_NOT_SHOW_TYPE;
    pstSmsCtx->ucParaCmsr           = VOS_FALSE;
    pstSmsCtx->ucSmsAutoReply       = VOS_FALSE;
    pstSmsCtx->enCsmsMsgVersion     = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    /* ME�洢״̬��ʼ�� */
    pstSmsCtx->enMsgMeStorageStatus = MN_MSG_ME_STORAGE_DISABLE;
    pstSmsCtx->ucLocalStoreFlg      = VOS_TRUE;

    pstSmsCtx->stCnmiType.CnmiModeType    = AT_CNMI_MODE_BUFFER_TYPE;
    pstSmsCtx->stCnmiType.CnmiMtType      = AT_CNMI_MT_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiBmType      = AT_CNMI_BM_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiDsType      = AT_CNMI_DS_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiBfrType     = AT_CNMI_BFR_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpModeType = AT_CNMI_MODE_BUFFER_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpMtType   = AT_CNMI_MT_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpBmType   = AT_CNMI_BM_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpDsType   = AT_CNMI_DS_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpBfrType  = AT_CNMI_BFR_SEND_TYPE;

    /* �������ʼ�� */
    pstSmsCtx->stCgsmsSendDomain.ucActFlg     = VOS_FALSE;
    pstSmsCtx->stCgsmsSendDomain.enSendDomain = MN_MSG_SEND_DOMAIN_CS_PREFERRED;

    /* �ı�������ز�����ʼ�� */
    /*
    27005 3 Text Mode 3.1 Parameter Definitions
    Message Data Parameters
    <fo> depending on the command or result code: first octet of 3GPP TS 23.040
    [3] SMS-DELIVER, SMS-SUBMIT (default 17), SMS-STATUS-REPORT, or SMS-COMMAND
    (default 2) in integer format
    <vp> depending on SMS-SUBMIT <fo> setting: 3GPP TS 23.040 [3] TP-Validity-
    Period either in integer format (default 167), in time-string format (refer
    <dt>), or if EVPF is supported, in enhanced format (hexadecimal coded string
    with double quotes)
    */
    PS_MEM_SET(&(pstSmsCtx->stCscaCsmpInfo), 0, sizeof(pstSmsCtx->stCscaCsmpInfo));
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucParmInd = 0xff;
    pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod     =
    MN_MSG_VALID_PERIOD_RELATIVE;
    pstSmsCtx->stCscaCsmpInfo.stVp.u.ucOtherTime     = AT_CSMP_SUBMIT_VP_DEFAULT_VALUE;

    /* ���ż�״̬�������ɾ����д�����ͻ���մ洢���ʳ�ʼ�� */
    pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore     = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemReadorDelete          = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite           = MN_MSG_MEM_STORE_SIM;

    /* ���ż�״̬��������ϱ���ʽ��ʼ�� */
    pstSmsCtx->stCpmsInfo.stRcvPath.enRcvSmAct       = MN_MSG_RCVMSG_ACT_STORE;
    pstSmsCtx->stCpmsInfo.stRcvPath.enRcvStaRptAct   = MN_MSG_RCVMSG_ACT_STORE;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmsServVersion = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    /* ���Ż�״̬���治�洢ֱ���ϱ�PDU�Ļ����ʼ�� */
    PS_MEM_SET(&(pstSmsCtx->stSmtBuffer), 0x00, sizeof(pstSmsCtx->stSmtBuffer));

    /* �����Զ�Ӧ�𻺴�����ָ���ʼ�� */
    PS_MEM_SET(pstSmsCtx->astSmsMtBuffer,
               0x00,
               (sizeof(AT_SMS_MT_BUFFER_STRU) * AT_SMSMT_BUFFER_MAX));

    /* �㲥���ŵ�����ѡ��Ͳ��洢ֱ���ϱ�PDU�Ļ����ʼ�� */
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    PS_MEM_SET(&(pstSmsCtx->stCbsDcssInfo), 0x00, sizeof(pstSmsCtx->stCbsDcssInfo));
    PS_MEM_SET(&(pstSmsCtx->stCbmBuffer), 0x00, sizeof(pstSmsCtx->stCbmBuffer));
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitModemNetCtx
 ��������  : ��ʼ��������ص�������
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_InitModemNetCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */
    pstNetCtx->ucCerssiReportType      = AT_CERSSI_REPORT_TYPE_5DB_CHANGE_REPORT;
    pstNetCtx->ucCregType              = AT_CREG_RESULT_CODE_NOT_REPORT_TYPE;
    pstNetCtx->ucCgregType             = AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE;

    pstNetCtx->ucCopsFormatType         = AT_COPS_LONG_ALPH_TYPE;
    pstNetCtx->enPrefPlmnType           = MN_PH_PREF_PLMN_UPLMN;
    pstNetCtx->ucCpolFormatType         = AT_COPS_NUMERIC_TYPE;
    pstNetCtx->ucRoamFeature            = AT_ROAM_FEATURE_OFF;
    pstNetCtx->ucSpnType                = 0;
    pstNetCtx->ucCerssiMinTimerInterval = 0;
    pstNetCtx->enCalculateAntennaLevel  = AT_CMD_ANTENNA_LEVEL_0;
    PS_MEM_SET(pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel));
    PS_MEM_SET(&(pstNetCtx->stTimeInfo), 0, sizeof(pstNetCtx->stTimeInfo));

#if(FEATURE_ON == FEATURE_LTE)
    pstNetCtx->ucCeregType           = AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE;
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitModemAgpsCtx
 ��������  : ��ʼ��AGPS��ص�������
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_InitModemAgpsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromModemId(enModemId);

    PS_MEM_SET(&(pstAgpsCtx->stXml), 0, sizeof(pstAgpsCtx->stXml));

    pstAgpsCtx->enCposrReport = AT_CPOSR_DISABLE;
    pstAgpsCtx->enXcposrReport = AT_XCPOSR_DISABLE;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitModemPsCtx
 ��������  : ��ʼ��PS���modem��ص�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : DTS2013110900839: ���ӳ���IP��RABIDӳ��ĳ�ʼ��
*****************************************************************************/
VOS_VOID AT_InitModemPsCtx(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstPsCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* ��ʼ��CID�ͺ���ʵ��ӳ��� */
    for (ulCnt = 0; ulCnt <= TAF_MAX_CID; ulCnt++)
    {
        pstPsCtx->aucCidToIndexTbl[ulCnt] = AT_PS_CALL_INVALID_CALLID;
    }

    /* ��ʼ������ʵ�� */
    for (ulCnt = 0; ulCnt < AT_PS_MAX_CALL_NUM; ulCnt++)
    {
        pstPsCtx->astCallEntity[ulCnt].ulUsedFlg   = VOS_FALSE;

        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stUsrDialParam,
                   0x00, sizeof(AT_DIAL_PARAM_STRU));

        pstPsCtx->astCallEntity[ulCnt].ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
        pstPsCtx->astCallEntity[ulCnt].enIpv4State = AT_PDP_STATE_IDLE;

        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stIpv4DhcpInfo,
                   0x00, sizeof(AT_IPV4_DHCP_PARAM_STRU));

#if (FEATURE_ON == FEATURE_IPV6)
        pstPsCtx->astCallEntity[ulCnt].ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
        pstPsCtx->astCallEntity[ulCnt].enIpv6State = AT_PDP_STATE_IDLE;

        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stIpv6RaInfo,
                   0x00, sizeof(AT_IPV6_RA_INFO_STRU));
        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stIpv6DhcpInfo,
                   0x00, sizeof(AT_IPV6_DHCP_PARAM_STRU));
#endif
    }

    /* ��ʼ��CHDATA CFG */
    for (ulCnt = 0; ulCnt <= TAF_MAX_CID; ulCnt++)
    {
        pstPsCtx->astChannelCfg[ulCnt].ulUsed        = VOS_FALSE;
        pstPsCtx->astChannelCfg[ulCnt].ulRmNetId     = AT_PS_INVALID_RMNET_ID;
        pstPsCtx->astChannelCfg[ulCnt].ulRmNetActFlg = VOS_FALSE;
    }

    /* ��ʼ�������� */
    pstPsCtx->enPsErrCause = TAF_PS_CAUSE_SUCCESS;

    /* ��ʼ��IP��ַ��RABID��ӳ��� */
    PS_MEM_SET(pstPsCtx->aulIpAddrRabIdMap, 0x00, (sizeof(VOS_UINT32) * AT_PS_RABID_MAX_NUM));

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitClientConfiguration
 ��������  : ��ʼ��AT��Client������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II: �����ɺ���

*****************************************************************************/
VOS_VOID AT_InitClientConfiguration(VOS_VOID)
{
    VOS_UINT8                           i;
    AT_CLIENT_CTX_STRU                 *pstClientCtx = VOS_NULL_PTR;

    for (i = 0; i < AT_CLIENT_BUTT; i++)
    {
        pstClientCtx = AT_GetClientCtxAddr(i);

        pstClientCtx->stClientConfiguration.ucReportFlg = VOS_TRUE;
        pstClientCtx->stClientConfiguration.enModemId   = MODEM_ID_0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitResetCtx
 ��������  : ��ʼ��RNIC��λ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��222��
   ��    ��   : j00177245
   �޸�����   : ��������warning
*****************************************************************************/
VOS_VOID AT_InitResetCtx(VOS_VOID)
{
    AT_RESET_CTX_STRU                   *pstResetCtx = VOS_NULL_PTR;

    PS_MEM_SET(&g_stAtStatsInfo, 0, sizeof(g_stAtStatsInfo));

    pstResetCtx = AT_GetResetCtxAddr();

    pstResetCtx->hResetSem     = VOS_NULL_PTR;
    pstResetCtx->ulResetingFlag = VOS_FALSE;

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate( "AT", 0, VOS_SEMA4_FIFO, &pstResetCtx->hResetSem))
    {
        (VOS_VOID)vos_printf("Create AT acpu cnf sem failed!\r\n");
        AT_DBG_SET_SEM_INIT_FLAG(VOS_FALSE);
        AT_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);

        return;
    }
    else
    {
        AT_DBG_SAVE_BINARY_SEM_ID(pstResetCtx->hResetSem);
    }

    AT_DBG_SET_SEM_INIT_FLAG(VOS_TRUE);

    return;
}

#if (FEATURE_ON == FEATURE_AT_HSUART)
/*****************************************************************************
 �� �� ��  : AT_InitUartCtx
 ��������  : ��ʼ��Uart��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��20��
    ��    ��   : z00189113
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��3��12��
    ��    ��   : A00165503
    �޸�����   : DTS2015032409785: ����ˮ�߼�⹦��
*****************************************************************************/
VOS_VOID AT_InitUartCtx(VOS_VOID)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    pstUartCtx     = AT_GetUartCtxAddr();

    PS_MEM_SET(pstUartCtx, 0, sizeof(AT_UART_CTX_STRU));

    /* ��ʼ��UART��ά�ɲ���Ϣ */
    AT_InitHsUartStats();

    /* ��ʼ��UART�����ʣ�֡��ʽĬ��ֵ */
    pstUartCtx->stPhyConfig.enBaudRate            = AT_UART_DEFAULT_BAUDRATE;
    pstUartCtx->stPhyConfig.stFrame.enFormat      = AT_UART_DEFAULT_FORMAT;
    pstUartCtx->stPhyConfig.stFrame.enParity      = AT_UART_DEFAULT_PARITY;

    /* ��ʼ��UART LINE CTRLĬ��ֵ */
    pstUartCtx->stLineCtrl.enDcdMode              = AT_UART_DEFAULT_DCD_MODE;
    pstUartCtx->stLineCtrl.enDtrMode              = AT_UART_DEFAULT_DTR_MODE;
    pstUartCtx->stLineCtrl.enDsrMode              = AT_UART_DEFAULT_DSR_MODE;

    /* ��ʼ��FLOW CTRLĬ��ֵ */
    pstUartCtx->stFlowCtrl.enDceByDte             = AT_UART_DEFAULT_FC_DCE_BY_DTE;
    pstUartCtx->stFlowCtrl.enDteByDce             = AT_UART_DEFAULT_FC_DTE_BY_DCE;

    /* ��ʼ��RI�źŲ���Ĭ��ֵ */
    pstUartCtx->stRiConfig.ulSmsRiOnInterval      = AT_UART_DEFAULT_SMS_RI_ON_INTERVAL;
    pstUartCtx->stRiConfig.ulSmsRiOffInterval     = AT_UART_DEFAULT_SMS_RI_OFF_INTERVAL;
    pstUartCtx->stRiConfig.ulVoiceRiOnInterval    = AT_UART_DEFAULT_VOICE_RI_ON_INTERVAL;
    pstUartCtx->stRiConfig.ulVoiceRiOffInterval   = AT_UART_DEFAULT_VOICE_RI_OFF_INTERVAL;
    pstUartCtx->stRiConfig.ucVoiceRiCycleTimes    = AT_UART_DEFAULT_VOICE_RI_CYCLE_TIMES;

    /* ��ʼ��RI�ź�״̬ */
    pstUartCtx->stRiStateInfo.ulRunFlg            = VOS_FALSE;
    pstUartCtx->stRiStateInfo.enType              = AT_UART_RI_TYPE_BUTT;

    pstUartCtx->stRiStateInfo.hVoiceRiTmrHdl      = VOS_NULL_PTR;
    pstUartCtx->stRiStateInfo.enVoiceRiTmrStatus  = AT_TIMER_STATUS_STOP;
    pstUartCtx->stRiStateInfo.ulVoiceRiCycleCount = 0;

    for (ucCallId = 0; ucCallId <= MN_CALL_MAX_NUM; ucCallId++)
    {
        pstUartCtx->stRiStateInfo.aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_STOP;
    }

    pstUartCtx->stRiStateInfo.hSmsRiTmrHdl        = VOS_NULL_PTR;
    pstUartCtx->stRiStateInfo.ulSmsRiOutputCount  = 0;
    pstUartCtx->stRiStateInfo.enSmsRiTmrStatus    = AT_TIMER_STATUS_STOP;

    pstUartCtx->ulTxWmHighFlg                     = VOS_FALSE;
    pstUartCtx->pWmLowFunc                        = VOS_NULL_PTR;

    return;
}
#endif
/*****************************************************************************
 �� �� ��  : AT_InitCommCtx
 ��������  : ��ʼ��������������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��5��2��
    ��    ��   : l60609
    �޸�����   : IPv6&TAF/SM Project

  3.��    ��   : 2013��09��22��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ����UART�����ĳ�ʼ��

  4.��    ��   : 2015��3��12��
    ��    ��   : A00165503
    �޸�����   : DTS2015032409785: ����ˮ�߼�⹦��
*****************************************************************************/
VOS_VOID AT_InitCommCtx(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    /* Ĭ��Ӧ������ΪMP */
    pstCommCtx->ucSystemAppConfigAddr = SYSTEM_APP_MP;

    /* ��ʼ��MUX��ص������� */
    PS_MEM_SET(&(pstCommCtx->stMuxCtx), 0, sizeof(AT_MUX_CTX_STRU));

    /* ��ʼ��PS�򹫹��������� */
    AT_InitCommPsCtx();

    AT_InitCommPbCtx();

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitClientCtx
 ��������  : ��ʼ��ͨ����ص�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_InitClientCtx(VOS_VOID)
{
    AT_InitClientConfiguration();
}

/*****************************************************************************
 �� �� ��  : AT_InitModemCtx
 ��������  : ��ʼ��Modem��ص�������
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��27��
    ��    ��   : z00220246
    �޸�����   : ��ʼ��ƽ̨Ĭ�Ͻ��뼼��
  3.��    ��   : 2013��3��5��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
  4.��    ��   : 2013��5��2��
    ��    ��   : l60609
    �޸�����   : IPv6&TAF/SM Project
*****************************************************************************/
VOS_VOID AT_InitModemCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_InitUsimStatus(enModemId);

    AT_InitPlatformRatList(enModemId);

    AT_InitModemCcCtx(enModemId);

    AT_InitModemSsCtx(enModemId);

    AT_InitModemSmsCtx(enModemId);

    AT_InitModemNetCtx(enModemId);

    AT_InitModemAgpsCtx(enModemId);

    AT_InitModemPsCtx(enModemId);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitCtx
 ��������  : ��ʼ��AT��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II: �����ɺ���
  2.��    ��   : 2013��3��4��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_VOID AT_InitCtx(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    AT_InitCommCtx();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        AT_InitModemCtx(enModemId);
    }

    AT_InitClientCtx();

    return;
}

/*****************************************************************************
 �� �� ��  : AT_GetModemIDFromPid
 ��������  : ����PID�õ�ModemID
 �������  : VOS_UINT32
 �������  : ��
 �� �� ֵ  : MODEM_ID_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
MODEM_ID_ENUM_UINT16 AT_GetModemIDFromPid(VOS_UINT32 ulPid)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          ulModemPidTabLen;
    VOS_UINT32                          i;

    ulModemPidTabLen    = (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU));

    for (i = 0; i < ulModemPidTabLen; i++)
    {

        if (ulPid == g_astAtModemPidTab[i].ulModem0Pid)
        {
            return MODEM_ID_0;
        }

        if (ulPid == g_astAtModemPidTab[i].ulModem1Pid)
        {
            return MODEM_ID_1;
        }

#if (3 == MULTI_MODEM_NUMBER)
        if (ulPid == g_astAtModemPidTab[i].ulModem2Pid)
        {
            return MODEM_ID_2;
        }
#endif

    }

    return MODEM_ID_BUTT;
#else
    return MODEM_ID_0;
#endif
}


/*****************************************************************************
 �� �� ��  : AT_GetSystemAppConfigAddr
 ��������  : ��ȡAPP�������Ե�NV�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �������Ե���Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : s62952
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��5��
   ��    ��   : l60609
   �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT8* AT_GetSystemAppConfigAddr(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    return &(pstCommCtx->ucSystemAppConfigAddr);
}

/*****************************************************************************
 �� �� ��  : AT_GetResetCtxAddr
 ��������  : ��ȡ��λ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_RESET_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_RESET_CTX_STRU* AT_GetResetCtxAddr(VOS_VOID)
{
    return &(g_stAtResetCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetCommCtxAddr
 ��������  : ��ȡ����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_COMM_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_COMM_CTX_STRU* AT_GetCommCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetCommPsCtxAddr
 ��������  : ��ȡPS��Ĺ���������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_PS_COMM_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_COMM_PS_CTX_STRU* AT_GetCommPsCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stPsCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetCommPbCtxAddr
 ��������  : ��ȡ�绰������������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_COMM_PB_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_COMM_PB_CTX_STRU* AT_GetCommPbCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stCommPbCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemCtxAddr
 ��������  : ��ȡModem��ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_CTX_STRU* AT_GetModemCtxAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId]);
}

/*****************************************************************************
 �� �� ��  : AT_GetUsimInfoCtxFromModemId
 ��������  : ����MODEM ID��ȡ��״̬
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_USIM_INFO_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_USIM_INFO_CTX_STRU* AT_GetUsimInfoCtxFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stAtUsimInfoCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetSptRatFromModemId
 ��������  : ����MODEM ID��ȡƽ̨����
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_SPT_RAT_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_SPT_RAT_STRU* AT_GetSptRatFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPlatformCapList.stPlatformRatList);
}

/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */

/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */

/*****************************************************************************
 �� �� ��  : AT_GetModemCcCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡ������ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_CC_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stCcCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemCcCtxAddrFromClientId
 ��������  : ����ClientId���غ�����ص�������
 �������  : VOS_UINT16                          usClientId
 �������  : ��
 �� �� ֵ  : AT_MODEM_CC_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemCcCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stCcCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemSsCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡSS��ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_SS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stSsCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemSsCtxAddrFromClientId
 ��������  : ����ClientId���ز���ҵ����ص�������
 �������  : VOS_UINT16                          usClientId
 �������  : ��
 �� �� ֵ  : AT_MODEM_SS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemSsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stSsCtx);
}
/*****************************************************************************
 �� �� ��  : AT_GetModemSmsCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡ������ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_SMS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stSmsCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemSmsCtxAddrFromClientId
 ��������  : ����ClientId��ȡ����Ϣ��ص�������
 �������  : VOS_UINT16                          usClientId
 �������  : ��
 �� �� ֵ  : AT_MODEM_SMS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��22��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemSmsCtxAddrFromClientId: Get modem id fail");
    }

    return &(g_astAtModemCtx[enModemId].stSmsCtx);
}


/*****************************************************************************
 �� �� ��  : AT_GetModemNetCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡ������ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_NET_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stNetCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemNetCtxAddrFromClientId
 ��������  : ����ClientId��ȡ������ص�������
 �������  : VOS_UINT16                          usClientId
 �������  : ��
 �� �� ֵ  : AT_MODEM_NET_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��22��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemNetCtxAddrFromClientId: Get modem id fail");
    }

    return &(g_astAtModemCtx[enModemId].stNetCtx);
}
/*****************************************************************************
 �� �� ��  : AT_GetModemAgpsCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡAGPS��ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_AGPS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stAgpsCtx);
}
/*****************************************************************************
 �� �� ��  : AT_GetModemAgpsCtxAddrFromClientId
 ��������  : ����ClientIdֵ��ȡAGPS��ص�������
 �������  : VOS_UINT16                          usClientId
 �������  : ��
 �� �� ֵ  : AT_MODEM_AGPS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemAgpsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stAgpsCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemPsCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡPS��MODEM��ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_PS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPsCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemPsCtxAddrFromClientId
 ��������  : ����CLIENT ID��ȡPS��MODEM��ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_PS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemPsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stPsCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetClientCtxAddr
 ��������  : ��ȡ�˿���ص�������
 �������  : AT_CLIENT_ID_ENUM_UINT16            enClientId
 �������  : ��
 �� �� ֵ  : AT_CLIENT_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_CLIENT_CTX_STRU* AT_GetClientCtxAddr(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
)
{
    return &(g_astAtClientCtx[enClientId]);
}

/*****************************************************************************
 �� �� ��  : AT_GetModemIdFromClient
 ��������  : ����AT CLIENT INDEX��ȡ������MODEM ID
 �������  : VOS_UINT16                          usClientId
             MODEM_ID_ENUM_UINT16               *pModemId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��03��13��
    ��    ��   : f00179208
    �޸�����   : DSDA PHASE III:�����쳣����

  3.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 AT_GetModemIdFromClient(
    VOS_UINT16                          usClientId,
    MODEM_ID_ENUM_UINT16               *pModemId
)
{
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    /* �ж��Ƿ���MODEM0�㲥��client index */
    if ((AT_BROADCAST_CLIENT_INDEX_MODEM_0 == usClientId)
     || (AT_BROADCAST_CLIENT_ID_MODEM_0 == usClientId))
    {
        *pModemId = MODEM_ID_0;
    }
    /* �ж��Ƿ���MODEM1�㲥��client index */
    else if ((AT_BROADCAST_CLIENT_INDEX_MODEM_1 == usClientId)
          || (AT_BROADCAST_CLIENT_ID_MODEM_1 == usClientId))
    {
        *pModemId = MODEM_ID_1;
    }
    /* �ж��Ƿ���MODEM2�㲥��client index */
    else if ((AT_BROADCAST_CLIENT_INDEX_MODEM_2 == usClientId)
          || (AT_BROADCAST_CLIENT_ID_MODEM_2 == usClientId))
    {
        *pModemId = MODEM_ID_2;
    }
    /* �ǹ㲥client index */
    else
    {
        /* client index ��Ч��ֱ�ӷ��� */
        if (usClientId >= AT_CLIENT_BUTT)
        {
            return VOS_ERR;
        }

        pstAtClientCtx = AT_GetClientCtxAddr(usClientId);

        *pModemId = pstAtClientCtx->stClientConfiguration.enModemId;
    }

    /* �ڵ�����ʱ��NV���������MODEMIDΪMODEM1ʱ���ᷢ���ڴ�Խ�磬�˴������쳣���� */
    if (*pModemId >= MODEM_ID_BUTT)
    {
        AT_ERR_LOG("AT_GetModemIdFromClient: modem id is invalid");

        *pModemId = MODEM_ID_0;
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_GetDestPid
 ��������  : ��ȡʵ�ʷ��͵�PID
 �������  : MN_CLIENT_ID_T                      usClientId
             VOS_UINT32                          ulRcvPid
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��17��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          i;

    enModemId = MODEM_ID_0;

    /* ��ȡclient id��Ӧ��Modem Id */
    ulRslt = AT_GetModemIdFromClient(usClientId, &enModemId);

    /* modem 1��ulRcvPid��Ӧ��pid */
    if ((VOS_OK == ulRslt)
     && (MODEM_ID_0 != enModemId))
    {
        for (i = 0; i < (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulRcvPid != g_astAtModemPidTab[i].ulModem0Pid)
            {
                continue;
            }

            if (MODEM_ID_1 == enModemId)
            {
                return g_astAtModemPidTab[i].ulModem1Pid;
            }

            if (MODEM_ID_2 == enModemId)
            {
                return g_astAtModemPidTab[i].ulModem2Pid;
            }
        }

        /* ��������Ҳ�����Ӧ��PIDӦ��ʱ������ */
        if (i >= (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU)))
        {
            (VOS_VOID)vos_printf("AT_GetDestPid: usClientId is %d, ulRcvPid is %d no modem1 pid. \r\n", usClientId, ulRcvPid);
        }
    }
#endif

    return ulRcvPid;
}

/*****************************************************************************
 �� �� ��  : AT_GetRealClientId
 ��������  : ��ȡ��ӦModem��CilentId
 �������  : MN_CLIENT_ID_T                      usClientId
             VOS_UINT32                          ulPid
 �������  : ��
 �� �� ֵ  : MN_CLIENT_ID_T
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��1��
    ��    ��   : L60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��28��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
MN_CLIENT_ID_T AT_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    /* ����Pid��ֵ��ȡModemId */
    enModemId = AT_GetModemIDFromPid(ulPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        return usClientId;
    }

    /* ����ModemId��ȡClientId */
    if (MODEM_ID_0 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_0);
    }
    else if (MODEM_ID_1 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_1);
    }
    else
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_2);
    }
}

/*****************************************************************************
 �� �� ��  : AT_IsModemSupportLte
 ��������  : �жϵ�ǰModem�Ƿ�֧��ĳ�ֽ��뼼��
 �������  : MODEM_ID_ENUM_UINT16                enModemId
             TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��27��
    ��    ��   : z00220246
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_UINT8 AT_IsModemSupportRat(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat
)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRatList = VOS_NULL_PTR;

    pstSptRatList = AT_GetSptRatFromModemId(enModemId);
    if (TAF_MMA_RAT_LTE == enRat)
    {
        return pstSptRatList->ucPlatformSptLte;
    }
    if (TAF_MMA_RAT_WCDMA == enRat)
    {
        if ((VOS_TRUE == pstSptRatList->ucPlatformSptWcdma)
         || (VOS_TRUE == pstSptRatList->ucPlatformSptUtralTDD))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }
    if (TAF_MMA_RAT_GSM == enRat)
    {
        return pstSptRatList->ucPlatformSptGsm;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_IsModemSupportUtralTDDRat
 ��������  : �жϵ�ǰModem�Ƿ�֧��UTRALTDD
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��22��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_IsModemSupportUtralTDDRat(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRatList = VOS_NULL_PTR;

    pstSptRatList = AT_GetSptRatFromModemId(enModemId);

    return pstSptRatList->ucPlatformSptUtralTDD;
}


/*****************************************************************************
 �� �� ��  : AT_SetCsCallErrCause
 ��������  : ����CS����д�����
 �������  : VOS_UINT16                          usClientId
             TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_SetCsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(usClientId);

    pstCcCtx->enCsErrCause = enCsErrCause;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_GetCsCallErrCause
 ��������  : ��ȡCS����д�����
 �������  : VOS_UINT16                          usClientId
 �������  : ��
 �� �� ֵ  : TAF_CS_CAUSE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 AT_GetCsCallErrCause(
    VOS_UINT16                          usClientId
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(usClientId);

    return pstCcCtx->enCsErrCause;
}


/*****************************************************************************
 �� �� ��  : AT_GetAbortCmdPara
 ��������  : ��ȡAT�������Ĳ���
 �������  : ��
 �� �� ֵ  : AT�������Ĳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��22��
    ��    ��   : lijun 00171473
    �޸�����   : �����ɺ��� for V7R1C50_At_Abort

  2.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : ��װ��Ͻṹ��
*****************************************************************************/
AT_ABORT_CMD_PARA_STRU* AT_GetAbortCmdPara(VOS_VOID)
{
    return &(gstAtAbortCmdCtx.stAtAbortCmdPara);
}

/*****************************************************************************
 �� �� ��  : AT_GetAbortRspStr
 ��������  : ��ȡAT��ϵķ��ؽ���ַ���
 �������  : ��
 �� �� ֵ  : AT��ϵķ��ؽ���ַ���, ����\0���������ַ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��22��
    ��    ��   : lijun 00171473
    �޸�����   : �����ɺ��� for V7R1C50_At_Abort

  2.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : ��װ��Ͻṹ��
*****************************************************************************/
VOS_UINT8* AT_GetAbortRspStr(VOS_VOID)
{
    return (gstAtAbortCmdCtx.stAtAbortCmdPara.aucAbortAtRspStr);
}


/*****************************************************************************
 �� �� ��  : AT_GetSsCustomizePara
 ��������  : ��ȡָ��SS ҵ��Ķ���״̬
 �������  : AT_SS_CUSTOMIZE_TYPE_UINT8 enSsCustomizeType   ҵ������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
                VOS_FALSE       ҵ��δ����
                VOS_TRUE        ҵ���Ѷ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��01��24��
    ��    ��   : f62575
    �޸�����   : DTS2013012408620, ֧��SS��ѯ�����������SS-STATUS����

*****************************************************************************/
VOS_UINT32 AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_TYPE_UINT8 enSsCustomizeType)
{
    VOS_UINT8                           ucMask;

    if (VOS_TRUE != g_stAtSsCustomizePara.ucStatus)
    {
        return VOS_FALSE;
    }

    ucMask = (VOS_UINT8)(AT_SS_CUSTOMIZE_SERVICE_MASK << enSsCustomizeType);
    if (0 != (g_stAtSsCustomizePara.ucSsCmdCustomize & ucMask))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : AT_GetResetSem
 ��������  : ��ȡAT��λ�ź���
 �������  : ��
 �������  : ��
 �� �� ֵ  : AT��λ�ź���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_SEM AT_GetResetSem(VOS_VOID)
{
    return g_stAtResetCtx.hResetSem;
}

/*****************************************************************************
 �� �� ��  : AT_GetResetFlag
 ��������  : ��ȡAT��λ��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : AT��λ��־
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_GetResetFlag(VOS_VOID)
{
    return g_stAtResetCtx.ulResetingFlag;
}

/*****************************************************************************
 �� �� ��  : AT_SetResetFlag
 ��������  : ����AT��λ��־
 �������  : ��λ״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetResetFlag(VOS_UINT32 ulFlag)
{
    g_stAtResetCtx.ulResetingFlag = ulFlag;
    return;
}


/*****************************************************************************
 �� �� ��  : AT_GetModemMtInfoCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡAGPS��ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_MT_INFO_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��30��
    ��    ��   : z60575
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_MODEM_MT_INFO_CTX_STRU* AT_GetModemMtInfoCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stMtInfoCtx);
}

/*****************************************************************************
 �� �� ��  : AT_InitTraceMsgTab
 ��������  : ��ʼ������ʹ�õĶ˿ں�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��07��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_InitTraceMsgTab(VOS_VOID)
{
    PS_MEM_SET(g_stAtTraceMsgIdTab, 0xFF, sizeof(g_stAtTraceMsgIdTab));
}

/*****************************************************************************
 �� �� ��  : AT_GetResultMsgID
 ��������  : ��ȡ Result MSG ID
 �������  : ucIndex   -- �˿�client ID ��ȷ���ɵ����߱�֤
 �������  : ��
 �� �� ֵ  : AT_INTER_MSG_ID_ENUM_UINT32 -- result msg id
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��07��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetResultMsgID(VOS_UINT8 ucIndex)
{
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgID;

    if (AT_BROADCAST_CLIENT_INDEX_MODEM_0 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_0;
    }
    else if (AT_BROADCAST_CLIENT_INDEX_MODEM_1 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_1;
    }
    else if (AT_BROADCAST_CLIENT_INDEX_MODEM_2 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_2;
    }
    else
    {
        enResultMsgID = g_stAtTraceMsgIdTab[ucIndex].enResultMsgID;
    }

    return enResultMsgID;
}

/*****************************************************************************
 �� �� ��  : AT_GetCmdMsgID
 ��������  : ��ȡ CMD MSG ID
 �������  : ucIndex   -- �˿�client ID ��ȷ���ɵ����߱�֤
 �������  : ��
 �� �� ֵ  : AT_INTER_MSG_ID_ENUM_UINT32 --cmd msg ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��07��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetCmdMsgID(VOS_UINT8 ucIndex)
{
    return g_stAtTraceMsgIdTab[ucIndex].enCmdMsgID;
}

/*****************************************************************************
 �� �� ��  : AT_ConfigTraceMsg
 ��������  : ���ö˿���������Ϣӳ��
 �������  : ucIndex       - �˿�����
             enCmdMsgId    - �˿�������Ϣ
             enResultMsgId - �˿�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��07��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ConfigTraceMsg(
    VOS_UINT8                           ucIndex,
    AT_INTER_MSG_ID_ENUM_UINT32         enCmdMsgId,
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgId
)
{
    g_stAtTraceMsgIdTab[ucIndex].enCmdMsgID = enCmdMsgId;
    g_stAtTraceMsgIdTab[ucIndex].enResultMsgID = enResultMsgId;

    return;
}

/*****************************************************************************
 �� �� ��  : At_SetAtCmdAbortTickInfo
 ��������  : ��������AT����ʱ��tickֵ��ʹ��ֵ
 �������  : ucIndex   : ͨ������
             ulTick    : tickֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID At_SetAtCmdAbortTickInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulTick
)
{
    gstAtAbortCmdCtx.stCmdAbortTick.ulAtSetTick[ucIndex]    = ulTick;

    return;
}

/*****************************************************************************
 �� �� ��  : At_GetAtCmdAbortTickInfo
 ��������  : ��ȡ���������AT����ʱ��Tickֵ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : AT_CMD_ABORT_TICK_INFO ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_CMD_ABORT_TICK_INFO* At_GetAtCmdAbortTickInfo(VOS_VOID)
{
    return &(gstAtAbortCmdCtx.stCmdAbortTick);
}

/*****************************************************************************
 �� �� ��  : At_GetAtCmdAnyAbortFlg
 ��������  : ��ȡ�����ַ���ϱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���������ϱ�Ǳ�ʾ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 At_GetAtCmdAnyAbortFlg(VOS_VOID)
{
    return (gstAtAbortCmdCtx.stAtAbortCmdPara.ucAnyAbortFlg);
}

/*****************************************************************************
 �� �� ��  : At_SetAtCmdAnyAbortFlg
 ��������  : ���������ַ���ϱ��
 �������  : ucFlg    : ��ϱ�־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID At_SetAtCmdAnyAbortFlg(
    VOS_UINT8                           ucFlg
)
{
    gstAtAbortCmdCtx.stAtAbortCmdPara.ucAnyAbortFlg = ucFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_GetUartCtxAddr
 ��������  : ��ȡUART�ڹ���������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_COMM_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_UART_CTX_STRU* AT_GetUartCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stUartCtx);
}

/*****************************************************************************
 �� �� ��  : AT_GetUartRiCfgInfo
 ��������  : ��ȡUART��������������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_UART_PHY_CFG_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_UART_PHY_CFG_STRU* AT_GetUartPhyCfgInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stPhyConfig);
}

/*****************************************************************************
 �� �� ��  : AT_GetUartLineCtrlInfo
 ��������  : ��ȡUART�˿ڹܽ��źſ�����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_UART_LINE_CTRL_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_UART_LINE_CTRL_STRU* AT_GetUartLineCtrlInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stLineCtrl);
}

/*****************************************************************************
 �� �� ��  : AT_GetUartFlowCtrlInfo
 ��������  : ��ȡUART�˿�����������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_UART_FLOW_CTRL_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_UART_FLOW_CTRL_STRU* AT_GetUartFlowCtrlInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stFlowCtrl);
}

/*****************************************************************************
 �� �� ��  : AT_GetUartRiCfgInfo
 ��������  : ��ȡUART�˿�RING���ź�������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_UART_RI_CFG_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_UART_RI_CFG_STRU* AT_GetUartRiCfgInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stRiConfig);
}

/*****************************************************************************
 �� �� ��  : AT_GetUartRiStateInfo
 ��������  : ��ȡUART�˿�RING���ź�״̬��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_UART_RI_STATE_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_UART_RI_STATE_INFO_STRU* AT_GetUartRiStateInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stRiStateInfo);
}

/*****************************************************************************
 �� �� ��  : AT_GetPortBuffCfgInfo
 ��������  : ��ȡ�Ѿ�ʹ�ö˿ڼ�¼��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_COMM_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_PORT_BUFF_CFG_STRU* AT_GetPortBuffCfgInfo(VOS_VOID)
{
    return &(AT_GetCommCtxAddr()->stPortBuffCfg);
}

/*****************************************************************************
 �� �� ��  : AT_GetPortBuffCfg
 ��������  : ��ȡ���Ż���NV����
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : AT_SMS_BUFF_CFG_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
*****************************************************************************/
AT_PORT_BUFF_CFG_ENUM_UINT8  AT_GetPortBuffCfg(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    return pstCommCtx->stPortBuffCfg.enSmsBuffCfg;
}

/*****************************************************************************
 �� �� ��  : AT_InitPortBuffCfg
 ��������  : ��ʼ����¼ʹ��clientID�ı�
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
*****************************************************************************/
VOS_VOID AT_InitPortBuffCfg(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstUsedClientIdTab = VOS_NULL_PTR;

    pstUsedClientIdTab = AT_GetPortBuffCfgInfo();

    PS_MEM_SET(pstUsedClientIdTab, 0xFF, sizeof(AT_PORT_BUFF_CFG_STRU));

    pstUsedClientIdTab->ucNum = 0;
}

/*****************************************************************************
 �� �� ��  : AT_AddUsedClientId2Tab
 ��������  : ��ʹ�õ�clientID��¼��ȫ�ֱ�����
 �������  : usClientId
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III

  2.��    ��   : 2014��2��14��
    ��    ��   : j00174725
    �޸�����   : TQE
*****************************************************************************/
VOS_VOID AT_AddUsedClientId2Tab(VOS_UINT16 usClientId)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    if (usClientId >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    /*  �ų��ڲ�ͨ�� */
    if ( (usClientId >= AT_MIN_APP_CLIENT_ID)
      && (usClientId <= AT_MAX_APP_CLIENT_ID))
    {
        return;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    if (AT_CLIENT_ID_SOCK == usClientId)
    {
        return;
    }
#endif

    if (pstPortBuffCfg->ucNum >= AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM -1;
    }

    /* ѭ�������Ƿ��Ѿ���¼�� */
    for (ucIndex = 0; ucIndex < pstPortBuffCfg->ucNum; ucIndex++)
    {
        if (usClientId == pstPortBuffCfg->ulUsedClientID[ucIndex])
        {
            return;
        }
    }

    /* ���û�м�¼�������¼����� */
    if (ucIndex == pstPortBuffCfg->ucNum)
    {
        pstPortBuffCfg->ulUsedClientID[ucIndex] = (VOS_UINT32)usClientId;
        pstPortBuffCfg->ucNum++;
    }
}

/*****************************************************************************
 �� �� ��  : AT_RmUsedClientIdFromTab
 ��������  : ��ClientID��ȫ�ֱ�����ɾ��
 �������  : usClientId
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
*****************************************************************************/
VOS_VOID AT_RmUsedClientIdFromTab(VOS_UINT16 usClientId)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    if (pstPortBuffCfg->ucNum > AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM;
    }

    /* ѭ�������Ƿ��Ѿ���¼�� */
    for (ulIndex = 0; ulIndex < pstPortBuffCfg->ucNum; ulIndex++)
    {
        if (usClientId == pstPortBuffCfg->ulUsedClientID[ulIndex])
        {
            break;
        }
    }

    /* ���û�м�¼����ֱ���˳� */
    if (ulIndex == pstPortBuffCfg->ucNum)
    {
        return;
    }

    /* ����ҵ���ɾ����Ӧ��client */
    if (ulIndex == pstPortBuffCfg->ucNum - 1)
    {
        pstPortBuffCfg->ucNum--;
        pstPortBuffCfg->ulUsedClientID[ulIndex] = VOS_NULL_DWORD;

    }
    else
    {
        pstPortBuffCfg->ulUsedClientID[ulIndex] =
                    pstPortBuffCfg->ulUsedClientID[pstPortBuffCfg->ucNum - 1];
        pstPortBuffCfg->ulUsedClientID[pstPortBuffCfg->ucNum - 1] = VOS_NULL_DWORD;
        pstPortBuffCfg->ucNum--;
    }
}


/*****************************************************************************
 �� �� ��  : AT_GetClientConfig
 ��������  : ��ȡClientConfig������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_CLIENT_CONFIGURATION_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��25��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_CLIENT_CONFIGURATION_STRU* AT_GetClientConfig(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
)
{
    return &(AT_GetClientCtxAddr(enClientId)->stClientConfiguration);
}

/*****************************************************************************
 �� �� ��  : AT_GetClientCfgMapTbl
 ��������  : ��ȡCLIENT CFG TAB������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_CLIENT_CFG_MAP_TAB_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��25��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_CLIENT_CFG_MAP_TAB_STRU* AT_GetClientCfgMapTbl(VOS_UINT8 ucIndex)
{
    return &(g_astAtClientCfgMapTbl[ucIndex]);
}
/*****************************************************************************
 �� �� ��  : AT_GetSmsFilterEnableFlg
 ��������  : ��ȡ����NV����������Ϣ���Ƿ���LOG�ı�ʶ
 �������  : ucIndex    : ClientId
 �������  : VOS_UINT32 : ��ʶ��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��25��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_GetSmsFilterEnableFlg(
    VOS_UINT8                           ucIndex
)
{
    return AT_GetModemSmsCtxAddrFromClientId(ucIndex)->stSmsFilterCfg.ucSmsFilterEnableFlg;
}

/*****************************************************************************
 �� �� ��  : AT_IsSupportReleaseRst
 ��������  : �ж��Ƿ�֧��Э��Rx�汾
 �������  : ulReleaseType
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��20��
   ��    ��   : w00316404
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 AT_IsSupportReleaseRst(VOS_UINT32 ulReleaseType)
{
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == g_stReleaseInfo.bitOpReleaseName)
    {
        if (ulReleaseType <= g_stReleaseInfo.ulReleaseName)
        {
            return VOS_TRUE;
        }
    }
#endif
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_GetModemCLModeCtxAddrFromModemId
 ��������  : ����MODEM ID��ȡCL mode��ص�������
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : ��
 �� �� ֵ  : AT_MODEM_SMS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��27��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* AT_GetModemCLModeCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPlatformCapList.ucIsCLMode);
}
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif