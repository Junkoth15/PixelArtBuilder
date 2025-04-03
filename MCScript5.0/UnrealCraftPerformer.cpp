#include "UnrealCraftPerformer.h"
#include"NoImagePerformer120.h"
#include"WinReader.h"
#include"UnrealCraftPackage.h"
#include"UnrealCraftPlayerInfoReader.h"
#include"UnrealCraftContainReader.h"

UnrealCraftPerformer::UnrealCraftPerformer(HWND window):
	ImagePerformer120(window,nullptr,nullptr,nullptr)
{
	//��װperforemer
	shared_ptr<UnrealCraftPackage> package = make_shared<UnrealCraftPackage>();
	shared_ptr<NoImagePerformer120> performer = make_shared<NoImagePerformer120>(window,package);
	setPerformer(performer);
	//��װPlayerReader
	setPlayerReader(make_shared<UnrealCraftPlayerInfoReader>());
	//��װContainReader
	setContainReader(make_shared<UnrealCraftContainReader>());
}
