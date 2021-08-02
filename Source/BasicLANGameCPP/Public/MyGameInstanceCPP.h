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
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
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

	//find online session
	void FindSessions(TSharedPtr<FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	//del. for searching sessions
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	//handle to above del.
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	//delegate func fired when search query for sessions is complete
	void OnFindSessionsComplete(bool bWasSuccessful);

	//these (and their defs) are copied from the base class to prevent build warnings
	virtual bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults);
	virtual bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult);
	
	//join session via a search result
	virtual bool JoinSession(TSharedPtr<FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	//del. for joining a session
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	//del. handle for joining session
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	//del. func run upon completion of session join request
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
