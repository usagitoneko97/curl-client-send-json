# POST JSON data using curl

## Prerequisites:
* json-c library [link](https://github.com/json-c/json-c)
* curl library [link](https://curl.haxx.se/)

## Several importants things:
create **json_object** and **curl** handler
```
CURL *curl;
json_object *json;
```
Initialize curl (In windows will initialize winsock stuff..)
```
curl_global_init(CURL_GLOBAL_ALL);
```
headers can be specify as below:
```
struct curl_slist *headers = NULL;
headers = curl_slist_append(headers, "Accept: application/json");
headers = curl_slist_append(headers, "Content-Type: application/json");
```
get a curl handle and create a json_object
```
/* get a curl handle */
curl = curl_easy_init();
/*allocate memory for json_object*/
json = json_object_new_object();
```
build the json data
```
json_object_object_add(json, "title", json_object_new_string("testies"));
json_object_object_add(json, "body", json_object_new_string("testies ... testies ... 1,2,3"));
json_object_object_add(json, "userId", json_object_new_int(133));
```
bind the curl with the header, data etc.. above
```
curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_object_to_json_string(json));
curl_easy_setopt(curl, CURLOPT_URL, "http://www.anyAddress.com:PORTNO");
```
finally, perform the request and capture the response. Analyze and process the response (not shown here)
```
CURLcode res;
res = curl_easy_perform(curl);
```
It's a good practice to clean-up all the operation after finishing the operations.
```
curl_easy_cleanup(curl);
curl_global_cleanup();
```
