#pragma once

#include <CryExtension/ICryUnknown.h>


struct IAwesomium : public ICryUnknown
{
	CRYINTERFACE_DECLARE(IAwesomium, 0x2386a062a90e40b4, 0xbb3761084a4e5895)

	virtual bool Init(bool enablePlugins) = 0;
	virtual void Shutdown() = 0;
	virtual void SetVisible(bool visible) = 0;
	virtual bool IsVisible() const = 0;
};

typedef boost::shared_ptr<IAwesomium> IAwesomiumPtr;