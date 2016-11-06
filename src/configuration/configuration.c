#include "configuration.h"

#define DEFAULT_BASE_URL "http://shilld.herokuapp.com/"

#if defined(_WIN32)
#define PATH_SEPARATOR "\\"
#elif defined(__linux__)
#define PATH_SEPARATOR "/"
#else
#error Platform not supported yet
#endif

void
configuration_initialize ()
{
  configuration.base_url.len = -1L;
  configuration.base_url.s = NULL;
  user_initialize (&configuration.u);
}

string
_configuration_get_file_path ()
{
  string conf_file_path;
  string home_directory;
  string file_name = string_create (".shill_config.json");
  string separator = string_create (PATH_SEPARATOR);

  if (arguments.config != NULL)
    {
      conf_file_path = string_create (arguments.config);
      return conf_file_path;
    }

  home_directory = string_create (getenv ("HOME"));

  if (home_directory.len > 0)
    {
      conf_file_path = string_catd (&home_directory, &separator);
      conf_file_path = string_catd (&conf_file_path, &file_name);
      return conf_file_path;
    }

  home_directory = string_create (getenv ("USERPROFILE"));

  if (home_directory.len > 0)
    {
      conf_file_path = string_catd (&home_directory, &separator);
      conf_file_path = string_catd (&conf_file_path, &file_name);
      return conf_file_path;
    }

  error (EXIT_FAILURE, errno, _ ("couldn't find home directory"));
}

void
configuration_parse ()
{
  int errnum;
  string conf_file_path;
  FILE* conf_file;
  json_t *json_root, *json_configuration, *json_server, *json_base_url,
          *json_user, *json_username, *json_auth_token;
  json_error_t json_error;

  conf_file_path = _configuration_get_file_path ();

  conf_file = fopen (conf_file_path.s, "r");
  if (conf_file == NULL)
    {
      errnum = errno;
      if (errnum == ENOENT)
        {
          /*
           * if "No such file or directory"
           * there is a chance we can create a new configuration and continue
           * (don't abort yet)
           */
          return;
        }
      else
        {
          error (EXIT_FAILURE, errnum,
                 _ ("cannot open configuration file: %s"), conf_file_path.s);
        }
    }

  json_root = json_loadf (conf_file, 0, &json_error);

  if (fclose (conf_file))
    {
      errnum = errno;
      json_decref (json_root);
      error (EXIT_FAILURE, errnum,
             _ ("cannot close configuration file: %s"), conf_file_path.s);
    }
  if (!json_root)
    {
      error (EXIT_FAILURE, 0,
             _ ("%s:%d:%d: cannot parse json file: %s"), conf_file_path.s,
             json_error.line,
             json_error.column,
             json_error.text);
    }

  if (!json_is_object (json_root))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("%s: cannot parse json file: \
expected root element to be a json object"),
             conf_file_path.s);
    }

  json_configuration = json_object_get (json_root, "configuration");

  if (!json_is_object (json_configuration))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("%s: cannot parse json file: \
expected \"configuration\" element to be a json object"),
             conf_file_path.s);
    }

  json_server = json_object_get (json_configuration, "server");

  json_user = json_object_get (json_configuration, "user");

  if (!json_is_object (json_server))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("%s: cannot parse json file: \
expected \"server\" element to be a json object"),
             conf_file_path.s);
    }

  json_base_url = json_object_get (json_server, "base-url");

  if (!json_is_string (json_base_url))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("%s: cannot parse json file: \
expected \"base-url\" element to be a json string"),
             conf_file_path.s);
    }

  configuration.base_url =
          string_create (json_string_value (json_base_url));

  if (json_is_object (json_user))
    {
      json_username = json_object_get (json_user, "username");
      json_auth_token = json_object_get (json_user, "auth_token");

      if (json_is_string (json_username))
        {
          configuration.u.username =
                  string_create (json_string_value (json_username));
        }

      if (json_is_string (json_auth_token))
        {
          configuration.u.auth_token =
                  string_create (json_string_value (json_auth_token));
        }
    }

  json_decref (json_root);
}

void
configuration_save_user ()
{
  int errnum;
  string conf_file_path;
  FILE* conf_file;
  json_t *json_root, *json_configuration, *json_user, *json_username,
          *json_auth_token;
  json_error_t json_error;

  conf_file_path = _configuration_get_file_path ();

  conf_file = fopen (conf_file_path.s, "r");
  if (conf_file == NULL)
    {
      error (EXIT_FAILURE, errno,
             _ ("cannot open configuration file: %s"), conf_file_path.s);
    }

  json_root = json_loadf (conf_file, 0, &json_error);

  if (fclose (conf_file))
    {
      errnum = errno;
      json_decref (json_root);
      error (EXIT_FAILURE, errnum,
             _ ("cannot close configuration file: %s"), conf_file_path.s);
    }
  if (!json_root)
    {
      error (EXIT_FAILURE, 0,
             _ ("%s:%d:%d: cannot parse json file: %s"), conf_file_path.s,
             json_error.line,
             json_error.column,
             json_error.text);
    }

  if (!json_is_object (json_root))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("%s: cannot parse json file: \
expected root element to be a json object"),
             conf_file_path.s);
    }

  json_configuration = json_object_get (json_root, "configuration");

  if (!json_is_object (json_configuration))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("%s: cannot parse json file: \
expected \"configuration\" element to be a json object"),
             conf_file_path.s);
    }

  json_username = json_pack ("s", configuration.u.username.s);
  json_auth_token = json_pack ("s", configuration.u.auth_token.s);

  json_user = json_object ();

  json_object_set (json_user, "username", json_username);
  json_object_set (json_user, "auth_token", json_auth_token);

  json_object_set (json_configuration, "user", json_user);

  conf_file = fopen (conf_file_path.s, "w");
  if (conf_file == NULL)
    {
      error (EXIT_FAILURE, errno,
             _ ("cannot open configuration file: %s"), conf_file_path.s);
    }

  if (json_dumpf (json_root, conf_file, JSON_INDENT (4)) == -1)
    {
      errnum = errno;
      json_decref (json_root);
      error (EXIT_FAILURE, errnum,
             _ ("cannot write into configuration file: %s"), conf_file_path.s);
    }

  if (fclose (conf_file))
    {
      errnum = errno;
      json_decref (json_root);
      error (EXIT_FAILURE, errnum,
             _ ("cannot close configuration file: %s"), conf_file_path.s);
    }

  json_decref (json_root);
}

void
configuration_create ()
{
  int errnum;
  string conf_file_path;
  FILE* conf_file;
  json_t *json_root, *json_configuration, *json_server, *json_base_url;

  conf_file_path = _configuration_get_file_path ();

  if (arguments.base_url == NULL)
    {
      json_base_url = json_pack ("s", DEFAULT_BASE_URL);
    }
  else
    {
      json_base_url = json_pack ("s", arguments.base_url);
    }

  json_configuration = json_object ();
  json_root = json_object ();
  json_server = json_object ();

  json_object_set (json_server, "base-url", json_base_url);
  json_object_set (json_configuration, "server", json_server);
  json_object_set (json_root, "configuration", json_configuration);

  conf_file = fopen (conf_file_path.s, "w");
  if (conf_file == NULL)
    {
      errnum = errno;
      json_decref (json_root);
      error (EXIT_FAILURE, errnum,
             _ ("cannot create configuration file: %s"), conf_file_path.s);
    }

  if (json_dumpf (json_root, conf_file, JSON_INDENT (4)) == -1)
    {
      errnum = errno;
      json_decref (json_root);
      error (EXIT_FAILURE, errnum,
             _ ("cannot write into configuration file: %s"), conf_file_path.s);
    }

  if (fclose (conf_file))
    {
      errnum = errno;
      json_decref (json_root);
      error (EXIT_FAILURE, errnum,
             _ ("cannot close configuration file: %s"), conf_file_path.s);
    }

  json_decref (json_root);
}

void
configuration_check_user ()
{
  if (configuration.u.username.s == NULL)
    {
      error (EXIT_FAILURE, 0,
             _ ("login required: \
cannot find a valid username in configuration"));
    }
  if (configuration.u.auth_token.s == NULL)
    {
      error (EXIT_FAILURE, 0,
             _ ("login required: \
cannot find a valid auth_token in configuration"));
    }
}
