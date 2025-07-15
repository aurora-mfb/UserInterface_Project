// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeWidget.generated.h"

class UCanvasPanel;
class UImage;
class UTextBlock;
class USkillWidget;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* m_pCanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* m_pBackgroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Tree")
	TArray<USkillWidget*> m_SkillWidgets;

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
