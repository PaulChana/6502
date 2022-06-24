#include <utils/FileDownloader.h>

#ifdef _MSC_VER
#include <windows.h>
int WinMain(HINSTANCE,HINSTANCE,LPSTR,int);
#else
int main (int, char**)
#endif
{
    utils::FileDownloader downloader;

    downloader.download ("", [](auto &&) {});
    return 0;
}
