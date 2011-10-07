package Archive::Peek::Libarchive;
use strict;
use warnings;
use Object::Tiny qw{ filename };
our $VERSION = '0.35';

require XSLoader;
XSLoader::load( 'Archive::Peek::Libarchive', $VERSION );

sub files {
    my $self     = shift;
    my $filename = $self->filename;
    my @files    = Archive::Peek::Libarchive::_files($filename);
    return @files;
}

sub file {
    my ( $self, $filename ) = @_;
    my $archive_filename = $self->filename;
    my $file
        = Archive::Peek::Libarchive::_file( $archive_filename, $filename );
    return $file;
}

1;
