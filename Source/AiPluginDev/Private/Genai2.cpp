// Fill out your copyright notice in the Description page of Project Settings.


#include "Genai2.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"

UGenai2* UGenai2::CreateInstance()
{
    return NewObject<UGenai2>();

}
void UGenai2::SendRequestToFastAPI(const FString& UserInput)
{
    //UserInput = TEXT("Who are you?");
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UGenai2::OnResponseReceived);
    Request->SetURL(TEXT("http://localhost:8000/ask/")); // Corrected URL
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    // Construct JSON request body
    TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject());
    RequestObj->SetStringField(TEXT("message"), UserInput);

    FString RequestBody;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer);

    Request->SetContentAsString(RequestBody);
    Request->ProcessRequest();
}

void UGenai2::GetThreadFromFastAPI(const FString& UserInput)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UGenai2::OnThreadResponseReceived);
    Request->SetURL(TEXT("http://localhost:8000/get_thread/")); // Replace with your FastAPI URL
    Request->SetVerb(TEXT("GET"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->ProcessRequest();
}

void UGenai2::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseString = Response->GetContentAsString();
        UE_LOG(LogTemp, Log, TEXT("HTTP Response: %s"), *ResponseString);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Response: %s"), *ResponseString));
        }
    }
    else
    {
        FString ErrorMessage = TEXT("Failed to receive HTTP response");
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ErrorMessage);
        }
    }
}
void UGenai2::OnThreadResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseString = Response->GetContentAsString();
        UE_LOG(LogTemp, Log, TEXT("HTTP Response: %s"), *ResponseString);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Response: %s"), *ResponseString));
        }
    }
    else
    {
        FString ErrorMessage = TEXT("Failed to receive HTTP response");
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ErrorMessage);
        }
    }
}

