#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include <archive.h>
#include <archive_entry.h>
/* #include "ppport.h" */

typedef struct archive* Archive__Peek__Libarchive;

struct archive* _open_file(const char * filename) {
    struct archive *a;
    int r;

    a = archive_read_new();
    archive_read_support_compression_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_file(a, filename, 10240))) {
        croak(archive_error_string(a));
    }
    return a;
}

void _close_file(struct archive* a) {
    archive_read_close(a);
    archive_read_finish(a);
}
    
MODULE = Archive::Peek::Libarchive          PACKAGE = Archive::Peek::Libarchive

void _files(const char * filename)
PPCODE:
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = _open_file(filename);

    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
	if (r != ARCHIVE_OK)
            croak(archive_error_string(a));
        if (archive_entry_filetype(entry) == AE_IFREG) {
            mXPUSHs(newSVpv(archive_entry_pathname(entry), 0));
        }
    }
    _close_file(a);

void _file(const char * archivename, const char * filename)
PPCODE:
    struct archive *a;
    struct archive_entry *entry;
    int r;
    const void *buffer;
    size_t size;
    off_t offset;
    SV* sv;
    SV* temp;

    a = _open_file(archivename);
    sv = newSVpvs("");
        
    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
	if (r != ARCHIVE_OK)
            croak(archive_error_string(a));
        if (archive_entry_filetype(entry) == AE_IFREG && (strcmp(archive_entry_pathname(entry), filename)) == 0) {
	    for (;;) {
                r = archive_read_data_block(a, &buffer, &size, &offset);
		if (r == ARCHIVE_EOF) {
                    break;
		}
		if (r != ARCHIVE_OK) {
                    croak(archive_error_string(a));
                }
		sv_catpvn(sv, buffer, size);
            }
        }
    }
    XPUSHs(sv);
    _close_file(a);
