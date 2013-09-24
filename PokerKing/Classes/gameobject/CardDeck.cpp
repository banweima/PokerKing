//
//  CardDeck.cpp
//  blackjack
//
//  Created by Banson Niu on 9/17/12.
//
//

#include "CardDeck.h"

static CardDeck s_CardDeck;
static bool bFirstUseCardDeck=true;

CardDeck::CardDeck()
: mNumberDecks(4)
, mNumberSuitsPerDeck(4)
, mNumberCardsPerSuit(13)
, mNumberShuffles(4)
{
    // 52 cards in a deck:
    mMaximumCardsInDeck = (mNumberSuitsPerDeck * mNumberCardsPerSuit);
    
    // Make an array to convert a suit index into a card suit:
    int i;
    for(i=0; i<4; i++)
        mCardSuitArray[i] = (CardSuit)(Diamonds+i);
    
    for(i=0; i<13; i++)
        mCardTypeArray[i] = (CardType)(Ace+i);
    
    for(i=0; i<10; i++)
        mCardValueArray[i] = i+1;
    mCardValueArray[10] = 10;
    mCardValueArray[11] = 10;
    mCardValueArray[12] = 10;
}

CardDeck::~CardDeck()
{
    CC_SAFE_RELEASE(mCards);
}

CardDeck* CardDeck::sharedCardDeck()
{
    return sharedCardDeck(4);
}

CardDeck* CardDeck::sharedCardDeck(int numberDecks)
{
    if (bFirstUseCardDeck)
    {
        bFirstUseCardDeck = false;
        s_CardDeck.mNumberDecks = numberDecks;
        s_CardDeck.init();
    }
    
    return &s_CardDeck;
}

bool CardDeck::init()
{
    mCards = CCArray::create();
    mCards->retain();
    // Compute the total number of cards:
    mNumberOfCards = mNumberDecks * mNumberSuitsPerDeck * mNumberCardsPerSuit;
    
    // Make new objects for this array:
    int	deckIndex	= 0;
    int	suitIndex	= 0;
    int	typeIndex	= 0;
    int	cardIndex	= 0;
    
    // Loop over all the decks:
    for (deckIndex = 0; deckIndex < mNumberDecks; ++deckIndex)
    {
        // Loop over all the suits:
        for (suitIndex = 0; suitIndex < mNumberSuitsPerDeck; ++suitIndex)
        {
            // Loop over all the card types in the suit:
            for (typeIndex = 0; typeIndex < mNumberCardsPerSuit; ++typeIndex)
            {
                // Set up the card:
                this->mCards->addObject(CardDeckCard::create(mCardSuitArray[suitIndex], mCardTypeArray[typeIndex],mCardValueArray[typeIndex]));
                
                //CCLog(((CardDeckCard*)this->mCards->objectAtIndex(cardIndex))->toString()->getCString());
                
                ++cardIndex;
            }
        }
    }
    
    CCLog("Deck was set up.");
    
    // Shuffle the deck:
    this->shuffleCardDeck();
    
    return true;
}

void CardDeck::shuffleCardDeck()
{
    int	deckIndex	= 0;
    int	suitIndex	= 0;
    int	typeIndex	= 0;
    int	cardIndex	= 0;
    
    srand((unsigned)time(0));
    
    CardDeckCard *pCardDeckCard;
    // Loop over all the decks:
    for (deckIndex = 0; deckIndex < mNumberDecks; ++deckIndex)
    {
        // Loop over all the suits:
        for (suitIndex = 0; suitIndex < mNumberSuitsPerDeck; ++suitIndex)
        {
            // Loop over all the card types in the suit:
            for (typeIndex = 0; typeIndex < mNumberCardsPerSuit; ++typeIndex)
            {
                pCardDeckCard = (CardDeckCard*)this->mCards->objectAtIndex(cardIndex);
                // Set up the card:
                pCardDeckCard->setCard(mCardSuitArray[suitIndex], mCardTypeArray[typeIndex], mCardValueArray[typeIndex]);
                
                ++cardIndex;
            }
        }
    }
    
    CardDeckCard *pCardDeckCard1;
    CardDeckCard *pCardDeckCard2;
    // Loop though a number of iterations to shuffle the cards:
    for (int iterationIndex = 0; iterationIndex < mNumberShuffles; ++iterationIndex)
    {
        // Loop over all the cards:
        for (cardIndex = 0; cardIndex < mNumberOfCards; ++cardIndex)
        {
            int	newCardIndex = cardIndex;
            CardSuit	firstSuit;
            CardType	firstType;
            int	firstValue;
            
            CardSuit	secondSuit;
            CardType	secondType;
            int	secondValue;
            
            // Now find a new index that's not the same as the current index:
            while (newCardIndex == cardIndex)
            {
                // Pick a new index:
                newCardIndex	= floor(rand()/(double)RAND_MAX * mNumberOfCards);
                
                pCardDeckCard1 = (CardDeckCard*)this->mCards->objectAtIndex(cardIndex);
                // Extract the information for the first card:
                firstSuit	= pCardDeckCard1->getSuit();
                firstType	= pCardDeckCard1->getType();
                firstValue	= pCardDeckCard1->getValue();
                
                pCardDeckCard2 = (CardDeckCard*)this->mCards->objectAtIndex(newCardIndex);
                // Extract the information for the second card:
                secondSuit	= pCardDeckCard2->getSuit();
                secondType	= pCardDeckCard2->getType();
                secondValue	= pCardDeckCard2->getValue();
                
                // Set the values flipping the cards:
                pCardDeckCard1->setCard(secondSuit, secondType, secondValue);
                pCardDeckCard2->setCard(firstSuit,firstType,firstValue);
                
                //CCLog("Flipping index %d with index %d", cardIndex, newCardIndex);
            }
        }
    }
    
    // Set up the current card index indicating the next card that will be pulled off the deck and dealt:
    mCurrentCardIndex = 0;
    
    // Set the number of cards remaining:
    mNumberRemainingCards = mNumberOfCards;
    
    // Set the minimum and maximum possible card index:
    int	minimumCardIndex = floor(0.50 * mNumberOfCards);	// At least half-way through the 4 decks = 104
    int	maximumCardIndex = floor(mNumberOfCards - 0.25 * mMaximumCardsInDeck); // At most within 26 cards of the end of the 4 decks: = 195
    
    // Also figure out where the last card will be in the deck to force another shuffle:
    mNewDeckCardIndex = minimumCardIndex + floor((maximumCardIndex - minimumCardIndex) * random());
    
    CCLog("The deck was shuffled");
    //log(this._numberOfCards + " cards in the deck");
    //log("Deck will be shuffled after card " + this._newDeckCardIndex + " is dealt");
    
    // See if blackjack is being forced:
//    if ( ( _DEBUG == true ) && ( tweaks.forceBlackjack == true ) )
//    {
//        // Make player get 21 and the dealer get 20:
//        this._cards[0].setType(PlayingCard.Type.Ace);
//        this._cards[0].setValue(11);
//        this._cards[1].setType(PlayingCard.Type.Ten);
//        this._cards[1].setValue(10);
//        this._cards[2].setType(PlayingCard.Type.Ten);
//        this._cards[2].setValue(10);
//        this._cards[3].setType(PlayingCard.Type.Ten);
//        this._cards[3].setValue(10);
//    }
}

////////////////////////////////////////////////////////////////
//
// Function to get the next card:
//

CardDeckCard* CardDeck::getNextCard()
{
    // Clone the next available card object to send to the caller:
    CardDeckCard *pNextCardDeckCard = (CardDeckCard *)this->mCards->objectAtIndex(mCurrentCardIndex);
    
    // Increment the card index:
    ++mCurrentCardIndex;
    --mNumberRemainingCards;
    
    return pNextCardDeckCard;
}

////////////////////////////////////////////////////////////////
//
// Returns true when the deck needs to be shuffled again:
//

bool CardDeck::needsShuffle()
{
    // See if we're far enough along to need shuffling:
    if (mCurrentCardIndex >= mNewDeckCardIndex)
        return true;
    
    return false;
}

void CardDeck::resetCardDeck()
{
    bFirstUseCardDeck = true;
}
