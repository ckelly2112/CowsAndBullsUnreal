// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Please guess the four letter isogram")); //TODO Fix magic number

    //NEED Set Lives
    //NEED Set Difficulty (WordLength)
    HiddenWord = TEXT("skate"); //TODO Make this not hard coded

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    PrintLine(Input);
    if(Input == HiddenWord){
        PrintLine(TEXT("You got it! Congratulations!"));
    }
    else{
        PrintLine(TEXT("That's incorrect, try again"));
    }
        //NEED Check isogram
        //NEED Right amount of characters
        //NEED Check if lives > 0
        //NEED play again if lives > 0
        //NEED remove life

}