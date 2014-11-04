#include "IVS_NetSource.h"
#include "NetChannelMgr.h"
#include "ivs_log.h"

#define LOG_CONF_PATH		"../log"
#define LOG_CONF		"mp_log.conf"// 配置文件名称
#define LOG_FILE_NAME		"IVS_NetSource"
#define MOUDLE_TYPE			"netsource"
#define MOUDLE_ID			100

#ifndef WIN32
/*
 * GetModuleFilePath
 * 获取指定库文件所在目录的上级目录
 * sModuleName [in] 库文件名称，如"libIVS_Player.so"
 * sPath [out] 返回目录
 * unSize [int] sPath的长度
 * added by zhangrui/233055
 */
int GetModuleFilePath(const char* sModuleName, char* sPath, unsigned int unSize)
{
	int iRet = IVS_FAIL;
	char sLine[1024] = {0};
	FILE *fp = NULL;
	char *pTmpFullDir = NULL;
	char *pTmpModuleDir = NULL;

	fp = fopen ("/proc/self/maps", "r");
	if (NULL == fp)
	{
		return iRet;
	}

	while (0 == feof(fp))
	{
		if (NULL == fgets(sLine, sizeof(sLine), fp))
		{
			continue;
		}

		pTmpFullDir = strchr(sLine, '/');
		if (NULL == strstr(sLine, "r-xp") ||  NULL == pTmpFullDir || NULL == strstr(sLine, sModuleName))//r-xp:私有只读可执行属性
		{
			continue;
		}

		//如果查找的模块直接放在根目录下，返回失败
		pTmpModuleDir = strrchr(pTmpFullDir, '/');            
		if (pTmpModuleDir == pTmpFullDir)
		{
			break;
		}

		*pTmpModuleDir = '\0';
		//查找的模块必须放在lib目录下，即lib/libXXX.so
		pTmpModuleDir = strrchr(pTmpFullDir, '/'); 
		if (pTmpModuleDir == pTmpFullDir)
		{
			iRet = IVS_SUCCEED;
			strcpy(sPath, "/");
			break;
		}

		*pTmpModuleDir = '\0';            

		if (strlen(pTmpFullDir) >= unSize)
		{
			break;
		}

		iRet = IVS_SUCCEED;
		strncpy(sPath, pTmpFullDir, strlen(pTmpFullDir) + 1);
		break;
	}

	return iRet;

}
#endif

IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_Init(const char* pLogPath)
{
    // 指定目录（多进程场景）
#ifdef WIN32 
	std::string strLogPath = LOG_CONF_PATH;
	std::string strLogConf = LOG_CONF;
#else
	char pModulePath[1024] = {0};
	int iResult = GetModuleFilePath("libIVS_NetSource.so", pModulePath, 1024);
	if (IVS_SUCCEED != iResult)
	{
		IVS_LOG(iResult, "GetModuleFileName Failed ", "failed.");
		return iResult;
	}
	std::string strLogPath = pModulePath;
	std::string strLogConf = pModulePath;
	strLogPath += "/log";
	strLogConf += "/config/";
	strLogConf += LOG_CONF;
#endif
    if (NULL !=pLogPath && 0 != strlen(pLogPath))
    {
        strLogPath = pLogPath;
    }
    int iRet = IVS_LogInit(strLogPath.c_str(), strLogConf.c_str(), LOG_FILE_NAME, MOUDLE_TYPE, MOUDLE_ID, NULL);
    if (IVS_SUCCEED != iRet)
    {
        // 初始化日志失败，无法打印错误内容;
        return iRet;
    }
    
    // 初始化管理类;
    CNetChannelMgr::instance().Init();

    //通知操作系统，启用SOCKET的DLL库，必须的
#ifdef WIN32
    WSADATA wsaData;
    int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);// 使用2.2版本的socket库;

    if (0 != nRet)
    {
        IVS_LOG(IVS_LOG_ERR, "IVS_NETSOURCE_Init", "Initial IVS dll, WSA Start fail.");
        return IVS_PLAYER_RET_GET_CHANNEL_ERROR;
    }

    return iRet;
#else
	return IVS_SUCCEED;
#endif
}

IVS_NETSOURCE_API IVS_VOID __SDK_CALL IVS_NETSOURCE_UnInit()
{
    CNetChannelMgr::instance().UnInit();
#ifdef WIN32
    //清除系统socket的DLL库
    WSACleanup();
#endif
	IVS_LogClean();
}

// 获取可用句柄;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_GetChannel(IVS_ULONG* pChannel)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_GetChannel in");
    if (NULL == pChannel)
    {
        IVS_LOG(IVS_LOG_ERR, "IVS_NETSOURCE_GetChannel", "Param error pChannel = NULL.");
        return IVS_PARA_INVALID;
    }

    unsigned long ulChannel = 0;
    int iRet = CNetChannelMgr::instance().GetChannel(ulChannel);
    *pChannel = ulChannel;
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_GetChannel out, channel[%lu]", ulChannel);
    return iRet;
}

// 释放指定通道;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_FreeChannel(IVS_ULONG ulChannel)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_FreeChannel in");
    int iRet = CNetChannelMgr::instance().FreeChannel(ulChannel);
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_FreeChannel out, Channel[%lu] ret[%d]", ulChannel, iRet);
	return iRet;
}	

// 设置媒体流传输协议类型;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_SetProtocolType(IVS_ULONG ulChannel, IVS_UINT32 uiProtocolType)
{
    return CNetChannelMgr::instance().SetProtocolType(ulChannel, uiProtocolType);
}

// 获得媒体流传输协议类型;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_GetProtocolType(IVS_ULONG ulChannel, IVS_UINT32* pProtocolType)
{
    if (NULL == pProtocolType)
    {
        IVS_LOG(IVS_LOG_ERR, "IVS_NETSOURCE_GetProtocolType", "Param error pProtocolType = NULL.");
        return IVS_PARA_INVALID;
    }

    unsigned int uiProtocolType = PROTOCOL_RTP_OVER_UDP;
    int iRet = CNetChannelMgr::instance().GetProtocolType(ulChannel, uiProtocolType);
    *pProtocolType = uiProtocolType;
    return iRet;
}

// 设置接收码流的Ip地址;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_SetLocalRecvStreamIP(IVS_ULONG ulChannel, IVS_CHAR* pLocalRecvStreamIp)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_SetLocalRecvStreamIP in");
    if (NULL == pLocalRecvStreamIp)
    {
        IVS_LOG(IVS_LOG_ERR, "IVS_NETSOURCE_SetLocalRecvStreamIP", "Param error pLocalRecvStreamIp = NULL.");
        return IVS_PARA_INVALID;
    }

    int iRet = CNetChannelMgr::instance().SetLocalRecvStreamIP(ulChannel, pLocalRecvStreamIp);
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_SetLocalRecvStreamIP out, Channel[%lu] LocalRecvStreamIp[%s]", ulChannel, pLocalRecvStreamIp);
	return iRet;
}//lint !e818 对外暴露的C接口，不使用const;

IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_GetLocalRecvStreamIP(IVS_ULONG ulChannel, IVS_CHAR* pLocalRecvStreamIp)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_GetLocalRecvStreamIP in");
    if (NULL == pLocalRecvStreamIp)
    {
        IVS_LOG(IVS_LOG_ERR, "IVS_NETSOURCE_GetLocalRecvStreamIP", "Param error pLocalRecvStreamIp = NULL.");
        return IVS_PARA_INVALID;
    }

    int iRet = CNetChannelMgr::instance().GetLocalRecvStreamIP(ulChannel, pLocalRecvStreamIp);
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_GetLocalRecvStreamIP out, Channel[%lu] LocalRecvStreamIp[%s]", ulChannel, pLocalRecvStreamIp);
	return iRet;
}

// 获取接收码流的地址IP和端口号;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_GetLocalRecvStreamPort(IVS_ULONG ulChannel, 
                                                                           IVS_UINT32* pLocalRecvStreamVideoRtpPort, 
                                                                           IVS_UINT32* pLocalRecvStreamAudioRtpPort)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_GetLocalRecvStreamPort in");
    if (NULL == pLocalRecvStreamVideoRtpPort || NULL == pLocalRecvStreamAudioRtpPort)
    {
        IVS_LOG(IVS_LOG_ERR, "IVS_NETSOURCE_GetLocalRecvStreamPort", 
                "Param error pLocalRecvStreamVideoRtpPort or pLocalRecvStreamAudioRtpPort is NULL.");
        return IVS_PARA_INVALID;
    }

    unsigned int uiLocalRecvStreamVideoRtpPort = 0;
    unsigned int uiLocalRecvStreamAudioRtpPort = 0;
    int iRet = CNetChannelMgr::instance().GetLocalRecvStreamPort(ulChannel, uiLocalRecvStreamVideoRtpPort, uiLocalRecvStreamAudioRtpPort);
    *pLocalRecvStreamVideoRtpPort = uiLocalRecvStreamVideoRtpPort;
    *pLocalRecvStreamAudioRtpPort = uiLocalRecvStreamAudioRtpPort;

	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_GetLocalRecvStreamPort out, Channel[%lu] LocalVideoPort[%u] AudioPort[%u]", 
				ulChannel, 
				uiLocalRecvStreamVideoRtpPort, 
				uiLocalRecvStreamAudioRtpPort);
    return iRet;
}


// 打开网络流;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_OpenNetStream(IVS_ULONG ulChannel, IVS_CHAR* pRemoteSendStreamIp, 
                                                                  IVS_UINT32 uiRemoteSendStreamVideoPort, 
                                                                  IVS_UINT32 uiRemoteSendStreamAudioPort)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_OpenNetStream in");
    // 由于 1.语音对讲只有音频端口可用 2.TCP连接收流只有一个端口(视频)
    // 端口检测改为不能同时为0
    if ((NULL == pRemoteSendStreamIp)
        || ((0 == uiRemoteSendStreamVideoPort)
        && (0 == uiRemoteSendStreamAudioPort)))
    {
        IVS_LOG(IVS_LOG_ERR, "IVS_NETSOURCE_OpenNetStream", "Param error pRemoteSendStreamIp = NULL or uiRemoteSendStreamVideoPort = %d or uiRemoteSendStreamAudioPort = %d.",uiRemoteSendStreamVideoPort,uiRemoteSendStreamAudioPort);
        return IVS_PARA_INVALID;
    }

    int iRet = CNetChannelMgr::instance().OpenNetStream(ulChannel, 
                                                        pRemoteSendStreamIp, 
                                                        uiRemoteSendStreamVideoPort, 
                                                        uiRemoteSendStreamAudioPort);

	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_OpenNetStream out, Channel[%lu] Ret[%d]", ulChannel, iRet);
    return iRet;
}//lint !e818 对外暴露的C接口，不使用const

// 关闭网络流;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_CloseNetStream(IVS_ULONG ulChannel)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_CloseNetStream in");
    int iRet = CNetChannelMgr::instance().CloseNetStream(ulChannel);
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_CloseNetStream out, Channel[%lu] Ret[%d]", ulChannel, iRet);
	return iRet;
}

// 启动收流;
IVS_NETSOURCE_API IVS_INT32 __SDK_CALL IVS_NETSOURCE_StartRecvStream(IVS_ULONG ulChannel)
{
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_StartRecvStream in");
    int iRet = CNetChannelMgr::instance().StartRecvStream(ulChannel);
	IVS_LOG(IVS_LOG_DEBUG, "", "IVS_NETSOURCE_StartRecvStream out, Channel[%lu] Ret[%d]", ulChannel, iRet);
	return iRet;
}

// 设置异常;
IVS_NETSOURCE_API IVS_VOID __SDK_CALL IVS_NETSOURCE_SetExceptionCallBack(NET_EXCEPTION_CALLBACK cbExceptionCallBack, 
                                                                        IVS_VOID* pUser)
{
	IVS_LOG(IVS_LOG_DEBUG, "IVS_NETSOURCE_SetExceptionCallBack", "ExceptionCallback[%x] pUser[%x]", cbExceptionCallBack, pUser);
    CNetChannelMgr::instance().SetExceptionCallBack(cbExceptionCallBack, pUser);
}

// 设置数据回调接口;
IVS_NETSOURCE_API IVS_VOID __SDK_CALL IVS_NETSOURCE_SetDataCallBack(IVS_ULONG ulChannel, 
                                                                   NET_DATA_CALLBACK cbDataCallBack, 
                                                                   IVS_VOID* pUser)
{
	IVS_LOG(IVS_LOG_DEBUG, "IVS_NETSOURCE_SetDataCallBack", "Channel[%x] DataCallBack[%x] pUser[%x]", ulChannel, cbDataCallBack, pUser);
    CNetChannelMgr::instance().SetDataCallBack(ulChannel, cbDataCallBack, pUser);
}

// 设置Session信息
IVS_NETSOURCE_API IVS_VOID __SDK_CALL IVS_NETSOURCE_SetSessionInfo(IVS_ULONG ulChannel, 
                                                                  IVS_CHAR* pSessionUrl, 
                                                                  IVS_CHAR* pSessionId)
{
    IVS_LOG(IVS_LOG_DEBUG, "IVS_NETSOURCE_SetSessionInfo", "Channel[%d] SessionUrl[%s] SessionId[%s]", ulChannel, pSessionUrl, pSessionId);
    CNetChannelMgr::instance().SetSessionInfo(ulChannel, pSessionUrl, pSessionId);
}
