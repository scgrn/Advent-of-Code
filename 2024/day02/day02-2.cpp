#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

bool isDampenedReportSafe(std::vector<int> const& report) {
    bool increasing = report[report.size() - 1] > report[0];
    for (int i = 1; i < report.size(); i++) {
        
        int level1 = report[i - 1];
        int level2 = report[i];

        if (increasing) {
            if (level2 <= level1) {
                return false;
            }
        } else {
            if (level2 >= level1) {
                return false;
            }
        }
        
        int diff = abs(level2 - level1);
        if (diff < 1 || diff > 3) {
            return false;
        }
    }

    return true;
}

bool isReportSafe(std::vector<int> const& report) {
    for (int i = 0; i < report.size(); i++) {
        std::vector<int> dampenedReport;
        for (int j = 0; j < report.size(); j++) {
            if (i != j) {
                dampenedReport.push_back(report[j]);
            }
        }
        
        if (isDampenedReportSafe(dampenedReport)) {
            return true;
        }
    }
    
    return false;
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<int> > reports;
    std::string line;

    std::ifstream file("2024/day02/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);

            std::vector<int> report;
            std::string level;
            while (getline(ss, level, ' ')) {
                report.push_back(atoi(level.c_str()));
            }
            reports.push_back(report);
        }
        file.close();

        int safeReports = 0;
        for (auto report : reports) {
            if (isReportSafe(report)) {
                safeReports++;
            }
        }
        std::cout << safeReports << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}
