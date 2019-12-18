// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
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
    PrintLine(TEXT("Your guess was: %s"), *Guess);

        if(Guess == HiddenWord){
            PrintLine(TEXT("You got it! Congratulations!"));
            EndGame();
        }
        else{
            if(Guess.Len() != HiddenWord.Len())
                PrintLine(TEXT("Length of the word should be %i letters"), HiddenWord.Len()); 
            if(Lives > 1){
                PrintLine(TEXT("Try again"));
                PrintLine(TEXT("Lives Left: %i"), --Lives);
            }
            else{
                PrintLine(TEXT("Game Over!"));
                EndGame();
            }
        }
    
        //TODO Check isogram
        //TODO Right amount of characters
        //TODO Check if lives > 0
        //TODO Guess Again
        //TODO Lives Left
        //TODO play again if lives 0
        //TODO remove life

}