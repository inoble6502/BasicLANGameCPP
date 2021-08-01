// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstanceCPP.h"

FString UMyGameInstanceCPP::LanPlayerName() const
{
	return LANPlayerName;
}

void UMyGameInstanceCPP::SetLanPlayerName(const FString& LanPlayerName)
{
	LANPlayerName = LanPlayerName;
}
