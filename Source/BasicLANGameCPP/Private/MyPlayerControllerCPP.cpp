// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerControllerCPP.h"


TSharedPtr<UMyGameInstanceCPP> AMyPlayerControllerCPP::Instance1() const
{
	return Instance;
}

void AMyPlayerControllerCPP::SetInstance(const TSharedPtr<UMyGameInstanceCPP>& GmInstance)
{
	this->Instance = Instance;
}

TSharedPtr<ALANPlayerStateCPP> AMyPlayerControllerCPP::PlayerState1() const
{
	return PlayerState;
}

void AMyPlayerControllerCPP::SetPlayerState(const TSharedPtr<ALANPlayerStateCPP>& PState)
{
	this->PlayerState = PlayerState;
}

void AMyPlayerControllerCPP::BeginPlay()
{
	this->Instance = MakeShareable(Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance()));;
	this->PlayerState = MakeShareable(this->GetPlayerState<ALANPlayerStateCPP>());
	this->IsNameSet = false;
	
	//this->temp = this->Instance->LanPlayerName();
	this->temp = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance())->LanPlayerName();
}

void AMyPlayerControllerCPP::Tick(float DeltaSeconds)
{
	if(this->IsNameSet)
		return;

	if(this->PlayerState.IsValid())
	{
		if(!HasAuthority())
		{
			if(!(this->PlayerState->LanPlayerName() == this->temp))
			{
				this->PlayerState->ChangeLanPlayerName(temp);
				this->IsNameSet = true;
			}
		}
	}
	else
	{
		this->PlayerState = MakeShareable(this->GetPlayerState<ALANPlayerStateCPP>());
	}
}

void AMyPlayerControllerCPP::PlayConServerTravelToLevel(FString levelName)
{
	UMyGameInstanceCPP *gi = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance());

	if(!gi)
		return;

	gi->ServerTravelToLevel(levelName);
}

void AMyPlayerControllerCPP::PlayConHostSession()
{
	UMyGameInstanceCPP *gi = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance());

	if(!gi)
		return;

	gi->StartOnlineGame();
}

void AMyPlayerControllerCPP::PlayConDestroySession()
{
	UMyGameInstanceCPP *gi = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance());

	if(!gi)
		return;

	gi->DestroySessionAndLeaveGame();
}

void AMyPlayerControllerCPP::PlayConJoinSession()
{
	UMyGameInstanceCPP *gi = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance());

	if(!gi)
		return;

	gi->JoinOnlineGame();
}

void AMyPlayerControllerCPP::PlayConJoinViaIP(FString ip)
{	
	UMyGameInstanceCPP *gi = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance());

	if(!gi)
		return;

	gi->JoinSessionViaIP(ip);
}

void AMyPlayerControllerCPP::PlayConJoinViaIPAndPort(FString ip, FString port)
{
	UMyGameInstanceCPP *gi = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance());

	if(!gi)
		return;

	gi->JoinSessionViaIPAndPort(ip, port);
	
}

void AMyPlayerControllerCPP::PlayConChangeNameOnPlayerState()
{
	if(!this->PlayerState)
		return;

	this->PlayerState->ChangeLanPlayerName(temp);
}
