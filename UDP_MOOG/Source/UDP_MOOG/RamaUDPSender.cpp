// Fill out your copyright notice in the Description page of Project Settings.

#include "RamaUDPSender.h"
#include "AnyCustomData.h"
#include "SocketSubsystem.h"

ARamaUDPSender::ARamaUDPSender(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SenderSocket = NULL;

	ShowOnScreenDebugMessages = true;
}

void ARamaUDPSender::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//~~~~~~~~~~~~~~~~

	if (SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}
}

bool ARamaUDPSender::StartUDPSender(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort,
	bool UDP
) {
	//Create Remote Address.
	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	RemoteAddr->SetIp(*TheIP, bIsValid);
	RemoteAddr->SetPort(ThePort);

	if (!bIsValid)
	{
		//ScreenMsg("Rama UDP Sender>> IP address was not valid!", TheIP);
		return false;
	}

	SenderSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsReusable()
		.WithBroadcast()
		;


	//check(SenderSocket->GetSocketType() == SOCKTYPE_Datagram);

	//Set Send Buffer Size
	int32 SendSize = 2 * 1024 * 1024;
	SenderSocket->SetSendBufferSize(SendSize, SendSize);
	SenderSocket->SetReceiveBufferSize(SendSize, SendSize);

	UE_LOG(LogTemp, Log, TEXT("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
	UE_LOG(LogTemp, Log, TEXT("Rama ****UDP**** Sender Initialized Successfully!!!"));
	UE_LOG(LogTemp, Log, TEXT("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"));

	return true;
}

bool ARamaUDPSender::RamaUDPSender_SendString(FString ToSend)
{
	if (!SenderSocket)
	{
		//ScreenMsg("No sender socket");
		return false;
	}
	//~~~~~~~~~~~~~~~~

	int32 BytesSent = 0;

	FAnyCustomData NewData;
	//NewData.Scale = FMath::FRandRange(0, 1000);
	//NewData.Scale = 1.1234f;
	//NewData.Count = 214;
	//NewData.Color = FLinearColor(FMath::FRandRange(0, 1), FMath::FRandRange(0, 1), FMath::FRandRange(0, 1), 1);

	FArrayWriter Writer;

	Writer << NewData; //Serializing our custom data, thank you UE4!

	SenderSocket->SendTo(Writer.GetData(), Writer.Num(), BytesSent, *RemoteAddr);

	if (BytesSent <= 0)
	{
		const FString Str = "Socket is valid but the receiver received 0 bytes, make sure it is listening properly!";
		UE_LOG(LogTemp, Error, TEXT("%s"), *Str);
		//ScreenMsg(Str);
		return false;
	}

	//ScreenMsg("UDP~ Send Succcess! Bytes Sent = ", BytesSent);

	return true;
}

uint16 ReverseUint16(uint16 val) {
	return (uint16)(val >> 8) | (val << 8);
}

uint32 ReverseUint32(uint32 val) {

	val = ((val >> 24) & 0xff) | // move byte 3 to byte 0
		((val << 8) & 0xff0000) | // move byte 1 to byte 2
		((val >> 8) & 0xff00) | // move byte 2 to byte 1
		((val << 24) & 0xff000000); // byte 0 to byte 3
	return val;
}

float ReverseFloat(const float inFloat)
{
	float retVal;
	char *floatToConvert = (char*)& inFloat;
	char *returnFloat = (char*)& retVal;

	// swap the bytes into a temporary buffer
	returnFloat[0] = floatToConvert[3];
	returnFloat[1] = floatToConvert[2];
	returnFloat[2] = floatToConvert[1];
	returnFloat[3] = floatToConvert[0];

	return retVal;
}


bool ARamaUDPSender::RamaUDPSender_SendAnyCustomData(FAnyCustomData anyCustomData)
{
	if (!SenderSocket)
	{
		return false;
	}
	int32 BytesSent = 0;
	SendingData sendingData;
	/*sendingData.Roll = ReverseFloat(anyCustomData.Roll);
	sendingData.Pitch = ReverseFloat(anyCustomData.Pitch);
	sendingData.Heave = ReverseFloat(anyCustomData.Heave);*/
	/*sendingData.Roll = anyCustomData.Roll;
	sendingData.Pitch = anyCustomData.Pitch;
	sendingData.Heave = anyCustomData.Heave;*/
	sendingData.Roll = ReverseFloat(anyCustomData.Roll);
	sendingData.Pitch = ReverseFloat(anyCustomData.Pitch);
	sendingData.Heave = ReverseFloat(anyCustomData.Heave);

	/*sendingData.Yaw = ReverseFloat(0.0f);
	sendingData.Sway = ReverseFloat(0.0f);
	sendingData.Surge = ReverseFloat(0.0f);*/

	sendingData.Yaw = 0;
	sendingData.Sway = 0;
	sendingData.Surge = ReverseFloat(anyCustomData.Surge);


	//sendingData.DisDOFPack.Roll = ReverseFloat(anyCustomData.DisDOFRoll);
	//sendingData.DisDOFPack.Pitch = ReverseFloat(anyCustomData.DisDOFPitch);
	//sendingData.DisDOFPack.Yaw = ReverseFloat(anyCustomData.DisDOFYaw);
	//sendingData.DisDOFPack.Longitudinal = ReverseFloat(anyCustomData.DisDOFLongitudinal);
	//sendingData.DisDOFPack.Lateral = ReverseFloat(anyCustomData.DisDOFLateral);
	//sendingData.DisDOFPack.Heave = ReverseFloat(anyCustomData.DisDOFHeave);


	sendingData.BuffPack.numSig = ReverseUint32(anyCustomData.BuffetSignalNum);
	sendingData.BuffPack.freq = ReverseFloat(anyCustomData.Buff_freq);
	sendingData.BuffPack.Xamp = ReverseFloat(anyCustomData.Buff_XAmp);
	sendingData.BuffPack.Yamp = ReverseFloat(anyCustomData.Buff_YAmp);
	sendingData.BuffPack.Zamp = ReverseFloat(anyCustomData.Buff_ZAmp);

	sendingData.WNpack.numSig = ReverseUint32(anyCustomData.WhiteSignalNum);
	sendingData.WNpack.XAcc = ReverseFloat(anyCustomData.WN_XAcc);
	sendingData.WNpack.XLoFreq = ReverseFloat(anyCustomData.WN_XLoFreq);
	sendingData.WNpack.XHiFreq = ReverseFloat(anyCustomData.WN_XHiFreq);
	sendingData.WNpack.YAcc = ReverseFloat(anyCustomData.WN_YAcc);
	sendingData.WNpack.YLoFreq = ReverseFloat(anyCustomData.WN_YLoFreq);
	sendingData.WNpack.YHiFreq = ReverseFloat(anyCustomData.WN_YHiFreq);
	sendingData.WNpack.ZAcc = ReverseFloat(anyCustomData.WN_ZAcc);
	sendingData.WNpack.ZLoFreq = ReverseFloat(anyCustomData.WN_ZLoFreq);
	sendingData.WNpack.ZHiFreq = ReverseFloat(anyCustomData.WN_ZHiFreq);


	FArrayWriter Writer;
	Writer << sendingData;
	SenderSocket->SendTo(Writer.GetData(), Writer.Num(), BytesSent, *RemoteAddr);

	if (BytesSent <= 0)
	{
		const FString Str = "Socket is valid but the receiver received 0 bytes, make sure it is listening properly!";
		UE_LOG(LogTemp, Error, TEXT("%s"), *Str);
		//ScreenMsg(Str);
		return false;
	}

	return true;
}

// Sets default values
//ARamaUDPSender::ARamaUDPSender()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}

// Called when the game starts or when spawned
//void ARamaUDPSender::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void ARamaUDPSender::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

