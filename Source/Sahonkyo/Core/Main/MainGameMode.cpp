#include "Core/Main/MainGameMode.h"
#include "Sahonkyo.h"
#include "Character/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"
#include "UI/Crosshair/CrosshairWidget.h"

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

void AMainGameMode::SetPlayerInput(const bool bIsEnable)
{
	ACharacterBase* Player = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (bIsEnable)
	{
		Player->SetInputEnabled(true);
		UIManager->GetCrosshairWidget()->ShowWidget();
	}
	else
	{
		Player->SetInputEnabled(false);
		UIManager->GetCrosshairWidget()->HideWidget();
	}
}
