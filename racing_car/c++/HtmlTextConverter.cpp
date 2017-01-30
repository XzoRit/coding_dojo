
#include "HtmlTextConverter.h"
#include "StringEscapeUtils.h"

std::string HtmlTextConverter::convert(std::istream& reader)
{
    std::string line;
    std::string html;
    while (std::getline(reader,line))
    {
        html += StringEscapeUtils::escapeHtml(line);
        html += "<br />";
    }
    return html;
}

HtmlTextConverter::HtmlTextConverter(std::string const& fullFilenameWithPath) : m_fullFilenameWithPath(fullFilenameWithPath)
{}

std::string HtmlTextConverter::convertToHtml() 
{
    std::ifstream reader(m_fullFilenameWithPath);

    std::string line;
    std::string html;
    while (std::getline(reader,line))
    {
        html += StringEscapeUtils::escapeHtml(line);
        html += "<br />";
    }
    return html;
}

std::string HtmlTextConverter::getFilename() 
{
    return m_fullFilenameWithPath;
}
