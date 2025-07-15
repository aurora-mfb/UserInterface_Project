// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SkillWidget.h"

void USkillTreeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SkillWidgets.Empty();

	const int32 PanelCount = m_pCanvasPanel->GetChildrenCount();

	for (int32 i = 0; i < PanelCount; ++i)
	{
		UWidget* ChildPanel = m_pCanvasPanel->GetChildAt(i);

		// Si el hijo es un contenedor (como HorizontalBox, VerticalBox, etc.)
		if (UPanelWidget* Panel = Cast<UPanelWidget>(ChildPanel))
		{
			const int32 SkillCount = Panel->GetChildrenCount();
			for (int32 j = 0; j < SkillCount; ++j)
			{
				UWidget* SkillWidgetCandidate = Panel->GetChildAt(j);
				if (USkillWidget* Skill = Cast<USkillWidget>(SkillWidgetCandidate))
				{
					m_SkillWidgets.Add(Skill);
				}
			}
		}
	}

	// Paso 1: Mapeamos SkillID -> Widget
	TMap<FName, USkillWidget*> SkillMap;
	for (USkillWidget* Skill : m_SkillWidgets)
	{
		if (Skill && !Skill->SkillID.IsNone())
		{
			SkillMap.Add(Skill->SkillID, Skill);
		}
	}

	// Paso 2: Rellenamos los punteros reales en m_pPreviousSkills
	for (USkillWidget* Skill : m_SkillWidgets)
	{
		if (!Skill) continue;

		Skill->m_pPreviousSkills.Empty();

		for (const FName& PrevID : Skill->m_PreviousSkillIDs)
		{
			if (USkillWidget** Found = SkillMap.Find(PrevID))
			{
				Skill->m_pPreviousSkills.Add(*Found);
			}
		}
	}
}

FReply USkillTreeWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
  return FReply::Handled();
}
