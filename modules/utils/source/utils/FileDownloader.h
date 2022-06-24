#pragma once

#include <functional>
#include <string>
#include <vector>

namespace utils
{
class FileDownloader
{
public:
    FileDownloader () = default;
    virtual ~FileDownloader () = default;

    virtual void
    download (const std::string & urlToDownloadFrom,
              std::function<void (const std::vector<unsigned char> &)> onDataDownloads);
};
};