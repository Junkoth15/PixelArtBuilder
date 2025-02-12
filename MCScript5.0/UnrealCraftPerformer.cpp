#include "UnrealCraftPerformer.h"
#include"NoImagePerformer120.h"
#include"UnrealCraftWinReader.h"
#include"UnrealCraftPackage.h"

UnrealCraftPerformer::UnrealCraftPerformer(HWND window):
	ImagePerformer120(window,nullptr,nullptr)
{
	shared_ptr<UnrealCraftPackage> package = make_shared<UnrealCraftPackage>();
	shared_ptr<NoImagePerformer120> performer = make_shared<NoImagePerformer120>(window,package);
	setPerformer(performer);
	shared_ptr<UnrealCraftWinReader> image_reader = make_shared<UnrealCraftWinReader>();
	setImageReader(image_reader);
}
