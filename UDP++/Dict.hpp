#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>
#include<unistd.h>
#include"Log.hpp"

using namespace log_ns;

//定义一个分割符等会检索这个分隔符
const static std::string sep = ":";

class Dict
{
private:
    void LoadDict(const std::string &path)
    {
        std::ifstream in(path);
        if(!in.is_open())
        {
            LOG(FATAL,"open %s fail\n",path.c_str());
            exit(0);
        }

        std::string line;
        while (std::getline(in,line))
        {
            LOG(DEBUG,"load info:%s , success\n",line.c_str());
            if(line.empty())
            {
                continue;
            }
            auto pos = line.find(sep);
            if(pos == std::string::npos)
            {
                continue;
            }
            std::string key = line.substr(0,pos);       //截取字符串
            std::string value = line.substr(pos+sep.size());        //截取下半部分
            if(value.empty())
            {
                continue;
            }
            _dict.insert(std::make_pair(key,value));
        }
        LOG(INFO,"load %s done\n",path.c_str());
        in.close();
    }
public:
    Dict(const std::string &dict_path):_dict_path(dict_path)
    {
        LoadDict(_dict_path);
    }
    std::string Translate(std::string word)
    {
        if(word.empty())
        {
            return "None";
        }
        auto iter = _dict.find(word);       //在字典里面查查查
        if(iter == _dict.end())
        {
            return "None";
        }
        else
        {
            return iter->second;
        }
    }
    ~Dict();
private:
    std::unordered_map<std::string,std::string>_dict;       //C++里面的字典，学go的可以跟我说说go的是什么
    std::string _dict_path;         //设定成环境变量
};