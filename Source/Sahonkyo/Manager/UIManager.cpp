#include "Manager/UIManager.h"
#include "Sahonkyo.h"
#include "Character/PlayerControllerBase.h"
#include "UI/CrosshairWidget.h"

UUIManager::UUIManager()
{
	static ConstructorHelpers::FClassFinder<UCrosshairWidget> WBP_CrosshairWidgetClass(TEXT("/Game/_Sahonkyo/HUD/WBP_Crosshair"));
	if (WBP_CrosshairWidgetClass.Succeeded())
	{
		LOG(TEXT("Crosshair Widget Class 로드 성공"));
		CrosshairWidgetClass = WBP_CrosshairWidgetClass.Class;
	}
}

void UUIManager::InitUI(UWorld* World)
{
	if (CrosshairWidgetClass)
	{
		CrosshairWidgetInstance = CreateWidget<UCrosshairWidget>(World, CrosshairWidgetClass);
	}
}
