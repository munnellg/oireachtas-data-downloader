#include <odd/odd.hpp>
#include <curl/curl.h>
#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace odd {

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

void OireachtasApi::legislation(OireachtasFilter const &filter) const {
	doRequest(m_legislationUrl, filter);
}

void OireachtasApi::debates(OireachtasFilter const &filter) const {
	doRequest(m_debatesUrl, filter);
}

void OireachtasApi::constituencies(OireachtasFilter const &filter) const {
	doRequest(m_constituenciesUrl, filter);
}

void OireachtasApi::parties(OireachtasFilter const &filter) const {
	doRequest(m_partiesUrl, filter);
}

void OireachtasApi::divisions(OireachtasFilter const &filter) const {
	doRequest(m_divisionsUrl, filter);
}

void OireachtasApi::questions(OireachtasFilter const &filter) const {
	doRequest(m_questionsUrl, filter);
}

void OireachtasApi::houses(OireachtasFilter const &filter) const {
	doRequest(m_housesUrl, filter);
}

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

