/********************************************************************
	filename	: 	LogMgrXMLProcess.h
	author		:	wulixia
	created		:	2012/12/03	
	description	:	处理操作日志XML
	copyright	:	Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
	history		:	2012/12/03 初始版本
*********************************************************************/

#ifndef __LOG_MGR_XML_PROCESS_H__
#define __LOG_MGR_XML_PROCESS_H__

#include "XmlProcess.h"

class CLogMgrXMLProcess
{
private:
	CLogMgrXMLProcess();
public:
	~CLogMgrXMLProcess();

public:
	/*****************************************************************
     function   : PraseResOperationLogXML
     description: 查询操作日志解析响应
	 intput     : pResOperationLog，响应消息结构体
	              iBufSize，缓存大小
     output     : xml，定义的目标xml
     return     : 成功返回0，失败返回错误码;
     *****************************************************************/

	static IVS_INT32 PraseResOperationLogXML(CXml& xml,IVS_OPERATION_LOG_LIST* pResOperationLog,const IVS_UINT32& uiBufSize);

	
};

#endif //__LOG_MGR_XML_PROCESS_H__

