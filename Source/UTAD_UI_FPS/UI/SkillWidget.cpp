// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWidget.h"
#include "Components/Button.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "NotificationWidget.h"

void USkillWidget::NativeConstruct()
{
  Super::NativeConstruct();

  m_pCharacterReference = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
  
  if (!m_pCharacterReference) return;

  if (m_pButton && m_pIcon)
  {
    // Crear el brush
    FSlateBrush ButtonBrush;
    ButtonBrush.SetResourceObject(m_pIcon);

    // Crear brush con la textura de icono desbloqueado
    FSlateBrush HoveredBrush;
    HoveredBrush.SetResourceObject(m_pUnlockedIcon);

    // Obtener el estilo actual del botón
    FButtonStyle NewStyle = m_pButton->WidgetStyle;
    NewStyle.SetNormal(ButtonBrush);

    // También puedes cambiar "Hovered" y "Pressed" si quieres
    NewStyle.SetHovered(HoveredBrush);
    NewStyle.SetPressed(HoveredBrush);

    // Aplicar estilo al botón
    m_pButton->SetStyle(NewStyle);
  }

  if (m_pButton)
  {
    m_pButton->OnPressed.AddDynamic(this, &USkillWidget::OnButtonPressed);
    m_pButton->OnReleased.AddDynamic(this, &USkillWidget::OnButtonReleased);
  }

  if (ProgressBar_Confirm)
  {
    ProgressBar_Confirm->SetPercent(0.f);
    ProgressBar_Confirm->SetVisibility(ESlateVisibility::Hidden);
  }

  m_iSkillPoints = m_pCharacterReference->GetSkillPoints();
}

void USkillWidget::OnButtonClicked()
{
  m_bSkillUnlocked = true;
  UnlockSkill();
  UnlockAbility();
}

void USkillWidget::UnlockAbility()
{
}

void USkillWidget::UnlockSkill()
{
  if (GEngine)
  {
    FString DebugMessage = FString::Printf(TEXT("Puntos que cuesta: %d"), m_iCost);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
  }

  int16 iSkillPoints = m_pCharacterReference->GetSkillPoints();
  m_pCharacterReference->SetSkillPoints(iSkillPoints-m_iCost);

  // Crear brush con la textura de icono desbloqueado
  FSlateBrush NewBrush;
  NewBrush.SetResourceObject(m_pUnlockedIcon);
  NewBrush.ImageSize = FVector2D(64.f, 64.f); // Ajusta tamaño si quieres

  // Obtener estilo actual del botón
  FButtonStyle NewButtonStyle = m_pButton->WidgetStyle;

  // Cambiar las imágenes de los estados a la nueva imagen
  NewButtonStyle.SetNormal(NewBrush);
  NewButtonStyle.SetHovered(NewBrush);
  NewButtonStyle.SetPressed(NewBrush);

  // Aplicar el nuevo estilo al botón
  m_pButton->SetStyle(NewButtonStyle);
}

void USkillWidget::OnButtonPressed()
{

  m_iSkillPoints = m_pCharacterReference->GetSkillPoints();

  if (GEngine)
  {
    FString DebugMessage = FString::Printf(TEXT("Puntos actuales: %d"), m_iSkillPoints);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
  }

  // Si no hay puntos
  if (m_iSkillPoints < m_iCost)
  {
    FString Message = "No hay puntos suficientes";
    ShowNotification(Message);
    return;
  }

  // Si ya esta desbloqueada
  if (m_bSkillUnlocked)
  {
    FString Message = "Habilidad ya seleccionada";
    ShowNotification(Message);
    return;
  }

  // Si tiene botones previos sin pulsar
  if (m_pPreviousSkills.Num() != 0)
  {
    for (USkillWidget* Element : m_pPreviousSkills)
    {
      if (!Element->m_bSkillUnlocked)
      {
        FString Message = "Debe seleccionar una habilidad anterior";
        ShowNotification(Message);
        return;
      }
    }
  }

  // Si todo esta bien
  bIsHolding = true;
  HoldTime = 0.f;
  if (ProgressBar_Confirm)
    ProgressBar_Confirm->SetVisibility(ESlateVisibility::Visible);
}

void USkillWidget::OnButtonReleased()
{
  bIsHolding = false;
  HoldTime = 0.f;
  if (ProgressBar_Confirm)
  {
    ProgressBar_Confirm->SetPercent(0.f);
    ProgressBar_Confirm->SetVisibility(ESlateVisibility::Hidden);
  }
}

void USkillWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
  Super::NativeTick(MyGeometry, InDeltaTime);

  if (bIsHolding)
  {
    HoldTime += InDeltaTime;

    float Percent = FMath::Clamp(HoldTime / HoldDuration, 0.f, 1.f);

    if (ProgressBar_Confirm)
    {
      ProgressBar_Confirm->SetPercent(Percent);
    }

    // Cuando se llena la barra, confirma la acción
    if (HoldTime >= HoldDuration)
    {
      bIsHolding = false;

      if (ProgressBar_Confirm)
        ProgressBar_Confirm->SetVisibility(ESlateVisibility::Hidden);

      OnButtonClicked();
    }
  }
}

void USkillWidget::ShowNotification(const FString& Message)
{
  if (UWorld* World = GetWorld())
  {
    APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
    if (PC && NotificationWidgetClass)
    {
      UNotificationWidget* Notification = CreateWidget<UNotificationWidget>(PC, NotificationWidgetClass);
      if (Notification)
      {
        Notification->AddToViewport();
        Notification->SetNotificationMessage(Message);
      }
    }
  }
}