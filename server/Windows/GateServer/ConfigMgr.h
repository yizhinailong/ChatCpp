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
    ConfigMgr(const ConfigMgr& src);
    ConfigMgr& operator=(const ConfigMgr& src);
    ~ConfigMgr();

    static ConfigMgr& Inst();

    SectionInfo operator[](const std::string& key);

private:
    ConfigMgr();
    std::map<std::string, SectionInfo> _config_map;
};
