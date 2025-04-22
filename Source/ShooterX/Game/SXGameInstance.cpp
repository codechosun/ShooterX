// SXGameInstance.cpp


#include "Game/SXGameInstance.h"
#include "SXGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

USXGameInstance::USXGameInstance()
{
    UE_LOG(LogTemp, Log, TEXT("USXGameInstance::USXGameInstance() has been called."));
}

void USXGameInstance::Init()
{
    Super::Init();
    // Super는 부모 클래스 이름의 재정의. 즉, 부모클래스의 Init() 함수를 호출하는 것.
    // 엔진 업데이트 루틴을 지키기 위해서, 언리얼 엔지니어가 작성한 코드가 먼저 실행되게끔 하기 위함.

    UE_LOG(LogTemp, Log, TEXT("USXGameInstance::Init() has been called."));

    UKismetSystemLibrary::PrintString(GetWorld(), TEXT("USXGameInstance::Init() has been called."));
    // UKismetSystemLibrary::PrintString() 함수의 첫 매개변수 이름은 "WorldContextObject"
    // Context란, 문맥상 ~될만한거 라고 생각하면 좋음. 여기서는 "월드 개체를 만들만한 거"라고 해석.
    // 따라서 GetWorld()를 통해서 진짜 World 개체를 넘겨줘도 되지만
    // this(USGameInstance 개체)를 전달해서 this가 속한 월드 개체를 구하게끔 해도된다는 뜻.

    //UKismetSystemLibrary::PrintString(GetWorld(), TEXT("USXGameInstance::Init() has been called."));
    UWorld* WorldInstance = GetWorld();
    if (IsValid(WorldInstance) == true) // UWorld 클래스이므로, UObject라서 IsValid() 사용 가능.
    {
        // 이런 식으로도 할 순 있지만, 만에하나 WorldInstance 개체가 유효하지 않다면?
        // 아무런 로직이 돌지 않으므로 다른 팀원은 잘못된건지 단박에 알아채지 못할 수도 있음.
        // WorldInstance 개체가 없다는건 큰 문제이므로 이럴 때 checkf()를 활용.
        UKismetSystemLibrary::PrintString(WorldInstance, TEXT("Init() has been called."));
    }

    checkf(IsValid(WorldInstance) == true, TEXT("WorldInstance is invalid."));
    // checkf() 매크로 함수를 잘 활용하면 if() 구문도 줄어서 더 깔끔한 코드 작성도 가능.
    // == 연산자를 != 연산자로 바꿔서 결과를 확인해보자.
    UKismetSystemLibrary::PrintString(WorldInstance, TEXT("Init() has been called."));
}

void USXGameInstance::Shutdown()
{
    Super::Shutdown();

    UE_LOG(LogTemp, Log, TEXT("USXGameInstance::Shutdown() has been called."));
}
