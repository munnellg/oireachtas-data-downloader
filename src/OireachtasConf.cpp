#include <odd/odd.hpp>

namespace odd {

std::string const OireachtasConf::DEFAULT_API_DOMAIN              = "https://api.oireachtas.ie/v1/";
std::string const OireachtasConf::DEFAULT_LEGISLATION_ENDPOINT    = "legislation";
std::string const OireachtasConf::DEFAULT_DEBATES_ENDPOINT        = "debates";
std::string const OireachtasConf::DEFAULT_CONSTITUENCIES_ENDPOINT = "constituencies";
std::string const OireachtasConf::DEFAULT_PARTIES_ENDPOINT        = "parties";
std::string const OireachtasConf::DEFAULT_DIVISIONS_ENDPOINT      = "divisions";
std::string const OireachtasConf::DEFAULT_QUESTIONS_ENDPOINT      = "questions";
std::string const OireachtasConf::DEFAULT_HOUSES_ENDPOINT         = "houses";
std::string const OireachtasConf::DEFAULT_MEMBERS_ENDPOINT        = "members";

size_t (*OireachtasConf::DEFAULT_WRITE_FUNC)(char *, size_t, size_t, void *) = nullptr;
void *const OireachtasConf::DEFAULT_USER_DATA = nullptr;

OireachtasConf::OireachtasConf() noexcept : 
	m_apiDomain(DEFAULT_API_DOMAIN), 
	m_legislationEndpoint(DEFAULT_LEGISLATION_ENDPOINT),
	m_debatesEndpoint(DEFAULT_DEBATES_ENDPOINT),
	m_constituenciesEndpoint(DEFAULT_CONSTITUENCIES_ENDPOINT),
	m_partiesEndpoint(DEFAULT_PARTIES_ENDPOINT),
	m_divisionsEndpoint(DEFAULT_DIVISIONS_ENDPOINT),
	m_questionsEndpoint(DEFAULT_QUESTIONS_ENDPOINT),
	m_housesEndpoint(DEFAULT_HOUSES_ENDPOINT),
	m_membersEndpoint(DEFAULT_MEMBERS_ENDPOINT),
	m_writeFunc(DEFAULT_WRITE_FUNC),
	m_userData(DEFAULT_USER_DATA) {}

OireachtasConf::OireachtasConf(OireachtasConf &conf) noexcept :
	m_apiDomain(conf.m_apiDomain), 
	m_legislationEndpoint(conf.m_legislationEndpoint),
	m_debatesEndpoint(conf.m_debatesEndpoint),
	m_constituenciesEndpoint(conf.m_constituenciesEndpoint),
	m_partiesEndpoint(conf.m_partiesEndpoint),
	m_divisionsEndpoint(conf.m_divisionsEndpoint),
	m_questionsEndpoint(conf.m_questionsEndpoint),
	m_housesEndpoint(conf.m_housesEndpoint),
	m_membersEndpoint(conf.m_membersEndpoint),
	m_writeFunc(conf.m_writeFunc),
	m_userData(conf.m_userData) {}

OireachtasConf::OireachtasConf(OireachtasConf &&conf) noexcept  :
	m_apiDomain(std::move(conf.m_apiDomain)), 
	m_legislationEndpoint(std::move(conf.m_legislationEndpoint)),
	m_debatesEndpoint(std::move(conf.m_debatesEndpoint)),
	m_constituenciesEndpoint(std::move(conf.m_constituenciesEndpoint)),
	m_partiesEndpoint(std::move(conf.m_partiesEndpoint)),
	m_divisionsEndpoint(std::move(conf.m_divisionsEndpoint)),
	m_questionsEndpoint(std::move(conf.m_questionsEndpoint)),
	m_housesEndpoint(std::move(conf.m_housesEndpoint)),
	m_membersEndpoint(std::move(conf.m_membersEndpoint)),
	m_writeFunc(std::move(conf.m_writeFunc)),
	m_userData(std::move(conf.m_userData)) {}

OireachtasConf::~OireachtasConf() noexcept {}

}
