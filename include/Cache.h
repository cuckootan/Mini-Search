#ifndef _CACHE_H_
#define _CACHE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <utility>
#include <unistd.h>
#include <stdexcept>
#include <stdlib.h>

#define CACHE_SIZE 5

struct Node
{
    std::string key_;
    std::set<std::string> value_;
    struct Node* next_;
    struct Node* pre_;
};

class Cache
{
    friend class EchoServer;

    public:
        typedef Node* pNode;

        Cache(const std::string& file_name);
        ~Cache();
        
        void get(const std::string& key, std::set<std::string>& value, bool& judge);
        void put(const std::string& key, const std::set<std::string>& value);
        void read_from_file();
        //服务器异常退出时，需要在退出前，将cache中的内容写回磁盘
        void write_to_file();

        void list_show();
        size_t list_size();
        void set_show(const std::set<std::string>& value)
        {
            for(std::set<std::string>::iterator it = value.begin();
                    it != value.end();
                    it++)
                std::cout << *it << "  ";
            std::cout << std::endl;
        }

    private:
        const std::string file_name_;
        std::ifstream in_file_;
        std::ofstream out_file_;

        pNode head_, tail_;
        size_t size_;

        std::unordered_map<std::string, pNode> word_ptr_;

    private:
        void open_in_file();
        void open_out_file();
        void close_in_file();
        void close_out_file();

        void list_init();
        void list_push_top(pNode ptr);
        void list_pop(pNode ptr);
        bool list_is_empty();
        void list_clear();
        void list_destroy();
};

#endif
