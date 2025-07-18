// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounter.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/TextBlock.h"

void UAmmoCounter::Show()
{
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());
	if (Character != nullptr)
	{
		Character->OnTotalBulletsChanged.BindUObject(this, &UAmmoCounter::UpdateTotalAmmo);
		UTP_WeaponComponent* WeaponComponent = Character->GetAttachedWeaponComponent();
		if (WeaponComponent != nullptr)
		{
			WeaponComponent->OnCurrentNumBulletsChanged.BindUObject(this, &UAmmoCounter::UpdateCurrentAmmo);
		}
	}
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UAmmoCounter::Hide()
{
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());
	if (Character != nullptr)
	{
		Character->OnTotalBulletsChanged.Unbind();
		UTP_WeaponComponent* WeaponComponent = Character->GetAttachedWeaponComponent();
		if (WeaponComponent != nullptr)
		{
			WeaponComponent->OnCurrentNumBulletsChanged.Unbind();
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UAmmoCounter::UpdateCurrentAmmo(int NewCurrentAmmo)
{
	CurrentAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewCurrentAmmo)));
	//UE_LOG(LogTemp, Error, TEXT("UpdateCurrentAmmo"));
	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, TEXT("UpdateCurrentAmmo"));
}

void UAmmoCounter::UpdateTotalAmmo(int NewTotalAmmo)
{
	TotalAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewTotalAmmo)));
}
