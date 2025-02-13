#pragma once
#include "const.h"

struct SectionInfo {
    SectionInfo();
    SectionInfo(const SectionInfo& src);
    ~SectionInfo();

    std::string operator[](const std::string& key);
    SectionInfo& operator=(const SectionInfo& src);

    std::map<std::string, std::string> _section_datas;
};

class ConfigMgr {
public:
    ConfigMgr();
    ConfigMgr(const ConfigMgr& src);
    ConfigMgr& operator=(const ConfigMgr& src);
    ~ConfigMgr();

    SectionInfo operator[](const std::string& key);

private:
    std::map<std::string, SectionInfo> _config_map;
};
