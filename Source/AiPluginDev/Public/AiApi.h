// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AIPLUGINDEV_API AiApi
{
public:
	AiApi();
	~AiApi();

	UFUNCTION(BlueprintCallable, Category = "Ai")
	void SendRequestToFastAPI(const FString& UserInput);
};
