/********************************************************************
filename	: 	IVS_Linux_Demo.cpp
author		:	z00233055
created		:	2013/11/29	
description:	IVS SDK Linux接口测试Demo
copyright	:	Copyright (C) 2013-2016
history		:	2013/11/29	 初始版本
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "inc/IVS_SDK.h"


IVS_VOID BeginMessage(const IVS_CHAR* pContent);
IVS_VOID RealPlayRawCallBack(IVS_ULONG ulHandle, IVS_RAW_FRAME_INFO* pRawFrameInfo, IVS_VOID* pBuf, IVS_UINT32 uiBufSize, IVS_VOID* pUserData);

IVS_VOID EventCallBackFunc(IVS_INT32 iEventType, IVS_VOID* pEventBuf, IVS_UINT32 uiBufSize, IVS_VOID* pUserData)
{
	FILE* fpEventInfo = fopen("Event.txt", "a");
	fprintf(fpEventInfo, "EventType:%d\n", iEventType);
	fclose(fpEventInfo);

	if (IVS_EVENT_FIND_DEVICE == iEventType)
	{
		IVS_CHAR* pResultInfo = reinterpret_cast<IVS_CHAR*>(pEventBuf);
		FILE* fpFindDevice = fopen("FindDevice.txt", "a");
		fprintf(fpFindDevice, "Result:%s\n", pResultInfo);
		fclose(fpFindDevice);
	}
}

int main() 
{
	IVS_INT32 iRet = 1;
	IVS_INT32 iSessionID =-1;
	std::string strReqXml = "";
	IVS_CHAR* pRspXml = NULL;
	IVS_UINT32 uiReqNum = 0;
	IVS_UINT32 uiBufSize = 0;
	IVS_UINT32 uiRoleID = 0;
	IVS_ULONG ulPlayHandle = 0;
	IVS_INDEX_RANGE IndexRange = {0};
	const IVS_CHAR* pDomainCode			= "86a067dbfab647bab5f7d6be882ef1c6";
	const IVS_CHAR* pDomainCodeVMU		= "9145a3f7c4164d3ab9e161fcb4221426";
	const IVS_CHAR* pMainDevCode617	= "01872810000000000000#f563c8bc3f8240009637a9edd500ca19";//617
	const IVS_CHAR* pCameraCode617		= "01872810000000000101#f563c8bc3f8240009637a9edd500ca19";
	const IVS_CHAR* pMainDevCode235	= "04598710000000000000#86a067dbfab647bab5f7d6be882ef1c6";//235
	const IVS_CHAR* pCameraCode235		= "04598710000000000101#86a067dbfab647bab5f7d6be882ef1c6";
	const IVS_CHAR* pAlarmOutCode		= "04598710000000000301#86a067dbfab647bab5f7d6be882ef1c6";
	const IVS_CHAR* pCameraCodeTest	= "11111111111111110101#86a067dbfab647bab5f7d6be882ef1c6";

#pragma region 开始
	BeginMessage("Test IVS_SDK_SetLogPath");
	iRet = IVS_SDK_SetLogPath("./log");
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_Init");
	iRet = IVS_SDK_Init();
	printf("Result = %d\n", iRet);
	if (IVS_SUCCEED != iRet)
	{
		return 0;
	}

	BeginMessage("Test IVS_SDK_Login");
	IVS_LOGIN_INFO LoginReqInfo = {0};
	LoginReqInfo.stIP.uiIPType = IP_V4;
	strncpy(LoginReqInfo.stIP.cIP, "10.170.103.60", IVS_IP_LEN);
	LoginReqInfo.uiPort = 9900;
	strncpy(LoginReqInfo.cUserName, "zhr", IVS_NAME_LEN);
	strncpy(LoginReqInfo.pPWD, "1qw2!QW@", IVS_PWD_LEN);
	iRet = IVS_SDK_Login(&LoginReqInfo, &iSessionID);
	if (IVS_SUCCEED == iRet)
	{
		IVS_SDK_SetEventCallBack(iSessionID, (EventCallBack)EventCallBackFunc, NULL);
	}
	printf("Result = %d\n", iRet);
#pragma endregion 开始

#pragma region 录像策略
	BeginMessage("Test IVS_SDK_SetRecordPolicyByTime");
	IVS_RECORD_POLICY_TIME RecordPolicy = {0};
	RecordPolicy.uiRecordMode = RECORD_MODE_FULL;
	RecordPolicy.uiTime = 30;
	RecordPolicy.uiFrameExtractRecordTime = 15;
	RecordPolicy.uiAlarmTime = 60;
	RecordPolicy.uiKeyframeTime = 30;
	RecordPolicy.uiBeforeAlarm = 5;
	RecordPolicy.uiAfterAlarm = 5;
	RecordPolicy.uiPlanStreamType = STREAM_TYPE_MAIN;
	RecordPolicy.uiAlarmStreamType = STREAM_TYPE_MAIN;
	RecordPolicy.uiAlarmRecordTTL = 0;
	RecordPolicy.uiManualRecordTTL = 0;
	RecordPolicy.uiPreRecord = PRERECORD_MODE_NONE;
	RecordPolicy.uiPreRecordTime = 1;
	RecordPolicy.bAssociatedAudio = 1;
	iRet = IVS_SDK_SetRecordPolicyByTime(iSessionID, pCameraCode235, &RecordPolicy);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetRecordPolicyByTime");
	IVS_RECORD_POLICY_TIME RecordPolicyGot = {0};
	iRet = IVS_SDK_GetRecordPolicyByTime(iSessionID, pCameraCode235, &RecordPolicyGot);
	if (IVS_SUCCEED == iRet)
	{
		printf("RecordMode:%d Time:%d\nPlanStreamType:%d AlarmStreamType:%d\n", 
			RecordPolicyGot.uiRecordMode, RecordPolicyGot.uiTime, RecordPolicyGot.uiPlanStreamType, RecordPolicyGot.uiAlarmStreamType);
	}
	printf("Result = %d\n", iRet);
#pragma endregion 录像策略

#pragma region 录像状态
	BeginMessage("Test IVS_SDK_GetRecordStatus");
	IVS_UINT32 RecordState = 0;
	iRet = IVS_SDK_GetRecordStatus(iSessionID, pCameraCode235, RECORD_METHOD_PLATFORM, &RecordState);
	if (IVS_SUCCEED== iRet)
	{
		printf("RecordState:%d\n", iRet);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetRecordTask");
	iRet = IVS_SDK_GetRecordTask(iSessionID, &pRspXml);
	if (NULL != pRspXml)
	{
		printf("%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);
#pragma endregion 录像状态

#pragma region 录像列表
	BeginMessage("Test IVS_SDK_QueryRecordList");
	uiReqNum = 5;
	uiBufSize = sizeof(IVS_QUERY_UNIFIED_FORMAT) + 6*sizeof(IVS_QUERY_FIELD);//7个查询条件
	IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery = reinterpret_cast<IVS_QUERY_UNIFIED_FORMAT*>(new IVS_CHAR[uiBufSize]);
	memset(pUnifiedQuery, 0, uiBufSize);
	pUnifiedQuery->stIndex.uiFromIndex = 1;
	pUnifiedQuery->stIndex.uiToIndex = uiReqNum;
	pUnifiedQuery->iFieldNum = 7;
	pUnifiedQuery->stQueryField[0].eFieID = QUERY_CAMERA_CODE;//摄像机编码
	strncpy(pUnifiedQuery->stQueryField[0].cValue, pCameraCode235, IVS_DEV_CODE_LEN);
	pUnifiedQuery->stQueryField[0].bExactQuery = 1;
	pUnifiedQuery->stQueryField[1].eFieID = QUERY_RECORD_QUERY_TYPE;//查询方式
	strncpy(pUnifiedQuery->stQueryField[1].cValue, "0", IVS_QUERY_VALUE_LEN);//0-按时间
	pUnifiedQuery->stQueryField[1].bExactQuery = 1;
	pUnifiedQuery->stQueryField[2].eFieID = QUERY_OPERATION_START_TIME;//开始时间
	strncpy(pUnifiedQuery->stQueryField[2].cValue, "20140101000000", IVS_TIME_LEN);
	pUnifiedQuery->stQueryField[2].bExactQuery = 1;
	pUnifiedQuery->stQueryField[3].eFieID = QUERY_OPERATION_END_TIME;//结束时间
	strncpy(pUnifiedQuery->stQueryField[3].cValue, "20140131000000", IVS_TIME_LEN);
	pUnifiedQuery->stQueryField[3].bExactQuery = 1;
	pUnifiedQuery->stQueryField[4].eFieID = QUERY_RECORD_TYPE;//录像类型
	strncpy(pUnifiedQuery->stQueryField[4].cValue, "7", IVS_QUERY_VALUE_LEN);//7 = 4+2+1，值参考IVS_RECORD_TYPE
	pUnifiedQuery->stQueryField[4].bExactQuery = 1;
	pUnifiedQuery->stQueryField[5].eFieID = QUERY_RECORD_METHOD;//录像存储位置
	strncpy(pUnifiedQuery->stQueryField[5].cValue, "0", IVS_QUERY_VALUE_LEN);//平台录像，值参考IVS_RECORD_METHOD
	pUnifiedQuery->stQueryField[5].bExactQuery = 1;
	pUnifiedQuery->stQueryField[6].eFieID = QUERY_OPERATOR_ID;//执行查询操作的用户ID
	strncpy(pUnifiedQuery->stQueryField[6].cValue, "1", IVS_QUERY_VALUE_LEN);
	pUnifiedQuery->stQueryField[6].bExactQuery = 1;
	uiBufSize = sizeof(IVS_RECORD_INFO_LIST) + (uiReqNum - 1)*sizeof(IVS_RECORD_INFO);
	IVS_RECORD_INFO_LIST* pRecordInfoList = reinterpret_cast<IVS_RECORD_INFO_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pRecordInfoList, 0, uiBufSize);
	iRet = IVS_SDK_QueryRecordList(iSessionID, pUnifiedQuery, pRecordInfoList, uiBufSize);
	if (IVS_SUCCEED == iRet)
	{
		printf("Total:%d\n", pRecordInfoList->uiTotal);
		for (IVS_UINT32 i=0; i<pRecordInfoList->uiTotal && i<uiReqNum; i++)
		{
			printf("Duration: %s~%s\n", pRecordInfoList->stRecordInfo[i].stTime.cStart, pRecordInfoList->stRecordInfo[i].stTime.cEnd);
		}
	}
	delete[] pUnifiedQuery;
	pUnifiedQuery = NULL;
	delete[] pRecordInfoList;
	pRecordInfoList = NULL;
	printf("Result = %d\n", iRet);
#pragma endregion 录像列表

#pragma region 告警管理
	BeginMessage("Test IVS_SDK_AlarmReport");
	IVS_ALARM_REPORT AlarmReport = {0};
	strncpy(AlarmReport.cAlarmInCode, "04598710000000000000", IVS_ALARM_CODE_LEN);
	strncpy(AlarmReport.cDevDomainCode, "86a067dbfab647bab5f7d6be882ef1c6", IVS_DOMAIN_CODE_LEN);
	strncpy(AlarmReport.cNvrCode, "4add48e4d34c45b5b88e948508bf6dfc", IVS_ALARM_REPORT_ID_LEN);
	strncpy(AlarmReport.cAlarmType, "ALARM_TYPE_MOVE_DECTION", IVS_ALARM_TYPE_LEN);
	strncpy(AlarmReport.cOccurTime, "20140106072020", IVS_TIME_LEN);
	strncpy(AlarmReport.cReportTime, "20140106072050", IVS_TIME_LEN);
	strncpy(AlarmReport.cAlarmID, "6771", IVS_ALARM_REPORT_ID_LEN);
	strncpy(AlarmReport.cAlarmDesc, "Alarm Test", IVS_ALARM_DESCRIPTION_LEN);
	AlarmReport.bAction = 1;
	AlarmReport.uiOccurNumber = 1;
	iRet = IVS_SDK_AlarmReport(iSessionID, &AlarmReport);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_UserAuthentication");
	iRet = IVS_SDK_UserAuthentication(iSessionID, "1qw2!QW@");
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_AlarmCommission");
	IVS_ALARM_COMMISSION AlarmCommission = {0};
	AlarmCommission.ullAlarmEventID = 6872;
	AlarmCommission.uiUserNum = 1;
	strncpy(AlarmCommission.stUserInfo->cDomainCode, pDomainCode, IVS_DOMAIN_CODE_LEN);
	AlarmCommission.stUserInfo->uiUserID = 92;//zhr
	iRet = IVS_SDK_AlarmCommission(iSessionID, pCameraCode235, &AlarmCommission);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_AlarmConfirm");
	IVS_ALARM_OPERATE_INFO AlarmOperateInfo = {0};
	AlarmOperateInfo.uiOperatorID = 92;//zhr
	strncpy(AlarmOperateInfo.cOperatorName, "zhangrui", IVS_NAME_LEN);
	strncpy(AlarmOperateInfo.cOperateTime, "20131130072059", IVS_TIME_LEN);
	strncpy(AlarmOperateInfo.cOperateInfo, "aaaaaaaa", IVS_ALARM_DESCRIPTION_LEN);
	iRet = IVS_SDK_AlarmConfirm(iSessionID, 6872, pCameraCode235, &AlarmOperateInfo);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_AlarmCancel");
	iRet = IVS_SDK_AlarmCancel(iSessionID, 6873, pCameraCode235, &AlarmOperateInfo);
	printf("Result = %d\n", iRet);
#pragma endregion 告警管理

#pragma region 告警联动
	BeginMessage("Test IVS_SDK_AddAlarmLinkage");
	strReqXml.clear();
	strReqXml += "<Content>";
	strReqXml +=	"<Linkage>";
	strReqXml +=		"<AlarmInCode>";
	strReqXml +=			pCameraCode235;
	strReqXml +=		"</AlarmInCode>";
	strReqXml +=		"<AlarmInType>01</AlarmInType>";
	strReqXml +=		"<AlarmType>ALARM_TYPE_MOVE_DECTION</AlarmType>";//移动侦测告警
	strReqXml +=		"<ActionList>";
	strReqXml +=			"<Action>";
	strReqXml +=				"<ActionType>4</ActionType>";//联动抓拍
	strReqXml +=				"<GlobalParam>99</GlobalParam>";
	strReqXml +=				"<ActionBranch>0</ActionBranch>";
	strReqXml +=				"<DevList>";
	strReqXml +=					"<DevInfo>";
	strReqXml +=						"<DevCode>";
	strReqXml +=						pCameraCode235;
	strReqXml +=						"</DevCode>";
	strReqXml +=						"<Param>yu</Param>";
	strReqXml +=					"</DevInfo>";
	strReqXml +=				"</DevList>";
	strReqXml +=			"</Action>";
	strReqXml +=		"</ActionList>";
	strReqXml +=	"</Linkage>";
	strReqXml += "</Content>";
	pRspXml = NULL;
	std::string strLinkageID = "";
	iRet = IVS_SDK_AddAlarmLinkage(iSessionID, strReqXml.c_str(), &pRspXml);
	if (NULL != pRspXml)
	{
		std::string strRspXml = pRspXml;
		IVS_UINT32 uiStartPos = strRspXml.find("<LinkageID>") + strlen("<LinkageID>");
		IVS_UINT32 uiEndPos = strRspXml.find("</LinkageID>");
		strLinkageID = strRspXml.substr(uiStartPos, uiEndPos-uiStartPos);
		printf("LinkageID:%s\nRspXml:%s\n", strLinkageID.c_str(), pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_ModifyAlarmLinkage");
	strReqXml.clear();
	strReqXml += "<Content>";
	strReqXml +=	"<Linkage>";
	strReqXml +=		"<LinkageID>";
	strReqXml +=			strLinkageID;
	strReqXml +=		"</LinkageID>";
	strReqXml +=		"<AlarmInCode>";
	strReqXml +=			pCameraCode235;
	strReqXml +=		"</AlarmInCode>";
	strReqXml +=		"<AlarmInType>01</AlarmInType>";
	strReqXml +=		"<AlarmType>ALARM_TYPE_MOVE_DECTION</AlarmType>";//移动侦测告警
	strReqXml +=		"<ActionList>";
	strReqXml +=			"<Action>";
	strReqXml +=				"<ActionType>4</ActionType>";//联动抓拍
	strReqXml +=				"<GlobalParam>99</GlobalParam>";
	strReqXml +=				"<ActionBranch>0</ActionBranch>";
	strReqXml +=				"<DevList>";
	strReqXml +=					"<DevInfo>";
	strReqXml +=						"<DevCode>";
	strReqXml +=						pCameraCode235;
	strReqXml +=						"</DevCode>";
	strReqXml +=						"<Param>yu</Param>";
	strReqXml +=					"</DevInfo>";
	strReqXml +=				"</DevList>";
	strReqXml +=			"</Action>";
	strReqXml +=			"<Action>";
	strReqXml +=				"<ActionType>2</ActionType>";//联动录像
	strReqXml +=				"<GlobalParam>301</GlobalParam>";
	strReqXml +=				"<ActionBranch>0</ActionBranch>";
	strReqXml +=				"<DevList>";
	strReqXml +=					"<DevInfo>";
	strReqXml +=						"<DevCode>";
	strReqXml +=						pCameraCode235;
	strReqXml +=						"</DevCode>";
	strReqXml +=						"<Param>yu</Param>";
	strReqXml +=					"</DevInfo>";
	strReqXml +=				"</DevList>";
	strReqXml +=			"</Action>";
	strReqXml +=		"</ActionList>";
	strReqXml +=	"</Linkage>";
	strReqXml += "</Content>";
	iRet = IVS_SDK_ModifyAlarmLinkage(iSessionID, strReqXml.c_str());
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetAlarmlinkageList");
	strReqXml.clear();
	strReqXml += "<Content>";
	strReqXml +=		"<AlarmInCode>";
	strReqXml +=			pCameraCode235;
	strReqXml +=		"</AlarmInCode>";
	strReqXml +=		"<AlarmInType>01</AlarmInType>";
	strReqXml += "</Content>";
	pRspXml = NULL;
	iRet = IVS_SDK_GetAlarmlinkageList(iSessionID, strReqXml.c_str(), &pRspXml);
	if (NULL != pRspXml)
	{
		printf("RspXml:%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetAlarmLinkageAction");
	strReqXml.clear();
	strReqXml += "<Content>";
	strReqXml +=	"<Linkage>";
	strReqXml +=		"<AlarmInCode>";
	strReqXml +=			pCameraCode235;
	strReqXml +=		"</AlarmInCode>";
	strReqXml +=		"<AlarmInType>01</AlarmInType>";
	strReqXml +=		"<AlarmType>ALARM_TYPE_MOVE_DECTION</AlarmType>";
	strReqXml +=		"<ActionType>4</ActionType>";
	strReqXml +=	"</Linkage>";
	strReqXml += "</Content>";
	pRspXml = NULL;
	iRet = IVS_SDK_GetAlarmLinkageAction(iSessionID, strReqXml.c_str(), &pRspXml);
	if (NULL != pRspXml)
	{
		printf("RspXml:%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetAlarmLinkage");
	strReqXml.clear();
	strReqXml += "<Content>";
	strReqXml +=	"<Linkage>";
	strReqXml +=		"<LinkageID>";
	strReqXml +=			strLinkageID;
	strReqXml +=		"</LinkageID>";
	strReqXml +=		"<AlarmInCode>";
	strReqXml +=			pCameraCode235;
	strReqXml +=		"</AlarmInCode>";
	strReqXml +=		"<AlarmInType>01</AlarmInType>";
	strReqXml +=		"<AlarmType>ALARM_TYPE_MOVE_DECTION</AlarmType>";//移动侦测告警
	strReqXml +=		"<DevDomainCode>";
	strReqXml +=			pDomainCode;
	strReqXml +=		"</DevDomainCode>";
	strReqXml +=	"</Linkage>";
	strReqXml += "</Content>";
	pRspXml = NULL;
	iRet = IVS_SDK_GetAlarmLinkage(iSessionID, strReqXml.c_str(), &pRspXml);
	if (NULL != pRspXml)
	{
		printf("RspXml:%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_DeleteAlarmLinkage");
	iRet = IVS_SDK_DeleteAlarmLinkage(iSessionID, strReqXml.c_str());
	printf("Result = %d\n", iRet);
#pragma endregion 告警联动

#pragma region 告警开关量
	BeginMessage("Test IVS_SDK_StartAlarmOut");
	iRet = IVS_SDK_StartAlarmOut(iSessionID, pAlarmOutCode);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_StopAlarmOut");
	iRet = IVS_SDK_StopAlarmOut(iSessionID, pAlarmOutCode);
	printf("Result = %d\n", iRet);
#pragma endregion 告警开关量

#pragma region 告警类型
	BeginMessage("Test IVS_SDK_GetAlarmTypeList");
	uiReqNum = 80;
	IVS_QUERY_UNIFIED_FORMAT UnifiedQuery = {0};
	UnifiedQuery.stIndex.uiFromIndex = 1;
	UnifiedQuery.stIndex.uiToIndex = uiReqNum;
	UnifiedQuery.iFieldNum = 1;
	UnifiedQuery.stQueryField->eFieID = QUERY_USER_ID;
	strncpy(UnifiedQuery.stQueryField->cValue, "92", IVS_QUERY_VALUE_LEN);
	uiBufSize = sizeof(IVS_ALARM_TYPE_LIST) + (uiReqNum-1)*sizeof(IVS_ALARM_TYPE);
	IVS_ALARM_TYPE_LIST* pAlarmTypeList = reinterpret_cast<IVS_ALARM_TYPE_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pAlarmTypeList, 0, uiBufSize);
	iRet = IVS_SDK_GetAlarmTypeList(iSessionID, &UnifiedQuery, pAlarmTypeList, uiBufSize);
	printf("Total:%d\n", pAlarmTypeList->iTotal);
	delete[] pAlarmTypeList;
	pAlarmTypeList = NULL;
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_SetAlarmTypeLevel");
	uiBufSize = sizeof(IVS_ALARM_TYPE_LIST) + sizeof(IVS_ALARM_TYPE);
	pAlarmTypeList = reinterpret_cast<IVS_ALARM_TYPE_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pAlarmTypeList, 0, uiBufSize);
	pAlarmTypeList->iTotal = 2;
	pAlarmTypeList->stSubscribeInfo[0].uiID = 2;//ALARM_NO_SIGNAL
	pAlarmTypeList->stSubscribeInfo[0].stAlarmLevel.uiAlarmLevelId = 1;
	pAlarmTypeList->stSubscribeInfo[1].uiID = 4;//ALARM_TYPE_MOVE_DECTION
	pAlarmTypeList->stSubscribeInfo[1].stAlarmLevel.uiAlarmLevelId = 1;
	iRet = IVS_SDK_SetAlarmTypeLevel(iSessionID, pAlarmTypeList);
	delete[] pAlarmTypeList;
	pAlarmTypeList = NULL;
	printf("Result = %d\n", iRet);
#pragma endregion 告警类型

#pragma region 告警级别
	BeginMessage("Test IVS_SDK_GetAlarmLevelList");
	IVS_UINT32 uiAlarmLevelNum = 0;
	IVS_ALARM_LEVEL AlarmLevelList[IVS_MAX_ALARM_LEVEL_NUM] = {0};
	iRet = IVS_SDK_GetAlarmLevelList(iSessionID, IVS_MAX_ALARM_LEVEL_NUM, &uiAlarmLevelNum, AlarmLevelList, sizeof(IVS_ALARM_LEVEL)*IVS_MAX_ALARM_LEVEL_NUM);
	if (IVS_SUCCEED == iRet)
	{
		for (int i=0; i<uiAlarmLevelNum; i++)
		{
			printf("LevelID:%d\tDesc:%s\tValue:%d\n", AlarmLevelList[i].uiAlarmLevelId, AlarmLevelList[i].cDescription, AlarmLevelList[i].uiValue);
		}
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetAlarmLevel");
	IVS_ALARM_LEVEL AlarmLevel = {0};
	iRet = IVS_SDK_GetAlarmLevel(iSessionID, 1, &AlarmLevel);
	if (IVS_SUCCEED == iRet)
	{
		printf("LevelID:%d\tDesc:%s\tValue:%d\n", AlarmLevel.uiAlarmLevelId, AlarmLevel.cDescription, AlarmLevel.uiValue);
	}
	printf("Result = %d\n", iRet);
#pragma endregion 告警级别

#pragma region 用户管理/列表
	BeginMessage("Test IVS_SDK_LockUser");
	iRet = IVS_SDK_LockUser(iSessionID, "", 4, 1);//加锁
	printf("Lock\tResult = %d\n", iRet);
	sleep(1);
	iRet = IVS_SDK_LockUser(iSessionID, "", 4, 0);//解锁
	printf("Unlock\tResult = %d\n", iRet);

	BeginMessage("Test IVS_SDK_SignOutUser");
	iRet = IVS_SDK_SignOutUser(iSessionID, "", 91);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_SignOutUserByRole");
	iRet = IVS_SDK_SignOutUserByRole(iSessionID, "", 3);//role_normal
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetOnlineUser");
	uiReqNum = 30;
	memset(&UnifiedQuery, 0, sizeof(UnifiedQuery));
	UnifiedQuery.iFieldNum = 1;
	UnifiedQuery.stIndex.uiFromIndex = 1;
	UnifiedQuery.stIndex.uiToIndex = uiReqNum;
	UnifiedQuery.stQueryField->eFieID = QUERY_INVALID;
	UnifiedQuery.stQueryField->bExactQuery = 0;
	//strncpy(UnifiedQuery.stQueryField->cValue, "super", IVS_QUERY_VALUE_LEN);
	uiBufSize = sizeof(IVS_ONLINE_USER_LIST) + (uiReqNum-1)*sizeof(IVS_ONLINE_USER);
	IVS_ONLINE_USER_LIST* pOnlineUserList = reinterpret_cast<IVS_ONLINE_USER_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pOnlineUserList, 0, uiBufSize);
	iRet = IVS_SDK_GetOnlineUser(iSessionID, "", &UnifiedQuery, pOnlineUserList, uiBufSize);
	if (IVS_SUCCEED == iRet)
	{
		for (IVS_UINT32 i=0; i<pOnlineUserList->uiTotal && i<uiReqNum; i++)
		{
			printf("%s\t%s\t%s\n", 
				pOnlineUserList->stOnlineUser[i].cUserName, pOnlineUserList->stOnlineUser[i].stIP.cIP, pOnlineUserList->stOnlineUser[i].cMachineName);
		}
	}
	delete[] pOnlineUserList;
	pOnlineUserList = NULL;
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_SignOutOnlineUser");
	iRet = IVS_SDK_SignOutOnlineUser(iSessionID, "", 3103);
	printf("Result = %d\n", iRet);
#pragma endregion 用户管理/列表

#pragma region 用户密码
	BeginMessage("Test IVS_SDK_ResetPWD");
	iRet = IVS_SDK_ResetPWD(iSessionID, "", 4, "1qw2!QW@");//94-goat
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_CheckPWDByRole");
	iRet = IVS_SDK_CheckPWDByRole(iSessionID, "", 2, "goat", "1qw2!QW@");
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetAutoCreatePWD");
	IVS_CHAR pNewPwd[IVS_PWD_LEN+1] = {0};
	iRet = IVS_SDK_GetAutoCreatePWD(iSessionID, "", 2, "goat", pNewPwd, IVS_PWD_LEN);
	if (IVS_SUCCEED == iRet)
	{
		printf("Password:%s\n", pNewPwd);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetPWDStrength");
	IVS_UINT32 uiStrength = 0;
	iRet = IVS_SDK_GetPWDStrength("1qaz!QAZ", &uiStrength);
	if (IVS_SUCCEED == iRet)
	{
		printf("Strength:%d\n", uiStrength);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetPWDExpireInfo");
	IVS_PWD_EXPIRE_INFO PWDExpireInfo = {0};
	iRet = IVS_SDK_GetPWDExpireInfo(iSessionID, &PWDExpireInfo);
	if (IVS_SUCCEED == iRet)
	{
		printf("NeedWarning:%s RemainDays:%d ExpiredDays:%d\n", 
			(0 == PWDExpireInfo.bIsNeedWarning ? "No" : "Yes"), PWDExpireInfo.uiRemainDays, PWDExpireInfo.uiExpiredDays);
	}
	printf("Result = %d\n", iRet);
#pragma endregion 用户密码

#pragma region 用户设备
	BeginMessage("Test IVS_SDK_SetUserDeviceList");
	uiBufSize = sizeof(IVS_USER_DEVICE_INFO_LIST) + sizeof(IVS_USER_DEVICE_INFO);
	IVS_USER_DEVICE_INFO_LIST *pUserDevList = reinterpret_cast<IVS_USER_DEVICE_INFO_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pUserDevList, 0, uiBufSize);
	pUserDevList->uiTotal = 2;
	pUserDevList->stUserDeviceInfo[0].bIsExDomain = 0;
	pUserDevList->stUserDeviceInfo[0].bIsTotalGroup = 0;
	strncpy(pUserDevList->stUserDeviceInfo[0].cDevGroupCode,"0",IVS_DEVICE_GROUP_LEN);
	strncpy(pUserDevList->stUserDeviceInfo[0].cDevDomainCode,pDomainCode,IVS_DOMAIN_CODE_LEN);
	strncpy(pUserDevList->stUserDeviceInfo[0].cDevCode,"04598710000000000101",IVS_DEV_CODE_LEN);//235
	pUserDevList->stUserDeviceInfo[1].bIsExDomain = 0;
	pUserDevList->stUserDeviceInfo[1].bIsTotalGroup = 0;
	strncpy(pUserDevList->stUserDeviceInfo[1].cDevGroupCode,"0",IVS_DEVICE_GROUP_LEN);
	strncpy(pUserDevList->stUserDeviceInfo[1].cDevDomainCode,pDomainCode,IVS_DOMAIN_CODE_LEN);
	strncpy(pUserDevList->stUserDeviceInfo[1].cDevCode,"02329900000000000101",IVS_DEV_CODE_LEN);//617
	iRet = IVS_SDK_SetUserDeviceList(iSessionID, pDomainCode, 94, pUserDevList, uiBufSize);//94-goat
	delete[] pUserDevList;
	pUserDevList = NULL;
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetUserDeviceList");
	uiReqNum = 20;
	IndexRange.uiFromIndex = 1;
	IndexRange.uiToIndex = uiReqNum;
	uiBufSize = sizeof(IVS_USER_DEVICE_INFO_LIST) + (uiReqNum-1)*sizeof(IVS_USER_DEVICE_INFO);
	pUserDevList = reinterpret_cast<IVS_USER_DEVICE_INFO_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pUserDevList, 0, uiBufSize);
	iRet = IVS_SDK_GetUserDeviceList(iSessionID, "", 94, &IndexRange, pUserDevList, uiBufSize);//94-goat
	if (IVS_SUCCEED == iRet)
	{
		for (IVS_UINT32 i=0; i<uiReqNum && i<pUserDevList->uiTotal; i++)
		{
			printf("DevCode:%s Domain:%s IsTotalGroup:%d\n", pUserDevList->stUserDeviceInfo[i].cDevCode, 
				pUserDevList->stUserDeviceInfo[i].cDevDomainCode, pUserDevList->stUserDeviceInfo[i].bIsTotalGroup);
		}
	}
	delete[] pUserDevList;
	pUserDevList = NULL;
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetDeviceUserList");
	uiReqNum = 20;
	IndexRange.uiFromIndex = 1;
	IndexRange.uiToIndex = uiReqNum;
	uiBufSize = sizeof(IVS_DEVICE_USER_INFO_LIST) + (uiReqNum-1)*sizeof(IVS_DEVICE_USER_INFO);
	IVS_DEVICE_USER_INFO_LIST* pDevUserList = reinterpret_cast<IVS_DEVICE_USER_INFO_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pDevUserList, 0, uiBufSize);
	iRet = IVS_SDK_GetDeviceUserList(iSessionID, "", pCameraCode235, 2, &IndexRange, pDevUserList, uiBufSize);//2-所有
	if (IVS_SUCCEED == iRet)
	{
		for (IVS_UINT32 i=0; i<uiReqNum && i<pDevUserList->uiTotal; i++)
		{
			printf("User:%s\tID:%d\n", pDevUserList->stDeviceUserInfo[i].cLoginName, pDevUserList->stDeviceUserInfo[i].uiUserID);
		}
	}
	delete[] pDevUserList;
	pDevUserList = NULL;
	printf("Result = %d\n", iRet);
#pragma endregion 用户设备

#pragma region 用户角色
	BeginMessage("Test IVS_SDK_AddRole");
	uiRoleID = 0;
	IVS_ROLE_INFO RoleInfo = {0};
	strncpy(RoleInfo.cDomainCode, pDomainCode, IVS_DOMAIN_CODE_LEN);
	strncpy(RoleInfo.cRoleName, "role_test_add", IVS_NAME_LEN);
	strncpy(RoleInfo.cRoleDescribe, "IVS_SDK_AddRole", IVS_DESCRIBE_LEN);
	strncpy(RoleInfo.cRight, "11110010110000000001111110000000000000011011111110000000000000000000000000000000000000000000000000000000000000000000000000000000", IVS_MAX_OPERATION_RIGHT);
	RoleInfo.uiRoleType = ROLE_TYPE_CUSTOM;
	RoleInfo.stAccountRule.bEnable = 1;//启用账户规则
	RoleInfo.stAccountRule.stPswConsist.bCapital = 1;
	RoleInfo.stAccountRule.stPswConsist.bLowercase = 1;
	RoleInfo.stAccountRule.stPswConsist.bSpecialChar = 1;
	RoleInfo.stAccountRule.stPswConsist.bFigure = 1;
	RoleInfo.stAccountRule.bFirstModify = 1;//首次修改密码
	RoleInfo.stAccountRule.bCheckOldPwd = 1;
	RoleInfo.stAccountRule.bAccountNotFit = 1;
	RoleInfo.stAccountRule.bDomainAccCheckPwd = 1;
	RoleInfo.stAccountRule.uiPwdMinLen = 8;//密码最短长度
	RoleInfo.stAccountRule.uiPwdDifferentNum = 3;
	RoleInfo.stAccountRule.uiAccountLockNum = 5;
	RoleInfo.stAccountRule.uiAccountLockElapse = 10;//10分钟密码错5次锁定
	RoleInfo.stAccountRule.uiAccountLockInterval = 15;//15分钟后重计错误次数
	RoleInfo.stAccountRule.uiPWDExpireTime = 90;//密码90天过期
	RoleInfo.stAccountRule.uiPWDExpireNotifyTime = 14;//提前两周提醒
	iRet = IVS_SDK_AddRole(iSessionID, &RoleInfo, &uiRoleID);
	if (IVS_SUCCEED == iRet)
	{
		printf("RoleID:%d Added\n", uiRoleID);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_ModifyRole");
	RoleInfo.uiRoleID = uiRoleID;
	strncpy(RoleInfo.cRoleDescribe, "IVS_SDK_ModifyRole", IVS_DESCRIBE_LEN);
	iRet = IVS_SDK_ModifyRole(iSessionID, &RoleInfo);
	if (IVS_SUCCEED == iRet)
	{
		printf("RoleID:%d Modified\n", uiRoleID);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetRoleList");
	uiReqNum = IVS_MAX_ROLE_INFO_NUM;
	IndexRange.uiFromIndex = 1;
	IndexRange.uiToIndex = uiReqNum;
	uiBufSize = sizeof(IVS_ROLE_INFO_LIST) + (uiReqNum-1)*sizeof(IVS_ROLE_INFO);
	IVS_ROLE_INFO_LIST* pRoleInfoList = reinterpret_cast<IVS_ROLE_INFO_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pRoleInfoList, 0, uiBufSize);
	iRet = IVS_SDK_GetRoleList(iSessionID, "", &IndexRange, pRoleInfoList, uiBufSize);
	if (IVS_SUCCEED == iRet)
	{
		for (IVS_UINT32 i=0; i<pRoleInfoList->uiTotal && i<uiReqNum; i++)
		{
			printf("RoleID:%d\tRoleName:%s\n", 
				pRoleInfoList->stRoleInfo[i].uiRoleID, pRoleInfoList->stRoleInfo[i].cRoleName);
		}
	}
	delete[] pRoleInfoList;
	pRoleInfoList = NULL;
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetRoleInfoByRoleID");
	memset(&RoleInfo, 0, sizeof(RoleInfo));
	iRet = IVS_SDK_GetRoleInfoByRoleID(iSessionID, pDomainCode, uiRoleID, &RoleInfo);
	if (IVS_SUCCEED == iRet)
	{
		printf("RoleID:%d\tRoleName:%s\tDescription:%s\n", RoleInfo.uiRoleID, RoleInfo.cRoleName, RoleInfo.cRoleDescribe);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetRoleInfoByUserID");
	memset(&RoleInfo, 0, sizeof(RoleInfo));
	iRet = IVS_SDK_GetRoleInfoByUserID(iSessionID, pDomainCode, 1, &RoleInfo);//1-super
	if (IVS_SUCCEED == iRet)
	{
		printf("RoleID:%d\tRoleName:%s\tDescription:%s\n", RoleInfo.uiRoleID, RoleInfo.cRoleName, RoleInfo.cRoleDescribe);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetDefaultRoleAccountRule");
	IVS_ROLE_ACCOUNT_RULE RoleAccountRule = {0};
	iRet = IVS_SDK_GetDefaultRoleAccountRule(iSessionID, pDomainCode, &RoleAccountRule);
	if (IVS_SUCCEED == iRet)
	{
		printf("Enable:%d\nUppercase:%d Lowercase:%d Figure:%d Special:%d\nFirstModify:%d\nPwdMinLen:%d\n", RoleAccountRule.bEnable, 
			RoleAccountRule.stPswConsist.bCapital, RoleAccountRule.stPswConsist.bLowercase, RoleAccountRule.stPswConsist.bFigure, 
			RoleAccountRule.stPswConsist.bSpecialChar,	RoleAccountRule.bFirstModify, RoleAccountRule.uiPwdMinLen);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetOperationRightGroup");
	uiReqNum = IVS_MAX_RIGHT_GROUP_NUM;
	uiBufSize = sizeof(IVS_OPERATION_RIGHT_GROUP_LIST) + (uiReqNum-1)*sizeof(IVS_OPERATION_RIGHT_GROUP);
	IVS_OPERATION_RIGHT_GROUP_LIST* pRightGroupList = reinterpret_cast<IVS_OPERATION_RIGHT_GROUP_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pRightGroupList, 0, uiBufSize);
	iRet = IVS_SDK_GetOperationRightGroup(iSessionID, "", pRightGroupList, uiBufSize);
	if (IVS_SUCCEED == iRet)
	{
		for (IVS_UINT32 i=0; i<pRightGroupList->uiTotal && i<uiReqNum; i++)
		{
			printf("RightGroupName:%s\tRight:%s\n", 
				pRightGroupList->stOperationRightGroup[i].cRightGroupName, pRightGroupList->stOperationRightGroup[i].cRight);
		}
	}
	delete[] pRightGroupList;
	pRightGroupList = NULL;
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_DeleteRole");
	iRet = IVS_SDK_DeleteRole(iSessionID, pDomainCode, uiRoleID);
	if (IVS_SUCCEED == iRet)
	{
		printf("RoleID:%d Deleted\n", uiRoleID);
	}
	printf("Result = %d\n", iRet);
#pragma endregion 用户角色

#pragma region 用户组
	BeginMessage("Test IVS_SDK_AddUserGroup");
	IVS_UINT32 uiUserGrpID = 100;
	IVS_USER_GROUP UserGroup;
	memset(&UserGroup, 0, sizeof(UserGroup));
	strncpy(UserGroup.cDomainCode, pDomainCodeVMU, IVS_DOMAIN_CODE_LEN);
	strncpy(UserGroup.cName, "OMG", IVS_NAME_LEN);
	UserGroup.uiParentID = 1;
	strncpy(UserGroup.cGroupDesc, "Bloody Hell", IVS_MAX_USER_GROUP_DESC_LEN);
	iRet = IVS_SDK_AddUserGroup(iSessionID, &UserGroup, &uiUserGrpID);
	if (IVS_SUCCEED == iRet)
	{
		printf("UserGrpID:%d\n", uiUserGrpID);
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_ModifyUserGroup");
	UserGroup.uiID = uiUserGrpID;
	strncpy(UserGroup.cName, "Hell", IVS_NAME_LEN);
	strncpy(UserGroup.cGroupDesc, "oops!", IVS_MAX_USER_GROUP_DESC_LEN);
	iRet = IVS_SDK_ModifyUserGroup(iSessionID, &UserGroup);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_MoveUserGroup");
	IVS_USER_GROUP_LIST UserGroupList = {0};
	UserGroupList.uiTotal = 1;
	memcpy(&UserGroupList.stUserGroup[0], &UserGroup, sizeof(UserGroupList.stUserGroup[0]));
	iRet = IVS_SDK_MoveUserGroup(iSessionID, pDomainCodeVMU, 2, &UserGroupList);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetUserGroupList");
	uiReqNum = 10;
	IndexRange.uiFromIndex = 1;
	IndexRange.uiToIndex = uiReqNum;
	uiBufSize = sizeof(IVS_USER_GROUP_LIST) + (uiReqNum - 1)*sizeof(IVS_USER_GROUP);
	IVS_USER_GROUP_LIST* pUserGroupList = reinterpret_cast<IVS_USER_GROUP_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pUserGroupList, 0, uiBufSize);
	iRet = IVS_SDK_GetUserGroupList(iSessionID, "", &IndexRange, pUserGroupList, uiBufSize);
	if (IVS_SUCCEED == iRet)
	{
		for (IVS_UINT32 i=0; i<pUserGroupList->uiTotal && i<uiReqNum; i++)
		{
			printf("GrpName:%s\tGrpID:%d\n", pUserGroupList->stUserGroup[i].cName, pUserGroupList->stUserGroup[i].uiID);
		}
	}
	delete[] pUserGroupList;
	pUserGroupList = NULL;
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_DeleteUserGroup");
	iRet = IVS_SDK_DeleteUserGroup(iSessionID, pDomainCodeVMU, uiUserGrpID);
	printf("Result = %d\n", iRet);
#pragma endregion 用户组

#pragma region 实况
	BeginMessage("Test IVS_SDK_StartRealPlayCBRaw");
	IVS_REALPLAY_PARAM RealplayPara = {0};
	RealplayPara.bDirectFirst = 0;
	RealplayPara.bMultiCast = 1;
	RealplayPara.uiProtocolType = 1;
	RealplayPara.uiStreamType = STREAM_TYPE_MAIN;
	iRet = IVS_SDK_StartRealPlayCBRaw(iSessionID, &RealplayPara, pCameraCode235, RealPlayRawCallBack, (IVS_VOID*)"HUAWEI", &ulPlayHandle);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_SetPlayQualityMode");
	iRet = IVS_SDK_SetPlayQualityMode(iSessionID, ulPlayHandle, PLAY_QUALITY_DEFINITION);
	printf("Result = %d\n", iRet);
	sleep(1);

	BeginMessage("Test IVS_SDK_StopRealPlay");
	iRet = IVS_SDK_StopRealPlay(iSessionID, ulPlayHandle);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_StartRealPlayByIP");
	IVS_MEDIA_ADDR MediaAddrDst = {0};
	IVS_MEDIA_ADDR MediaAddrSrc = {0};
	MediaAddrDst.stIP.uiIPType = IP_V4;
	strncpy(MediaAddrDst.stIP.cIP, "10.170.54.78", IVS_IP_LEN);
	MediaAddrDst.uiAudioPort = 2048;
	MediaAddrDst.uiVideoPort = 2050;
	iRet = IVS_SDK_StartRealPlayByIP(iSessionID, pCameraCode235, &MediaAddrDst, &MediaAddrSrc, &ulPlayHandle);
	if (IVS_SUCCEED == iRet)
	{
		printf("SrcVideoPort:%d SrcAudioPort:%d\n", MediaAddrSrc.uiVideoPort, MediaAddrSrc.uiAudioPort);
	}
	printf("Result = %d\n", iRet);
	sleep(2);

	BeginMessage("Test IVS_SDK_StopRealPlayByIP");
	iRet = IVS_SDK_StopRealPlayByIP(iSessionID, ulPlayHandle);
	printf("Result = %d\n", iRet);
#pragma endregion 实况

#pragma region 磁盘（组）
	BeginMessage("Test IVS_SDK_OMUQueryRaidGroup");
	iRet = IVS_SDK_OMUQueryRaidGroup(iSessionID, &pRspXml);
	if (IVS_SUCCEED == iRet)
	{
		printf("%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_OMUQueryRaidGroupDisk");
	strReqXml = "<Content><PortalClientIP></PortalClientIP></Content>";
	iRet = IVS_SDK_OMUQueryRaidGroupDisk(iSessionID, strReqXml.c_str(), &pRspXml);
	if (IVS_SUCCEED == iRet)
	{
		printf("%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);
#pragma endregion 磁盘（组）

#pragma region 前端设备
	BeginMessage("Test IVS_SDK_SetDevPWD");
	iRet = IVS_SDK_SetDevPWD(iSessionID, pMainDevCode617, "admin", "huawei123", "");
	printf("Result = %d\n", iRet);
#pragma endregion 前端设备

#pragma region 录像
	BeginMessage("Test IVS_SDK_StartPlatformRecord");
	iRet = IVS_SDK_StartPlatformRecord(iSessionID, pCameraCode235, 300);
	printf("Result = %d\n", iRet);
	sleep(3);

	BeginMessage("Test IVS_SDK_StopPlatformRecord");
	iRet = IVS_SDK_StopPlatformRecord(iSessionID, pCameraCode235);
	printf("Result = %d\n", iRet);
#pragma endregion 录像

#pragma region 新开发接口
	BeginMessage("Test IVS_SDK_StartRealPlayByIPEx");
	IVS_REALPLAY_PARAM  RealplayParam = {0};
	RealplayParam.bDirectFirst = MEDIA_DIRECT;
	RealplayParam.bMultiCast = BROADCAST_MULTICAST;
	RealplayParam.uiProtocolType = PROTOCOL_RTP_OVER_TCP;
	RealplayParam.uiStreamType = STREAM_TYPE_MAIN;
	//IVS_MEDIA_ADDR MediaAddrDst = {0};
	//IVS_MEDIA_ADDR MediaAddrSrc = {0};
	//MediaAddrDst.stIP.uiIPType = IP_V4;
	//strncpy(MediaAddrDst.stIP.cIP, "10.170.54.78", IVS_IP_LEN);
	MediaAddrDst.uiAudioPort = 2052;
	MediaAddrDst.uiVideoPort = 2054;
	iRet = IVS_SDK_StartRealPlayByIPEx(iSessionID, &RealplayParam, pCameraCode235, &MediaAddrDst, &MediaAddrSrc, &ulPlayHandle);
	if (IVS_SUCCEED == iRet)
	{
		printf("SrcVideoPort:%d SrcAudioPort:%d\n", MediaAddrSrc.uiVideoPort, MediaAddrSrc.uiAudioPort);
	}
	printf("Result = %d\n", iRet);
	sleep(3);

	BeginMessage("Test IVS_SDK_StopRealPlayByIPEx");
	iRet = IVS_SDK_StopRealPlayByIPEx(iSessionID, ulPlayHandle);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_StartPlatformPlayBackByIP");
	IVS_PLAYBACK_PARAM PlaybackParam = {0};
	PlaybackParam.uiProtocolType = 1;
	PlaybackParam.fSpeed = 1.0;
	strncpy(PlaybackParam.stTimeSpan.cStart, "20140103013139", IVS_TIME_LEN);
	strncpy(PlaybackParam.stTimeSpan.cEnd, "20140103013639", IVS_TIME_LEN);
	//IVS_MEDIA_ADDR MediaAddrDst = {0};
	//IVS_MEDIA_ADDR MediaAddrSrc = {0};
	//MediaAddrDst.stIP.uiIPType = IP_V4;
	//strncpy(MediaAddrDst.stIP.cIP, "10.170.54.78", IVS_IP_LEN);
	MediaAddrDst.uiAudioPort = 2056;
	MediaAddrDst.uiVideoPort = 2058;
	iRet = IVS_SDK_StartPlatformPlayBackByIP(iSessionID, pCameraCode235, &PlaybackParam, &MediaAddrDst, &MediaAddrSrc, &ulPlayHandle);
	if (IVS_SUCCEED == iRet)
	{
		printf("SrcVideoPort:%d SrcAudioPort:%d\n", MediaAddrSrc.uiVideoPort, MediaAddrSrc.uiAudioPort);
	}
	printf("Result = %d\n", iRet);
	sleep(3);

	BeginMessage("Test IVS_SDK_StopPlatformPlayBackByIP");
	iRet = IVS_SDK_StopPlatformPlayBackByIP(iSessionID, ulPlayHandle);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_PtzControlWithLockerInfo");
	//IVS_UINT32 uiLockStatus = 2;
	IVS_PTZ_CONTROL_INFO PtzControlInfo = {0};
	iRet = IVS_SDK_PtzControlWithLockerInfo(iSessionID, pCameraCode617, PTZ_STOP, "2", "3", &PtzControlInfo);
	printf("LockStatus:%d\nResult = %d\n", PtzControlInfo.uiLockStatus, iRet);
#pragma endregion 新开发接口

#pragma region 设备组
	BeginMessage("Test IVS_SDK_AddDeviceGroup");
	IVS_DEV_GROUP DevGroup;
	memset(&DevGroup, 0, sizeof(DevGroup));
	strncpy(DevGroup.cDomainCode, pDomainCode, IVS_DOMAIN_CODE_LEN);
	strncpy(DevGroup.cName, "Ping", IVS_NAME_LEN);
	DevGroup.uiParentID = 0;
	IVS_UINT32 uiDevGrpIDPing = 100;
	iRet = IVS_SDK_AddDeviceGroup(iSessionID, &DevGroup, &uiDevGrpIDPing);
	strncpy(DevGroup.cName, "Pang", IVS_NAME_LEN);
	IVS_UINT32 uiDevGrpIDPang = 100;
	iRet = IVS_SDK_AddDeviceGroup(iSessionID, &DevGroup, &uiDevGrpIDPang);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetDeviceGroup");
	uiBufSize = sizeof(IVS_DEVICE_GROUP_LIST) + 19*sizeof(IVS_DEVICE_GROUP);
	IVS_DEVICE_GROUP_LIST* pDeviceGroupList = reinterpret_cast<IVS_DEVICE_GROUP_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pDeviceGroupList, 0, uiBufSize);
	iRet = IVS_SDK_GetDeviceGroup(iSessionID, pDomainCode, "0", pDeviceGroupList, uiBufSize);//系统默认的根设备组ID是"0"
	if (IVS_SUCCEED == iRet) 
	{ 
		printf("Total:%d\n", pDeviceGroupList->uiTotal);
		for (IVS_INT32 i=0; i<pDeviceGroupList->uiTotal; i++)
		{
			printf("Name:%s\tGroupCode:%s\tParentCode:%s\n", 
				pDeviceGroupList->stDeviceGroup[i].cGroupName, pDeviceGroupList->stDeviceGroup[i].cGroupCode, pDeviceGroupList->stDeviceGroup[i].cParentGroupCode);
		}
	}
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_ModifyDeviceGroupName");
	iRet = IVS_SDK_ModifyDeviceGroupName(iSessionID, pDomainCode, uiDevGrpIDPing, "Big");
	iRet = IVS_SDK_ModifyDeviceGroupName(iSessionID, pDomainCode, uiDevGrpIDPang, "Bang");
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_MoveDeviceGroup");
	iRet = IVS_SDK_MoveDeviceGroup(iSessionID, pDomainCode, uiDevGrpIDPing, uiDevGrpIDPang);
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_GetDeviceGroup");
	memset(pDeviceGroupList, 0, uiBufSize);
	iRet = IVS_SDK_GetDeviceGroup(iSessionID, pDomainCode, "0", pDeviceGroupList, uiBufSize);//系统默认的根设备组ID是"0"
	if (IVS_SUCCEED == iRet) 
	{ 
		printf("Total:%d\n", pDeviceGroupList->uiTotal);
		for (IVS_INT32 i=0; i<pDeviceGroupList->uiTotal; i++)
		{
			printf("Name:%s\tGroupCode:%s\tParentCode:%s\n", 
				pDeviceGroupList->stDeviceGroup[i].cGroupName, pDeviceGroupList->stDeviceGroup[i].cGroupCode, pDeviceGroupList->stDeviceGroup[i].cParentGroupCode);
		}
	}
	delete[] pDeviceGroupList;
	pDeviceGroupList = NULL;
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_AddDeviceToGroup");
	IVS_DEV_GROUP_CAMERA DevCamera = {0};
	strncpy(DevCamera.cCameraCode, pCameraCode235, IVS_DEV_CODE_LEN);
	strncpy(DevCamera.cCameraDomainCode, pDomainCode, IVS_DOMAIN_CODE_LEN);
	DevCamera.uiDevGroupID = 0;
	iRet = IVS_SDK_AddDeviceToGroup(iSessionID, pDomainCode, uiDevGrpIDPang, 1, &DevCamera);
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_DeleteDeviceFromGroup");
	DevCamera.uiDevGroupID = uiDevGrpIDPang;
	iRet = IVS_SDK_DeleteDeviceFromGroup(iSessionID, pDomainCode, 1, &DevCamera);
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_DeleteDeviceGroup");
	iRet = IVS_SDK_DeleteDeviceGroup(iSessionID, pDomainCode, uiDevGrpIDPang);
	iRet = IVS_SDK_DeleteDeviceGroup(iSessionID, pDomainCode, uiDevGrpIDPing);
	printf("Result = %d\n", iRet);
#pragma endregion 设备组

#pragma region 子设备列表
	BeginMessage("Test IVS_SDK_GetChannelList");
	uiReqNum = 20;
	uiBufSize = sizeof(IVS_DEV_CHANNEL_BRIEF_INFO_LIST) + (uiReqNum-1)*sizeof(IVS_DEV_CHANNEL_BRIEF_INFO);
	IVS_DEV_CHANNEL_BRIEF_INFO_LIST* pChannelList = reinterpret_cast<IVS_DEV_CHANNEL_BRIEF_INFO_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pChannelList, 0, uiBufSize);
	pChannelList->stIndexRange.uiFromIndex = 1;
	pChannelList->stIndexRange.uiToIndex = uiReqNum;
	iRet = IVS_SDK_GetChannelList(iSessionID, pMainDevCode235, pChannelList, uiBufSize);
	if (IVS_SUCCEED == iRet)
	{
		printf("Total:%d\n", pChannelList->uiTotal);
		for (IVS_UINT32 i=0; i<pChannelList->uiTotal && i<uiReqNum; i++)
		{
			printf("Code:%s\tType:%d\tName:%s\n", 
				pChannelList->stDevChannelBriefInfo[i].cChannelCode, pChannelList->stDevChannelBriefInfo[i].uiChannelType, pChannelList->stDevChannelBriefInfo[i].cChannelName);
		}
	}
	delete[] pChannelList;
	pChannelList = NULL;
	printf("Result = %d\n", iRet);
#pragma endregion 子设备列表

#pragma region 操作日志
	BeginMessage("Test IVS_SDK_GetOperationLog");
	uiReqNum = 100;
	memset(&UnifiedQuery, 0, sizeof(UnifiedQuery));
	UnifiedQuery.iFieldNum = 0;
	UnifiedQuery.stIndex.uiFromIndex = 1;
	UnifiedQuery.stIndex.uiToIndex = uiReqNum;
	uiBufSize = sizeof(IVS_OPERATION_LOG_LIST) + (uiReqNum-1)*sizeof(IVS_OPERATION_LOG_INFO);
	IVS_OPERATION_LOG_LIST* pResOperLogList = reinterpret_cast<IVS_OPERATION_LOG_LIST*>(new IVS_CHAR[uiBufSize]);
	memset(pResOperLogList, 0, uiBufSize);
	iRet = IVS_SDK_GetOperationLog(iSessionID, &UnifiedQuery, pResOperLogList, uiBufSize);
	if (IVS_SUCCEED == iRet)
	{
		printf("Total:%d From:%d To:%d\n", pResOperLogList->uiTotal, pResOperLogList->stIndexRange.uiFromIndex, pResOperLogList->stIndexRange.uiToIndex);
	}
	delete[] pResOperLogList;
	pResOperLogList = NULL;
	printf("Result = %d\n", iRet);
#pragma endregion 操作日志

#pragma region 防区
	BeginMessage("Test IVS_SDK_AddAlarmArea");
	strReqXml = "";
	strReqXml += "<Content>";
	strReqXml +=	"<DomainCode>";
	strReqXml +=		pDomainCode;
	strReqXml +=	"</DomainCode>";
	strReqXml +=	"<AlarmAreaInfo>";
	strReqXml +=		"<AlarmAreaName>Rucifr</AlarmAreaName>";
	strReqXml +=		"<AlarmInList>";
	strReqXml +=			"<AlarmInInfo>";
	strReqXml +=				"<AlarmInCode>";
	strReqXml +=					pCameraCode235;
	strReqXml +=				"</AlarmInCode>";
	strReqXml +=				"<DevDomainCode>";
	strReqXml +=					pDomainCode;
	strReqXml +=				"</DevDomainCode>";
	strReqXml +=			"</AlarmInInfo>";
	strReqXml +=		"</AlarmInList>";
	strReqXml +=	"</AlarmAreaInfo>";
	strReqXml += "</Content>";
	pRspXml = NULL;
	std::string strAlarmAreaID = "";
	iRet = IVS_SDK_AddAlarmArea(iSessionID, strReqXml.c_str(), &pRspXml);
	if (NULL != pRspXml)
	{
		std::string strRspXml = pRspXml;
		IVS_UINT32 uiStartPos = strRspXml.find("<AlarmAreaID>") + strlen("<AlarmAreaID>");
		IVS_UINT32 uiEndPos = strRspXml.find("</AlarmAreaID>");
		strAlarmAreaID = strRspXml.substr(uiStartPos, uiEndPos-uiStartPos);
		printf("AlarmAreaID:%s\nRspXml:%s\n", strAlarmAreaID.c_str(), pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetAlarmAreaInfo");
	pRspXml = NULL;
	iRet = IVS_SDK_GetAlarmAreaInfo(iSessionID, pDomainCode, atoi(strAlarmAreaID.c_str()), &pRspXml);
	if (NULL != pRspXml)
	{
		printf("AlarmAreaInfo:%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_ModifyAlarmArea");
	strReqXml = "";
	strReqXml += "<Content>";
	strReqXml +=	"<DomainCode>";
	strReqXml +=		pDomainCode;
	strReqXml +=	"</DomainCode>";
	strReqXml +=	"<AlarmAreaInfo>";
	strReqXml +=		"<AlarmAreaID>";
	strReqXml +=			strAlarmAreaID;
	strReqXml +=		"</AlarmAreaID>";
	strReqXml +=		"<AlarmAreaName>Lucifer</AlarmAreaName>";
	strReqXml +=		"<AlarmInList>";
	strReqXml +=			"<AlarmInInfo>";
	strReqXml +=				"<AlarmInCode>";
	strReqXml +=					pCameraCode235;
	strReqXml +=				"</AlarmInCode>";
	strReqXml +=				"<DevDomainCode>";
	strReqXml +=					pDomainCode;
	strReqXml +=				"</DevDomainCode>";
	strReqXml +=			"</AlarmInInfo>";
	strReqXml +=			"<AlarmInInfo>";
	strReqXml +=				"<AlarmInCode>";
	strReqXml +=					pCameraCodeTest;
	strReqXml +=				"</AlarmInCode>";
	strReqXml +=				"<DevDomainCode>";
	strReqXml +=					pDomainCode;
	strReqXml +=				"</DevDomainCode>";
	strReqXml +=			"</AlarmInInfo>";
	strReqXml +=		"</AlarmInList>";
	strReqXml +=	"</AlarmAreaInfo>";
	strReqXml += "</Content>";
	iRet = IVS_SDK_ModifyAlarmArea(iSessionID, strReqXml.c_str());
	printf("Result = %d\n", iRet);
	
	BeginMessage("Test IVS_SDK_GetAlarmAreaList");
	strReqXml = "";
	strReqXml += "<Content>";
	strReqXml +=	"<DomainCode>";
	strReqXml +=		pDomainCode;
	strReqXml +=	"</DomainCode>";
	strReqXml +=	"<PageInfo>";
	strReqXml +=		"<FromIndex>1</FromIndex>";
	strReqXml +=		"<ToIndex>10</ToIndex>";
	strReqXml +=		"<QueryCond>";
	strReqXml +=			"<QueryField>";
	strReqXml +=				"<Field>AlarmAreaName</Field>";
	strReqXml +=				"<Value>r</Value>";
	strReqXml +=				"<QueryType>INEXACT</QueryType>";
	strReqXml +=			"</QueryField>";
	strReqXml +=			"<QueryField>";
	strReqXml +=				"<Field>AlarmInCode</Field>";
	strReqXml +=				"<Value>";
	strReqXml +=					pCameraCode235;
	strReqXml +=				"</Value>";
	strReqXml +=				"<QueryType>EXACT</QueryType>";
	strReqXml +=			"</QueryField>";
	strReqXml +=		"</QueryCond>";
	strReqXml +=	"</PageInfo>";
	strReqXml += "</Content>";
	pRspXml = NULL;
	iRet = IVS_SDK_GetAlarmAreaList(iSessionID, strReqXml.c_str(), &pRspXml);
	if (NULL != pRspXml)
	{
		printf("RspXml:%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_StartAlarmAreaGuard");
	iRet = IVS_SDK_StartAlarmAreaGuard(iSessionID, pDomainCode, atoi(strAlarmAreaID.c_str()));
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_AllocAreaGuardPlan");
	strReqXml = "";
	strReqXml += "<Content>";
	strReqXml +=	"<DomainCode>";
	strReqXml +=		pDomainCode;
	strReqXml +=	"</DomainCode>";
	strReqXml +=	"<Plan>";
	strReqXml +=		"<AlarmAreaID>";
	strReqXml +=			strAlarmAreaID;
	strReqXml +=		"</AlarmAreaID>";
	strReqXml +=		"<PlanType>DAY</PlanType>";//DAY-日计划 WEEK-周计划
	strReqXml +=		"<IsStartup>1</IsStartup>";//0-不启用 1-启用
	strReqXml +=		"<PlanList>";
	strReqXml +=			"<PlanInfo>";
	strReqXml +=				"<DayType>0</DayType>";//每天
	strReqXml +=				"<TimeInfoNum>2</TimeInfoNum>";
	strReqXml +=				"<TimeList>";
	strReqXml +=					"<TimeInfo>";
	strReqXml +=						"<StartTime>080000</StartTime>";
	strReqXml +=						"<EndTime>095959</EndTime>";
	strReqXml +=					"</TimeInfo>";
	strReqXml +=					"<TimeInfo>";
	strReqXml +=						"<StartTime>150000</StartTime>";
	strReqXml +=						"<EndTime>165959</EndTime>";
	strReqXml +=					"</TimeInfo>";
	strReqXml +=				"</TimeList>";
	strReqXml +=			"</PlanInfo>";
	strReqXml +=		"</PlanList>";
	strReqXml +=	"</Plan>";
	strReqXml += "</Content>";
	iRet = IVS_SDK_AllocAreaGuardPlan(iSessionID, strReqXml.c_str());
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_GetAreaGuardPlan");
	pRspXml = NULL;
	iRet = IVS_SDK_GetAreaGuardPlan(iSessionID, pDomainCode, atoi(strAlarmAreaID.c_str()), &pRspXml);
	if (NULL != pRspXml)
	{
		printf("RspXml:%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_SetDeviceGuard");
	strReqXml = "";
	strReqXml += "<Content>";
	strReqXml +=	"<DomainCode>86a067dbfab647bab5f7d6be882ef1c6</DomainCode>";
	strReqXml +=	"<DevInfo>";
	strReqXml +=		"<DevCode>04598710000000000101#86a067dbfab647bab5f7d6be882ef1c6</DevCode>";
	strReqXml +=		"<State>GUARD</State>";//UNGUARD
	strReqXml +=	"</DevInfo>";
	strReqXml += "</Content>";
	iRet = IVS_SDK_SetDeviceGuard(iSessionID, strReqXml.c_str());
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_StopAlarmAreaGuard");
	iRet = IVS_SDK_StopAlarmAreaGuard(iSessionID, pDomainCode, atoi(strAlarmAreaID.c_str()));
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_DeleteAlarmArea");
	iRet = IVS_SDK_DeleteAlarmArea(iSessionID, pDomainCode, atoi(strAlarmAreaID.c_str()));
	printf("Result = %d\n", iRet);
#pragma endregion 防区

#pragma region 搜索前端设备
	BeginMessage("Test IVS_SDK_StartSearchDevice");
	strReqXml = "";
	strReqXml +=	"<Content>";
	strReqXml +=		"<SearchInfo>";
	strReqXml +=			"<ProtocolType>HIKSDK</ProtocolType>";
	strReqXml +=			"<ServerCode>73dd44b0d0604463a7837fc7519f92c9</ServerCode>";
	strReqXml +=			"<IPList>";
	strReqXml +=				"<IPInfo>";
	strReqXml +=					"<DevIPFrom>10.170.54.46</DevIPFrom>";
	strReqXml +=					"<DevIPTo>10.170.54.50</DevIPTo>";
	strReqXml +=					"<DevPort></DevPort>";
	strReqXml +=				"</IPInfo>";
	strReqXml +=			"</IPList>";
	strReqXml +=		"</SearchInfo>";
	strReqXml +=	"</Content>";
	iRet = IVS_SDK_StartSearchDevice(iSessionID, "f563c8bc3f8240009637a9edd500ca19", strReqXml.c_str());
	printf("Result = %d\n", iRet);

	sleep(20);

	BeginMessage("Test IVS_SDK_StopSearchDevice");
	strReqXml = "";
	strReqXml +=	"<Content>";
	strReqXml +=		"<ServerCode>73dd44b0d0604463a7837fc7519f92c9</ServerCode>";
	strReqXml +=	"</Content>";
	iRet = IVS_SDK_StopSearchDevice(iSessionID, "f563c8bc3f8240009637a9edd500ca19", strReqXml.c_str());
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_VerifyDevice");
	strReqXml = "";
	strReqXml +=	"<Content>";
	strReqXml +=		"<ValidateInfo>";
	strReqXml +=			"<ServerCode>73dd44b0d0604463a7837fc7519f92c9</ServerCode>";//10.170.103.90
	strReqXml +=			"<ProtocolType>HIKSDK</ProtocolType>";
	strReqXml +=			"<DevIP>10.170.54.48</DevIP>";
	strReqXml +=			"<DevPort>8000</DevPort>";
	strReqXml +=			"<DevUser>admin</DevUser>";
	strReqXml +=			"<DevPWD>huawei123</DevPWD>";
	strReqXml +=		"</ValidateInfo>";
	strReqXml +=	"</Content>";
	pRspXml = NULL;
	iRet = IVS_SDK_VerifyDevice(iSessionID, "f563c8bc3f8240009637a9edd500ca19", strReqXml.c_str(), &pRspXml);
	if (NULL != pRspXml)
	{
		printf("RspXml:%s\n", pRspXml);
		IVS_SDK_ReleaseBuffer(pRspXml);
		pRspXml = NULL;
	}
	printf("Result = %d\n", iRet);
#pragma endregion 搜索前端设备

#pragma region 结束
	BeginMessage("Test IVS_SDK_Logout");
	iRet = IVS_SDK_Logout(iSessionID);
	printf("Result = %d\n", iRet);

	BeginMessage("Test IVS_SDK_Cleanup");
	iRet = IVS_SDK_Cleanup();
	printf("Result = %d\n", iRet);
#pragma endregion 结束

	return 0;
}

IVS_VOID BeginMessage(const IVS_CHAR* pContent)
{
	IVS_UINT32 uiMsgLen = 120;
	IVS_UINT32 uiTitleLen = strlen(pContent);
	if (uiMsgLen < uiTitleLen)
		return;
	IVS_CHAR pMessage[120];
	memset(pMessage, '=', uiMsgLen);
	pMessage[uiMsgLen-1] = '\0';
	IVS_UINT32 uiEndPoint = (uiMsgLen - uiTitleLen) / 2;
	pMessage[uiEndPoint] = '\0';
	strncpy(pMessage+uiEndPoint, pContent, uiTitleLen);
	printf("\n%s\n", pMessage);
}

IVS_VOID RealPlayRawCallBack(IVS_ULONG ulHandle, IVS_RAW_FRAME_INFO* pRawFrameInfo, IVS_VOID* pBuf, IVS_UINT32 uiBufSize, IVS_VOID* pUserData)
{
	if(99 == pRawFrameInfo->uiStreamType || 26 == pRawFrameInfo->uiStreamType)
	{
		static int iCnt = 0;
		iCnt++;
		if (0 == iCnt%3)
		{
			printf("---RealPlayRawCallBack Being Called---\n");
		}
	}
}
