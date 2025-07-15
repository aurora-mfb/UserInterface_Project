// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include "SkillWidget.generated.h"

class UButton;
class AUTAD_UI_FPSCharacter;

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None		UMETA(DisplayName = "None"),
	Fireball	UMETA(DisplayName = "Fireball"),
	IceBlast	UMETA(DisplayName = "Ice Blast"),
	Heal		UMETA(DisplayName = "Heal"),
	Shield		UMETA(DisplayName = "Shield")
};

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	FName SkillID;


	UPROPERTY(EditAnywhere, Category = "Skills | Previous Skills")
	TArray<USkillWidget*> m_pPreviousSkills;

	UPROPERTY(EditAnywhere, Category = "Skills | Previous Skills")
	TArray<FName> m_PreviousSkillIDs;

protected:

	// Is a function taht going to be triggered when the widget is created
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UButton* m_pButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UProgressBar* ProgressBar_Confirm;

	UPROPERTY(EditAnywhere, Category = "UI")
	UTexture2D* m_pIcon;

	UPROPERTY(EditAnywhere, Category = "UI")
	UTexture2D* m_pUnlockedIcon;

	UPROPERTY(EditAnywhere, Category = "Skills | Sill Type")
	ESkillType m_pSkillType;

	UPROPERTY(EditAnywhere, Category = "Skills | Cost")
	int16 m_iCost;

	bool m_bSkillUnlocked = false;

	AUTAD_UI_FPSCharacter* m_pCharacterReference;

	void ShowNotification(const FString& Message);

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> NotificationWidgetClass;

	UUserWidget* CurrentNotification = nullptr;

	// Tiempo total que hay que mantener pulsado para confirmar
	UPROPERTY(EditAnywhere, Category = "Confirm")
	float HoldDuration = 2.0f; // 2 segundos, por ejemplo

	// Tiempo acumulado manteniendo pulsado
	float HoldTime = 0.0f;

	// Flag para saber si el botón está pulsado
	bool bIsHolding = false;

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonPressed();

	UFUNCTION()
	void OnButtonReleased();

	void UnlockAbility();

	void UnlockSkill();

private:

	int16 m_iSkillPoints;
};
