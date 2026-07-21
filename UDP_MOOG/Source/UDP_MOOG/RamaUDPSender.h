// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "AnyCustomData.h"
#include "GameFramework/Actor.h"
#include "RamaUDPSender.generated.h"

UCLASS()
class ARamaUDPSender : public AActor
{
	GENERATED_UCLASS_BODY()

		bool IsUDP;

	UFUNCTION(BlueprintCallable, Category = RamaUDPSender)
		bool RamaUDPSender_SendString(FString ToSend);

public:
	UFUNCTION(BlueprintCallable, Category = RamaUDPSender)
		bool RamaUDPSender_SendAnyCustomData(FAnyCustomData anyCustomData);

public:
	TSharedPtr<FInternetAddr>	RemoteAddr;
	FSocket* SenderSocket;

	UFUNCTION(BlueprintCallable, Category = StartUDPSender)
		bool StartUDPSender(
			const FString& YourChosenSocketName,
			const FString& TheIP,
			const int32 ThePort,
			bool UDP = false
		);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rama UDP Sender", meta = (AllowPrivateAccess = true))
		bool ShowOnScreenDebugMessages;


	//ScreenMsg
	//FORCEINLINE void ScreenMsg(const FString& Msg)
	//{
	//	if (!ShowOnScreenDebugMessages) return;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	//}
	//FORCEINLINE void ScreenMsg(const FString& Msg, const float Value)
	//{
	//	if (!ShowOnScreenDebugMessages) return;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %f"), *Msg, Value));
	//}
	//FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	//{
	//	if (!ShowOnScreenDebugMessages) return;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	//}


public:

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};