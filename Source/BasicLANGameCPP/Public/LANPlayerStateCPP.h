// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/PlayerState.h"
#include "LANPlayerStateCPP.generated.h"

/**
 * 
 */
UCLASS()
class BASICLANGAMECPP_API ALANPlayerStateCPP : public APlayerState
{
	GENERATED_BODY()

public:
	//UPROPERTY(Replicated)
	FName LANPlayerName;
	
	FName LanPlayerName() const;
	void SetLanPlayerName(const FName& LanPlayerName);

	//UFUNCTION(Server, Reliable)
	void ChangeLanPlayerName(const FName& name);

	//required for replicating variables
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
