#include "ini.h"
#include <iostream>

/*namespace Ini {
	using Section = unordered_map<string, string>;

	class Document {
	public:
		Section& AddSection(string name);
		const Section& GetSection(const string& name) const;
		size_t SectionCount() const;

	private:
		unordered_map<string, Section> sections;
	};

	Document Load(istream& input);
}*/

namespace Ini {
	Section& Document::AddSection(string name) {
		return sections[move(name)];
	}

	const Section& Document::GetSection(const string& name) const {
		return sections.at(name);
	}

	size_t Document::SectionCount() const {
		return sections.size();
	}

	Document Load(istream& input) {
		Document result;
		Section* cur_section = nullptr;
		for (string line; getline(input, line);) {
			if (line[0] == '[') {
				cur_section = &result.AddSection(line.substr(1, line.size() - 2));
			}
			else if (!line.empty()) {
				size_t delim_pos = line.find('=');
				cur_section->insert({ line.substr(0, delim_pos), line.substr(delim_pos + 1) });
			}
		}
		return result;
	}
}
