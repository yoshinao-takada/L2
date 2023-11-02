# Coding Rules
## About this document
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

Revision history
Rev.     Date   Author Description
00.00.00 231031 YT     Initial creation

## Overview
Following basic rules are intended.
* The coding rules shall be MISRA-C compliant.
* Too long identifier shall be avoid.
* Anything shall be as regular as possible.
Note: If you meet a situation not defined in this document,
please follow original MISRA-C rules.

## Rules
### Directory
T.B.D.
<!--
Each project must have a root directory. The root directory
has
* One or more build uinit (e.g. VisualStudio solution and projects),
* license document,
* readme file.
-->
### Files
* Character encoding shall be UTF-8 without BOM.
* Filenames and underscores shall begin with English alphabetical characters and consist of only alpha-numeric characters allowing upper and lower cases.
* In the case of large program it may be a good idea to place section numbers of design documents in filenames.

### Text Organization
* Line length shall be up to 75 visible characters. It is suitable to print in A4 portraite
with four digit line numbers.
* Line count in a file shall be up to 9999 for manageability.
* `#pragma region` and `#pragma endregion` directives shall be used to clarify logical code blocks.
Both of the directives must be accompanied by their label text describing the code block meanings.
* Every source file must begin with file header.
File header shall contain license statement, file description.
File header can optionally contain revision history.
Sample is available in [Markdown to C template](../98Tools/Template.md).
* Single function definition is not allowed to exceeds 50 lines.
* Single macro definition is not allowed to exceeds 10 lines.
* Local macro definition must be undefined as soon as it is not necessary.

### Generic Rules
Global scope identifiers must begin with their module names followed by
an uderscore and thier own descriptive names. In the case of library
projects, the module names begin with project prefix of capital letters.
<br/>
Example of project prefix: 'Q', 'PL', 'YT'
<br/>
Example of module name: 'Module', 'Uart', 'Adc', 'Array', 'RingBuffer'<br/>
Note: Use of abbreviation is recommended if it is well recognized in the relevant field.<br/>
    e.g. Geom: Geometry, 
<br/>
Example of Descriptive name: 'Init', 'ClearElements', 'FillWithZero'
<br/>
<br/>
Example of identifiers: 'QUart_Init', PLArray_ClearElements<br/>
In the case of redefinition of standard API or so, it is allowed for identifiers
to have no module name.<br/>
Example: `typedef int32_t I32_t;` <br/>
Example with project prefix and descriptive name: `#define Q_M_PI M_PI`

### Structured Element identifiers
#### Type names defined by `typedef`
Type names must have postfix '`_t`' for real body types.<br/>
Types of pointers which point variable real bodies must have postfix '`_pt`'.<br/>
Types of const pointers which point constant real bodies must have postfix '`_cpt`'.<br/>
TYpes of function pointers must have postfix '`_f`'.<br/>
Example<br/>
```
// variable body type
typedef float complex     SLC_C64_t;

// constant body type
typedef const SLC_C64_t   SLC_C64_ct;

// pointer type pointing a variable
typedef SLC_C64_t*        SLC_C64_pt;

// pointer type pointing a constant
typedef const SLC_C64_t*  SLC_C64_cpt;
```
This rule shall be applied to struct and union.

#### Enumeration items
Enumeration type name must also follows the above description. Items in an `enum`
declaration has one or more items. Each item name begins with its type name removing its postfix. A own name part of an enum item name is capitalized and its component english words are separated underscores.<br/>
Example<br/>
```
typedef enum 
{
  QLCModule1_EnumName_ENUM_0 = 0x8000,
  QLCModule1_EnumName_ENUM_1,
  QLCModule1_EnumName_ENUM_A,
  QLCModule1_EnumName_FAILURE,
  QLCModule1_EnumName_END_OF_ENUM,
}
QLCModule1_EnumName_t;
```
#### Macros
Macro names with global scope must consists of their module names followed by single underscore
sepertors and their descriptive names. The descriptive names consists of uppercase letters, numbers, and underscore word separators.<br/>
Arguments of functional macros must begin with single underscores and consists of camel formatted
alphanumeric strings.
Example<br/>
```
// global scope constant macro
#define QLCModule1_CONSTANT_MACRO_NAME    "a literal const string"

// global scope functional macro
#define QLCModule1_FUNCTIONAL_MACRO_NAME(_varFirst, _varSecond) \
  if (_varFirst > 0) { _varSecond = 1; } else { _varSecond = -1; }
```
Local scope macro must begin with uppercase letters and consists of upperscore alphabetical
characters, digits, and word separator underscores.<br/>
Example<br/>
```
// internal scope constant macro
#define CONSTANT_MACRO_NAME   "an internal scope literal string"

// internal scope functional macro
#define FUNCTIONAL_MACRO_NAME(_varFirst, _varSecond) \
  if (_varFirst > 0) { _varSecond = 1; } else { _varSecond = -1; }
```

#### Identifier Names Based on Well-known C/C++ Identifiers
There are many well-known C/C++ identifiers like
`HANDLE`, `FILE`, `errno_t`, etc.
Source codes which the coding rule is applied to contains identifiers based
on the well-known existing identifers, they do not need keep the rule exactly.<br/>
Example<br/>
```
// define an extended errno type
typedef SLC_I32_t SLC_errno_t;

// define custom handle type
typedef void* SLC_Ptr_t;
typedef SLC_Ptr_t SLC_HANDLE_t;
```

#### local variables
local variables must have camel formatted name beginning with lowercase letters.<br/>
Example<br/>
```
SLC_I32_t integralNumber;
const SLC_C64_t complexConstant = CMPLXF();
```

#### Assert
`assert` macro is recommended to detect design defect of programs.
In many cases, array size mismatching, null pointers, etc. do not depend
on data values but on fixed program structure. In these cases, `assert` macro
is easy and resource saving method.
`assert` macro is effective only in debug mode. And it shall not be used to
detect errors depending on data values like near singular matrices, iterative
numerical solver convergence error, etc.

#### Function Error Handling
`if-error-break` and `do-while` program structure is useful to create maintenable codes.
Please consider to use this structure if a code block must detect errors
in a sequential execution of statements.<br/>
Example<br/>
```
#define  BUFFER_SIZE    1024
SLC_errno_t   SLCModule_FunctionReturnsError()
{
    SLC_errno_t err = EXIT_SUCCESS;
    // declare a pointer and initilize it to NULL
    SLC_R64_t* buffer = NULL;
    do
    {
        buffer = (SLC_R64_t*)malloc(BUFFER_SIZE);
        if (!buffer)
        { // no heap memory error
            err = errno;
            break;
        }

        //
        // do some useful operation
        //
    }
    while (0);
    if (buffer) // check NULL pointer
    {
        free(buffer);
        buffer = NULL;
    }
    return err;
}
#undef BUFFER_SIZE
```
