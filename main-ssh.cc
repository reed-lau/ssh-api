#include <stdio.h>
#include <libssh/libssh.h>

#include <string>

const char *user = "user";
const char *host = "127.0.0.1";
const char *port = "2222";
const char *passwd = "password";

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

  ret = ssh_options_set(session, SSH_OPTIONS_PASSWORD_AUTH, passwd);
  printf("ssh_options_set(port) = %d\n", ret);

  ret = ssh_connect(session);
  printf("ssh_connect(...) = %d\n", ret);

  ret = ssh_userauth_password(session, NULL, passwd);
  fprintf(stderr, "ssh_userauth_password = %d, SSH_AUTH_SUCCESS = %d\n",
          ret, SSH_AUTH_SUCCESS);

  ssh_channel channel = ssh_channel_new(session);
  printf("ssh_channel_new = %p\n", channel);

  ret = ssh_channel_open_session(channel);
  printf("ssh_channel_open_session = %d\n", ret);

  // std::string cmd = "sleep 10000 0>/dev/null 1>/dev/null &";
  // std::string cmd = "ifconfig";
  std::string cmd = "cat /proc/cpuinfo";
  ret = ssh_channel_request_exec(channel, cmd.c_str());
  printf("ssh_channel_request_exec = %d\n", ret);

  std::string data;
  while (1) {
    char buf[1024] = {0};
    int nret = ssh_channel_read(channel, buf, 1024, 0);
    if (nret > 0) {
      data.append(buf, nret);
    } else {
      break;
    }
  }
  ret = ssh_channel_send_eof(channel);

  printf("data = \n%s", data.c_str());

  ssh_channel_close(channel);
  ssh_channel_free(channel);
  ssh_disconnect(session);
  ssh_free(session);
  ssh_finalize();
}
