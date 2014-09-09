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
        
	//从cache中获取候选词集
        void get(const std::string& key, std::set<std::string>& value, bool& judge);
	//将候选词集添加至cache中
        void put(const std::string& key, const std::set<std::string>& value);
	
	//cache的初始化
        void read_from_file();
        //服务器异常退出时，需要在退出前，将cache中的内容写回磁盘
        void write_to_file();

	//打印存储cache的链表
        void list_show();
	//获取链表的长度
        size_t list_size();
	//打印用户词对应候选词集
        void set_show(const std::set<std::string>& value)
        {
            for(std::set<std::string>::iterator it = value.begin();
                    it != value.end();
                    it++)
                std::cout << *it << "  ";
            std::cout << std::endl;
        }

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

    private:
        const std::string file_name_;
        std::ifstream in_file_;
        std::ofstream out_file_;

        pNode head_, tail_;
        size_t size_;

        std::unordered_map<std::string, pNode> word_ptr_;
};

#endif
