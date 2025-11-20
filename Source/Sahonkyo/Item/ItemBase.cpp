#include "Item/ItemBase.h"
#include "Sahonkyo.h"
#include "UI/Item/ItemWidget.h"
#include "Character/CharacterBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Define/Define.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(SceneComponent);

	IconTriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("IconTriggerCollision"));
	IconTriggerCollision->SetupAttachment(ItemMesh);
	IconTriggerCollision->SetCollisionResponseToChannel(ECC_ICON_TRACE, ECR_Ignore);
	IconTriggerCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(ItemMesh);
	InteractCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractCollision->SetCollisionResponseToChannel(ECC_INTERACTABLE, ECR_Block);

	ItemWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ItemWidgetComponent"));
	ItemWidgetComponent->SetupAttachment(ItemMesh);
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

	SetActorTickEnabled(false);

	Params.AddIgnoredActor(this);
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceToPlayer();
}

void AItemBase::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	LOG(TEXT("아이템과 상호작용 합니다."));
}

void AItemBase::OnInteractablePossible_Implementation()
{
	IInteractable::OnInteractablePossible_Implementation();

	if (UUserWidget* Widget = ItemWidgetComponent->GetUserWidgetObject())
	{
		if (UItemWidget* ItemWidget = Cast<UItemWidget>(Widget))
		{
			//LOG(TEXT("아이템과 상호작용이 가능합니다."));
			ItemWidget->SetObjectImageActive(true);
		}
	}
}

void AItemBase::OnInteractableImpossible_Implementation()
{
	IInteractable::OnInteractableImpossible_Implementation();

	if (UUserWidget* Widget = ItemWidgetComponent->GetUserWidgetObject())
	{
		if (UItemWidget* ItemWidget = Cast<UItemWidget>(Widget))
		{
			LOG(TEXT("아이템과 상호작용이 불가능합니다."));
			ItemWidget->SetObjectImageActive(false);
		}
	}
}

void AItemBase::DeactivateItemCollision()
{
	IconTriggerCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InteractCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItemBase::OnIconTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->IsA(ACharacterBase::StaticClass())) return;

	SetActorTickEnabled(true);

	LOG(TEXT("아이템 아이콘 트리거에 플레이어가 진입했습니다."));
}

void AItemBase::OnIconTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || !OtherActor->IsA(ACharacterBase::StaticClass())) return;
	
	ItemWidgetComponent->SetVisibility(false);

	LOG(TEXT("아이템 아이콘 트리거에 플레이어가 진입했습니다."));

	SetActorTickEnabled(false);
}

void AItemBase::TraceToPlayer()
{
	const FVector Start = InteractCollision->GetComponentLocation();
	const FVector End = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_ICON_TRACE, Params);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.5f, 0, 2.0f);

	if (HitResult.GetActor() && HitResult.GetActor()->IsA(ACharacterBase::StaticClass()))
	{
		ItemWidgetComponent->SetVisibility(true);
	}
}
