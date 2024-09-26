#ifndef FAKE_STDIO_H
#define FAKE_STDIO_H

#include <stdio.h>
#include <stdlib.h>
#include "fatfs.h"

#define newlib_FILE     FILE
#define newlib_fopen    fopen
#define newlib_fclose   fclose
#define newlib_fseek    fseek
#define newlib_rewind   rewind
#define newlib_ftell    ftell
#define newlib_feof     feof
#define newlib_fread    fread
#define newlib_fwrite   fwrite
#define newlib_fprintf  fprintf
#define newlib_fgetc    fgetc
#define newlib_getc     getc
#define newlib_fputc    fputc
#define newlib_putc     putc
#define newlib_fgets    fgets
#define newlib_fputs    fputs
//#define newlib_truncate truncate
#define newlib_fflush   fflush
//#define newlib_stat     stat
#define newlib_ungetc   ungetc
#define newlib_ferror   ferror
#define newlib_fgetpos  fgetpos
#define newlib_fsetpos  fsetpos

#undef FILE   
#undef fopen  
#undef fclose 
#undef fseek  
#undef rewind 
#undef ftell  
#undef feof   
#undef fread  
#undef fwrite 
#undef fprintf
#undef fgetc
#undef getc
#undef fputc
#undef putc
#undef fgets
#undef fputs
//#undef truncate
#undef fflush
//#undef stat
#undef ungetc
#undef ferror
#undef fgetpos
#undef fsetpos

#define FILE     FIL
#define fopen    fake_fopen
#define fclose   fake_fclose
#define fseek    fake_fseek
#define rewind   fake_rewind
#define ftell    fake_ftell
#define feof     fake_feof
#define fread    fake_fread
#define fwrite   fake_fwrite
#define fprintf  f_printf
#define fgetc    fake_fgetc
#define getc     fake_fgetc
#define fputc    f_putc
#define putc     f_putc
#define fgets    f_gets
#define fputs    f_puts
//#define truncate fake_truncate
#define fflush   f_sync
//#define stat     fake_stat
#define ungetc   fake_ungetc
#define ferror   fake_ferror
#define fgetpos  fake_fgetpos
#define fsetpos  fake_fsetpos

static inline FILE *fake_fopen(const char *path, const char *pcMode)
{
    FIL *fp = (FIL *)malloc(sizeof(FIL));
    uint8_t ucModeBits = 0x00;
    while( *pcMode != '\0' )
    {
        switch( *pcMode )
        {
            case 'r': /* Allow Read. */
            case 'R':
                ucModeBits |= FA_READ;
                break;

            case 'w': /* Allow Write. */
            case 'W':
                ucModeBits |= FA_WRITE;
                ucModeBits |= FA_CREATE_ALWAYS; /* Create if not exist. */
                break;

            case 'a': /* Append new writes to the end of the file. */
            case 'A':
                ucModeBits |= FA_WRITE;
                ucModeBits |= FA_OPEN_APPEND;
                break;

            case '+':                        /* Update the file, don't Append! */
                ucModeBits |= FA_READ;
                ucModeBits |= FA_WRITE; /* RW Mode. */
                break;

            case 'b':
            case 'B':
                /* b|B flags not supported (Binary mode is native anyway). */
                break;

            default:
                break;
        }
        pcMode++;
    }
    if (f_open(fp, path, ucModeBits) != FR_OK) {
        free(fp);
        return NULL;
    }
    return fp;
}

static inline int fake_fclose(FILE *fp)
{
    f_close(fp);
    free(fp);
    return 0;
}

static inline int fake_fseek(FILE *fp, long offset, int whence)
{
    if (whence == SEEK_SET)
        return f_lseek(fp, offset);
    if (whence == SEEK_END && whence == 0)
        return f_lseek(fp, f_size(fp));
    if (whence == SEEK_CUR)
        return f_lseek(fp, f_tell(fp)+offset);
    return -1;
}

static inline void fake_rewind(FILE *fp)
{
    f_lseek(fp, 0);
}

static inline long fake_ftell(FILE *fp)
{
    return f_tell(fp);
}

static inline int fake_feof(FILE *fp)
{
    return f_eof(fp);
}

static inline size_t fake_fread(void *ptr, size_t size, size_t nitem, FILE *fp)
{
    UINT res;
    FRESULT err = f_read(fp, ptr, size*nitem, &res);
    if (err) {
        iprintf("fread %p %u %u %p = %u\n", ptr, size, nitem, fp, res);
        iprintf("error = %d\n", err);
        exit(1);
    }
    return res / size;
}

static inline size_t fake_fwrite(const void *ptr, size_t size, size_t nitem, FILE *fp)
{
    UINT res;
    FRESULT err = f_write(fp, ptr, size*nitem, &res);
    if (err) {
        iprintf("write %p %u %u %p = %u\n", ptr, size, nitem, fp, res);
        iprintf("error = %d\n", err);
        exit(1);
    }
    return res / size;
}

static inline int fake_fgetc(FILE *fp)
{
    unsigned char c;
    size_t amt = fake_fread(&c, 1, 1, fp);
    return amt == 0 ? EOF : (unsigned int)c;
}

static inline int fake_ungetc(int c, FILE *fp)
{
    if (f_tell(fp) < 1)
        return -1;
    f_lseek(fp, f_tell(fp)-1);
    return 0;
}

static inline int fake_ferror(FILE *stream)
{
    return 0;
}

static inline int fake_fgetpos(FILE *stream, fpos_t *pos)
{
    *pos = f_tell(stream);
    return 0;
}

static inline int fake_fsetpos(FILE *stream, fpos_t *pos)
{
    f_lseek(stream, *pos);
    return 0;
}

#endif
