# Simple C Book Downloader

### A pdf/djvu/epub downloader using [Library Genesis](http://gen.lib.rus.ec/).

#### Installation

##### ArchLinux based distros

`yay -S scbd-git`

##### Others

`git clone https://github.com/josecleiton/book-downloader.git`

`cd book-downloader/src`

`sudo make install`

`scbd -h`

#### Usage

Required arguments:

        -s               Set the string search (usually author/book name)


Optional arguments:

        -h               Show this help message

        -o               Set another sort order { id | author | title | publisher | year | pages | filesize | extension }

        -m               Set another sort mode { ASC[endant] | DESC[endant] }

        -b               Set another reference folder (where .bib will be downloaded) [empty string to ignore bib file]

        -d               Set another book folder [empty string to ignore book file]

        -v               Verbose mode

usage: `scbd -s STR [ -b STR ] [ -d STR ] [ -o STR ] [ -m ASC | DESC ] [ -v ]`

Don't forget to read the `LICENSE` file.
