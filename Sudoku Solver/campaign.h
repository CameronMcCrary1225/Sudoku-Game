#pragma once
#include <vector>
using namespace std;

#ifndef CAMPAIGN_H
#define CAMPAIGN_H
class campaign {
public:
	int currentlevel = 1;
	bool oncampaign = false;
	vector<vector<int>> loadcurrentlevel();
};
#endif