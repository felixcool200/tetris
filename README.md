# Terminal Tetris with ncurses in C++ 
My simple terminal tetris game build using ncurses.

## Requirements
### Ncurses
To install ncurses on: inspired by [How To Install Ncurses Library In Linux](https://ostechnix.com/how-to-install-ncurses-library-in-linux/).
#### Debian based distros (Debian, Ubuntu, Mint, PopOS):
    $ sudo apt-get install libncurses5-dev libncursesw5-dev
#### Arch based distors ()
    $ sudo pacman -S ncurses
#### REHL based distros (Fedora,RHEL, CentOS)
    $ sudo yum install ncurses-devel
#### Other (install from source):
Download latest version
    $ wget https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.1.tar.gz
Extract the file:
    $ tar xzf ncurses-6.1.tar.gz
Move to the directory
    $ cd ncurses-6.1
Run the config
    $ ./configure --prefix=/opt/ncurses
Compile
    $ make
    $ sudo make install
Verify
    $ ls -la /opt/ncurses

## How to build using CMake
- Create a directory called build inside the folder
- Move into the build folder
- Run "cmake -S ../"
- The run "make"
- This creates a executable called Tetris.out
