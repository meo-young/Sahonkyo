#include "UI/ItemWidget.h"
#include "Components/Image.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetObjectImageActive(false);
}

void UItemWidget::SetObjectImage(UTexture2D* InTexture)
{
	if (Object_Image && InTexture)
	{
		Object_Image->SetBrushFromTexture(InTexture);
	}
}

void UItemWidget::SetObjectImageActive(const bool bIsActive)
{
	if (bIsActive)
	{
		if (Object_Image)
		{
			Object_Image->SetOpacity(1.0f);
		}
	}
	else
	{
		if (Object_Image)
		{
			Object_Image->SetOpacity(0.0f);
		}
	}
}
