#include "Item/MonologueItem.h"
#include "Core/Main/MainGameMode.h"
#include "Manager/UIManager.h"
#include "UI/Monologue/MonologueWidget.h"

void AMonologueItem::Interact_Implementation()
{
	Super::Interact_Implementation();
	
	UMonologueWidget* MonologueWidget = GameMode->GetUIManager()->GetMonologueWidget();
	MonologueWidget->ShowWidget(Monologue, this);
}
