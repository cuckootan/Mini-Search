#include "Text.h"

using namespace std;

Text::Text(const string& text_name):
    text_name_(text_name)
{
    
}

Text::~Text()
{

}

void Text::text_open()
{
    if_text_.open(text_name_.c_str());
    if(!if_text_)
    {
        throw runtime_error("text open failed");
    }
}

void Text::text_close()
{
    if_text_.close();
}
