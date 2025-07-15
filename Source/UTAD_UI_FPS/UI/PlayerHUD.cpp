// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Crosshair.h"
#include "AmmoCounter.h"
#include "PlayerHealthBar.h"
#include "ReloadBar.h"

void UPlayerHUD::ShowNoWeapon()
{
  AmmoCounterWidget->Hide();
}

void UPlayerHUD::ShowAll()
{
  AmmoCounterWidget->Show();
}

void UPlayerHUD::Hide()
{
  AmmoCounterWidget->Hide();
}
