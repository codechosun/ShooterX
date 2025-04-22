// SXGameInstance.cpp


#include "SXGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SXUnrealObject.h"

USXGameInstance::USXGameInstance()
{
    Name = TEXT("SXGameInstance's Class Default Object");
    // CDO의 Name 속성에 저장됨.
    // 중단점을 걸어보면 언리얼 에디터가 실행되기 전에 호출됨을 알 수 있음.
}

void USXGameInstance::Init()
{
    Super::Init();

	USXUnrealObject* USXObject01 = NewObject<USXUnrealObject>();
	// 언리얼은 이런식으로 new 키워드를 안쓰고 NewObject<>() API를 사용해야 함.

	UE_LOG(LogTemp, Log, TEXT("USXObject01's Name: %s"), *USXObject01->GetObjectName());
	// 우리가 정의한 Getter()

	FProperty* NameProperty = USXUnrealObject::StaticClass()->FindPropertyByName(TEXT("Name"));
	FString CompiletimeUSObjectName;
	if (nullptr != NameProperty)
	{
		NameProperty->GetValue_InContainer(USXObject01, &CompiletimeUSObjectName);
		UE_LOG(LogTemp, Log, TEXT("CompiletimeUSObjectName: %s"), *CompiletimeUSObjectName);
		// 리플렉션 시스템을 활용
	}

	USXObject01->HelloUnreal();
	// 멤버 함수 호출.

	UFunction* HelloUnrealFunction = USXObject01->GetClass()->FindFunctionByName(TEXT("HelloUnreal"));
	if (nullptr != HelloUnrealFunction)
	{
		USXObject01->ProcessEvent(HelloUnrealFunction, nullptr);
		// 리플렉션 시스템을 활용
	}
}

void USXGameInstance::Shutdown()
{
    Super::Shutdown();
}
