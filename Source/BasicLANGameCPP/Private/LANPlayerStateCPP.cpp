// Fill out your copyright notice in the Description page of Project Settings.
#include "LANPlayerStateCPP.h"

#include "Net/UnrealNetwork.h"

FName ALANPlayerStateCPP::LanPlayerName() const
{
	return LANPlayerName;
}

void ALANPlayerStateCPP::SetLanPlayerName(const FName& LanPlayerName)
{
	LANPlayerName = LanPlayerName;
}

void ALANPlayerStateCPP::ChangeLanPlayerName(const FName& name)
{
	this->SetLanPlayerName(name);
}

void ALANPlayerStateCPP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALANPlayerStateCPP, LANPlayerName);
}
