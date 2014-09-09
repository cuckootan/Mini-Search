#ifndef _TEXT_H_
#define _TEXT_H_

#include <fstream>
#include <string>
#include <stdexcept>

class Text
{
	friend class Words;

    public:
        Text(const std::string& text_name);
        ~Text();

        void text_open();
        void text_close();

    private:
        std::string text_name_;
        std::ifstream if_text_;
};

#endif
