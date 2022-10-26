// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "Blueprint/UserWidget.h"
#include "BKPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BRAVEKNIGHT_API ABKPlayerController : public APlayerController
{
	GENERATED_BODY()

	
public:
	
	ABKPlayerController();


	/* THIS CODE DOES NOT COMPILED
	* 
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UI")
	class UUserWidget* HUDOverlay;
	*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<class UUserWidget> HUDOverlayAsset;
	
	/** Variable to hold the widget after creating it */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//UUserWidget* HUDOverlay;

	

protected:
	void BeginPlay() override;


};
