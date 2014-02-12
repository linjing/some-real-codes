#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en, msg) \
  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void display_stack_attr (pthread_attr_t *attr, char *prefix) {
  int s;
  size_t stack_size, guard_size, stack_size_check;
  void *stack_addr;

  s = pthread_attr_getguardsize(attr, &guard_size);
  if (s != 0)
    handle_error_en(s, "pthread_attr_getguardsize");
  printf("%sGuard size          = %d bytes\n", prefix, guard_size);

  s = pthread_attr_getstack(attr, &stack_addr, &stack_size);
  if (s != 0)
    handle_error_en(s, "pthread_attr_getstack");
  printf("%sStack address       = %p", prefix, stack_addr);
  if (stack_size > 0)
    printf(" (EOS = %p)", (char *) stack_addr + stack_size);
  printf("\n");
  s = pthread_attr_getstacksize (attr, &stack_size_check);
  if (s != 0)
    handle_error_en(s, "pthread_attr_getstacksize");
  assert (stack_size_check == stack_size);
  printf("%sStack size          = 0x%x (%d) bytes\n",
      prefix, stack_size, stack_size);
}

static void display_thread_attr(pthread_t thread, char *prefix) {
  int s;
  pthread_attr_t attr;

  s = pthread_getattr_np(thread, &attr);
  if (s != 0)
    handle_error_en(s, "pthread_getattr_np");

  display_stack_attr (&attr, prefix);

  s = pthread_attr_destroy(&attr);
  if (s != 0)
    handle_error_en(s, "pthread_attr_destroy");
}

static void * thread_start(void *arg) {
  printf("Attributes of created thread:\n");
  display_thread_attr (pthread_self(), "\t");

  exit(EXIT_SUCCESS);         /* Terminate all threads */
}

int main(int argc, char *argv[])
{
  int s;
  pthread_t thr;
  pthread_attr_t attr;

  s = pthread_create(&thr, NULL, &thread_start, NULL);
  if (s != 0)
    handle_error_en(s, "pthread_create");

  pause();    /* Terminates when other thread calls exit() */
}

