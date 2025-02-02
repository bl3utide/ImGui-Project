﻿#include "common.hpp"
#include "logger.hpp"
#include "config/config.hpp"
#include "config/cv.hpp"
#include "config/reader.hpp"
#include "config/writer.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Config
{

// private
std::string config_file_name_;
std::unordered_map<Key, Cv> cv_by_key_;

const Cv& getCv(Key key) noexcept
{
    return cv_by_key_.at(key);
}

void load() noexcept
{
    mINI::INIStructure read_is;
    const auto file = mINI::INIFile(config_file_name_);

    if (file.read(read_is))
    {
        Logger::debug("Load config from existing ini file");
        // ini-file already exists
        for (auto key_i = 0; key_i < static_cast<int>(Key::_COUNT_); ++key_i)
        {
            const auto key = static_cast<Key>(key_i);
            Reader::iniValueToCv(read_is, cv_by_key_.at(key));
        }
    }
    else
    {
        Logger::debug("Ini file does not exists");
    }
}

void save() noexcept
{
    mINI::INIStructure write_is;
    const auto file = mINI::INIFile(config_file_name_);

    for (auto key_i = 0; key_i < static_cast<int>(Key::_COUNT_); ++key_i)
    {
        const auto key = static_cast<Key>(key_i);
        Writer::cvToIni(cv_by_key_.at(key), write_is);
    }

    if (!file.write(write_is, true))
    {
        Logger::debug("Failed to write config file");
    }
}

constexpr std::string_view GET_CONFIG_VALUE_TYPE_ERR_TEXT = "Config key '{0}' is not {1}";

template<typename T>
T getConfigValue(Key key)
{
    throw new std::runtime_error("Unexpected type of Cv");
}

template<>
std::string getConfigValue(Key key)
{
    const auto& cv = cv_by_key_.at(key);

    if (cv.type() != Cv::Type::String)
    {
        throw new std::runtime_error(std::format(GET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "string"));
    }

    return cv.cv();
}

template<>
int getConfigValue(Key key)
{
    const auto& cv = cv_by_key_.at(key);

    if (cv.type() != Cv::Type::Int)
    {
        throw new std::runtime_error(std::format(GET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "int"));
    }

    return std::stoi(cv.cv());
}

template<>
bool getConfigValue(Key key)
{
    const auto& cv = cv_by_key_.at(key);

    if (cv.type() != Cv::Type::Bool)
    {
        throw new std::runtime_error(std::format(GET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "bool"));
    }

    return cv.cv() == "1";
}

constexpr std::string_view SET_CONFIG_VALUE_TYPE_ERR_TEXT = "The type of config key '{0}' is not {1}";

template<typename T>
void setConfigValue(Key key, T value)
{
    throw new std::runtime_error("Unexpected type of value");
}

template<>
void setConfigValue(Key key, std::string value)
{
    auto& cv = cv_by_key_.at(key);

    if (cv.type() != Cv::Type::String)
    {
        throw new std::runtime_error(std::format(SET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "string"));
    }

    cv.set(value);
}

template<>
void setConfigValue(Key key, int value)
{
    auto& cv = cv_by_key_.at(key);

    if (cv.type() != Cv::Type::Int)
    {
        throw new std::runtime_error(std::format(SET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "int"));
    }

    cv.set(std::to_string(value));
}

template<>
void setConfigValue(Key key, bool value)
{
    auto& cv = cv_by_key_.at(key);

    if (cv.type() != Cv::Type::Bool)
    {
        throw new std::runtime_error(std::format(SET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "bool"));
    }

    std::string set_v = value ? "1" : "0";
    cv.set(set_v);
}

void initialize()
{
    config_file_name_ = std::format("{}.ini", APP_NAME);

    // TODO add ini keys initialization
    // ex)
    // [NewSection]
    cv_by_key_.insert({ Key::NewKey1,   Cv(Section::NewSection, Key::NewKey1, std::string()) });
    cv_by_key_.insert({ Key::NewKey2,   Cv(Section::NewSection, Key::NewKey2, 1, 10, 1) });
    cv_by_key_.insert({ Key::NewKey3,   Cv(Section::NewSection, Key::NewKey3, false) });
}

} // Config
} // ImGuiProject
