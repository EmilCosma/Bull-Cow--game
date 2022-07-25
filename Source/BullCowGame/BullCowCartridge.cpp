#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Words[ FMath::RandRange( 0, Words.Num() - 1 ) ];
    Lives = HiddenWord.Len()*2;
    //welcoming the player
    PrintLine(TEXT("Bun venit in jocul BullCow"));
    PrintLine(TEXT("Ghiceste animalul de %i litere"), HiddenWord.Len());
    PrintLine(TEXT("Ai %i vieti"), Lives);
    PrintLine(TEXT("Apasa TAB pentru a scrie raspunsul si apoienter..."));
    bGameOver = false;
    //PrintLine(FString::Printf(TEXT("The HiddenWord is: %s and has %i         characters\n"), *HiddenWord, HiddenWord.Len() )); //Debug line

}


void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nApasa enter ca sa joci din nou..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if(Guess == HiddenWord)
    {
        PrintLine(TEXT("Ai castigat!"));
        EndGame();
        return;
    }
    //Check if right
    if(HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("Cuvantul are %i litere"), HiddenWord.Len());
        return;
    } 
    //Check if Isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("In cuvant nu se repeta nicio litera!"));
        return;
    }
    //Remove life
    --Lives;
    //PrintLine(TEXT("Ai pierdut o viata!"));

    if(Lives<1)
    {
        ClearScreen();
        PrintLine(TEXT("Nu mai ai nicio viata."));
        PrintLine(TEXT("Cuvantul corect era: %s"), *HiddenWord);
        EndGame();
        return;
    }

    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("Ai %i Bulls si %i Cows"), Bulls, Cows);

    PrintLine(TEXT("Incearca din nou! Mai ai %i vieti"), Lives);
    
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    
    for(int i=0; i < Word.Len() - 1; i++)
        for(int j = i+1; j < Word.Len(); j++)
            if(Word[i] == Word[j])
                return false;
    return true;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount=CowCount=0;
    for(int32 i = 0; i < Guess.Len(); i++)
    {
        if(Guess[i] == HiddenWord[i])
            BullCount++;
        else
            for (int32 j = 0; j < HiddenWord.Len(); j++)
                if(Guess[i] == HiddenWord[j])
                {
                    CowCount++; 
                    break;
             }
        }
}