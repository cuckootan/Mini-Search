#ifndef _WORDS_H_
#define _WORDS_H_

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Text.h"

#define MAX_EDIT_INSTANCE 2

//优先队列元素对象的类
class Word_info
{
    friend class Words;
    friend class EchoServer;

    public:
        void set_word_name(const std::string& word_name)
        {
            word_name_ = word_name;
        }

        void set_word_cost(const int& word_cost)
        {
            word_cost_ = word_cost;
        }

        void set_word_freq(const int& word_freq)
        {
            word_freq_ = word_freq;
        }
        
        bool operator <(const Word_info& other) const
        {
            if(word_cost_ == other.word_cost_)
                return word_freq_ < other.word_freq_;
            else
                return word_cost_ > other.word_cost_;
        }

    private:
        std::string word_name_;
        int word_cost_;
        int word_freq_;
};

class Words
{
    friend class EchoServer;

    public:
        Words(const std::string& text_name);
        ~Words();

	//用于建立以及读取词库，将每个不同单词插入到map中
        void word_freq_insert(const std::string& word);
        void read_text();
        void read_word_freq(const std::string& word);

	//用于建立读取优先队列
        void priority_queue_init(const std::string& word);
        void priority_queue_clear()
        {
            while(!que_.empty())
                que_.pop();
        }
        void priority_queue_fetch(std::set<std::string>& value)
        {
            while(!que_.empty())
            {
                value.insert(que_.top().word_name_);
                que_.pop();
            }
        }

	//用于读取所建立的索引
        void index_show(const char& ch);

    private:
	//计算最小编辑距离
        int min_edit_instance(const std::string& src, const std::string& des);

	//建立索引以及建立候选词集
        void index_insert(const char& ch, const std::string& word);
        void set_candidate_words_set(const std::string& word);

    private:
        Text text_;
        //记录每个单词的出现的词频
        std::map<std::string, int> word_freq_;
	
	//存储编辑距离不大于设定的编辑距离值的词
        std::priority_queue<Word_info> que_;

	//存储索引项，候选词集
        std::unordered_multimap<char, std::string> index_;
        std::set<std::string> candidate_words_;
};

inline int min_cost(int a, int b, int c)
{
    int min = a;
    
    min = b < min? b: min;
    min = c < min? c: min;

    return min;
}

#endif
