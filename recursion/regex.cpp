#include <iostream>
#include <stdio.h>


const uint32_t bracket_mode = 0x1;
// This means that there is at least one match in the bracket
const uint32_t bracket_mode_found = 0x2;

std::string get_malformed_error_string(uint32_t modes) {
	if (modes | bracket_mode) {
		return "Malformed regex expression - invalid bracket";
	} else {
		return "";
	}
}

std::pair<bool, std::string> regex_helper(const std::string &regex, const std::string &search, const size_t ii, const size_t si, uint32_t modes) {
	if (ii == regex.size() || si == search.size()) {
		// Make sure we are not in any other mode
		if (modes == 0) {
			return std::make_pair(true,"");
		} else {
			return std::make_pair(false, get_malformed_error_string(modes));
		}
	}

	// Text string match one another - pass for case
	if (regex[ii] == search[si]) {
		return regex_helper(regex, search, ii+1, si+1, modes);
	} else if (regex[si] == '[') {
		// Turn bracket mode and trust the code
		modes |= bracket_mode;
		return regex_helper(regex, search, ii+1, si, modes);
	} else if (modes & bracket_mode) {
		// We are in bracket mode - keep matching 
		if (regex[ii] == search[si]) {
			modes |= bracket_mode_found;
			// Found a match - find the closing bracket to continue
			auto new_ii = ii;
			for (; new_ii < regex.size(); new_ii++) {
				if (search[new_ii] == ']') {
					// Found closing
					return regex_helper(regex, search, new_ii, si, modes);
				}
			}
			// This means we reached the end and a closing bracket was not found
			std::string errorString = get_malformed_error_string(modes);
			return std::make_pair(false, errorString);
		} else {
			// We have not found a match in the bracket yet
			return regex_helper(regex, search, ii+1, si, modes);
		}
	} else {
		// No match
		std::string errorString = "Character: ";
		errorString += regex[ii];
		errorString += " mismatches with: ";
		errorString += search[si];
		return std::make_pair(false, errorString);
	}
}

std::pair<bool, std::string> validate_regex(const std::string &regex, const std::string &search) {
	return regex_helper(regex, search, 0, 0, 0);
}

int main() {
	std::cout << "Enter a regex pattern: ";
	std::string regex_string, search_string;
	std::cin >> regex_string;
	std::cout << "Enter a string to be searched: ";
	std::cin >> search_string;
	auto validate_res = validate_regex(regex_string, search_string);
	if (validate_res.first) {
		std::cout << "Valid" << std::endl;
	} else {
		std::cout << "Invalid due to: " << validate_res.second << std::endl;
	}
	return 0;
}
