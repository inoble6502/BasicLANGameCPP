// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerControllerCPP.h"


AMyPlayerControllerCPP::AMyPlayerControllerCPP()
{
	this->temp = "";
	this->IsNameSet = 0;
	this->PlayerState = 0;
	this->Instance = 0;
}

UMyGameInstanceCPP* AMyPlayerControllerCPP::Instance1() const
{
	return Instance;
}

void AMyPlayerControllerCPP::SetInstance(UMyGameInstanceCPP* GmInstance)
{
	this->Instance = GmInstance;
}

ALANPlayerStateCPP* AMyPlayerControllerCPP::PlayerState1() const
{
	return PlayerState;
}

void AMyPlayerControllerCPP::SetPlayerState(ALANPlayerStateCPP* PState)
{
	this->PlayerState = PlayerState;
}

void AMyPlayerControllerCPP::BeginPlay()
{
	this->Instance = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance());
	this->PlayerState = this->GetPlayerState<ALANPlayerStateCPP>();
	this->IsNameSet = false;
	
	//this->temp = this->Instance->LanPlayerName();
	this->temp = Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance())->LanPlayerName();
}

void AMyPlayerControllerCPP::Tick(float DeltaSeconds)
{
	if(this->IsNameSet)
		return;

	if(this->PlayerState)
	{
		if(!HasAuthority())
		{
			if(!(this->PlayerState->GetLanPlayerName() == this->temp))
			{
				this->PlayerState->ChangeLanPlayerName(temp);
				this->IsNameSet = true;
			}
		}
	}
	else
	{
		this->PlayerState = this->GetPlayerState<ALANPlayerStateCPP>();
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

	gi->FindOnlineGames();

	GetWorld()->GetTimerManager().SetTimer(
		this->PlayConTimerHandle,
		[&]()
		{
			//have to cast again to prevent exception access violation error
			Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance())->JoinOnlineGame();
		},
		10,
		false);
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
	this->GetPlayerState<ALANPlayerStateCPP>()->ChangeLanPlayerName(Cast<UMyGameInstanceCPP>(GetWorld()->GetGameInstance())->LanPlayerName());
}
