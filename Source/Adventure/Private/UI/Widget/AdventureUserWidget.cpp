// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/Widget/AdventureUserWidget.h"

void UAdventureUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
