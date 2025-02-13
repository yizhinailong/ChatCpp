#include "ConfigMgr.h"

SectionInfo::SectionInfo() {
}

SectionInfo::SectionInfo(const SectionInfo& src) {
    _section_datas = src._section_datas;
}

SectionInfo::~SectionInfo() {
    _section_datas.clear();
}

std::string SectionInfo::operator[](const std::string& key) {
    if (_section_datas.find(key) == _section_datas.end()) {
        return "";
    }

    return _section_datas[key];
}

SectionInfo& SectionInfo::operator=(const SectionInfo& src) {
    if (&src == this) {
        return *this;
    }

    this->_section_datas = src._section_datas;
}

ConfigMgr::ConfigMgr() {
    boost::filesystem::path current_path = boost::filesystem::current_path();
    boost::filesystem::path config_path = current_path / "config.ini";

    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(config_path.string(), pt);

    for (const auto& section_pair : pt) {
        const ::std::string& section_name = section_pair.first;
        const boost::property_tree::ptree& section_tree = section_pair.second;
        SectionInfo section_info;
        for (const auto& key_value_pair : section_tree) {
            const ::std::string& key = key_value_pair.first;
            const ::std::string& value = key_value_pair.second.get_value<std::string>();
            section_info._section_datas[key] = value;
        }

        _config_map[section_name] = section_info;
    }

    for (const auto& section_entry : _config_map) {
        const std::string& section_name = section_entry.first;
        SectionInfo section_config = section_entry.second;
        std::cout << "[" << section_name << "]" << std::endl;
        for (const auto& key_value_pair : section_config._section_datas) {
            std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
        }
    }
}

ConfigMgr::ConfigMgr(const ConfigMgr& src) {
    _config_map = src._config_map;
}

ConfigMgr& ConfigMgr::operator=(const ConfigMgr& src) {
    if (&src == this) {
        return *this;
    }

    _config_map = src._config_map;
}

ConfigMgr::~ConfigMgr() {
    _config_map.clear();
}

SectionInfo ConfigMgr::operator[](const std::string& key) {
    if (_config_map.find(key) == _config_map.end()) {
        return SectionInfo();
    }

    return _config_map[key];
}
