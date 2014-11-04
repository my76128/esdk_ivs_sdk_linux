/*****************************************************************
 filename    :    LogMgr.h
 author      :    wWX155351
 created     :    2012/11/14
 description :    查询操作日志;
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2012/11/14 初始版本
*****************************************************************/

//#pragma once

#ifndef _OPERATIONLOG_MNG_H_
#define _OPERATIONLOG_MNG_H_


#include "hwsdk.h"
#include "ivs_error.h"

/*
#include "NSSOperator.h"
#include "nss_mt.h"*/
class CUserMgr;
class CLogMgr
{
public:
	CLogMgr(void);
	~CLogMgr(void);

	// 设置用户对象类
	void SetUserMgr(void *pUserMgr);

private:
	CUserMgr *m_pUserMgr;

public:
	// 查询操作日志
	IVS_INT32 GetOperationLog(const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, IVS_OPERATION_LOG_LIST* pResOperLogList,const IVS_UINT32& uiBufSize) const;

};
#endif 

