/*
 * Copyright © 2008-2012 Kristian Høgsberg
 * Copyright © 2010-2012 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Struct definintions shared by the client code and test suite. */

/** \cond */

struct wl_event_queue {
	struct wl_list event_list;
	struct wl_list proxy_list; /**< struct wl_proxy::queue_link */
	struct wl_display *display;
	char *name;
};

struct wl_proxy {
	struct wl_object object;
	struct wl_display *display;
	struct wl_event_queue *queue;
	uint32_t flags;
	int refcount;
	void *user_data;
	wl_dispatcher_func_t dispatcher;
	uint32_t version;
	const char * const *tag;
	struct wl_list queue_link; /**< in struct wl_event_queue::proxy_list */
};

struct wl_display {
	struct wl_proxy proxy;
	struct wl_connection *connection;

	/* errno of the last wl_display error */
	int last_error;

	/* When display gets an error event from some object, it stores
	 * information about it here, so that client can get this
	 * information afterwards */
	struct {
		/* Code of the error. It can be compared to
		 * the interface's errors enumeration. */
		uint32_t code;
		/* interface (protocol) in which the error occurred */
		const struct wl_interface *interface;
		/* id of the proxy that caused the error. There's no warranty
		 * that the proxy is still valid. It's up to client how it will
		 * use it */
		uint32_t id;
	} protocol_error;
	int fd;
	struct wl_map objects;
	struct wl_event_queue display_queue;
	struct wl_event_queue default_queue;
	pthread_mutex_t mutex;

	int reader_count;
	uint32_t read_serial;
	pthread_cond_t reader_cond;
};

/** \endcond */
