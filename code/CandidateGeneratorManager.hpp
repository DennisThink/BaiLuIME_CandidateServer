#ifndef _BAI_LU_IME_CANDIDATE_GENERATOR_MANAGER_H_
#define _BAI_LU_IME_CANDIDATE_GENERATOR_MANAGER_H_
#include <string>
#include <vector>
class CCandidateGeneratorManager
{
public:
	static CCandidateGeneratorManager* GetInstance();
	std::vector<std::string> GenerateCandidates(const std::string& userInput,const int maxCount);
private:
	CCandidateGeneratorManager();
	virtual ~CCandidateGeneratorManager();

};
#endif