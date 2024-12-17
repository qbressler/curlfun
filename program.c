#include <stdio.h>
#include <stdlib.h>
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
	char *url;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if(argc == 1)
	{
		printf("Please provide a url for request\n\n");
		printf("No URL provided. Using example.com for testing\n");
		url = "http://example.com";
	}
	else
	{
		url = argv[1];
	}

	fp = fopen(output_filename, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "Could not open output file for writing");
		exit(1);
	}

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
