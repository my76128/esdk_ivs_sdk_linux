#include "LogMgrXMLProcess.h"
#include "ToolsHelp.h"
#include "bp_log.h"
#include "ivs_xml.h"
#include "UserMgr.h"
#include "IVS_Trace.h"

CLogMgrXMLProcess::CLogMgrXMLProcess()
{
}

CLogMgrXMLProcess::~CLogMgrXMLProcess()
{
}

// 解析响应xml
IVS_INT32 CLogMgrXMLProcess::PraseResOperationLogXML(CXml& xml,IVS_OPERATION_LOG_LIST* pResOperationLog,const IVS_UINT32& uiBufSize)
{
	CHECK_POINTER(pResOperationLog, IVS_OPERATE_MEMORY_ERROR);  
	IVS_DEBUG_TRACE("");

	if (!xml.FindElem("Content"))
	{
		BP_RUN_LOG_ERR(IVS_XML_INVALID, "Prase Response Operation Log XML ", "xml.FindElem(Content) is fail");
		return IVS_XML_INVALID;
	}   
	xml.IntoElem();
	if (!xml.FindElem("PageInfo"))
	{
		BP_RUN_LOG_ERR(IVS_XML_INVALID, "Prase Response Operation Log XML", "xml.FindElem(PageInfo) is fail");
		return IVS_XML_INVALID;
	}
	xml.IntoElem();
	const char* szElemValue = NULL;
	IVS_INT32 iTotal = 0;
	IVS_INT32 iFromIndex = 0;
	IVS_INT32 iToIndex = 0;
	GET_ELEM_VALUE_NUM("RealNum", szElemValue,iTotal , xml);
	GET_ELEM_VALUE_NUM("FromIndex", szElemValue, iFromIndex, xml);
	GET_ELEM_VALUE_NUM("ToIndex",szElemValue,iToIndex , xml);

	// 判断RealNum，FromIndex，ToIndex是否合法
	if (iTotal < 0 || iToIndex < 0 || iFromIndex < 0 || iFromIndex > iToIndex)
	{
		BP_RUN_LOG_ERR(IVS_XML_INVALID, "Prase Response Operation Log XML", "ToIndex[%d], FromIndex[%d], ToIndex[%d]", iTotal, iFromIndex, iToIndex);
		return IVS_XML_INVALID;
	}	

	pResOperationLog->stIndexRange.uiFromIndex = static_cast<IVS_UINT32>(iFromIndex);
	pResOperationLog->stIndexRange.uiToIndex = static_cast<IVS_UINT32>(iToIndex);
	pResOperationLog->uiTotal = static_cast<IVS_UINT32>(iTotal);
	xml.OutOfElem();	
	if (0 == iTotal)
	{
		return IVS_SUCCEED;
	}
	if (!xml.FindElem("OperationLogList"))
	{
		BP_RUN_LOG_ERR(IVS_XML_INVALID, "Prase Response Operation Log XML", "Find Elememt(OperationLogList) failed");
		return IVS_XML_INVALID;
	}
	xml.IntoElem();  
	// 响应消息中传回来的页数
	IVS_UINT32 uiResNum = ((pResOperationLog->stIndexRange).uiToIndex - (pResOperationLog->stIndexRange).uiFromIndex) + 1;
	// 实际要用到的内存大小
	IVS_UINT32 uiResBufSize = sizeof(IVS_OPERATION_LOG_LIST) + ((uiResNum) - 1) * sizeof(IVS_OPERATION_LOG_INFO);
	// 实际需要内存与分配内存大小的比较
	if (uiBufSize < uiResBufSize)
	{
		BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "Prase Response Operation Log XML","memory is not enough");
		return IVS_ALLOC_MEMORY_ERROR;
	}
	IVS_UINT32 i = 0;	

	if (!xml.FindElem("OperationLogInfo"))
	{
		BP_RUN_LOG_ERR(IVS_XML_INVALID, "Prase Response Operation Log XML", "Find Elememt(OperationLogInfo) failed");
		return IVS_XML_INVALID;
	}  
	while(i < uiResNum)
	{
		IVS_OPERATION_LOG_INFO &pOperationLogInfo = pResOperationLog->stOperationInfo[i];
		xml.IntoElem();		
		IVS_INT32 iTemp = 0;
		GET_ELEM_VALUE_CHAR("Account", szElemValue,  pOperationLogInfo.cAccount, (IVS_NAME_LEN), xml);
		GET_ELEM_VALUE_CHAR("ClientIP", szElemValue, pOperationLogInfo.cClientIp, (IVS_IP_LEN), xml);
		GET_ELEM_VALUE_NUM("Grade", szElemValue, iTemp,xml);
		pOperationLogInfo.iGrade = static_cast<IVS_UINT32>(iTemp);
		GET_ELEM_VALUE_CHAR("ServiceCode", szElemValue,pOperationLogInfo.cServiceCode, (IVS_DESCRIBE_LEN), xml);
		GET_ELEM_VALUE_CHAR("ModuleType", szElemValue,pOperationLogInfo.cModuleType, (IVS_DESCRIBE_LEN), xml);
		GET_ELEM_VALUE_CHAR("ModuleCode", szElemValue,pOperationLogInfo.cModuleCode, (IVS_DEV_CODE_LEN), xml);
		GET_ELEM_VALUE_CHAR("OperationCode", szElemValue,pOperationLogInfo.cOperationCode, (IVS_DEV_CODE_LEN), xml);
		GET_ELEM_VALUE_CHAR("OperationObjectCode", szElemValue,pOperationLogInfo.cOperationObjectCode, (IVS_DESCRIBE_LEN), xml);
		GET_ELEM_VALUE_CHAR("OccurTime", szElemValue,pOperationLogInfo.cOccurTime, (IVS_TIME_LEN),xml);
		GET_ELEM_VALUE_CHAR("ErrorCode", szElemValue,pOperationLogInfo.cErrorCode, (IVS_DESCRIBE_LEN), xml);
		GET_ELEM_VALUE_NUM("Result", szElemValue, iTemp, xml);
		pOperationLogInfo.iResult = static_cast<IVS_UINT32>(iTemp);
		GET_ELEM_VALUE_CHAR("AdditionalInfo", szElemValue,pOperationLogInfo.cAdditionalInfo, (IVS_DESCRIBE_LEN), xml);
		xml.OutOfElem();
		if (!xml.NextElem())
		{
			break;
		}
		i++;
	}    

	xml.OutOfElem();
	return IVS_SUCCEED;
}
