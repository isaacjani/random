#include <stdio.h>
#include <string.h>
#include <libxml/HTMLparser.h>
#include <libxml/tree.h>
#include <curl/curl.h>

int main() {
	printf("What is the url of the website? \n");

	char url[1000];
	fgets(url, sizeof(url), stdin);
	url[strcspn(url, "\n")] = '\0';

	printf("How many sentences should the summary be? \n");
	char input[20];
	fgets(input, sizeof(input), stdin);
	int amount = atoi(input);

    CURL *curl;
    FILE *file = fopen("page.html", "wb");

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Summarizer/1.0");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    fclose(file);

    htmlDocPtr doc = htmlReadFile("page.html", NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_RECOVER);

    if (!doc) return 1;

	xmlNodePtr root = xmlDocGetRootElement(doc);

	char article[200000] = "";

	for (xmlNodePtr node = root; node;) {

		if (node->type == XML_ELEMENT_NODE &&
			xmlStrEqual(node->name, BAD_CAST "p")) {

			xmlChar *content = xmlNodeGetContent(node);

			strcat(article, (char *)content);
			strcat(article, " ");

			xmlFree(content);
		}


		if (node->children)
			node = node->children;
		else {
			while (node && !node->next)
				node = node->parent;

			if (node)
				node = node->next;
		}
	}

    printf("\nSummary:\n\n");

    int count = 0;
    char *sentence = strtok(article, ".");

    while (sentence && count < amount) {
        while (*sentence == ' ') sentence++;

        if (strlen(sentence) > 50) {
            printf("%s.\n\n", sentence);
            count++;
        }

        sentence = strtok(NULL, ".");
    }

    xmlFreeDoc(doc);
    remove("page.html");

    return 0;
}