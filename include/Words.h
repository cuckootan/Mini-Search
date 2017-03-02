#ifndef _WORDS_H_
#define _WORDS_H_

#include <iostream>
#include <string>
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

/*
class Word_info
{
    friend class cmp;
    friend class Words;

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

    private:
        std::string word_name_;
        int word_cost_;
        int word_freq_;
};

class cmp
{
    public:
        bool operator ()(const Word_info& a, const Word_info& b) const
        {
            if(a.word_cost_ == b.word_cost_)
                return a.word_freq_ > b.word_freq_ ? false : true;
            else
                return a.word_cost_ < b.word_cost_;
        }

};
*/

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

        void word_freq_insert(const std::string& word);
        void read_text();
        void read_word_freq(const std::string& word);

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

        void index_show(const char& ch);

    private:
        Text text_;
        //记录每个单词的出现的词频
        std::map<std::string, int> word_freq_;
//      std::priority_queue<Word_info, std::vector<Word_info>, cmp> que_;

        std::priority_queue<Word_info> que_;

        std::unordered_multimap<char, std::string> index_;
        std::set<std::string> candidate_words_;
        std::set<std::string> fetch_;

    private:
        int min_edit_instance(const std::string& src, const std::string& des, int i, int j);

        void index_insert(const char& ch, const std::string& word);
        void set_candidate_words_set(const std::string& word);
};

inline int min_cost(int a, int b, int c)
{
    int min = a;
    if(b < min)
        min = b;
    if(c < min)
        min = c;
    return min;
}

#endif
