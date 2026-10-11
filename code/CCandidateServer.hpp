#ifndef _BAILU_IME_CCANDIDATE_SERVER_HPP_
#define _BAILU_IME_CCANDIDATE_SERVER_HPP_
class CCandidateServer final
{
public:
	CCandidateServer();
	virtual ~CCandidateServer();
	void start();
	void run();
	void stop();
};
#endif