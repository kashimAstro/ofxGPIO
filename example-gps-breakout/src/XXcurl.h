#include "ofMain.h"
#include <curl/curl.h>
#include <boost/iostreams/stream.hpp>

class CURLDevice
{
    private:
        CURL* handle;
    public:
        typedef char                            char_type;
        typedef boost::iostreams::source_tag    category;

        CURLDevice()
        {
            handle = curl_easy_init();
        }

        CURLDevice(const std::string &url)
        {
            handle = curl_easy_init();
            open( url );
        }

        ~CURLDevice()
        {
            curl_easy_cleanup(handle);
        }

        void open(const std::string &url)
        {
            curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(handle, CURLOPT_CONNECT_ONLY, 1);
            curl_easy_perform(handle);
        }

        std::streamsize read(char* s, std::streamsize n)
        {
            size_t read;
            CURLcode ret = curl_easy_recv(handle, s, n, &read);
            if ( ret == CURLE_OK || ret == CURLE_AGAIN )
                return read;
            else
                return -1;
        }
};
