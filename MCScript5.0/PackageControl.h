#pragma once
#include<string>
#include <memory>
#include"Package.h"
#include"NameSpace.h"
class PackageControl
{
public:
	virtual string getPackageInfo() = 0;
	virtual shared_ptr<Package> getPackage() = 0;
	virtual shared_ptr<Package> setPackage(shared_ptr<Package> package) = 0;
	virtual void open_Or_closePackage() = 0;
};

