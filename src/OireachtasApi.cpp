#include <odd/odd.hpp>
#include <curl/curl.h>
#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace odd {


/*
static size_t resp2str(char *ptr, size_t size, size_t nmemb, void *userdata) {
	std::string *data = static_cast<std::string *>(userdata);
	std::copy(ptr, ptr + size * nmemb, std::back_inserter(*data));
	return size * nmemb;
}

static CURLcode web_request(std::string url, std::string &resp_data,
		struct curl_slist *headers = nullptr) {
	CURL *curl = curl_easy_init();

	char errbuf[CURL_ERROR_SIZE] = {0};

	if (!curl) {
		std::cerr << "Easy cURL initialization failed" << std::endl;
		return CURLE_FAILED_INIT;
	}
	
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	
	// follow redirects
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	// configure callback for parsing webpage
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp_data);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, resp2str);
	
	// register pointer to buffer for human readable error messages
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

	// set target URL
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	// execute the request
	CURLcode res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	return res;
}

static std::string query_endpoint(std::string const &url, OireachtasFilter const &filter) {
	std::string resp_data;

	CURLcode res = web_request(url + filter.qstring(), resp_data);

	return resp_data;
}
*/

OireachtasApi::OireachtasApi() :
	OireachtasApi(OireachtasConf()) {}

OireachtasApi::OireachtasApi(OireachtasApi const &api) :
		m_legislationUrl(api.m_legislationUrl),
		m_debatesUrl(api.m_debatesUrl),
		m_constituenciesUrl(api.m_constituenciesUrl),
		m_partiesUrl(api.m_partiesUrl),
		m_divisionsUrl(api.m_divisionsUrl),
		m_questionsUrl(api.m_questionsUrl),
		m_housesUrl(api.m_housesUrl),
		m_membersUrl(api.m_membersUrl),
		m_curl(copyCurl(api)),
		m_curlErrbuf(api.m_curlErrbuf) {

	curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, m_curlErrbuf);
}
	

OireachtasApi::OireachtasApi(OireachtasApi &&api) :
		m_legislationUrl(std::move(api.m_legislationUrl)),
		m_debatesUrl(std::move(api.m_debatesUrl)),
		m_constituenciesUrl(std::move(api.m_constituenciesUrl)),
		m_partiesUrl(std::move(api.m_partiesUrl)),
		m_divisionsUrl(std::move(api.m_divisionsUrl)),
		m_questionsUrl(std::move(api.m_questionsUrl)),
		m_housesUrl(std::move(api.m_housesUrl)),
		m_membersUrl(std::move(api.m_membersUrl)),
		m_curl(std::move(api.m_curl)),
		m_curlErrbuf(std::move(api.m_curlErrbuf)) {

	curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, m_curlErrbuf);
}


OireachtasApi::OireachtasApi(OireachtasConf const &conf) :
		m_legislationUrl(conf.m_apiDomain + conf.m_legislationEndpoint),
		m_debatesUrl(conf.m_apiDomain + conf.m_debatesEndpoint),
		m_constituenciesUrl(conf.m_apiDomain + conf.m_constituenciesEndpoint),
		m_partiesUrl(conf.m_apiDomain + conf.m_partiesEndpoint),
		m_divisionsUrl(conf.m_apiDomain + conf.m_divisionsEndpoint),
		m_questionsUrl(conf.m_apiDomain + conf.m_questionsEndpoint),
		m_housesUrl(conf.m_apiDomain + conf.m_housesEndpoint),
		m_membersUrl(conf.m_apiDomain + conf.m_membersEndpoint),
		m_curl(initCurl(conf)),
		m_curlErrbuf{0} {

	curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, m_curlErrbuf);
}


OireachtasApi::~OireachtasApi() {
	if (m_curl) {
		curl_easy_cleanup(m_curl);
	}
}

void OireachtasApi::legislation(OireachtasFilter const &filter) const {}
void OireachtasApi::debates(OireachtasFilter const &filter) const {}
void OireachtasApi::constituencies(OireachtasFilter const &filter) const {}
void OireachtasApi::parties(OireachtasFilter const &filter) const {}
void OireachtasApi::divisions(OireachtasFilter const &filter) const {}
void OireachtasApi::questions(OireachtasFilter const &filter) const {}
void OireachtasApi::houses(OireachtasFilter const &filter) const {}
void OireachtasApi::members(OireachtasFilter const &filter) const {
	doRequest(m_membersUrl, filter);
}

void OireachtasApi::doRequest(std::string const &url, OireachtasFilter const &filter) const {
	CURLcode res = get(url + filter.qstring());
	// TODO: Handle error codes
}

CURLcode OireachtasApi::get(std::string const &url) const {
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	return curl_easy_perform(m_curl);
}

CURL* OireachtasApi::initCurl(OireachtasConf const &conf) {
	CURL *curl = curl_easy_init();

	if (!curl) {
		throw "Easy cURL initialization failed";
	}

	if (conf.m_userData != nullptr) {
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, conf.m_userData);
	}

	if (conf.m_writeFunc != nullptr) {
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, conf.m_writeFunc);
	}

	return curl;
}

CURL* OireachtasApi::copyCurl(OireachtasApi const &api) {
	CURL *curl = curl_easy_duphandle(api.m_curl);

	if (!curl) {
		throw "Easy cURL duplication failed";
	}

	return curl;
}

}

