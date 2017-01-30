
#include <string>
#include <fstream>

class HtmlTextConverter
{
    std::string m_fullFilenameWithPath;

public:
    static std::string convert(std::istream& txt);

    [[deprecated("use static string convert(istream&) instead")]]
    HtmlTextConverter(std::string const& fullFilenameWithPath);

    [[deprecated("use static string convert(istream&) instead")]]
    std::string convertToHtml();

    [[deprecated("use static string convert(istream&) instead")]]
    std::string getFilename();
};
