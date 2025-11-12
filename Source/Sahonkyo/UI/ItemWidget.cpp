#include "UI/ItemWidget.h"
#include "Components/Image.h"


void UItemWidget::SetObjectImage(UTexture2D* InTexture)
{
	if (Object_Image && InTexture)
	{
		Object_Image->SetBrushFromTexture(InTexture);
	}
}
