#include "sock.h"

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int set_sock_nb (int sock, int nb)
{
	/* set the socket to be non blocking */
	int flags = fcntl (sock, F_GETFL, 0);
	if (flags == -1) 
		return errno;

	if (nb)
		flags |= O_NONBLOCK;
	else
		flags &= ~O_NONBLOCK;
	int ret = fcntl (sock, F_SETFL, flags);
	if (ret == -1) 
		return errno;

	return 0;
}

int connected_sock (const struct addrinfo *addrs, int *sock, unsigned timeout)
{
	int ret;

	*sock = socket (addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
	if (*sock == -1) {
		ret = errno;
		goto err;
	}

	ret = set_sock_nb (*sock, 1);
	if (ret) 
		goto err;

	/* connect */
	ret = timed_connect (*sock, addrs->ai_addr, addrs->ai_addrlen, timeout);
	if (!ret) 
		goto exit;

err:
	if (*sock != -1) {
		close (*sock);
		*sock = -1;
	}

exit:
	return ret;
}

int timed_select (int fd, int to_write, unsigned seconds)
{
	struct timeval timeout;
	fd_set theset;

	time_t start_ts = time (NULL);
	time_t now = time (NULL);

	do {
		unsigned elapsed = now - start_ts;
		if (start_ts == -1 || now == -1)
			elapsed = 0;
		timeout.tv_sec = seconds - elapsed;
		timeout.tv_usec = 0;
		FD_ZERO (&theset);
		FD_SET (fd, &theset);
		int ret = select (fd + 1, to_write ? NULL : &theset,
				to_write ? &theset : NULL, NULL, &timeout);
		int err = errno;
		if (ret < 0) {
			if (err != EINTR)
				/* error */
				return err;
			/* else: try again */
		} else if (ret > 0) 
			return 0;
		else
			/* timed out */
			return ETIMEDOUT;

		now = time (NULL);
	} while (start_ts != -1 && now != -1 && now < start_ts + seconds);

	return ETIMEDOUT;
}

int timed_connect (int sockfd, const struct sockaddr *addr, socklen_t addrlen,
		unsigned seconds) 
{
	int ret = 0;

	socklen_t errsize;
	int errval = 0;

	if (sockfd == -1)
		return ENOTSOCK;

	ret = connect (sockfd, addr, addrlen);
	int err = errno;
	if (ret < 0) {
		if (err == EINPROGRESS) {
			ret = timed_select (sockfd, 1, seconds);
			if (!ret) {
				/* connected or unconnectable */
				errsize = sizeof (errval);
				if (getsockopt (sockfd, SOL_SOCKET, SO_ERROR, (void *) &errval,
							&errsize) < 0) 
					return errno;

				/* check for errors */
				return errval;
			} else
				/* timed out */
				return ret;
		} else
			return err;
	}

	/* immediately connected, connect to local server maybe */
	return 0;
}

time_t get_timed_deadline (unsigned timeout)
{
	time_t start_ts = time (NULL);
	time_t deadline = start_ts + timeout;

	if (start_ts == -1 || timeout == -1)
		/* no timeout or cannot determine it */
		deadline = -1;

	return deadline;
}

int timed_write (int fd, const void *buf, size_t count, unsigned io_timeout,
		time_t deadline)
{
	while (count) {
		time_t now = time (NULL);
		if (now != -1 && now > (unsigned long long) deadline)
			return ETIMEDOUT;

		unsigned op_timeout = now == -1 ? -1 : deadline - now;
		int ret = timed_select (
				fd, 1, op_timeout < io_timeout ? op_timeout : io_timeout);
		if (ret)
			return ret;

		while (count && (ret = write (fd, buf, count)) >= 0) {
			count -= ret;
			buf = (const char *) buf + ret;
		}

		if (ret < 0) {
			ret = errno;
			if (ret != EAGAIN)
				return ret;
		}
	} 

	return 0;
}

int timed_read (int fd, void *buf, size_t count, size_t *red,
		unsigned io_timeout, time_t deadline)
{
	*red = 0;

	if (count) {
		time_t now = time (NULL);
		if (now != -1 && now > (unsigned long long) deadline)
			return ETIMEDOUT;

		unsigned op_timeout = now == -1 ? -1 : deadline - now;
		int ret = timed_select (
				fd, 0, op_timeout < io_timeout ? op_timeout : io_timeout);
		if (ret)
			return ret;

		while (count && (ret = read (fd, buf, count)) > 0) {
			count -= ret;
			buf = (char *) buf + ret;
			*red += ret;
		}

		if (ret < 0) {
			ret = errno;
			if (ret != EAGAIN)
				return ret;
		}

		return 0;
	}

	return 0;
}





