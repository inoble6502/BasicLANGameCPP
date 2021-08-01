// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstanceCPP.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UMyGameInstanceCPP::UMyGameInstanceCPP(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//bind func for session creation
	this->OnCreateSessionCompleteDelegate =
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceCPP::OnCreateSessionComplete);
	this->OnStartSessionCompleteDelegate =
		FOnStartSessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceCPP::OnStartOnlineGameComplete);
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
		GEngine->AddOnScreenDebugMessage(-1,
			10.f,
			FColor::Red,
			TEXT("No OnlineSubsytem found!"));
		
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
	return;
}

void UMyGameInstanceCPP::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	return;
}
