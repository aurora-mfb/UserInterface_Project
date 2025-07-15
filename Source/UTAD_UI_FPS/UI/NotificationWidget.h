// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "NotificationWidget.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

public:
	/** Sets the message to be shown */
	UFUNCTION(BlueprintCallable, Category = "Notification")
	void SetNotificationMessage(const FString& Message);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Message;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;

	UFUNCTION()
	void OnCloseButtonClicked();
};
