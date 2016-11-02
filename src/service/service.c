#include "service.h"

post_collection
service_get_posts ()
{
  long http_code;
  string raw_result;
  post_collection result;
  raw_result = repository_get (TARGET_POSTS, &http_code);

  post_collection_initialize (&result);

  result = post_collection_deserialize (raw_result);

  string_destroy (&raw_result);

  return result;
}

post
service_get_post (unsigned long id)
{
  long http_code;
  string raw_result;
  post result;
  raw_result = repository_get (TARGET_POST, id, &http_code);

  result = post_deserialize (raw_result);

  return result;
}

post
service_post (post p)
{
  string post_data;
  long http_code;
  string raw_result;
  post result;

  post_data = post_serialize (p);

  raw_result = repository_post (TARGET_POSTS, &http_code, post_data);
  string_destroy (&post_data);

  result = post_deserialize (raw_result);

  return result;
}

user
service_register (user u)
{
  string post_data;
  long http_code;
  string raw_result;
  user result;

  post_data = user_serialize (u);

  raw_result = repository_post (TARGET_REGISTER, &http_code, post_data);
  string_destroy (&post_data);

  result = user_deserialize (raw_result);

  return result;
}

user
service_login (user u)
{
  string post_data;
  long http_code;
  string raw_result;
  user result;

  post_data = user_serialize (u);

  raw_result = repository_post (TARGET_LOGIN, &http_code, post_data);
  string_destroy (&post_data);

  user_initialize (&result);
  result = user_deserialize (raw_result);

  return result;
}