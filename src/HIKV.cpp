//#include "HIKV.h"
//namespace  HK {
/////等待键盘触发
//void WaitForKeyPress(void)
//{
//    while(!_kbhit())
//    {
//        Sleep(10);
//    }
//    _getch();
//}

/////MV_CC_DEVICE_INFO 获取相机物理参数
//bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
//{
//    if (NULL == pstMVDevInfo)
//    {
//        printf("The Pointer of pstMVDevInfo is NULL!\n");
//        return false;
//    }
//    if (pstMVDevInfo->nTLayerType == MV_CAMERALINK_DEVICE)
//    {
//        printf("chPortID: [%s]\n", pstMVDevInfo->SpecialInfo.stCamLInfo.chPortID);
//        printf("chModelName: [%s]\n", pstMVDevInfo->SpecialInfo.stCamLInfo.chModelName);
//        printf("chFamilyName: [%s]\n", pstMVDevInfo->SpecialInfo.stCamLInfo.chFamilyName);
//        printf("chDeviceVersion: [%s]\n", pstMVDevInfo->SpecialInfo.stCamLInfo.chDeviceVersion);
//        printf("chManufacturerName: [%s]\n", pstMVDevInfo->SpecialInfo.stCamLInfo.chManufacturerName);
//        printf("Serial Number: [%s]\n", pstMVDevInfo->SpecialInfo.stCamLInfo.chSerialNumber);
//    }
//    else
//    {
//        printf("Not support.\n");
//    }

//    return true;
//}

//// Get the value of various feature nodes
/////获取相机内部参数
//int GetParameters(void* handle)
//{
//    if ( NULL == handle )
//    {
//        return MV_E_PARAMETER;
//    }

//    int nRet = MV_OK;

//    // Get value of Integer nodes. Such as, 'width' etc.
//    MVCC_INTVALUE stIntVal;
//    memset(&stIntVal, 0, sizeof(MVCC_INTVALUE));
//    nRet = MV_CC_GetIntValue(handle, "Width", &stIntVal);
//    if (MV_OK != nRet)
//    {
//        printf("Get Width fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }
//    printf("Current Width [%d]\n", stIntVal.nCurValue);

//    // Get value of Enum nodes. Such as, 'TriggerMode' etc.
//    MVCC_ENUMVALUE stEnumVal;
//    memset(&stEnumVal, 0, sizeof(MVCC_ENUMVALUE));

//    nRet = MV_CC_GetEnumValue(handle, "TriggerMode", &stEnumVal);
//    if (MV_OK != nRet)
//    {
//        printf("Get Trigger Mode fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }
//    printf("Current TriggerMode [%d]\n", stEnumVal.nCurValue);

//    // Get value of float nodes. Such as, 'AcquisitionFrameRate' etc.
//    MVCC_FLOATVALUE stFloatVal;
//    memset(&stFloatVal, 0, sizeof(MVCC_FLOATVALUE));
//    nRet = MV_CC_GetFloatValue(handle, "AcquisitionFrameRate", &stFloatVal);
//    if (MV_OK != nRet)
//    {
//        printf("Get AcquisitionFrameRate fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }
//    printf("Current AcquisitionFrameRate [%f] Fps\n", stFloatVal.fCurValue);

//    // Get value of bool nodes. Such as, 'AcquisitionFrameRateEnable' etc.
//    bool bBoolVal = false;
//    nRet = MV_CC_GetBoolValue(handle, "AcquisitionFrameRateEnable", &bBoolVal);
//    if (MV_OK != nRet)
//    {
//        printf("Get AcquisitionFrameRateEnable fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }
//    printf("Current AcquisitionFrameRateEnable [%d]\n", bBoolVal);

//    // Get value of String nodes. Such as, 'DeviceUserID' etc.
//    MVCC_STRINGVALUE stStrVal;
//    memset(&stStrVal, 0, sizeof(MVCC_STRINGVALUE));
//    nRet = MV_CC_GetStringValue(handle, "DeviceUserID", &stStrVal);
//    if (MV_OK != nRet)
//    {
//        printf("Get DeviceUserID fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }
//    printf("Current DeviceUserID [%s]\n", stStrVal.chCurValue);

//    return MV_OK;
//}

//// Set the value of various feature nodes
/////设置相机参数
//int SetParameters(void* handle)
//{
//    if ( NULL == handle )
//    {
//        return MV_E_PARAMETER;
//    }

//    int nRet = MV_OK;

//    // Set value of Integer nodes. Such as, 'width' etc.
//    nRet = MV_CC_SetIntValue(handle, "Width", 200);
//    if (MV_OK != nRet)
//    {
//        printf("Set Width fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }

//    // Set value of float nodes. Such as, 'AcquisitionFrameRate' etc.
//    nRet = MV_CC_SetFloatValue(handle, "AcquisitionFrameRate", 8.8f);
//    if (MV_OK != nRet)
//    {
//        printf("Set AcquisitionFrameRate fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }

//    // Set value of bool nodes. Such as, 'AcquisitionFrameRateEnable' etc.
//    nRet = MV_CC_SetBoolValue(handle, "AcquisitionFrameRateEnable", true);
//    if (MV_OK != nRet)
//    {
//        printf("Set AcquisitionFrameRateEnable fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }

//    // Set value of String nodes. Such as, 'DeviceUserID' etc.
//    nRet = MV_CC_SetStringValue(handle, "DeviceUserID", "UserIDChanged");
//    if (MV_OK != nRet)
//    {
//        printf("Set DeviceUserID fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }

//    // Execute Command nodes. Such as, 'TriggerSoftware' etc.
//    // precondition
//    // Set value of Enum nodes. Such as, 'TriggerMode' etc.
//    nRet = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_ON);
//    if (MV_OK != nRet)
//    {
//        printf("Set TriggerMode fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }
//    nRet = MV_CC_SetEnumValue(handle, "TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
//    if (MV_OK != nRet)
//    {
//        printf("Set TriggerSource fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }

//    // execute command
//    nRet = MV_CC_SetCommandValue(handle, "TriggerSoftware");
//    if (MV_OK != nRet)
//    {
//        printf("Execute TriggerSoftware fail! nRet [0x%x]\n", nRet);
//        return nRet;
//    }

//    return MV_OK;
//}
/////相机掉线
////MV_EXCEPTION_DEV_DISCONNECT

//void __stdcall ExceptionCallBack(unsigned int nMsgType, void* pUser)
//{
//    if(nMsgType == MV_EXCEPTION_DEV_DISCONNECT)
//    {
//        printf("MV_EXCEPTION_DEV_DISCONNECT");
//    }
//    else
//    {
//        printf("Unknown exception 0x[%x] ", nMsgType);
//    }
//}

//static  unsigned int __stdcall WorkThread(void* pUser,bool g_bExit = false)
//{
//    int nRet = MV_OK;
//    MV_FRAME_OUT stImageInfo = {0};

//    while(1)
//    {
//        nRet = MV_CC_GetImageBuffer(pUser, &stImageInfo, 1000);
//        if (nRet == MV_OK)
//        {
//            printf("Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
//                stImageInfo.stFrameInfo.nWidth, stImageInfo.stFrameInfo.nHeight, stImageInfo.stFrameInfo.nFrameNum);

//            nRet = MV_CC_FreeImageBuffer(pUser, &stImageInfo);
//            if(nRet != MV_OK)
//            {
//                printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
//            }
//        }
//        else
//        {
//            printf("No data[0x%x]\n", nRet);
//        }
//        if(g_bExit)
//        {
//            break;
//        }
//    }

//    return 0;
//}





//}
