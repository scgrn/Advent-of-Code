#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

std::vector<int> program;
int a, b, c;
int instructionPointer;

std::string output;

int interpretComboOperand(int operand) {
    if (operand <= 3) {
        return operand;
    }

    switch (operand) {
        case 4: return a; break;
        case 5: return b; break;
        case 6: return c; break;
        default: return -1; break;
    }
}

void adv(int operand) {
    a = a / pow(2, interpretComboOperand(operand));
}

void bxl(int operand) {
    b = b ^ operand;
}

void bst(int operand) {
    b = interpretComboOperand(operand) % 8;
}

void jnz(int operand) {
    if (a != 0) {
        instructionPointer = operand / 2;
        instructionPointer -= 2;
    }
}

void bxc(int operand) {
    b = b ^ c;
}

void out(int operand) {
    if (!output.empty()) {
        output += ',';
    }
    output += std::to_string(interpretComboOperand(operand) % 8);
}

void bdv(int operand) {
    b = a / pow(2, interpretComboOperand(operand));
}

void cdv(int operand) {
    c = a / pow(2, interpretComboOperand(operand));
}

void execute() {
    instructionPointer = 0;
    while (instructionPointer < program.size() - 1) {
        int opcode = program[instructionPointer];
        int operand = program[instructionPointer + 1];

        switch (opcode) {
            case 0: adv(operand); break;
            case 1: bxl(operand); break;
            case 2: bst(operand); break;
            case 3: jnz(operand); break;
            case 4: bxc(operand); break;
            case 5: out(operand); break;
            case 6: bdv(operand); break;
            case 7: cdv(operand); break;
            default: break;
        }

        instructionPointer += 2;
    }
}

void loadProgram(std::vector<std::string> input) {
    //  parse register A
    std::string num = input[0].substr(input[0].find(':') + 2, std::string::npos);
    a = atoi(num.c_str());

    //  parse register B
    num = input[1].substr(input[1].find(':') + 2, std::string::npos);
    b = atoi(num.c_str());

    //  parse register C
    num = input[2].substr(input[2].find(':') + 2, std::string::npos);
    c = atoi(num.c_str());

    std::string programStr = input[4].substr(input[4].find(':') + 2, std::string::npos);
    std::stringstream ss(programStr);
    std::string str;
    while (getline(ss, str, ',')) {
        program.emplace_back(atoi(str.c_str()));
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day17/input.txt");

    if (file.is_open()) {
        std::vector<std::string> input;
        std::string line;

        while (getline(file, line)) {
            input.emplace_back(line);
        }
        file.close();

        loadProgram(input);
        execute();

        std::cout << output << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

