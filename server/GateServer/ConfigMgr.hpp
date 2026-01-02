#pragma once

#include "Const.hpp"

struct SectionInfo {
    std::unordered_map<std::string, std::string> m_section_datas;

    SectionInfo();
    ~SectionInfo();
    SectionInfo(const SectionInfo& src);
    SectionInfo& operator=(const SectionInfo& src);
    std::string operator[](const std::string& key);
};

class ConfigMgr {
public:
    ConfigMgr();
    ~ConfigMgr();
    ConfigMgr(const ConfigMgr& src);
    ConfigMgr& operator=(const ConfigMgr& src);
    SectionInfo operator[](const std::string& section);

private:
    std::unordered_map<std::string, SectionInfo> m_config_map;
};
