#include "CandidateGeneratorManager.hpp"
#include "BaiLuIME_CandidateGenerator/code/source/CandidateGenerator.h"
#include "BaiLuIME_CandidateGenerator/code/source/SimpleCandidateGenerator.h"
#include "BaiLuIME_CandidateGenerator/code/source/SimpleQuanPinGenerator.h"
#include "BaiLuIME_CandidateGenerator/code/source/RimeCandidateGenerator.h"
#include <vector>
#include <memory>
using Generator_Shared_Ptr = std::shared_ptr<CandidateGenerator>;
static std::vector<Generator_Shared_Ptr> g_candidateGenerators;
CCandidateGeneratorManager* CCandidateGeneratorManager::GetInstance()
{
	static CCandidateGeneratorManager instance;
	return &instance;
}

CCandidateGeneratorManager::CCandidateGeneratorManager()
{
	{
		auto generator1 = std::make_shared<SimpleCandidateGenerator>();
		g_candidateGenerators.push_back(generator1);
	}
	{
		auto generator2 = std::make_shared<CSimpleQuanPinGenerator>();
		g_candidateGenerators.push_back(generator2);
	}
	{
		auto generator3 = std::make_shared<CRimeCandiateGenerator>();
		g_candidateGenerators.push_back(generator3);
	}
}

CCandidateGeneratorManager::~CCandidateGeneratorManager()
{

}

std::vector<std::string> CCandidateGeneratorManager::GenerateCandidates(const std::string& userInput, const int maxCount)
{
	std::vector<std::string> candidates;
	for (auto item : g_candidateGenerators)
	{
		auto tempCandidates = item->Generate(userInput, maxCount);
		candidates.insert(candidates.end(), tempCandidates.begin(), tempCandidates.end());
	}

	if (candidates.size() >= maxCount)
	{
		candidates.resize(maxCount);
	}
	return candidates;
}