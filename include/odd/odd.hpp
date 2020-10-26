#ifndef ODD_HPP
#define ODD_HPP

#include <array>
#include <string>
#include <vector>
#include <curl/curl.h>

namespace odd {

struct OireachtasFilter {
public:
	static int const DEFAULT_HOUSE_NO;
	static int const DEFAULT_LIMIT;
	static int const DEFAULT_SKIP;
	static int const DEFAULT_QUESTION_NO;
	static std::string const DEFAULT_LANG;
	static std::string const DEFAULT_ACT_NO;
	static std::string const DEFAULT_ACT_YEAR;
	static std::string const DEFAULT_DATE_END;
	static std::string const DEFAULT_DATE_START;
	static std::string const DEFAULT_DEBATE_ID;
	static std::string const DEFAULT_MEMBER_ID;
	static std::string const DEFAULT_VOTE_ID;
	static std::string const DEFAULT_QUESTION_ID;
	static std::string const DEFAULT_BILL_ID;
	static std::string const DEFAULT_BILL_NO;
	static std::string const DEFAULT_BILL_YEAR;
	static std::string const DEFAULT_CHAMBER;
	static std::string const DEFAULT_CHAMBER_TYPE;

	static std::string const QFIELD_HOUSE_NO;
	static std::string const QFIELD_LIMIT;
	static std::string const QFIELD_SKIP;
	static std::string const QFIELD_LANG;
	static std::string const QFIELD_ACT_NO;
	static std::string const QFIELD_ACT_YEAR;
	static std::string const QFIELD_DATE_END;
	static std::string const QFIELD_DATE_START;
	static std::string const QFIELD_DEBATE_ID;	
	static std::string const QFIELD_OUTCOME;
	static std::string const QFIELD_MEMBER_ID;
	static std::string const QFIELD_VOTE_ID;
	static std::string const QFIELD_QUESTION_ID;
	static std::string const QFIELD_QUESTION_NO;
	static std::string const QFIELD_BILL_ID;
	static std::string const QFIELD_BILL_NO;
	static std::string const QFIELD_BILL_YEAR;
	static std::string const QFIELD_BILL_SOURCE;
	static std::string const QFIELD_BILL_STATUS;
	static std::string const QFIELD_CHAMBER;
	static std::string const QFIELD_CHAMBER_TYPE;
	static std::string const QFIELD_CHAMBER_ID;
	static std::string const QFIELD_QTYPE; 

	int m_houseNo;
	int m_limit;
	int m_skip;

	std::string m_lang;
	std::string m_actNo;
	std::string m_actYear;

	std::string m_dateEnd;
	std::string m_dateStart;

	std::string m_debateId;
	std::vector<std::string> m_outcome;

	std::string m_memberId;
	std::string m_voteId;
	
	std::string m_questionId;
	int m_questionNo;

	std::string m_billId;
	std::string m_billNo;
	std::string m_billYear;
	std::vector<std::string> m_billSource;
	std::vector<std::string> m_billStatus;

	std::string m_chamber;
	std::string m_chamberType;
	std::vector<std::string> m_chamberId;

	std::vector<std::string> m_qtype;

	[[nodiscard]] OireachtasFilter() noexcept;
	[[nodiscard]] OireachtasFilter(OireachtasFilter &filter) noexcept;
	[[nodiscard]] OireachtasFilter(OireachtasFilter &&filter) noexcept;
	~OireachtasFilter() noexcept;

	std::string const qstring() const noexcept;
private:
	std::string join(std::vector<std::string> const &vec, char const c) const noexcept;
};

struct OireachtasConf {
	static std::string const DEFAULT_API_DOMAIN;
	static std::string const DEFAULT_LEGISLATION_ENDPOINT;
	static std::string const DEFAULT_DEBATES_ENDPOINT;
	static std::string const DEFAULT_CONSTITUENCIES_ENDPOINT;
	static std::string const DEFAULT_PARTIES_ENDPOINT;
	static std::string const DEFAULT_DIVISIONS_ENDPOINT;
	static std::string const DEFAULT_QUESTIONS_ENDPOINT;
	static std::string const DEFAULT_HOUSES_ENDPOINT;
	static std::string const DEFAULT_MEMBERS_ENDPOINT;
	
	static size_t (*DEFAULT_WRITE_FUNC)(char *, size_t, size_t, void *);
	static void *const DEFAULT_USER_DATA;

	std::string m_apiDomain;
	std::string m_legislationEndpoint;
	std::string m_debatesEndpoint;
	std::string m_constituenciesEndpoint;
	std::string m_partiesEndpoint;
	std::string m_divisionsEndpoint;
	std::string m_questionsEndpoint;
	std::string m_housesEndpoint;
	std::string m_membersEndpoint;

	size_t (*m_writeFunc)(char *, size_t, size_t, void *);
	void *m_userData;

	[[nodiscard]] OireachtasConf() noexcept;
	[[nodiscard]] OireachtasConf(OireachtasConf &conf) noexcept;
	[[nodiscard]] OireachtasConf(OireachtasConf &&conf) noexcept;
	~OireachtasConf() noexcept;
};

class OireachtasApi {
private:
	std::string m_legislationUrl;
	std::string m_debatesUrl;
	std::string m_constituenciesUrl;
	std::string m_partiesUrl;
	std::string m_divisionsUrl;
	std::string m_questionsUrl;
	std::string m_housesUrl;
	std::string m_membersUrl;

	CURL *m_curl;

	std::array<char, CURL_ERROR_SIZE> m_curlErrbuf;

	void doRequest(std::string const &url, OireachtasFilter const &filter) const;

	CURLcode get(std::string const &url) const;

	static CURL *initCurl(OireachtasConf const &conf);
	static CURL *copyCurl(OireachtasApi const &conf);

public:
	[[nodiscard]] OireachtasApi();
	[[nodiscard]] OireachtasApi(OireachtasApi const &api);
	[[nodiscard]] OireachtasApi(OireachtasApi &&api);
	[[nodiscard]] OireachtasApi(OireachtasConf const &conf);
	~OireachtasApi();

	void legislation(OireachtasFilter const &filter = OireachtasFilter()) const;

	void debates(OireachtasFilter const &filter = OireachtasFilter()) const;

	void constituencies(OireachtasFilter const &filter = OireachtasFilter()) const;

	void parties(OireachtasFilter const &filter = OireachtasFilter()) const;

	void divisions(OireachtasFilter const &filter = OireachtasFilter()) const;

	void questions(OireachtasFilter const &filter = OireachtasFilter()) const;

	void houses(OireachtasFilter const &filter = OireachtasFilter()) const;

	void members(OireachtasFilter const &filter = OireachtasFilter()) const;
};

}
#endif
