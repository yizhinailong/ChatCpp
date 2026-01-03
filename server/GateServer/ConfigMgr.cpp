#include "ConfigMgr.hpp"

#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

SectionInfo::SectionInfo() {
}

SectionInfo::~SectionInfo() {
    m_section_datas.clear();
}

SectionInfo::SectionInfo(const SectionInfo& src) {
    m_section_datas = src.m_section_datas;
}

SectionInfo& SectionInfo::operator=(const SectionInfo& src) {
    if (&src != this) {
        this->m_section_datas = src.m_section_datas;
    }

    return *this;
}

std::string SectionInfo::operator[](const std::string& key) {
    if (m_section_datas.find(key) == m_section_datas.end()) {
        return "";
    }

    return m_section_datas[key];
}

ConfigMgr::ConfigMgr() {
    boost::filesystem::path current_path = boost::filesystem::current_path();
    boost::filesystem::path config_path = current_path / "config.ini";
    std::cout << "Config path is " << config_path.string() << std::endl;

    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(config_path.string(), pt);
    for (const auto& section_pair : pt) {
        const std::string& section_name = section_pair.first;
        const boost::property_tree::ptree& section_tree = section_pair.second;
        std::unordered_map<std::string, std::string> section_config;
        for (const auto& key_value_pair : section_tree) {
            const std::string& key = key_value_pair.first;
            const std::string& value = key_value_pair.second.get_value<std::string>();
            section_config[key] = value;
        }
        SectionInfo section_info;
        section_info.m_section_datas = section_config;
        m_config_map[section_name] = section_info;
    }
}

ConfigMgr::~ConfigMgr() {
    m_config_map.clear();
}

ConfigMgr::ConfigMgr(const ConfigMgr& src) {
    m_config_map = src.m_config_map;
}

ConfigMgr& ConfigMgr::operator=(const ConfigMgr& src) {
    if (&src != this) {
        this->m_config_map = src.m_config_map;
    }

    return *this;
}

SectionInfo ConfigMgr::operator[](const std::string& section) {
    if (m_config_map.find(section) == m_config_map.end()) {
        return SectionInfo();
    }
    return m_config_map[section];
}

ConfigMgr& ConfigMgr::GetInstance() {
    static ConfigMgr instance;
    return instance;
}
