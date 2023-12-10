#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <tuple>

enum HandType {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

const char cards[] = {'e', 'd', 'c', 'b', 'a', '9', '8', '7', '6', '5', '4', '3', '2'};

struct Hand {
    std::string cards;
    HandType type;
    int bid;
    
    bool operator < (const Hand& other) const {
        return std::tie(type, cards) < std::tie(other.type, other.cards);
    }    
};

std::vector<Hand> hands;

HandType getHandType(const Hand& hand) {
    const int NUM_CARD_VALUES = 13;
    
    //  count frequency of each card value
    int count[NUM_CARD_VALUES];
    for (int i = 0; i < NUM_CARD_VALUES; i++) {
        count[i] = 0;
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < NUM_CARD_VALUES; j++) {
            if (hand.cards[i] == cards[j]) {
                count[j]++;
            }
        }
    }
    
    int highestIndex = 0;
    for (int i = 1; i < NUM_CARD_VALUES; i++) {
        if (count[i] > count[highestIndex]) {
            highestIndex = i;
        }
    }
    int highestCount = count[highestIndex];
    
    int secondHighestIndex = 0;
    for (int i = 1; i < NUM_CARD_VALUES; i++) {
        if (i != highestIndex && count[i] > count[secondHighestIndex]) {
            secondHighestIndex = i;
        }
    }
    int secondHighestCount = count[secondHighestIndex];

    //  determine hand type
    if (highestCount == 5) {
        return FIVE_OF_A_KIND;
    }
    
    if (highestCount == 4) {
        return FOUR_OF_A_KIND;
    }
    
    if (highestCount == 3 && secondHighestCount == 2) {
        return FULL_HOUSE;
    }
    
    if (highestCount == 3) {
        return THREE_OF_A_KIND;
    }

    if (highestCount == 2 && secondHighestCount == 2) {
        return TWO_PAIR;
    }

    if (highestCount == 2) {
        return ONE_PAIR;
    }
    
    return HIGH_CARD;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day07/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            Hand hand;
            ss >> hand.cards;
            ss >> hand.bid;
            
            std::replace(hand.cards.begin(), hand.cards.end(), 'A', 'e');
            std::replace(hand.cards.begin(), hand.cards.end(), 'K', 'd');
            std::replace(hand.cards.begin(), hand.cards.end(), 'Q', 'c');
            std::replace(hand.cards.begin(), hand.cards.end(), 'J', 'b');
            std::replace(hand.cards.begin(), hand.cards.end(), 'T', 'a');
            
            hand.type = getHandType(hand);
            hands.push_back(hand);
        }
        file.close();

        int winnings = 0;
        int rank = 1;
        
        std::sort(hands.begin(), hands.end());
        for (const auto& hand : hands) {
            winnings += (hand.bid * rank);
            std::cout << hand.type << " - " << rank << " - " << hand.cards << " - " << hand.bid << std::endl;
            
            rank++;
        }
        std::cout << std::endl << winnings << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

