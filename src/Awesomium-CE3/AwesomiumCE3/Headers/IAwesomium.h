#pragma once

#include <CryExtension/ICryUnknown.h>


struct IAwesomium : public ICryUnknown
{
	CRYINTERFACE_DECLARE(IAwesomium, 0x0, 0x1)

	virtual bool Init(bool enablePlugins) = 0;
	virtual void Shutdown() = 0;
};

typedef boost::shared_ptr<IAwesomium> IAwesomiumPtr;