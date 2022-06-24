#include <catch2/catch_all.hpp>
#include <utils/FileDownloader.h>

SCENARIO ("Files Download properly", "[utils]")
{
    GIVEN ("A file downloader")
    {
        utils::FileDownloader downloader;

        THEN ("When we request a download, we get a callback")
        {
            downloader.download (
                "", [] (const std::vector<unsigned char> & data) { REQUIRE (! data.empty ()); });
        }
    }
}
