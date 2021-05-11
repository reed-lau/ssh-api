#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <libssh/libssh.h>

#include <string>
#include <sstream>

const char *user = "user";
const char *host = "127.0.0.1";
const char *port = "2222";
const char *passwd = "123456";

int main() {
  ssh_session session;

  session = ssh_new();
  printf("session = %p\n", session);

  int ret = 0;
  ret = ssh_options_set(session, SSH_OPTIONS_USER, user);
  printf("ssh_options_set(user) = %d\n", ret);

  ret = ssh_options_set(session, SSH_OPTIONS_HOST, host);
  printf("ssh_options_set(host) = %d\n", ret);

  ret = ssh_options_set(session, SSH_OPTIONS_PORT_STR, port);
  printf("ssh_options_set(port) = %d\n", ret);

  int verbose = SSH_LOG_NOLOG;
  ret = ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, &verbose);
  printf("ssh_options_set(log_verbosity) = %d\n", ret);

  /*
  ret = ssh_options_set(session, SSH_OPTIONS_PASSWORD_AUTH, passwd);
  printf("ssh_options_set(port) = %d\n", ret);
  */

  ret = ssh_connect(session);
  printf("ssh_connect(...) = %d\n", ret);

  ret = ssh_userauth_password(session, NULL, passwd);
  fprintf(stderr, "ssh_userauth_password = %d, SSH_AUTH_SUCCESS = %d\n", ret,
          SSH_AUTH_SUCCESS);

  ssh_scp scp = ssh_scp_new(session, SSH_SCP_WRITE | SSH_SCP_RECURSIVE, ".");
  printf("ssh_scp_new = %p\n", scp);

  ret = ssh_scp_init(scp);
  printf("ssh_scp_init = %d\n", ret);

  ret = ssh_scp_push_directory(scp, "dir_name", S_IRWXU);
  printf("ssh_scp_push_directory = %d %s\n", ret, ssh_get_error(session));

  for (int i = 0; i < 3; ++i) {
    std::ostringstream ss;
    ss<< i;
    std::string data = std::string("I am the content") + ss.str();
    std::string file = std::string("file_name") + ss.str() + ".txt";
    ret =
        ssh_scp_push_file(scp, file.c_str(), data.size(), S_IRUSR | S_IWUSR);
    printf("ssh_scp_push_file = %d\n", ret);

    ret = ssh_scp_write(scp, data.data(), data.size());
    printf("ssh_scp_write = %d\n", ret);
  }

  ssh_scp_close(scp);
  ssh_scp_free(scp);
  ssh_disconnect(session);
  ssh_free(session);
  ssh_finalize();
}
