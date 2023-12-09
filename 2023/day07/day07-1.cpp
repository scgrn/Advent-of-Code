#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

const char cards[] = {'e', 'd', 'c', 'b', 'a', '9', '8', '7', '6', '5', '4', '3', '2'};

struct Hand {
    std::string cards;
    int bid;
    
    static bool cmp(const Hand& a, const Hand& b) {
        return a.cards.compare(b.cards) < 0;
    }
};

std::vector<Hand> hands[7];

int getHandType(const Hand& hand) {
    int count[13];
    for (int i = 0; i < 13; i++) {
        count[i] = 0;
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 13; j++) {
            if (hand.cards[i] == cards[j]) {
                count[j]++;
            }
        }
    }
    
    int highestIndex = 0;
    for (int i = 0; i < 13; i++) {
        if (count[i] > count[highestIndex]) {
            highestIndex = i;
        }
    }
    int highestCount = count[highestIndex];
    
    int secondHighestIndex = 0;
    for (int i = 0; i < 13; i++) {
        if (i != highestIndex && count[i] > count[secondHighestIndex]) {
            secondHighestIndex = i;
        }
    }
    int secondHighestCount = count[secondHighestIndex];

    if (highestCount == 5) {
        return 6;   //  five of a kind
    }
    
    if (highestCount == 4) {
        return 5;   //  four of a kind
    }
    
    if (highestCount == 3 && secondHighestCount == 2) {
        return 4;   //  full house
    }
    
    if (highestCount == 3) {
        return 3;   //  three of a kind
    }

    if (highestCount == 2 && secondHighestCount == 2) {
        return 2;   //  two pair
    }

    if (highestCount == 2) {
        return 1;   //  one pair
    }
    
    return 0;   //  high card
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
            
            hands[getHandType(hand)].push_back(hand);
        }

        for (int i = 0; i < 7; i++) {
            std::sort(hands[i].begin(), hands[i].end(), Hand::cmp);
        }
        
        int winnings = 0;
        int rank = 1;
        
        for (int i = 0; i < 7; i++) {
            std::cout << "-------------------  " << std::endl;
            for (auto hand : hands[i]) {
                winnings += (hand.bid * rank);
                std::cout << rank << " - " << hand.cards << " - " << hand.bid << std::endl;
                
                rank++;
            }
        }
        std::cout << std::endl << winnings << std::endl;
        
        file.close();
        
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

