// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpRequest.h"
#include "Genai2.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AIPLUGINDEV_API UGenai2 : public UObject
{
	GENERATED_BODY()

public:

	// Factory method to create an instance
	UFUNCTION(BlueprintCallable, Category = "Genai")
	static UGenai2* CreateInstance();

	UFUNCTION(BlueprintCallable, Category = "Genai")
	void SendRequestToFastAPI(const FString& UserInput);

	UFUNCTION(BlueprintCallable, Category = "Genai")
	void GetThreadFromFastAPI(const FString& UserInput);

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnThreadResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
};
