#pragma once

#include <map>
#include <utils/FileDownloader.h>

namespace utils
{
class MockFileDownloader : public FileDownloader
{
public:
    MockFileDownloader () = default;
    ~MockFileDownloader () override = default;
    void
    download (const std::string & urlToDownloadFrom,
              std::function<void (const std::vector<unsigned char> &)> onDataDownloads) override;

    void addData (const std::string & urlToDownloadFrom, const std::vector<unsigned char> & data);

private:
    std::map<std::string, std::vector<unsigned char>> _dataMap;
};
}