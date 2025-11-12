#include "Core/Main/MainGameMode.h"
#include "Sahonkyo.h"
#include "Manager/UIManager.h"
#include "UI/CrosshairWidget.h"

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UIManager = NewObject<UUIManager>(this);
}

void AMainGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UIManager->InitUI(GetWorld());
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UIManager->GetCrosshairWidget())
	{
		UIManager->GetCrosshairWidget()->ShowWidget();
	}

}
