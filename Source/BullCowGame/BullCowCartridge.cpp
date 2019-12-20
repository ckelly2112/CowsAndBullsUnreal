// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    TArray<FString> Words = GetValidWords(WordList);
    SetupGame();
    
    PrintLine(TEXT("Number of valid words is: %i"), Words.Num());
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver){
        ClearScreen();
        SetupGame();
    }
    else{
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame(){
    HiddenWord = TEXT("skate"); //TODO Make this not hard coded
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("There is a %i letter isogram"), HiddenWord.Len());
    PrintLine(TEXT("Type your guess here and \npress enter to continue..."));
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(TEXT("Please press enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    ClearScreen();
    PrintLine(TEXT("Your guess was: %s"), *Guess);

        if(Guess == HiddenWord){
            PrintLine(TEXT("You got it! Congratulations!"));
            EndGame();
            return;
        }
        
        if(Guess.Len() != HiddenWord.Len()){
            PrintLine(TEXT("Length of the word should be %i letters"), HiddenWord.Len());
            PrintLine(TEXT("You still have %i lives left"), Lives);
            return;
        }
        if(!bIsIsogram(Guess)){
            PrintLine(TEXT("An Isogram has no repeating letters!"));
        }
        
       //Remove Lives if wrong 
        if(Lives > 1){
            PrintLine(TEXT("Try again"));
            PrintLine(TEXT("Lives Left: %i"), --Lives);
        } else{
            ClearScreen();
            PrintLine(TEXT("You ran out of Lives!"));
            PrintLine(TEXT("Game Over!"));
            EndGame();
        }
}

bool UBullCowCartridge::bIsIsogram(FString Guess) const{

    //Loop i (index) and compare with j (Comparisson)
    for(int32 i = 0; i < Guess.Len(); i++){
        for(int32 j = 0; j < Guess.Len(); j++){
            if (Guess[i] == Guess[j] && i != j){
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> Words) const{

    TArray<FString> ValidWords;
     for (auto Index : Words){
        if(Index.Len() >= 4 && Index.Len() <= 8 && bIsIsogram(Index)){
            ValidWords.Emplace(Index);
        }
    }

    return ValidWords;
}