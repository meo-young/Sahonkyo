#include "UI/WidgetBase.h"
#include "Sahonkyo.h"

void UWidgetBase::ShowWidget()
{
	if (!IsInViewport())
	{
		LOG(TEXT("%s 위젯을 뷰포트에 추가합니다."), *GetName());
		AddToViewport();
	}
}

void UWidgetBase::HideWidget()
{
	if (IsInViewport())
	{
		LOG(TEXT("%s 위젯을 뷰포트에서 제거합니다."), *GetName());
		RemoveFromParent();
	}
}
