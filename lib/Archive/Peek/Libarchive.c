/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.2206 from the
 * contents of Libarchive.xs. Do not edit this file, edit Libarchive.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "lib/Archive/Peek/Libarchive.xs"
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
    
#line 39 "lib/Archive/Peek/Libarchive.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
            Perl_croak(aTHX_ "Usage: %s::%s(%s)", hvname, gvname, params);
        else
            Perl_croak(aTHX_ "Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
        Perl_croak(aTHX_ "Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#ifdef PERL_IMPLICIT_CONTEXT
#define croak_xs_usage(a,b)	S_croak_xs_usage(aTHX_ a,b)
#else
#define croak_xs_usage		S_croak_xs_usage
#endif

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#line 91 "lib/Archive/Peek/Libarchive.c"

XS(XS_Archive__Peek__Libarchive__files); /* prototype to pass -Wmissing-prototypes */
XS(XS_Archive__Peek__Libarchive__files)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "filename");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	const char *	filename = (const char *)SvPV_nolen(ST(0));
#line 33 "lib/Archive/Peek/Libarchive.xs"
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
#line 125 "lib/Archive/Peek/Libarchive.c"
	PUTBACK;
	return;
    }
}


XS(XS_Archive__Peek__Libarchive__file); /* prototype to pass -Wmissing-prototypes */
XS(XS_Archive__Peek__Libarchive__file)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "archivename, filename");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	const char *	archivename = (const char *)SvPV_nolen(ST(0));
	const char *	filename = (const char *)SvPV_nolen(ST(1));
#line 53 "lib/Archive/Peek/Libarchive.xs"
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
#line 181 "lib/Archive/Peek/Libarchive.c"
	PUTBACK;
	return;
    }
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Archive__Peek__Libarchive); /* prototype to pass -Wmissing-prototypes */
XS(boot_Archive__Peek__Libarchive)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    XS_VERSION_BOOTCHECK ;

        newXS("Archive::Peek::Libarchive::_files", XS_Archive__Peek__Libarchive__files, file);
        newXS("Archive::Peek::Libarchive::_file", XS_Archive__Peek__Libarchive__file, file);
#if (PERL_REVISION == 5 && PERL_VERSION >= 9)
  if (PL_unitcheckav)
       call_list(PL_scopestack_ix, PL_unitcheckav);
#endif
    XSRETURN_YES;
}

