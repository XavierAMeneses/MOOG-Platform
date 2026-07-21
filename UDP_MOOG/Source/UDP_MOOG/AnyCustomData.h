// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatform.h"
#include "AnyCustomData.generated.h"
//Displacement DOF struct
struct DisDOF
{
	float Roll;
	float Pitch;
	float Yaw;
	float Longitudinal;
	float Lateral;
	float Heave;
};

//Displacement Buffet struct to set values for Buffet
struct DisBuffet
{
	uint32 numSig = 0;
	float freq;
	float Xamp;
	float Yamp;
	float Zamp;
};

//WhiteNoise struct to set values for white noise
struct AccWhieNoise
{
	uint32 numSig = 0;
	float XAcc;
	float XLoFreq;
	float XHiFreq;
	float YAcc;
	float YLoFreq;
	float YHiFreq;
	float ZAcc;
	float ZLoFreq;
	float ZHiFreq;
};

struct SendingData {
	float Roll;
	float Pitch;
	float Heave;
	float Yaw;
	float Sway;
	float Surge;

	//DisDOF DisDOFPack;
	DisBuffet BuffPack; //if a BuffetPack pack is going to be sent it will be stored here
	AccWhieNoise WNpack; //if a white noise pack is going to be sent it will be stored here
	//FString end;
};

USTRUCT(BlueprintType)
struct FAnyCustomData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Pitch = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Roll = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Yaw = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Heave = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Sway = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Surge = 0;

	// DISPLACEMENT DOF SEEMS TO BREAK EVERYTHING - DEREK DEPEW 9/18/19 derek@depew.net
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	//	float DisDOFRoll = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	//	float DisDOFPitch = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	//	float DisDOFYaw = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	//	float DisDOFLongitudinal = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	//	float DisDOFLateral = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	//	float DisDOFHeave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		int32 BuffetSignalNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Buff_freq = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Buff_XAmp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Buff_YAmp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Buff_ZAmp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		int32 WhiteSignalNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_XAcc = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_XLoFreq = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_XHiFreq = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_YAcc = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_YLoFreq = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_YHiFreq = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_ZAcc = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_ZLoFreq = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float WN_ZHiFreq = 0;

	FAnyCustomData()
	{}
};
//
//USTRUCT(BlueprintType)
//struct FAnyCustomDataMQ
//{
//	GENERATED_USTRUCT_BODY()
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		uint32 PacketLength;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		uint32 PacketSeqCount;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		uint32 Reserved;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		uint32 MotionCommandMode;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		uint32 CommandState; // Message ID
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		uint32 StatusResponse;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		uint32 MotionCueingCommandWord;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float RollEuler = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float PitchEuler = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float YawEuler = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float RollVelocity = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float PitchVelocity = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float YawVelocity = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float RollAccel = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float PitchAccel = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float YawAccel = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float SurgeAccel = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float SwayAccel = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
//		float HeaveAccel = 0;
//
//	FAnyCustomDataMQ()
//	{}
//};

FORCEINLINE FArchive& operator<<(FArchive &Ar, FAnyCustomData& TheStruct)
{
	//Ar << TheStruct.Name;
	Ar << TheStruct.Pitch;
	Ar << TheStruct.Roll;
	Ar << TheStruct.Heave;
	//Ar << TheStruct.Color;

	return Ar;
}


FORCEINLINE FArchive& operator<<(FArchive &Ar, SendingData& TheStruct)
{
	Ar << TheStruct.Roll;
	Ar << TheStruct.Pitch;
	Ar << TheStruct.Heave;
	Ar << TheStruct.Yaw;
	Ar << TheStruct.Sway;
	Ar << TheStruct.Surge;


	//Ar << TheStruct.DisDOFPack.Roll;
	//Ar << TheStruct.DisDOFPack.Pitch;
	//Ar << TheStruct.DisDOFPack.Yaw;
	//Ar << TheStruct.DisDOFPack.Longitudinal;
	//Ar << TheStruct.DisDOFPack.Lateral;
	//Ar << TheStruct.DisDOFPack.Heave;


	Ar << TheStruct.BuffPack.numSig;
	if (TheStruct.BuffPack.numSig > 0)
	{
		Ar << TheStruct.BuffPack.freq;
		Ar << TheStruct.BuffPack.Xamp;
		Ar << TheStruct.BuffPack.Yamp;
		Ar << TheStruct.BuffPack.Zamp;
	}
	else
	{
		float temp = 0.0f;
		Ar << temp;
		Ar << temp;
		Ar << temp;
		Ar << temp;
	}


	Ar << TheStruct.WNpack.numSig;
	if (TheStruct.WNpack.numSig > 0)
	{
		Ar << TheStruct.WNpack.XAcc;
		Ar << TheStruct.WNpack.XLoFreq;
		Ar << TheStruct.WNpack.XHiFreq;
		Ar << TheStruct.WNpack.YAcc;
		Ar << TheStruct.WNpack.YLoFreq;
		Ar << TheStruct.WNpack.YHiFreq;
		Ar << TheStruct.WNpack.ZAcc;
		Ar << TheStruct.WNpack.ZLoFreq;
		Ar << TheStruct.WNpack.ZHiFreq;
	}
	else
	{
		float temp = 0.0f;
		Ar << temp;
		Ar << temp;
		Ar << temp;
		Ar << temp;
		Ar << temp;
		Ar << temp;
		Ar << temp;
		Ar << temp;
		Ar << temp;
	}



	return Ar;
}