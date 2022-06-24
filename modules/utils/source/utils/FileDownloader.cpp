#include "FileDownloader.h"

#include <algorithm>
#include <iterator>
#include <vector>

namespace utils
{
void FileDownloader::download (
    const std::string & urlToDownloadFrom,
    std::function<void (const std::vector<unsigned char> &)> onDataDownloads)
{
    std::vector<unsigned char> result;
    std::fill_n (std::back_inserter (result), 10, 'a');
    (void) urlToDownloadFrom;
    if (onDataDownloads != nullptr)
        onDataDownloads (result);
}
}