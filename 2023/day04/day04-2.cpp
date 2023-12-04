#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

const int NUM_CARDS = 204;

struct Card {
    int instances;
    int matches;
} cards[NUM_CARDS];

std::vector<int> splitGroup(std::string group) {
    std::vector<int> ret;

    std::stringstream ss(group);
    std::string number;
    while (getline(ss, number, ' ')) {
        //  remove extraneous spaces
        number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
        
        if (number.size() > 0) {
            ret.push_back(atoi(number.c_str()));
        }
    }
    
    return ret;
}

int calculateMatches(std::string line) {
    line = line.substr(line.find(':') + 1);

    int split = line.find('|');
    std::string winningGroup = line.substr(0, split);
    std::string numbersGroup = line.substr(split + 1);

    std::vector<int> winning = splitGroup(winningGroup);
    std::vector<int> numbers = splitGroup(numbersGroup);

    int matches = 0;
    for (auto number : numbers) {
        for (auto winningNumber : winning) {
            if (number == winningNumber) {
                matches++;
            }
        }
    }
    
    return matches;
}

int countCards() {
    int sum = 0;
    for (int card = 0; card < NUM_CARDS; card++) {
        for (int instance = 0; instance < cards[card].instances; instance++) {
            for (int match = 0; match < cards[card].matches; match++) {
                int newCard = card + match + 1;
                if (newCard < NUM_CARDS) {
                    cards[newCard].instances++;
                }
            }
        }
        sum += cards[card].instances;
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
    int sum = 0;
    
    std::string line;
    std::ifstream file("2023/day04/input.txt");
    if (file.is_open()) {
        int index = 0;
        while (getline(file, line)) {
            cards[index].instances = 1;
            cards[index].matches = calculateMatches(line);
            index++;
        }
        file.close();
    }
    
    std::cout << countCards() << "\n";
    
    return 0;
}

