// grade_estimator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "util.h"

int main(int argc, char* argv[])
{
    std::vector<float> indivHw;
    std::vector<float> indivExam;
    std::vector<std::pair<float, float>> classHw;
    std::vector<std::pair<float, float>> classExam;

    std::ifstream f{ argv[1] };
    util::parseHomeworkScores(f, classHw, indivHw);
    util::parseExamScores(f, classExam, indivExam);
    util::calcClassDrops(classHw);
    util::calcIndivDrops(indivHw);

    float indivScore = util::calcIndivScore(indivHw, indivExam);
    float classScore = util::calcClassAvg(classHw, classExam);
    float classSd = util::calcClassStd(classHw, classExam);

    std::cout << "Class Estimated Average: " << classScore << std::endl;
    std::cout << "Class Estiamted Standard Deviation: " << classSd << std::endl;
    std::cout << "Your estimated Score: " << indivScore << std::endl;
    std::cout << "Your estimated grade: " << util::calcGrade(indivScore, classScore, classSd) << std::endl;
}

