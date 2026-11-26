# str_lib: small C string helpers

Version 1.0 (2026). Split from NewIO 0.12, https://github.com/cnystrom/newio

str_lib is a handful of C string helpers from NewIO: trimming trailing
whitespace, a counted-length copy into new memory, a plain `strlen`, and
`strlcpy`/`strlcat` for bounded copies.

## API

From `str_lib.h`:

| Function | What it does |
|---|---|
| `void strclean(char *s)` | Removes trailing whitespace in place. |
| `char *str_null_terminated(char *s, int num)` | Returns a new NUL-terminated copy of the first `num` characters of `s` (fewer if `s` has a NUL first; a negative `num` counts as 0). `s` need not be NUL terminated. Free the result. |
| `int str_len(char *s)` | Length of `s`, like `strlen`. |
| `size_t strlcpy(char *dst, const char *src, size_t siz)` | Bounded copy that always NUL terminates; returns `strlen(src)`. |
| `size_t strlcat(char *dst, const char *src, size_t siz)` | Bounded append; returns the length it tried to create. |

`str_lib_version.h` defines `STR_LIB_VERSION` ("1.0") and `STR_LIB_ORIGIN`.

## Dependencies

None. Only the C library.

## Build

```sh
make            # builds str_lib.a
make test       # builds and runs test_str_lib
make CC=clang test
make clean
```

## License

LGPL 2.1 or later, the same as NewIO. See `LICENSE` (GNU LGPL 2.1). `COPYING`
holds the GNU GPL 2, as in NewIO. Copyright Chris Nystrom; see the header of
each file for its years.

## Origin

Split from NewIO 0.12, https://github.com/cnystrom/newio (tag `newio-0.12`,
commit `ce54c5b`), directory `common/str_lib/`. The library code is Chris
Nystrom's original, copied unchanged except for the lines listed under
"Changes from NewIO" below.

Contact: Chris Nystrom <cnystrom@gmail.com>

## Changes from NewIO

- Added `strlcpy.c` and `strlcat.c`. NewIO 0.12's `str_lib/Makefile` lists
  them, but the third-party OpenBSD files were removed before NewIO was
  published, so `make` failed there. These are Chris's own 2026
  implementations from c-libs (`misc_lib/strlcpy.c`, `misc_lib/strlcat.c`),
  with one change each: line 19 includes `"str_lib.h"` instead of
  `"misc_lib.h"`.
- `str_null.c`: bug fix, see "Fixed in 1.0".
- Removed two old personal contact lines (a web-log URL and a chat handle) from the file headers, at Chris's request (2026). The rest of each header and the authorship are unchanged, so header-area line numbers are 2 lower than in NewIO.
- Added `str_lib_version.h`, `test_str_lib.c`, a `make test` target at the
  end of the `Makefile`, this README, `LICENSE` and `COPYING`.
- Not copied: `archive.sh` (it uploaded tarballs to an old newio.org server).

## Fixed in 1.0

- **`str_null_terminated()` kept only `num - 1` characters** (`str_null.c:3`,
  `:13-23`). The intended contract is clear from the code and its NewIO
  callers (`nio_lib/rw_stdio.c`, `d0/src/rw_ssh.c`). It `malloc()`s `num + 1`
  bytes, and callers pass a raw `read()`/`write()` buffer of `num` bytes to
  get a printable, NUL-terminated copy of all of it. `strlcpy(p, s, num)`
  dropped the last byte. It also read past a buffer with no NUL, because
  strlcpy scans for the end of `src`. And it overflowed when a failed
  `read()` passed `num == -1`. Now it copies up to `num` characters with
  `strncpy`, stopping at a NUL, always terminates, and treats a negative
  `num` as 0. Tested in `test_str_lib.c`.

## Known issues

Kept as in NewIO 0.12:

- `strclean.c:14-17`: on an empty or all-whitespace string the loop reads
  before the start of the buffer.
- On glibc 2.38 and later, `<string.h>` also declares `strlcpy`/`strlcat`.
  The prototypes match, and programs linked with `str_lib.a` use these
  copies.
