#include "Manager/UIManager.h"
#include "Sahonkyo.h"
#include "Character/PlayerControllerBase.h"
#include "UI/Crosshair/CrosshairWidget.h"
#include "UI/Monologue/MonologueWidget.h"
#include "UI/Monologue/DialogueWidget.h"

UUIManager::UUIManager()
{
	static ConstructorHelpers::FClassFinder<UCrosshairWidget> WBP_CrosshairWidgetClass(TEXT("/Game/_Sahonkyo/HUD/WBP_Crosshair"));
	if (WBP_CrosshairWidgetClass.Succeeded())
	{
		LOG(TEXT("Crosshair Widget Class 로드 성공"));
		CrosshairWidgetClass = WBP_CrosshairWidgetClass.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UMonologueWidget> WBP_MonologueWidgetClass(TEXT("/Game/_Sahonkyo/HUD/WBP_Monologue"));
	if (WBP_MonologueWidgetClass.Succeeded())
	{
		LOG(TEXT("Monologue Widget Class 로드 성공"));
		MonologueWidgetClass = WBP_MonologueWidgetClass.Class;
	}
}

void UUIManager::InitUI(UWorld* World)
{
	if (CrosshairWidgetClass)
	{
		CrosshairWidgetInstance = CreateWidget<UCrosshairWidget>(World, CrosshairWidgetClass);
	}
	
	if (MonologueWidgetClass)
	{
		MonologueWidgetInstance = CreateWidget<UMonologueWidget>(World, MonologueWidgetClass);
	}
}
