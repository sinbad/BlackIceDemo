# Black Ice Demo (1995, DOS, Turbo Assember 4.0)

I'm putting this code online for posterity, this was the one and only project I 
ever wrote 100% in assembly language, in early 1995. It's now 20 years later and
it's probably useless, but screw it, it's personal history :)

I wrote this for a bulletin board called Black Ice, run by a friend of mine
here in Guernsey in 90's. It was a typical demo teaser featuring VGA effects 
like a 'scrolly' message using ModeX, simulated fire, image scaling/warping and
so on, all featuring details of the BBS and some art from local friends. 

It was originally designed for DOS (written before Windows 95 came out). You 
can't even run it any ore on modern versions of Windows I'm afraid, given the
way it plays with some of the hardware; it was very much of its time.

The original README can be found in [README.SRC](README.SRC). Originally this
code was shared on FTP sites like `x2ftp.oulu.fi` and `ftp.sunet.se`. If you
remember those, you're as old as I am :)

## Data files

I've omitted the data files, music and image data mostly, because they're all
in processed form anyway - there are no image decoders in this code, all data 
was extracted pre-flight with C tools I built (I've lost them) and embedded in
the data segment directly, e.g. as colour (.dat) and palette (.pal) data, during
linking. Old skool, baby.

## Libraries 
I only used one library, everything else was made from scratch. I used
Future Crew's STMIK (Scream Tracker Music Interface Kit) to play music in the 
demo, again this isn't embedded here, it was just an OBJ file.

## Filenames
Some of the filenames have numbers in them, because in 1995 I wasn't using
source control yet. Don't judge me, I'd only used Visual Sourcesafe at the time,
and it was rubbish (and I didn't have a license for home). I didn't discover
CVS until the late 1990s.

## License

*Seriously?*

If you're crazy enough to want to use this code for anything today, knock
yourself out. Consider it public domain - I can't even guarantee I didn't use
other people's code in here, back then most of us didn't even know about 
open source / licenses and just exchanged code freely on BBS's and the 
aforementioned FTP sites.