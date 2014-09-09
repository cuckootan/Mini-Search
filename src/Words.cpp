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

int Words::min_edit_instance(const string& src, const string& des)
{
    size_t len1 = src.size();
    size_t len2 = des.size();
    size_t i, j;
    int seq[50][50];
    memset(seq, -1, sizeof seq);

    for(i = 0; i != len1 + 1; i++)
    {
        for(j = 0; j != len2 + 1; j++)
        {
            if(i == 0)
            {
                seq[i][j] = j;
                continue;
            }
            else if(j == 0)
            {
                seq[i][j] = i;
                continue;
            }

            if(src[i - 1] == des[j - 1])
                seq[i][j] = seq[i - 1][j - 1];
            else
                seq[i][j] = min_cost(seq[i - 1][j] + 1, seq[i][j - 1] + 1, seq[i - 1][j - 1] + 1);
        }
    }

    return seq[len1][len2];
}

void Words::priority_queue_init(const string& word)
{
    priority_queue_clear();

    set_candidate_words_set(word);
    for(set<string>::iterator it_ = candidate_words_.begin();
        it_ != candidate_words_.end();
        it_++)
    {   
	if(abs(it_->size() - word.size()) > MAX_EDIT_INSTANCE)
	    continue;

	int dist = min_edit_instance(word, *it_);
	if(dist > MAX_EDIT_INSTANCE)
	    continue;

        Word_info temp;
        temp.set_word_name(*it_);
        temp.set_word_cost(dist);
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
