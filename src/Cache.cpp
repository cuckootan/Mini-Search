#include "Cache.h"

using namespace std;

Cache::Cache(const string& file_name):
    file_name_(file_name),
    size_(0)
{
    list_init();
    read_from_file();
}

Cache::~Cache()
{
    list_destroy();
}

void Cache::open_in_file()
{
    in_file_.open(file_name_.c_str());
    if(!in_file_)
        throw runtime_error("text open failed");
}

void Cache::open_out_file()
{
    out_file_.open(file_name_.c_str());
    if(!out_file_)
        throw runtime_error("text open failed");
}

void Cache::close_in_file()
{
    in_file_.close();
}

void Cache::close_out_file()
{
    out_file_.close();
}

void Cache::read_from_file()
{
    cout << "init cache from file" << endl;
    open_in_file();

    string line, key, value;
    set<string> value_set;

    while(line.clear(), getline(in_file_, line))
    {
        istringstream stream(line);

        key.clear();
        value_set.clear();
        stream >> key;

        pNode ptr = new Node;
        ptr->key_ = key;
        ptr->pre_ = NULL;
        ptr->next_ = NULL;

        while(value.clear(), stream >> value)
            value_set.insert(value);

        ptr->value_ = value_set;
        list_push_top(ptr);
        word_ptr_.insert(make_pair(ptr->key_, ptr));
    }

    close_in_file();
}

void Cache::write_to_file()
{
    open_out_file();
    
    string line;

    pNode ptr = head_->next_;
    while(ptr != tail_)
    {
        line.clear();
        line.append(ptr->key_);

        for(set<string>::iterator it = ptr->value_.begin();
                it != ptr->value_.end();
                it++)
        {
            line += '\t';
            line.append(*it);
        }
        
        line += '\n';

        out_file_ << line;

        ptr = ptr->next_;
    }
    
    close_out_file();

    cout << "write cache to file" << endl;
}

void Cache::list_init()
{
    head_ = new Node;
    tail_ = new Node;

    head_->pre_ = NULL;
    head_->next_ = tail_;

    tail_->pre_ = head_;
    tail_->next_ = NULL;
}

void Cache::list_show()
{
    pNode ptr = head_->next_;

    while(ptr != tail_)
    {
        cout << ptr->key_ << " : ";
        for(set<string>::iterator it = ptr->value_.begin();
                it != ptr->value_.end();
                it++)
            cout << *it << "  ";
        cout << endl;

        ptr = ptr->next_;
    }
}

size_t Cache::list_size()
{
    return size_;    
}

void Cache::get(const string& key, set<string>& value, bool& judge)
{
    if(word_ptr_.count(key) == 0)
    {
        judge = false;
        cout << "the word does not exist, need to search from wordlib" << endl;
    }
    else
    {
        judge = true;
        cout << "the word does exist, directly get the candidates of " << key << endl;
        pNode ptr = word_ptr_[key];
        list_pop(ptr);
        list_push_top(ptr);
        value = ptr->value_;
    }
}

void Cache::put(const string& key, const set<string>& value)
{
    if(word_ptr_.count(key) != 0)
    {
        cout << "exist, can not put" << endl;
    }
    else
    {
        if(size_ >= CACHE_SIZE)
        {
            cout << "Cache is full, need to replace, then put to cache, and get the candidates " << key << endl;
            //首先将list的尾部结点存入硬盘cache中，然后删除之。接着从word_count这个map中读取至外部，同时存入这个内存cache中，最后修改word_ptr这个map
            pNode ptr = tail_->pre_;
            list_pop(ptr);
            word_ptr_.erase(ptr->key_);
            cout << "delete  " << ptr->key_ << " : ";
            set_show(ptr->value_);
            
            ptr->key_ = key;
            ptr->value_ = value;
            
            list_push_top(ptr);
            word_ptr_.insert(make_pair(ptr->key_, ptr));
        }
        else
        {
            cout << "Cache is not full, directly put to cache, and get the candidates of " << key << endl;
            pNode ptr = new Node;
            ptr->key_ = key;
            ptr->value_ = value;
            ptr->pre_ = NULL;
            ptr->next_ = NULL;

            list_push_top(ptr);

            word_ptr_.insert(make_pair(key,ptr));
        }
    }
}

void Cache::list_pop(pNode ptr)
{
    cout << "pop" << endl;
    ptr->pre_->next_ = ptr->next_;
    ptr->next_->pre_ = ptr->pre_;
    ptr->pre_ = NULL;
    ptr->next_ = NULL;
    size_--;
}

void Cache::list_push_top(pNode ptr)
{
    cout << "push" << endl;
    ptr->next_ = head_->next_;
    ptr->pre_ = head_;
    head_->next_->pre_ = ptr;
    head_->next_ = ptr;
    size_++;
}

bool Cache::list_is_empty()
{
    return size_ == 0;
}

void Cache::list_clear()
{
    while(!list_is_empty())
    {
        pNode ptr = head_->next_;
        list_pop(ptr);
        delete ptr;
        ptr = NULL;
    }
}

void Cache::list_destroy()
{
    list_clear();

    delete head_;
    head_ = NULL;

    delete tail_;
    tail_ = NULL;
}
