#!/usr/bin/perl
#
# Eurionize - add the so-called "EURion constellation" anti-copying mark
# to a postscript document.
#
# Copyright 2004 Asher Blum - licensed under the GNU GPL.
# Based on research by Markus Kuhn - http://www.cl.cam.ac.uk/~mgk25/eurion.pdf
#
# Version 0.1

use strict;

undef $/;
my $doc = <>;
my $ps = ps();
$doc =~ s|([^/])showpage|$1ashershowpage|g;
$doc =~ s/%%BeginProlog/%%BeginProlog\n$ps/;
print $doc;

sub ps {
    my $ps = <<EOT;
    
/zzdonut {
    /angle exch def
    /radius exch def
    gsave
    0.45 setlinewidth
    1.417 1.417 scale
    angle rotate
    radius 0 0.72 0 360 arc stroke
    grestore
} def
    
/zzconstellation {
    1 1 0 setrgbcolor
    0 0      zzdonut
    7.8 0    zzdonut
    7.2 72   zzdonut
    4.8 168  zzdonut
    4.9 249  zzdonut
} def

/ashershowpage {
    gsave
    matrix defaultmatrix setmatrix
    1 1 5 {
        pop
        100 100 translate zzconstellation
    } for
    grestore
    showpage
} def
EOT
    $ps;
}
