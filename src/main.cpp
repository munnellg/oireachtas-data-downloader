#include <argp.h>
#include <cstdio>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <iostream>

#include <odd/odd.hpp>

const char *argp_program_version = "odd 0.1.0";

const char args_doc[] = "ENDPOINT";

char const *argp_program_bug_address = "<munnellg@tcd.ie>";

static char doc[] = 
	"Oireachtas Data Downloader -- application for obtaining json data from the "
	"Oireachtas data API.";

static struct argp_option options[] = {
	{ "house-no",     'H', "INT",  0, "Filter by House Number." },
	{ "limit",        'L', "INT",  0, "Limit number of returned records" },
	{ "skip",         'S', "INT",  0, "Skip records (for pagination)" },
	{ "language",     'l', "LANG", 0, "Language of document to extract. Defaults to English (en)" },
	{ "act-no",       'A', "INT",  0, "Filter bill by Act number" },
	{ "act-year",     'a', "YEAR", 0, "Filter bill by Act year" },
	{ "date-start",   's', "DATE", 0, "Filter by Start Date related to the Section" },
	{ "date-end",     'e', "DATE", 0, "Filter by End Date related to the Section" },
	{ "debate-id",    'd', "URI",  0, "Filter by debate URI" },
	{ "outcome",      'O', "LIST", 0, "Filter divisions by outcome" },
	{ "member-id",    'M', "URI",  0, "Filter by member URI" },
	{ "vote-id",      'V', "URI",  0, "Division identifier for a Single Division" },
	{ "question-id",  'Q', "URI",  0, "Identifier for a single question" },
	{ "question-no",  'q', "INT",  0, "Filter by question No." },
	{ "bill-id",      'B', "URI",  0, "Filter results by Bill URI e.g. /ie/oireachtas/bill/2016/2" },
	{ "bill-no",      'b', "INT",  0, "Filter Bill by number" },
	{ "bill-year",    'R', "YEAR", 0, "Filter Bill by year" },
	{ "bill-source",  'r', "LIST", 0, "An array used to filter legislation by origin source" },
	{ "bill-status",  'p', "LIST", 0, "An array which is used to filter legislation by status" },
	{ "chamber",      'c', "STR",  0, "Filter by house name (dail or seanad)" },
	{ "chamber-type", 't', "STR",  0, "Filter results by house i.e. Dail or Seanad or committees" },
	{ "chamber-id",   'C', "URI",  0, "Filter by house or committee URI. Example /ie/oireachtas/house/dail/32" },
	{ "qtype",        'T', "STR",  0, "Filter questions by oral or writtens" },
	{ "output",       'o', "FILE", 0, "Output to FILE instead of standard output" },
	{ 0 }
};

struct Arguments {
	std::string outputFile;
	std::string endpoint;
	odd::OireachtasConf conf;
	odd::OireachtasFilter filter;

	Arguments() {
		outputFile = "-";
	}
};

std::vector<std::string> splitstr(std::string const &s, char const c = ',') {
	std::vector<std::string> vec;
	size_t lo = 0, hi = s.find_first_of(c);
	
	while (hi != std::string::npos) {
		vec.push_back(s.substr(lo, hi-lo));
		lo = hi + 1;
		hi = s.find(c, lo);
	}

	if (lo < s.size()) {
		vec.push_back(s.substr(lo));
	}

	return vec;
}

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
	Arguments *args = static_cast<Arguments *>(state->input);

	switch (key) {
	case 'H': {
			std::stringstream ss(arg);
			ss >> args->filter.m_houseNo;
			if (!ss) {
				std::cerr << "Invalid argument for House Number -- Nan : " << arg << std::endl;
			}
		}
			break;
	case 'L': {
			std::stringstream ss(arg);
			ss >> args->filter.m_limit;
			if (!ss) {
				std::cerr << "Invalid argument for Limit -- Nan : " << arg << std::endl;
			}
		}
			break;
	case 'S': {
			std::stringstream ss(arg);
			ss >> args->filter.m_skip;
			if (!ss) {
				std::cerr << "Invalid argument for Skip -- Nan : " << arg << std::endl;
			}
		}
			break;
	case 'l':
			args->filter.m_lang = std::string(arg);
			break;
	case 'A':
			args->filter.m_actNo = std::string(arg);
			break;
	case 'a':
			args->filter.m_actYear = std::string(arg);
			break;
	case 's':
			args->filter.m_dateStart = std::string(arg);
			break;
	case 'e':
			args->filter.m_dateEnd = std::string(arg);
			break;
	case 'd':
			args->filter.m_debateId = std::string(arg);
			break;
	case 'O':
			args->filter.m_outcome = splitstr(arg);
			break;
	case 'M':
			args->filter.m_memberId = std::string(arg);
			break;
	case 'V':
			args->filter.m_voteId = std::string(arg);
			break;
	case 'Q':
			args->filter.m_questionId = std::string(arg);
			break;
	case 'q': {
			std::stringstream ss(arg);
			ss >> args->filter.m_questionNo;
			if (!ss) {
				std::cerr << "Invalid argument for Question Number -- Nan" << arg << std::endl;
			}
		}
			break;
	case 'B':
			args->filter.m_billId = std::string(arg);
			break;
	case 'b':
			args->filter.m_billNo = std::string(arg);
			break;
	case 'R':
			args->filter.m_billYear = std::string(arg);
			break;
	case 'r':
			args->filter.m_billSource = splitstr(arg);
			break;
	case 'p':
			args->filter.m_billStatus = splitstr(arg);
			break;
	case 'c':
			args->filter.m_chamber = std::string(arg);
			break;
	case 't':
			args->filter.m_chamberType = std::string(arg);
			break;
	case 'C':
			args->filter.m_chamberId = splitstr(arg);
			break;
	case 'T':
			args->filter.m_qtype = splitstr(arg);
			break;
	case 'o':
			args->outputFile = std::string(arg);
			break;
	default:
		return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

size_t writeFile(char *ptr, size_t size, size_t nmemb, void *userdata) {
	FILE *fp = static_cast<FILE *>(userdata);
	fwrite(ptr, size, nmemb, fp);
	return size * nmemb;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char *argv[]) {
	Arguments arguments;

	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	FILE *f = nullptr;

	// messy mixing streams and C Files, but can't see how to pass stream to curl
	if (arguments.outputFile != "-") {
		f = fopen(arguments.outputFile.c_str(), "w");
		if (!f) {
			std::cerr << "Unable to open \""  << arguments.outputFile << "\"" << std::endl;
			return 1;
		}

		arguments.conf.m_writeFunc = writeFile;
		arguments.conf.m_userData = f;
	}

	odd::OireachtasApi api(arguments.conf);

	api.members(arguments.filter);
	
	// if output was written to file, close file
	if (f) { fclose(f); }

	return 0;
}

