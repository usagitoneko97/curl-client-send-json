#include "curljson.h"
#include <curl/curl.h>
#include <json-c/json.h>

const char* IPADDRESS = ("192.168.4.3:5555") ;
int sendJson(){
  CURL *curl;
  CURLcode res;
  json_object *json;
  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);
  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Accept: application/json");
  headers = curl_slist_append(headers, "Content-Type: application/json");

  /* get a curl handle */
  curl = curl_easy_init();
  /*allocate memory for json_object*/
  json = json_object_new_object();

    /* build post data */
  json_object_object_add(json, "period", json_object_new_int(42));
  json_object_object_add(json, "status", json_object_new_int(152));
  json_object_object_add(json, "maxStep", json_object_new_int(133));
    /* set curl options */
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_object_to_json_string(json));
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, IPADDRESS);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;

}
