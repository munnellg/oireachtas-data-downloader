#include <odd/odd.hpp>

#include <vector>
#include <sstream>
#include <algorithm>

namespace odd {

int const OireachtasFilter::DEFAULT_HOUSE_NO             = 0;
int const OireachtasFilter::DEFAULT_LIMIT                = 50;
int const OireachtasFilter::DEFAULT_SKIP                 = 0;
int const OireachtasFilter::DEFAULT_QUESTION_NO          = 0;
std::string const OireachtasFilter::DEFAULT_LANG         = "";
std::string const OireachtasFilter::DEFAULT_ACT_NO       = "";
std::string const OireachtasFilter::DEFAULT_ACT_YEAR     = "";
std::string const OireachtasFilter::DEFAULT_DATE_END     = "";
std::string const OireachtasFilter::DEFAULT_DATE_START   = "";
std::string const OireachtasFilter::DEFAULT_DEBATE_ID    = "";
std::string const OireachtasFilter::DEFAULT_MEMBER_ID    = "";
std::string const OireachtasFilter::DEFAULT_VOTE_ID      = "";
std::string const OireachtasFilter::DEFAULT_QUESTION_ID  = "";
std::string const OireachtasFilter::DEFAULT_BILL_ID      = "";
std::string const OireachtasFilter::DEFAULT_BILL_NO      = "";
std::string const OireachtasFilter::DEFAULT_BILL_YEAR    = "";
std::string const OireachtasFilter::DEFAULT_CHAMBER      = "";
std::string const OireachtasFilter::DEFAULT_CHAMBER_TYPE = "";

std::string const OireachtasFilter::QFIELD_HOUSE_NO     = "house_no";
std::string const OireachtasFilter::QFIELD_LIMIT        = "limit";
std::string const OireachtasFilter::QFIELD_SKIP         = "skip";
std::string const OireachtasFilter::QFIELD_LANG         = "lang";
std::string const OireachtasFilter::QFIELD_ACT_NO       = "act_no";
std::string const OireachtasFilter::QFIELD_ACT_YEAR     = "act_year";
std::string const OireachtasFilter::QFIELD_DATE_END     = "date_end";
std::string const OireachtasFilter::QFIELD_DATE_START   = "date_start";
std::string const OireachtasFilter::QFIELD_DEBATE_ID    = "debate_id";	
std::string const OireachtasFilter::QFIELD_OUTCOME      = "outcome";
std::string const OireachtasFilter::QFIELD_MEMBER_ID    = "member_id";
std::string const OireachtasFilter::QFIELD_VOTE_ID      = "vote_id";
std::string const OireachtasFilter::QFIELD_QUESTION_ID  = "question_id";
std::string const OireachtasFilter::QFIELD_QUESTION_NO  = "question_no";
std::string const OireachtasFilter::QFIELD_BILL_ID      = "bill_id";
std::string const OireachtasFilter::QFIELD_BILL_NO      = "bill_no";
std::string const OireachtasFilter::QFIELD_BILL_YEAR    = "bill_year";
std::string const OireachtasFilter::QFIELD_BILL_SOURCE  = "bill_source";
std::string const OireachtasFilter::QFIELD_BILL_STATUS  = "bill_status";
std::string const OireachtasFilter::QFIELD_CHAMBER      = "chamber";
std::string const OireachtasFilter::QFIELD_CHAMBER_TYPE = "chamber_type";
std::string const OireachtasFilter::QFIELD_CHAMBER_ID   = "chamber_id";
std::string const OireachtasFilter::QFIELD_QTYPE        = "qtype"; 

OireachtasFilter::OireachtasFilter() noexcept :
	m_houseNo(DEFAULT_HOUSE_NO),
	m_limit(DEFAULT_LIMIT),
	m_skip(DEFAULT_SKIP),
	m_lang(DEFAULT_LANG),
	m_actNo(DEFAULT_ACT_NO),
	m_actYear(DEFAULT_ACT_YEAR),
	m_dateEnd(DEFAULT_DATE_END),
	m_dateStart(DEFAULT_DATE_START), 
	m_debateId(DEFAULT_DEBATE_ID),
	m_memberId(DEFAULT_MEMBER_ID),
	m_voteId(DEFAULT_VOTE_ID),
	m_questionId(DEFAULT_QUESTION_ID),
	m_questionNo(DEFAULT_QUESTION_NO),
	m_billId(DEFAULT_BILL_ID),
	m_billNo(DEFAULT_BILL_NO),
	m_billYear(DEFAULT_BILL_YEAR),
	m_chamber(DEFAULT_CHAMBER),
	m_chamberType(DEFAULT_CHAMBER_TYPE) {}

OireachtasFilter::OireachtasFilter(OireachtasFilter &filter) noexcept :
	m_houseNo(filter.m_houseNo),
	m_limit(filter.m_limit),
	m_skip(filter.m_skip),
	m_lang(filter.m_lang),
	m_actNo(filter.m_actNo),
	m_actYear(filter.m_actYear),
	m_dateEnd(filter.m_dateEnd),
	m_dateStart(filter.m_dateStart), 
	m_debateId(filter.m_debateId),
	m_outcome(filter.m_outcome),
	m_memberId(filter.m_memberId),
	m_voteId(filter.m_voteId),
	m_questionId(filter.m_questionId),
	m_questionNo(filter.m_questionNo),
	m_billId(filter.m_billId),
	m_billNo(filter.m_billNo),
	m_billYear(filter.m_billYear),
	m_billSource(filter.m_billSource),
	m_billStatus(filter.m_billStatus),
	m_chamber(filter.m_chamber),
	m_chamberType(filter.m_chamberType),
	m_chamberId(filter.m_chamberId),
	m_qtype(filter.m_qtype) {}

OireachtasFilter::OireachtasFilter(OireachtasFilter &&filter) noexcept :
	m_houseNo(std::move(filter.m_houseNo)),
	m_limit(std::move(filter.m_limit)),
	m_skip(std::move(filter.m_skip)),
	m_lang(std::move(filter.m_lang)),
	m_actNo(std::move(filter.m_actNo)),
	m_actYear(std::move(filter.m_actYear)),
	m_dateEnd(std::move(filter.m_dateEnd)),
	m_dateStart(std::move(filter.m_dateStart)), 
	m_debateId(std::move(filter.m_debateId)),
	m_outcome(std::move(filter.m_outcome)),
	m_memberId(std::move(filter.m_memberId)),
	m_voteId(std::move(filter.m_voteId)),
	m_questionId(std::move(filter.m_questionId)),
	m_questionNo(std::move(filter.m_questionNo)),
	m_billId(std::move(filter.m_billId)),
	m_billNo(std::move(filter.m_billNo)),
	m_billYear(std::move(filter.m_billYear)),
	m_billSource(std::move(filter.m_billSource)),
	m_billStatus(std::move(filter.m_billStatus)),
	m_chamber(std::move(filter.m_chamber)),
	m_chamberType(std::move(filter.m_chamberType)),
	m_chamberId(std::move(filter.m_chamberId)),
	m_qtype(std::move(filter.m_qtype)) {}

OireachtasFilter::~OireachtasFilter() noexcept {}

std::string const OireachtasFilter::qstring() const noexcept {
	std::ostringstream oss("?", std::ios::app);

	if (m_houseNo > 0)           { oss << QFIELD_HOUSE_NO     << '=' << m_houseNo               << '&'; }
	if (m_limit >= 0)            { oss << QFIELD_LIMIT        << '=' << m_limit                 << '&'; }
	if (m_skip >= 0)             { oss << QFIELD_SKIP         << '=' << m_skip                  << '&'; }
	if (!m_lang.empty())         { oss << QFIELD_LANG         << '=' << m_lang                  << '&'; }
	if (!m_actNo.empty())        { oss << QFIELD_ACT_NO       << '=' << m_actNo                 << '&'; }
	if (!m_actYear.empty())      { oss << QFIELD_ACT_YEAR     << '=' << m_actYear               << '&'; }
	if (!m_dateEnd.empty())      { oss << QFIELD_DATE_END     << '=' << m_dateEnd               << '&'; }
	if (!m_dateStart.empty())    { oss << QFIELD_DATE_START   << '=' << m_dateStart             << '&'; }
	if (!m_debateId.empty())     { oss << QFIELD_DEBATE_ID    << '=' << m_debateId              << '&'; }
	if (m_outcome.size() > 0)    { oss << QFIELD_OUTCOME      << '=' << join(m_outcome, ',')    << '&'; }
	if (!m_memberId.empty())     { oss << QFIELD_MEMBER_ID    << '=' << m_memberId              << '&'; }
	if (!m_voteId.empty())       { oss << QFIELD_VOTE_ID      << '=' << m_voteId                << '&'; }
	if (!m_questionId.empty())   { oss << QFIELD_QUESTION_ID  << '=' << m_questionId            << '&'; }
	if (m_questionNo > 0)        { oss << QFIELD_QUESTION_NO  << '=' << m_questionNo            << '&'; }
	if (!m_billId.empty())       { oss << QFIELD_BILL_ID      << '=' << m_billId                << '&'; }
	if (!m_billNo.empty())       { oss << QFIELD_BILL_NO      << '=' << m_billNo                << '&'; }
	if (!m_billYear.empty())     { oss << QFIELD_BILL_YEAR    << '=' << m_billYear              << '&'; }
	if (m_billSource.size() > 0) { oss << QFIELD_BILL_SOURCE  << '=' << join(m_billSource, ',') << '&'; }
	if (m_billStatus.size() > 0) { oss << QFIELD_BILL_STATUS  << '=' << join(m_billStatus, ',') << '&'; }
	if (!m_chamber.empty())      { oss << QFIELD_CHAMBER      << '=' << m_chamber               << '&'; }
	if (!m_chamberType.empty())  { oss << QFIELD_CHAMBER_TYPE << '=' << m_chamberType           << '&'; }
	if (m_chamberId.size() > 0)  { oss << QFIELD_CHAMBER_ID   << '=' << join(m_chamberId, ',')  << '&'; }
	if (m_qtype.size() > 0)      { oss << QFIELD_QTYPE        << '=' << join(m_qtype, ',')      << '&'; }

	std::string result = oss.str();
	
	// remove the last & from the query string, or the ? if query string is empty
	result.pop_back();

	return result;
}

std::string OireachtasFilter::join(std::vector<std::string> const &vec, char const c) const noexcept {
	std::ostringstream oss;
	std::for_each(vec.begin(), vec.end(), [&](std::string const &s) { oss << s << c; });
	std::string result = oss.str();
	if (result.size() > 0) { result.pop_back(); }
	return result;
}

}
