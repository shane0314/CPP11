#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *stream)
{
    std::string *str = (std::string*)stream;
    (*str).append((char*)contents, size*nmemb);
    return size * nmemb;
}

int main(void)
{
  CURL *curl_handle;
  CURLcode res;
  CURLcode res2;

  std::string chunk;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://192.168.0.18:9000/api/auth/ip");

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
  res = curl_easy_perform(curl_handle);

  /* check for errors */
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */
    char *ct;
    /* ask for the content-type */
    res2 = curl_easy_getinfo(curl_handle, CURLINFO_CONTENT_TYPE, &ct);

    if((CURLE_OK == res2) && ct)
    printf("\nWe received Content-Type: %s\n", ct);

    std::string strJson(chunk);
    printf("what retrieved: %s\n", strJson.c_str());
    
    Json::Reader reader;
    Json::Value root;
    bool status;
    std::string message;
    if( reader.parse( strJson, root) )
    {
        status = root["status"].asBool();
        message = root["message"].asString();
        std::cout << "status:" << status << ", message:" << message << std::endl;
    }
    else
    {
        std::cout << "Json reader parse failed!" << std::endl;
    }
  }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  return 0;
}
