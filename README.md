# Overview
This project has some objectives.
* Implementing number crunching library with a manner regularly generalized to
multiple base number types, `float`,`double`, `float complex`, and `double complex`.
* Coding style keeps MISRA-C compliant.
* C99 built-in complex number is fully utilized.
* All codes and their background theories are well documented even in the case of complicated mathematical background. The documentation depends on LaTeX Markdown
to render readable mathematical formulus.
* Global scope identifiers exported by the library are prefixed by a common project
prefix `SLC` meaning `Small Library for C`.

# Directory Structure
* `L2`: Project root directory
    - `00Base`: Common basic definitions and functions
    - `01Math`: Mathematical functions
    - `00BaseUT`: Unit tests for `00Base`
    - `01MathUT`: Unit tests for `01Math`
    - `bin`: Compiled binary files
        + `debug`: Debug built binaries
            * `o`: Object files
        + `release`: Release built binaries
            * `o`: Object files
    - `include/SLC`: Header files
    - `README.md`
    - `LICENSE`
    - `.gitignore`
