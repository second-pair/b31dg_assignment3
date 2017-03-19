#  b31dg_assignment3
Assignment 3 for the Heriot-Watt B31DG Course

##  Requirements
This project requires a few things to build:
1.  A suitable mbed-compatible compilation toochain.
	*  This project is using the `ARM_GCC` toolchain, but this can be changed in the *Makefile*.
	*  These toolchains are most likely available from your package manager as well as from the developer's website.
1.  The `mbed_cli` CLI.

##  Setup Instructions
1.  Clone the project with git:
	*  `git clone https://github.com/second-pair/b31dg_assignment3.git`
1.  Initialise using the `mbed_cli`:
	*  `cd b31dg_assignment3`
	*  `mbed deploy`
	*  `mbed new .`

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
*  `arm_gcc` toolchain available from <https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads>.
*  `mbed_cli` documentation available from <https://docs.mbed.com/docs/mbed-os-handbook/en/5.1/dev_tools/cli/>.
*  This project's repository is <https://github.com/second-pair/b31dg_assignment3.git>.
