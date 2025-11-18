#include "Library/WidgetLibrary.h"
#include "Components/Image.h"

void UWidgetLibrary::SetImageOpacity(UImage* ImageWidget, const float Opacity)
{
	ImageWidget->SetOpacity(Opacity);
}
