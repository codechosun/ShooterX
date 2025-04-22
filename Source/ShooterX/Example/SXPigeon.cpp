// SXPigeon.cpp


#include "Example/SXPigeon.h"

USXPigeon::USXPigeon()
{
	Name = TEXT("Pigeon");
}

void USXPigeon::Fly()
{
	UE_LOG(LogTemp, Log, TEXT("%s is now flying."), *Name);
}

void USXPigeon::Serialize(FArchive& InOutAr)
{
	Super::Serialize(InOutAr);

	InOutAr << Name;
	InOutAr << ID;
}
