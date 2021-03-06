#include <assert.h>
#include <stdio.h>

#include "../xhash.h"

void
test_iteration(int ec)
{
  xhash x;
  xh_entry *it;
  int i, c = 0;

  xh_init_int(&x, sizeof(int));

  for (i = 0; i < ec; ++i) {
    xh_put_int(&x, i, &i);
  }

  i = 0;
  for (it = xh_begin(&x); it != NULL; it = xh_next(it)) {
    ++c;
    assert(i++ == xh_val(it, int));
  }

  assert(c == ec);
}

void
test_resize(size_t c)
{
  xhash x;
  size_t i;

  xh_init_int(&x, sizeof(int));

  for (i = 0; i < c; ++i) {
    xh_put_int(&x, i, &i);
  }

  assert(x.count == c);
  assert(x.count <= x.size * XHASH_RESIZE_RATIO);
}

void
test()
{
  xh_entry *e;
  xhash x;
  int one = 1, two = 2, three = 3;

  xh_init_str(&x, sizeof(int));

  xh_put_str(&x, "aaaaa", &one);
  xh_put_str(&x, "bbbbb", &two);
  xh_put_str(&x, "aaaab", &three);

  e = xh_get_str(&x, "aaaaa");
  assert(e && xh_val(e, int) == one);
  e = xh_get_str(&x, "bbbbb");
  assert(e && xh_val(e, int) == two);
  e = xh_get_str(&x, "aaaab");
  assert(e && xh_val(e, int) == three);

  xh_destroy(&x);
}

int
main()
{
  puts("---- xhash test started ----");

  test();
  test_iteration(30);
  test_resize(300);

  puts("---- xhash test successfully finished ----");

  return 0;
}
