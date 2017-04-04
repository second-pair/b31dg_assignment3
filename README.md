#  b31dg_assignment3
Assignment 3 for the Heriot-Watt B31DG Course

##  Requirements
This project requires a few things to build:
1.  A suitable mbed-compatible compilation toochain.
	*  This project is using the `ARM_GCC` toolchain, but this can be changed in the *Makefile*.
	*  These toolchains are most likely available from your package manager as well as from the developer's website.
1.  `make` (Optional).
1.  `git`.
1.  `hg` (Mercurial).
1.  `python2` (the `mbed-cli` does Not support `python3`, but can run alongside it).
1.  The `mbed_cli` CLI.

##  Environment Installation Instructions (Windows)
I had difficulty and encountered a lot of problems getting this to work, so I thought I'd share my $0.02.
1.  Install the toolchain, `make`, `git` and `hg` - I used:
	*  `make` "Complete package, except sources".
	*  `git` "64-bit git for Windows Setup".
	*  `hg` "Mercurial 4.1.1 MSI installer - x64 Windows".
	*  `python2` "Windows x86-64 MSI Installer".
1.	Configure *Path* (It's up to you whether you want to use the User or System *Path*):
	*  In the control panel classic view, navigate to *System -> Advanced Settings -> Environment Variables... -> Path -> Edit...*.
	*  Ensure the following locations are present (or wherever they ended up being installed to):
		*  *C:\Program Files (x86)\Python\Python27*.
		*  *C:\Program Files (x86)\Python\Python27\Scripts*.
		*  *C:\Program Files\Mercurial\*.
		*  *C:\Program Files\Git\cmd*.
		*  *C:\Program Files (x86)\GNU Tools ARM Embedded\6 2017-q1-update\bin*.
		*  *C:\Program Files (x86)\GnuWin32\bin*.
1.  Relaunch any CMD windows.
1.  Install the `mbed-cli` with `pip2 install mbed-cli` in an elevated prompt.
	*  Note:  If you have Python3 installed and don't specify `pip2` or `pip2.7`, you will likely end up with a non-working copy installed with Python3.

###  A note about `python3`:
If you also have `python3` installed, you may want to consider adding these to your *Path* as well:
	*  *C:\Users\Blair Edwards\AppData\Local\Programs\Python\Python36-32*
	*  *C:\Users\Blair Edwards\AppData\Local\Programs\Python\Python36-32\Scripts*
Also, instead of invoking using the `python` command, consider using `py`, which is included on the *Path* at *C:\Windows*.
If you are running a script with a valid shebang, the launcher should auto-detect the correct  varsion and run it accordingly.
Otherwise, this will enable you to run a `python2` script with `py -2 py2Script.py` and a `python3` script with `py -3 py3Script.py`. 
These versions should then coexst nicely, with the exception of `pip` as discussed above.

##  Project Setup Instructions
1.  Clone the project with git:
	*  `git clone https://github.com/second-pair/b31dg_assignment3.git`
1.  Initialise using the `mbed_cli`:
	*  `cd b31dg_assignment3`
	*  `pip2 install -r .temp\tools\requirements.txt`
	*  `mbed deploy`

##  Compilation Instructions
While this project can be compiled using `mbed compile`, a *Makefile* has also been provided.
This currently only works in a Windows environment.
The *Makefile* currently accepts the following arguments:
*  libs: Builds a static copy of the libraries.
*  srcs: Builds the source files (assumes libraries have been statically built).
*  make: Runs `srcs` (this is what is run if `make` is run without any arguments).
*  all: Runs `libs` then `srcs`.
*  clean: Cleans built files form the project.

For example, running `make all` will recompile the static libraries and then compile the main source.

##  Links
*  `mbed_cli` documentation available from <https://docs.mbed.com/docs/mbed-os-handbook/en/5.1/dev_tools/cli/>.
*  This project's repository is <https://github.com/second-pair/b31dg_assignment3.git>.

###  Windows-specific download locations:
*  `arm_gcc` toolchain available from <https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads>.
*  `make` available from <http://gnuwin32.sourceforge.net/packages/make.htm>.
*  `git` available from <https://git-scm.com/downloads>.
*  `hg` available from <https://www.mercurial-scm.org/downloads>.
*  `python2` available from <https://www.python.org/downloads/windows/>.
