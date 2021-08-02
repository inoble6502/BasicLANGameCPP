// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstanceCPP.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstanceCPP::UMyGameInstanceCPP(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//bind func for session creation and starting respectively
	this->OnCreateSessionCompleteDelegate =
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceCPP::OnCreateSessionComplete);
	this->OnStartSessionCompleteDelegate =
		FOnStartSessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceCPP::OnStartOnlineGameComplete);

	//bind func for session search
	this->OnFindSessionsCompleteDelegate =
		FOnFindSessionsCompleteDelegate::CreateUObject(this, &UMyGameInstanceCPP::OnFindSessionsComplete);

	//bind func for joining a session
	this->OnJoinSessionCompleteDelegate =
		FOnJoinSessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceCPP::OnJoinSessionComplete);
}

FString UMyGameInstanceCPP::LanPlayerName() const
{
	return LANPlayerName;
}

void UMyGameInstanceCPP::SetLanPlayerName(const FString& LanPlayerName)
{
	LANPlayerName = LanPlayerName;
}

bool UMyGameInstanceCPP::HostSession(TSharedPtr<FUniqueNetId> UserId,
	FName SessionName,
	bool bIsLAN,
	bool bIsPresence,
	int32 MaxNumPlayers)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

	if(!OnlineSub)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.f,
			FColor::Red,
			TEXT("No OnlineSubsytem found!")
			);
		
		return false;
	}

	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if(UserId.IsValid() && Sessions.IsValid())
	{
		//prepare settings
		this->SessionSettings = MakeShareable(new FOnlineSessionSettings());
		
		this->SessionSettings->bIsLANMatch = bIsLAN;
		this->SessionSettings->bUsesPresence = bIsPresence;
		this->SessionSettings->NumPublicConnections = MaxNumPlayers;
		this->SessionSettings->NumPrivateConnections = 0;
		this->SessionSettings->bAllowInvites = true;
		this->SessionSettings->bAllowJoinInProgress = true;
		this->SessionSettings->bShouldAdvertise = true;
		this->SessionSettings->bAllowJoinViaPresence = true;
		this->SessionSettings->bAllowJoinViaPresenceFriendsOnly = true;

		this->SessionSettings->Set(SETTING_MAPNAME, FString("Map Name"), EOnlineDataAdvertisementType::ViaOnlineService);

		this->OnCreateSessionCompleteDelegateHandle =
			Sessions->AddOnCreateSessionCompleteDelegate_Handle(this->OnCreateSessionCompleteDelegate);

		return Sessions->CreateSession(*UserId, SessionName, *this->SessionSettings);
	}

	return false;
}

void UMyGameInstanceCPP::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::White,
		FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful)
		);

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if(OnlineSub)
	{
		//retrieve session interface
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if(Sessions.IsValid())
		{
			//clear OnCreateSessionComplete delegate
			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(this->OnCreateSessionCompleteDelegateHandle);

			if(bWasSuccessful)
			{
				//set startsession delegate handle
				this->OnStartSessionCompleteDelegateHandle =
					Sessions->AddOnStartSessionCompleteDelegate_Handle(this->OnStartSessionCompleteDelegate);

				//OnStartSessionCompleteDelegate should be called here
				Sessions->StartSession(SessionName);
			}
		}
	}
}

void UMyGameInstanceCPP::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Red,
		FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful)
		);

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if(OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if(Sessions.IsValid())
		{
			//clear the delegate
			Sessions->ClearOnStartSessionCompleteDelegate_Handle(this->OnStartSessionCompleteDelegateHandle);
		}
	}

	if(bWasSuccessful)
		UGameplayStatics::OpenLevel(GetWorld(), "LevelName", true, "listen");
}

void UMyGameInstanceCPP::FindSessions(TSharedPtr<FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence)
{
	//get OnlineSubsystem
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if(OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if(Sessions.IsValid() && UserId.IsValid())
		{
			//set up search settings
			this->SessionSearch = MakeShareable(new FOnlineSessionSearch());
			this->SessionSearch->bIsLanQuery = bIsLAN;
			this->SessionSearch->MaxSearchResults = 20;
			this->SessionSearch->PingBucketSize = 50;

			//only set if bIsPresence is true
			if(bIsPresence)
				this->SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);

			TSharedRef<FOnlineSessionSearch> SearchSettingsRef = this->SessionSearch.ToSharedRef();

			//set del. to del. handle of FindSession func
			this->OnFindSessionsCompleteDelegateHandle =
				Sessions->AddOnFindSessionsCompleteDelegate_Handle(this->OnFindSessionsCompleteDelegate);

			//call SessionInterface func, del. gets called once this is finished
			Sessions->FindSessions(*UserId, SearchSettingsRef);
		}
	}
	else
	{
		OnFindSessionsComplete(false);
	}
}

void UMyGameInstanceCPP::OnFindSessionsComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::White,
		FString::Printf(TEXT("OFindSessionsComplete bSuccess: %d"), bWasSuccessful)
		);

	//get online subsystem
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if(OnlineSub)
	{
		//retrieve session interface
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if(Sessions.IsValid())
		{
			//clears del. handle
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(this->OnFindSessionsCompleteDelegateHandle);

			//print num of sarch results
			GEngine->AddOnScreenDebugMessage(
				-1,
				10.f,
				FColor::Blue,
				FString::Printf(TEXT("Num Search Results: %d"), this->SessionSearch->SearchResults.Num()));

			if(this->SessionSearch->SearchResults.Num() > 0)
			{
				//this->SessionSearch->SearchResults is an array contains all the info of all found sessions
				for(int32 SearchIdx = 0; SearchIdx < this->SessionSearch->SearchResults.Num(); SearchIdx++)
				{
					//OwningUserName is SessionName here
					GEngine->AddOnScreenDebugMessage(
						-1,
						10.f,
						FColor::Blue,
						FString::Printf(TEXT("Session Number: %d | Sessionname: %s "),
							SearchIdx+1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName))
						);
				}
			}
		}
	}
}

bool UMyGameInstanceCPP::JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults)
{
	return false;
}

bool UMyGameInstanceCPP::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	return false;
}

bool UMyGameInstanceCPP::JoinSession(TSharedPtr<FUniqueNetId> UserId, FName SessionName,
                                     const FOnlineSessionSearchResult& SearchResult)
{
	bool bSuccesssful = false;

	//get online subsystem
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if(OnlineSub)
	{
		//retrieve session interface
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if(Sessions.IsValid() && UserId.IsValid())
		{
			//set del. handle
			this->OnJoinSessionCompleteDelegateHandle =
				Sessions->AddOnJoinSessionCompleteDelegate_Handle(this->OnJoinSessionCompleteDelegate);

			//call "join session" function with SearchResult
			bSuccesssful = Sessions->JoinSession(*UserId, SessionName, SearchResult);
		}
	}

	return bSuccesssful;
}

void UMyGameInstanceCPP::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Blue,
		FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int>(Result)));

	//get online subsystem
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if(OnlineSub)
	{
		//retrieve session interface
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if(Sessions.IsValid())
		{
			//clear del.
			Sessions->ClearOnJoinSessionCompleteDelegate_Handle(this->OnJoinSessionCompleteDelegateHandle);

			//get first local PlayCon, for client travel to get to the server map
			//done automatically by BP node "Join Session"
			APlayerController* const PlayerController = GetFirstLocalPlayerController();

			//needed for ClientTravel, SessionInterface constructs string
			//to account for different OnlineSubsystems
			FString TravelURL;

			if(PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
			{
				//run client travel
				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}
