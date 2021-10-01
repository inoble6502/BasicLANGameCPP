// Fill out your copyright notice in the Description page of Project Settings.
#include "LANPlayerStateCPP.h"
#include "Net/UnrealNetwork.h"

ALANPlayerStateCPP::ALANPlayerStateCPP()
{
	//this->LANPlayerName = "";
}

FName ALANPlayerStateCPP::GetLanPlayerName() const
{
	return this->LANPlayerName;
}

void ALANPlayerStateCPP::SetLanPlayerName(const FName& PlayerName)
{
	LANPlayerName = PlayerName;
}

void ALANPlayerStateCPP::ChangeLanPlayerName_Implementation(const FName& name)
{
	this->SetLanPlayerName(name);
}

// void ALANPlayerStateCPP::ChangeLanPlayerName(const FName& name)
// {
// 	this->SetLanPlayerName(name);
// }

void ALANPlayerStateCPP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALANPlayerStateCPP, LANPlayerName);
}
