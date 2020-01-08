#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, meta = (BitFlags))
enum class EKeyType : uint8
{
	EKT_Red = 1 UMETA(DisplayName = "Red key"),
	EKT_Green = 2 UMETA(DisplayName = "Green key"),
	EKT_Blue = 4 UMETA(DisplayName = "Blue key"),
	EKT_Yellow = 8 UMETA(DisplayName = "Yellow key"),
	EKT_Orange = 16 UMETA(DisplayName = "Orange key"),
	EKT_Purple = 32 UMETA(DisplayName = "Purple key"),
	EKT_MAX = 0 UMETA(DisplayName = "Default")
};
