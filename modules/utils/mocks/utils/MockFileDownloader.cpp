#include "MockFileDownloader.h"

namespace utils
{
void MockFileDownloader::download (
    const std::string & urlToDownloadFrom,
    std::function<void (const std::vector<unsigned char> &)> onDataDownloads)
{
    auto iter = _dataMap.find (urlToDownloadFrom);
    if (iter != _dataMap.end () && onDataDownloads)
        onDataDownloads (iter->second);
}

void MockFileDownloader::addData (const std::string & urlToDownloadFrom,
                                  const std::vector<unsigned char> & data)
{
    _dataMap [urlToDownloadFrom] = data;
}
}