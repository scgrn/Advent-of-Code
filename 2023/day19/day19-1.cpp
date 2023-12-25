#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Rule {
    enum Operand {
        X, M, A, S
    } operand;

    enum Operator {
        LT, GT, NONE
    } op;
    
    int value;
    std::string destination;
};
std::unordered_map<std::string, std::vector<Rule>> workflows;

struct Part {
    int x, m, a, s;
};
std::vector<Part> parts;

void parseWorkflow(const std::string& line) {
    int braceIndex = line.find_first_of('{');
    
    std::string name = line.substr(0, braceIndex);
    std::string rulesStr = line.substr(braceIndex + 1, line.length() - braceIndex - 2);

    std::vector<Rule> rules;
    std::stringstream ss(rulesStr);
    std::string ruleStr;
    while (getline(ss, ruleStr, ',')) {
        Rule rule;
        int colonIndex = ruleStr.find_first_of(':');
        if (colonIndex == std::string::npos) {
            rule.op = Rule::NONE;
            rule.destination = ruleStr;
        } else {
            std::string condition = ruleStr.substr(0, colonIndex);
            int opIndex = condition.find_first_of('<');
            if (opIndex != std::string::npos) {
                rule.op = Rule::LT;
            } else {
                opIndex = condition.find_first_of('>');
                rule.op = Rule::GT;
            }
            switch (condition[0]) {
                case 'x': rule.operand = Rule::X; break;                
                case 'm': rule.operand = Rule::M; break;                
                case 'a': rule.operand = Rule::A; break;                
                case 's': rule.operand = Rule::S; break;                
                default: break;
            };
            rule.value = atoi(condition.substr(opIndex + 1).c_str());
            rule.destination = ruleStr.substr(colonIndex + 1);
        }
        rules.push_back(rule);
    }

    workflows.emplace(name, rules);
}

void parsePart(const std::string& line) {
    std::string stripped = line.substr(1, line.length() - 2);
    std::stringstream ss(stripped);
    std::string rating;
    Part part;
    
    getline(ss, rating, ',');
    part.x = atoi(rating.substr(2).c_str());

    getline(ss, rating, ',');
    part.m = atoi(rating.substr(2).c_str());

    getline(ss, rating, ',');
    part.a = atoi(rating.substr(2).c_str());

    getline(ss, rating, ',');
    part.s = atoi(rating.substr(2).c_str());

    parts.push_back(part);
}

uint32_t evaluatePart(const Part& part) {
    std::string currentRule = "in";
     
    while (currentRule != "A" && currentRule != "R") {
        for (auto& rule : workflows[currentRule]) {
            int operand;
            switch (rule.operand) {
                case Rule::X: operand = part.x; break;
                case Rule::M: operand = part.m; break;
                case Rule::A: operand = part.a; break;
                case Rule::S: operand = part.s; break;
                default: break;
            }

            if (rule.op == Rule::LT) {
                if (operand < rule.value) {
                    currentRule = rule.destination;
                    break;
                }
            } else if (rule.op == Rule::GT) {
                if (operand > rule.value) {
                    currentRule = rule.destination;
                    break;
                }
            } else {
                currentRule = rule.destination;
                break;
            }
        }
    }

    if (currentRule == "A") {
        return part.x + part.m + part.a + part.s;
    } else {
        return 0;
    }
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day19/input.txt");
    if (file.is_open()) {
        bool parsingParts = false;
        while (getline(file, line)) {
            if (line.empty()) {
                parsingParts = true;
            } else {
                parsingParts ? parsePart(line) : parseWorkflow(line);
            }
        }
        file.close();

        uint64_t sum = 0;
        for (auto& part : parts) {
            sum += evaluatePart(part);
        }
        std::cout << sum << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

