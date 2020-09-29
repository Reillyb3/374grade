#include "util.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>

void util::parseHomeworkScores(std::ifstream& f, std::vector<std::pair<float, float>>& tot, std::vector<float>& indiv) {
    int i = 0;
    
    while (f) {
        std::string s;
        std::getline(f, s);

        std::vector<std::string> entries = getRowEntries(s);
        if (entries[1] == "" || entries[0] == "Problem") continue;
        if (entries[0] == "Exam") break;

        tot.push_back(std::pair<float, float>{std::stof(entries[1]), std::stof(entries[2])});
        indiv.push_back(std::stof(entries[3]));
    }
}

void util::parseExamScores(std::ifstream& f, std::vector<std::pair<float, float>>& tot, std::vector<float>& indiv) {
    while (f) {
        std::string s;
        std::getline(f, s);
        
        std::vector<std::string> entries = getRowEntries(s);
        if (entries.empty() || entries[1] == "") break;

        tot.push_back(std::pair<float, float>{std::stof(entries[1]), std::stof(entries[2])});
        indiv.push_back(std::stof(entries[3]));
    }
}

std::vector<std::string> util::getRowEntries(std::string& s) {
    std::stringstream ss{s};
    std::vector<std::string> entries;
    std::string to_add;
    while (std::getline(ss, to_add, ',')) entries.push_back(to_add);

    return entries;
}

float util::calcIndivScore(std::vector<float>& hw_drop, std::vector<float>& ex) {
    float hw_tot = 0.0f;
    for (int i = 0; i < hw_drop.size(); ++i) hw_tot += hw_drop[i];
    float hw_points = hw_tot * kHwWeight/ kUndropHomeworks;
    
    float ex_tot = 0.0f;
    for (int i = 0; i < ex.size(); ++i) {
        if (i == 0 || i == 1) ex_tot += kMidtermWeight * ex[i];
        else if (i == 2) ex_tot += kFinalWeight * ex[i];
    }

    return ex_tot + hw_points;
}

float util::calcClassAvg(std::vector<std::pair<float, float>>& hw_drop, std::vector<std::pair<float, float>>& ex) {
    float hw_tot = 0.0f;
    for (int i = 0; i < hw_drop.size(); ++i) hw_tot += hw_drop[i].first;
    float hw_points = hw_tot * kHwWeight / kUndropHomeworks;

    float ex_tot = 0.0f;
    for (int i = 0; i < ex.size(); ++i) {
        if (i == 0 || i == 1) ex_tot += kMidtermWeight * ex[i].first;
        else if (i == 2) ex_tot += kFinalWeight * ex[i].first;
    }

    return ex_tot + hw_points;
}

float util::calcClassStd(std::vector<std::pair<float, float>>& hw_drop, std::vector<std::pair<float, float>>& ex) {
	float variance = 0.0f;
    for (int i = 0; i < hw_drop.size(); ++i) {
        float std = kHwWeight * hw_drop[i].second / kUndropHomeworks;
        variance += std::pow(std, 2.0f);
    }

    for (int i = 0; i < ex.size(); ++i) {
        if (i == 0 || i == 1) {
            float std = ex[i].second * kMidtermWeight;
            variance += std::pow(std, 2.0f);
        }
        else if (i == 2){
            float std = ex[i].second * kFinalWeight;
            variance += std::pow(std, 2.0f);
        }
    }

    return std::sqrt(variance);
}

void util::calcClassDrops(std::vector<std::pair<float, float>>& hw) {
    std::sort(hw.begin(), hw.end(), compareAvgStd);

    int num_drops = std::floor(((float) hw.size()) * kDropRatio);
    for (int i = 0; i < num_drops; ++i) hw.erase(hw.begin());
}

void util::calcIndivDrops(std::vector<float>& hw) {
    std::sort(hw.begin(), hw.end());

    int num_drops = std::floor(((float)hw.size()) * kDropRatio);
    for (int i = 0; i < num_drops; ++i) hw.erase(hw.begin());
}

bool util::compareAvgStd(std::pair<float, float> a, std::pair<float, float> b) {
    //Compare means
    float diff1 = a.first - b.first;
    if (diff1 > kEpsilonVal) return false;
    if (diff1 < -1.0f * kEpsilonVal) return true;
    //Compare Standard Devs
    float diff2 = a.second - b.second;
    if (diff2 > kEpsilonVal) return true;
    if (diff2 < -1.0f * kEpsilonVal) return false;
    //Default to false
    return false;
}

std::string util::calcGrade(float indiv_score, float class_score, float class_std) {
    float z = (indiv_score - class_score) / class_std;

    if (z > kApCutoff) return "A+";
    if (z > kACutoff) return "A";
    if (z > kAmCutoff) return "A-";
    if (z > kBpCutoff) return "B+";
    if (z > kBCutoff) return "B";
    if (z > kBmCutoff) return "B-";
    if (z > kCpCutoff) return "C+";
    if (z > kCCutoff) return "C";
    if (z > kCmCutoff) return "C-";
    if (z > kDpCutoff) return "D+";
    if (z > kDCutoff) return "D";
    if (z > kDmCutoff) return "D-";

    return "F";
}




