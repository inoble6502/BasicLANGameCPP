// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstanceCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BASICLANGAMECPP_API UMyGameInstanceCPP : public UGameInstance
{
	GENERATED_BODY()

protected:
	FString LANPlayerName;
	
public:
	FString LanPlayerName() const;
	void SetLanPlayerName(const FString& LanPlayerName);

	void InstanceServerTravelToLevel(const APlayerController& pc, const FString& levelName);
	void InstanceCreateSession(const APlayerController& pc);
	void InstanceJoinSession(const APlayerController& pc);
	void InstanceJoinSessionByIP(const APlayerController& pc);
	void InstanceDestroySession(const APlayerController& pc);
	
};
