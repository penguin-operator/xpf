#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <lib.h>

int main() {
	u8 _[3] = {0,0,0};

	char* display = getenv("DISPLAY");
	char* xauth_file = getenv("XAUTHORITY");
	struct stat x_st;
	stat(xauth_file, &x_st);
	int x_auth = open(xauth_file, O_RDONLY, 0600);
	uint16_t xauth_family;
	read(x_auth, &xauth_family, 2);
	xauth_t *xauth = malloc(x_st.st_size - 2);
	int n = (x_st.st_size - 2) / sizeof(xauth_t), x = 0;
	for (int i = 0; i < n; i++) {
		read(x_auth, &xauth[i].addr_len, 2);
		xauth[i].addr_len = ntohs(xauth[i].addr_len);
		xauth[i].addr = malloc(xauth[i].addr_len);
		read(x_auth, xauth[i].addr, xauth[i].addr_len);
		read(x_auth, &xauth[i].display_len, 2);
		xauth[i].display_len = ntohs(xauth[i].display_len);
		xauth[i].display = malloc(xauth[i].display_len);
		read(x_auth, xauth[i].display, xauth[i].display_len);
		read(x_auth, &xauth[i].name_len, 2);
		xauth[i].name_len = ntohs(xauth[i].name_len);
		xauth[i].name = malloc(xauth[i].name_len);
		read(x_auth, xauth[i].name, xauth[i].name_len);
		read(x_auth, &xauth[i].data_len, 2);
		xauth[i].data_len = ntohs(xauth[i].data_len);
		xauth[i].data = malloc(xauth[i].data_len);
		read(x_auth, xauth[i].data, xauth[i].data_len);
		if (strcmp(xauth[i].display, display+1) == 0) x = i;
	}
	close(x_auth);

	int x_sock = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un addr = { .sun_family = AF_UNIX };
	strcpy(addr.sun_path, X_SOCKET);
	strcpy(addr.sun_path+strlen(X_SOCKET), display+1);
	connect(x_sock, (struct sockaddr*)&addr, sizeof(addr));
	struct {
		setup_req_t req;
		setup_resp_t resp;
	} setup = {
		.req = {l, { 11, 0 }, { xauth[x].name_len, xauth[x].data_len }, },
	};
	writev(x_sock, (struct iovec[]){
		{ &setup.req, sizeof(setup.req) },
		{ &_, (4 - sizeof(setup.req) & 3) & 3 },
		{ xauth[x].name, xauth[x].name_len },
		{ &_, (4 - xauth[x].name_len & 3) & 3 },
		{ xauth[x].data, xauth[x].data_len },
		{ &_, (4 - xauth[x].data_len & 3) & 3 },
	}, 6);
	read(x_sock, &setup.resp, 8);
	if (setup.resp.status == 0) {
		char* reason = malloc(setup.resp.reason_len+1);
		read(x_sock, reason, setup.resp.reason_len);
		fprintf(stderr, "\e[1;91mERROR\e[0m %s\n", reason);
		return 1;
	} else read(x_sock, ((char*)&setup.resp)+8, sizeof(setup.resp)-8);
	return 0;
}
