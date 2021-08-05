// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LANPlayerStateCPP.h"
#include "MyGameInstanceCPP.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerControllerCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BASICLANGAMECPP_API AMyPlayerControllerCPP : public APlayerController
{
	GENERATED_BODY()

private:
	TSharedPtr<ALANPlayerStateCPP> PlayerState = 0;
	TSharedPtr<UMyGameInstanceCPP> Instance = 0;
	FName temp = "";
	bool IsNameSet = 0;

public:
	TSharedPtr<UMyGameInstanceCPP> Instance1() const;
	void SetInstance(const TSharedPtr<UMyGameInstanceCPP>& GmInstance);
	TSharedPtr<ALANPlayerStateCPP> PlayerState1() const;
	void SetPlayerState(const TSharedPtr<ALANPlayerStateCPP>& PState);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void PlayConServerTravelToLevel(FString levelName);
	
	UFUNCTION(BlueprintCallable)
	void PlayConHostSession();
	
	UFUNCTION(BlueprintCallable)
	void PlayConDestroySession();
	
	UFUNCTION(BlueprintCallable)
	void PlayConJoinSession();
	
	UFUNCTION(BlueprintCallable)
	void PlayConJoinViaIP(FString ip);
	
	UFUNCTION(BlueprintCallable)
	void PlayConJoinViaIPAndPort(FString ip, FString port);
	
	UFUNCTION(BlueprintCallable)
	void PlayConChangeNameOnPlayerState();
};
