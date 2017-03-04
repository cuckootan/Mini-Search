#include "Words.h"

using namespace std;

Words::Words(const string& text_name):
    text_(text_name)
{
    read_text();
}

Words::~Words()
{
    priority_queue_clear();
}

void Words::word_freq_insert(const string& word)
{
	pair<map<string,int>::iterator,bool> ret = word_freq_.insert(make_pair(word, 1));
    if(!ret.second)
        ++ret.first->second;
}

void Words::read_text()
{
	text_.text_open();

	string line,word;

	while(getline(text_.if_text_, line))
	{
		istringstream stream(line);

		while(stream >> word)
        {
			word_freq_insert(word);

            for(string::iterator it = word.begin(); it != word.end(); it++)
                index_insert(*it, word);
        }
	}
}

void Words::read_word_freq(const string& word)
{
    if(word_freq_.count(word) == 0)
        cout << "The word does not exist" << endl;
    else
        cout << word_freq_[word] << endl;
}


int Words::min_edit_instance(const string &src, const string &des, int i, int j)
{
    if(i == 0)
        return j;

    if(j == 0)
        return i;

    if(src[i - 1] == des[j - 1]) 
        return min_edit_instance(src, des, i - 1, j - 1); 
    else
    {   
        int insert_cost = min_edit_instance(src, des, i - 1, j) + 1;
        int delete_cost = min_edit_instance(src, des, i, j - 1) + 1;
        int replace_cost = min_edit_instance(src, des, i - 1, j - 1) + 1;
        return min_cost(insert_cost, delete_cost, replace_cost);
    }   
}

void Words::priority_queue_init(const string& word)
{
    priority_queue_clear();

    set_candidate_words_set(word);
    for(set<string>::iterator it_ = candidate_words_.begin();
        it_ != candidate_words_.end();
        it_++)
    {   
        Word_info temp;
        temp.set_word_name(*it_);
        temp.set_word_cost(min_edit_instance(word, *it_, word.size(), it_->size()));
        if(temp.word_cost_ > MAX_EDIT_INSTANCE)
            continue;
        temp.set_word_freq(word_freq_[*it_]);
        que_.push(temp);
    }
}

void Words::index_insert(const char& ch, const string& word)
{
    unordered_multimap<char, string>::iterator it = index_.find(ch);
    if(it != index_.end())
    {
        unordered_multimap<char, string>::size_type len = index_.count(ch);
        unordered_multimap<char, string>::size_type cnt;
        for(cnt = 0; cnt != len; cnt++, it++)
        {
            if(it->second == word)
                break;
        }
        if(cnt == len)
            index_.insert(make_pair(ch, word));
        else
            return;
    }
    else
        index_.insert(make_pair(ch, word));
}

void Words::index_show(const char& ch)
{
    unordered_multimap<char, string>::iterator it = index_.find(ch);
    cout << ch << ":" << endl;
    if(it != index_.end())
    {
        unordered_multimap<char, string>::size_type len = index_.count(ch);
        unordered_multimap<char, string>::size_type cnt;
        for(cnt = 0; cnt != len; cnt++, it++)
        {
            cout << it->second << "  ";
        }
        cout << endl;
    }
    else
        cout << "not exist" << endl;
}

void Words::set_candidate_words_set(const string& word)
{
    candidate_words_.clear();

    unordered_multimap<char, string>::size_type len;
    unordered_multimap<char, string>::size_type cnt;
    unordered_multimap<char, string>::iterator it_map;
    
    for(string::const_iterator it_string = word.begin(); it_string != word.end(); it_string++)
    {
        it_map = index_.find(*it_string);

        if(it_map != index_.end())
        {
            len = index_.count(*it_string);
            for(cnt = 0; cnt != len; cnt++, it_map++)
            {
                candidate_words_.insert(it_map->second);
            }
        }
    }
}
