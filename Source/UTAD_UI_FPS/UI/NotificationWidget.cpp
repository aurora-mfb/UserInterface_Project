// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationWidget.h"


void UNotificationWidget::NativeConstruct()
{
	if (Button_Close)
	{
		Button_Close->OnClicked.AddDynamic(this, &UNotificationWidget::OnCloseButtonClicked);
	}
}

void UNotificationWidget::OnCloseButtonClicked()
{
	this->RemoveFromParent();
}

void UNotificationWidget::SetNotificationMessage(const FString& Message)
{
	if (Text_Message)
	{
		Text_Message->SetText(FText::FromString(Message));
	}
}
