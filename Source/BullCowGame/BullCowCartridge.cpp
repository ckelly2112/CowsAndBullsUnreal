// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(WordList);
    SetupGame();

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
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("BULL = A letter is correct \nand in the right spot"));
    PrintLine(TEXT("COW: A letter is correct \nbut not in the correct spot\n"));
    PrintLine(TEXT("There is a %i letter isogram\n"), HiddenWord.Len());
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
            PrintLine(TEXT("Incorrect, try again!"));
            PrintLine(TEXT("Lives Left: %i"), --Lives);
        } else{
            ClearScreen();
            PrintLine(TEXT("You ran out of Lives!"));
            PrintLine(TEXT("Your word was: %s"), *HiddenWord);
            PrintLine(TEXT("Game Over!"));
            EndGame();
            return;
        }

        FBullCowCount Score = GetBullsCows(Guess);
        PrintLine(TEXT("WORD LENGTH: %i"), HiddenWord.Len());
        PrintLine(TEXT("BULLS: %i COWS: %i"), Score.Bulls, Score.Cows);
}

bool UBullCowCartridge::bIsIsogram(const FString& Guess) const{

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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Words) const{

    TArray<FString> ValidWords;
     for (auto Index : Words){
        if(Index.Len() >= 4 && Index.Len() <= 8 && bIsIsogram(Index)){
            ValidWords.Emplace(Index);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullsCows(const FString& Guess) const{
    FBullCowCount Count;

    for(int32 i = 0; i < Guess.Len(); i++){
        if(Guess[i] == HiddenWord[i]){
            Count.Bulls++;
            continue;
        }
        for(int32 j = 0; j < HiddenWord.Len(); j++){
            if (Guess[i] == HiddenWord[j]){
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}