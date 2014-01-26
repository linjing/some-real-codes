#include <string>
#include <vector>

using namespace std;


#ifndef WIN32
#include <iconv.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#define OUTBUF_SIZE 7
//#define OUTBUF_SIZE 32768

#define error(a,b,c,...) fprintf(stderr, c, ##__VA_ARGS__)

static int process_block(iconv_t cd, char *addr, size_t len, char *to_addr, size_t * to_len)
{
    const char *start = addr;
    char outbuf[OUTBUF_SIZE];
    char *outptr;
    size_t outlen;
    size_t n;
    int max_len = *to_len;
    int total_len = 0;

    while (len > 0) {
        outptr = outbuf;
        outlen = OUTBUF_SIZE;
        n = iconv(cd, &addr, &len, &outptr, &outlen);

        if (outptr != outbuf) {
            /* We have something to write out.  */
            int errno_save = errno;

            if (total_len + (outptr - outbuf) <= max_len) {
                memcpy(to_addr + total_len, outbuf, (outptr - outbuf));
                total_len += (outptr - outbuf);
                *to_len = total_len;
            } else {
                return -1;
            }

            errno = errno_save;
        }

        //?/if (n != (size_t) - 1) {
        //?/    /* All the input test is processed.  For state-dependent
        //?/       character sets we have to flush the state now.  */
        //?/    outptr = outbuf;
        //?/    outlen = OUTBUF_SIZE;
        //?/    n = iconv(cd, NULL, NULL, &outptr, &outlen);

        //?/    if (outptr != outbuf) {
        //?/        /* We have something to write out.  */
        //?/        int errno_save = errno;

        //?/        if (total_len + (outptr - outbuf) <= max_len) {
        //?/            memcpy(to_addr + total_len, outbuf, (outptr - outbuf));
        //?/            total_len += (outptr - outbuf);
        //?/            *to_len = total_len;
        //?/        } else {
        //?/            return -1;
        //?/        }

        //?/        errno = errno_save;
        //?/    }

        //?/    if (n != (size_t) - 1)
        //?/        break;
        //?/}

        if (errno != E2BIG)
        {
            /* iconv() ran into a problem.  */
            switch (errno)
            {
            case EILSEQ:
                error(0, 0, ("illegal input sequence at position %ld:%s\n"),
                      (long int)(addr - start), addr);
                break;
            case EINVAL:
                error(0, 0, ("\
                             incomplete character or shift sequence at end of buffer\n"));
                break;
            case EBADF:
                error(0, 0, ("internal error (illegal descriptor)\n"));
                break;
            default:
                error(0, 0, ("unknown iconv() error %d\n"), errno);
                break;
            }

            return -1;
        }
    }

    return 0;
}

// $ export | grep LANG
// declare -x LANG="zh_CN.UTF-8"

string get_language_encoding() {
    const char *lang = getenv("LANG");
    if (!lang)
        return "";
    const char *p = strchr(lang, '.');
    if (!p)
        return "";
    string s = p + 1;
    return s;
}

bool is_utf8 (const string &encode) {
    return (strcasestr(encode.c_str(), "UTF8") || strcasestr(encode.c_str(), "UTF-8"));
}

static int cli_iconv(char *addr, size_t len, char *to_addr, size_t * to_len)
{
    string encode = get_language_encoding();
    if (is_utf8 (encode)) {
        memcpy(to_addr, addr, len);
        *to_len = len;
        return 0;
    }

    iconv_t cd;
    cd = iconv_open("UTF8", encode.c_str());
    if (cd == (iconv_t) - 1) {
        return -1;
    }

    int ret = process_block(cd, addr, len, to_addr, to_len);
    iconv_close(cd);
    return ret;
}
#endif

#ifdef WIN32                    //WideCharToMultiByte
BOOL ConvertString(const char *strSrc, UINT nSrcCodePage, char *strDes, UINT nDecCodePage,
                   int nMaxDesLen);
static int cli_iconv(char *addr, size_t len, char *to_addr, size_t * to_len)
{
    bool ret = ConvertString(addr, CP_ACP, to_addr, CP_UTF8, *to_len);
    if (ret)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

BOOL ConvertString(const char *strSrc, UINT nSrcCodePage, char *strDes, UINT nDecCodePage,
                   int nMaxDesLen)
{
    //.....
    size_t nTmpBufSize = MultiByteToWideChar(nSrcCodePage, 0, strSrc, -1, NULL, 0);
    if (nTmpBufSize == 0)
        return FALSE;

    wchar_t *pStrTmpBuffer = new wchar_t[nTmpBufSize + 1];
    nTmpBufSize =
        MultiByteToWideChar(nSrcCodePage, 0, strSrc, -1, pStrTmpBuffer, (int)nTmpBufSize);
    if (nTmpBufSize == 0)
    {
        if (pStrTmpBuffer)
            delete[]pStrTmpBuffer;

        return FALSE;
    }
    //.........
    nTmpBufSize =
        WideCharToMultiByte(nDecCodePage, 0, pStrTmpBuffer, -1, strDes, nMaxDesLen, NULL, NULL);

    if (pStrTmpBuffer)
        delete[]pStrTmpBuffer;

    return nTmpBufSize != 0;

}
#endif

// Not add a null automatically.
// addr[len] should be readable, and to_addr[to_len] should be writable
int cli_iconv2(char *addr, size_t len, char *to_addr, size_t * to_len)
{
    if (len > *to_len)
        return -1;

    int i = 0;
    char *addr_bak = addr;
    char *to_addr_bak = to_addr;

    //copy data from addr to to_addr for asciis >0
    while ((i = *to_addr++ = *addr++) > 0) ;

    //Has non-ascii
    if (i < 0)
        return cli_iconv(addr_bak, len, to_addr_bak, to_len);
    else
        *to_len = len;
    return 0;
}

bool utf8_string (const char *input_str, vector<char> &output_str)
{
    // input_str is null-terminated.
    size_t len = strlen(input_str);
    vector<char> input (&input_str[0], &input_str[len]);
    printf ("%d [%s] \n", len, &input[0]);

    output_str.resize (len * 6 + 1);
    size_t len2 = output_str.size () - 1;    // must add one null manually.
    printf ("%zd %zd %zu\n", len, len2, output_str.size ());

    int ret = cli_iconv2((char *)&input[0], len, (char *)&output_str[0], &len2);
    fprintf (stderr, "ret %d\n", ret);
    if (ret < 0)
        return false;
    return true;
}

int main (int argc, char **argv) {
    vector<char> output_str;
    if (utf8_string ("新东方是大家开发\n", output_str))
        fprintf(stderr, "Title is %s\n", &output_str[0]);
    else
        fprintf(stderr, "Failed \n");
    return 0;
}
