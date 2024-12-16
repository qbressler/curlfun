#include <stdio.h>
#include <curl/curl.h>

size_t write_to_file(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]) 
{
	CURL *curl;
	CURLcode res;
	char response[4096];
	FILE *fp;
	const char *output_filename = "output.resp";

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	/*
	if(argc == 1)
	{
		printf("please provide a url for request\n");
		return 1;
	}
	*/

	fp = fopen(output_filename, "wb");
	if(fp == NULL)
	{
		printf("Error opening file for writing");
		return 1;
	}



	//char *url = argv[1];
	char url[] = "http://example.com";

	if (curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);
		printf("Writing output to %s \n", output_filename);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
		    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);

		curl_global_cleanup();
	}
	else
	{
		printf("Something went wrong. Exiting!\n");
		return 1;
	}

	fclose(fp);
	
	return 0;
}
