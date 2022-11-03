#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/urlapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leptjson.h"

struct string {
  char *ptr;
  size_t len;
};

static void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

static size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}

// todo simply request response
static void caiyun(char **res, char *sentence) {
  lept_value payload;
  lept_init(&payload);
  payload.type = LEPT_OBJECT;
  payload.u.o.size = 3;
  lept_member arr[3];

  size_t i = 0;
  char *p = sentence;
  while (*p++) i++;

  lept_value vsource;
  lept_init(&vsource);
  vsource.type = LEPT_STRING;
  vsource.u.s.len = i;
  vsource.u.s.s = sentence;
  lept_member source;
  source.k = "source";
  source.klen = 6;
  source.v = vsource;
  arr[0] = source;

  lept_value v_trans_type;
  lept_init(&v_trans_type);
  v_trans_type.type = LEPT_STRING;
  v_trans_type.u.s.len = 5;
  v_trans_type.u.s.s = "en2zh";
  lept_member trans_type;
  trans_type.k = "trans_type";
  trans_type.klen = 10;
  trans_type.v = v_trans_type;
  arr[1] = trans_type;

  lept_value v_request_id;
  lept_init(&v_request_id);
  v_request_id.type = LEPT_STRING;
  v_request_id.u.s.len = 4;
  v_request_id.u.s.s = "demo";
  lept_member request_id;
  request_id.k = "request_id";
  request_id.klen = 10;
  request_id.v = v_request_id;
  arr[2] = request_id;

  payload.u.o.m = arr;

  *res = lept_stringify(&payload, NULL);
}

int fanyi(char *sentence) {
  CURL *curl;
  CURLcode res;
  char *postthis;
  caiyun(&postthis, sentence);

  extern char authorization[44];

  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, "content-type: application/json");
  chunk = curl_slist_append(chunk, authorization);

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl) {
    struct string s;
    init_string(&s);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL, "http://api.interpreter.caiyunai.com/v1/translator");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    res = curl_easy_perform(curl);

    lept_value v;
    lept_parse(&v, s.ptr);
    lept_value *value;
    value = lept_get_object_value(&v, 1);
    printf("翻译: %s\n", value->u.s.s);

#if !WAYLAND
    char dwm[1024];
    sprintf(dwm, "xsetroot -name \"%s\"", value->u.s.s);
    system(dwm);
#endif

    free(s.ptr);
    if (res != CURLE_OK) { fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); }
  }

  curl_easy_cleanup(curl);
  free(postthis);
  curl_global_cleanup();
  return 0;
}
