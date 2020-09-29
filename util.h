#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>
namespace util {
	void parseHomeworkScores(std::ifstream& f, std::vector<std::pair<float,float>>& tot, std::vector<float>& indiv);
	void parseExamScores(std::ifstream& f, std::vector<std::pair<float,float>>& tot, std::vector<float>& indiv);
	std::vector<std::string> getRowEntries(std::string& s);
	float calcIndivScore(std::vector<float>& hw_drop, std::vector<float>& ex);
	float calcClassAvg(std::vector<std::pair<float, float>>& hw_drop, std::vector<std::pair<float, float>>& ex);
	float calcClassStd(std::vector<std::pair<float, float>>& hw_drop, std::vector<std::pair<float, float>>& ex);
	void calcClassDrops(std::vector<std::pair<float, float>>& hw);
	void calcIndivDrops(std::vector<float>& hw);
	bool compareAvgStd(std::pair<float, float> a, std::pair<float, float> b);
	std::string calcGrade(float indiv_score, float class_score, float class_std);

	const static float kDropRatio = 0.4166666667f; //15 out of 36 homeworks are dropped
	const static float kEpsilonVal = 0.01f;
	const static float kHwWeight = 0.28f;
	const static float kMidtermWeight = 0.21f;
	const static float kFinalWeight = 0.3f;
	const static float kUndropHomeworks = 21.0f;

	const static float kApCutoff = 1.6666666f;
	const static float kACutoff = 1.333333f;
	const static float kAmCutoff = 1.0f;
	const static float kBpCutoff = 0.6666666f; 
	const static float kBCutoff = 0.33333333f;
	const static float kBmCutoff = 0.0f;
	const static float kCpCutoff = -0.3333333f;
	const static float kCCutoff = -0.66666666f;
	const static float kCmCutoff = -1.0f;
	const static float kDpCutoff = -1.33333333f;
	const static float kDCutoff = -1.66666666f;
	const static float kDmCutoff = -2.0f;
};