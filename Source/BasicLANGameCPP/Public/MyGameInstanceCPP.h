// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
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
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	
public:
	UMyGameInstanceCPP(const FObjectInitializer& ObjectInitializer);
	
	FString LanPlayerName() const;
	void SetLanPlayerName(const FString& LanPlayerName);

	bool HostSession(TSharedPtr<FUniqueNetId> UserId,
		FName SessionName,
		bool bIsLAN,
		bool bIsPresence,
		int32 MaxNumPlayers);

	//delegates for creating and starting session completion respectively
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	//handles for creating and starting session respectively
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	//runs on completion of session create request
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	//runs on completion of session start request
	virtual void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
};
