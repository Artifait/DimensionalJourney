#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <sstream>

namespace DJ
{
	inline void ltrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
	}

	inline void rtrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	inline void trim(std::string& s) {
		rtrim(s);
		ltrim(s);
	}

	inline void removeSpaces(std::string& s) {
		s.erase(remove(s.begin(), s.end(), ' '), s.end());
	}

	class DJIniStructure
	{
	private:
		struct IniSection
		{
			std::unordered_map<std::string, std::string> SectionIniData;
		};
		std::unordered_map<std::string, IniSection> m_IniData;
	public:

		void AddData(const std::string& section, const std::string& key, const std::string& value)
		{
			CreateSection(section);
			m_IniData[section].SectionIniData[key] = value;
		}

		std::string ReadData(const std::string& section, const std::string& key, const std::string& def = "")
		{
			if (CheckKeyOfSection(section, key))
				return m_IniData[section].SectionIniData[key];

			return def;
		}

	private:
		void CreateSection(const std::string& title)
		{
			if(m_IniData.find(title) == m_IniData.end())
				m_IniData[title] = IniSection();
		}
		bool CheckKeyOfSection(const std::string& section, const std::string& key)
		{
			CreateSection(section);
			return m_IniData[section].SectionIniData.find(key) != m_IniData[section].SectionIniData.end();
		}
	};
	class DJIni
	{
	private:
		std::string m_currentNameSection;
		DJIniStructure m_IniData;
	public:
		DJIni(std::string path)
		{
			Parse(path);
		}

		void Parse(std::string path)
		{
			std::vector<std::string> fileData(std::move(ReadFile(path)));

			for (int i = 0; i < fileData.size(); i++)
			{
				std::string line = fileData[i];
				removeSpaces(line);

				if (line == "")
				{
					continue;
				}
				else if (line[0] == '[' && line[line.length() - 1] == ']')
				{
					m_currentNameSection = line.substr(1, line.length() - 2);
				}
				else
				{
					int indexSeparator = line.find('=');
					std::string key{ line.substr(0, indexSeparator) }, value{ line.substr(indexSeparator + 1, line.size() - indexSeparator - 1) };

					m_IniData.AddData(m_currentNameSection, key, value);
				}

			}
		}

		template<typename T> T GetAs(const std::string& section, const std::string& key, T defValue)
		{
			std::string data = m_IniData.ReadData(section, key);
			if (data == "") return defValue;

			std::stringstream ss(data);

			T num;
			ss >> num;
			return num;
		}
	private:
		std::vector<std::string> ReadFile(std::string path)
		{
			std::vector<std::string> fileData;
			std::string line;
			std::ifstream in(path);

			if (in.is_open())
			{
				while (std::getline(in, line))
				{
					fileData.push_back(line);
				}
			}
			in.close();
			return fileData;
		}
	};
}