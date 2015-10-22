//
//  WGPlatformObserver.h
//  WGPlatform
//
//  Created by fly chen on 2/22/13.
//  Copyright (c) 2013 tencent.com. All rights reserved.
//

#ifndef WGPlatform_WGQQGroupObserver_h
#define WGPlatform_WGQQGroupObserver_h

#include <string>
#include "WGCommon.h"

/*! @brief 广告通知类
 *
 * SDK通过通知类和外部调用者通讯
 */
class WGQQGroupObserver
{
public:
    virtual void OnQueryGroupInfoNotify(QQGroupRet& groupRet) = 0;
    virtual void OnBindGroupNotify(QQGroupRet& groupRet) = 0;
    virtual void OnUnbindGroupNotify(QQGroupRet& groupRet) = 0;

	virtual ~WGQQGroupObserver() {};
	
};

#endif
