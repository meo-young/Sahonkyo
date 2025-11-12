#include "Item/ItemBase.h"
#include "Sahonkyo.h"
#include "UI/ItemWidget.h"
#include "Character/CharacterBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

AItemBase::AItemBase()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	IconTriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("IconTriggerCollision"));
	IconTriggerCollision->SetupAttachment(ItemMesh);
	IconTriggerCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(ItemMesh);

	ItemWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ItemWidgetComponent"));
	ItemWidgetComponent->SetupAttachment(RootComponent);
	ItemWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	ItemWidgetComponent->SetDrawAtDesiredSize(true);
	ItemWidgetComponent->SetPivot(FVector2D(0.5f, 1.0f));
	ItemWidgetComponent->SetRelativeLocation(FVector(0, 0, 0.f));
	ItemWidgetComponent->SetWidgetClass(UItemWidget::StaticClass());
	ItemWidgetComponent->SetVisibility(false);
}

void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	IconTriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnIconTriggerBeginOverlap);
	IconTriggerCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnIconTriggerEndOverlap);

	if (UUserWidget* Widget = ItemWidgetComponent->GetUserWidgetObject())
	{
		if (UItemWidget* ItemWidget = Cast<UItemWidget>(Widget))
		{
			ItemWidget->SetObjectImage(ItemIcon);
		}
	}
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::OnIconTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->IsA(ACharacterBase::StaticClass())) return;

	LOG(TEXT("Item 아이콘울 표시합니다."));

	ItemWidgetComponent->SetVisibility(true);

}

void AItemBase::OnIconTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || !OtherActor->IsA(ACharacterBase::StaticClass())) return;

	LOG(TEXT("Item 아이콘을 숨깁니다."));

	ItemWidgetComponent->SetVisibility(false);

}
