# Coding Rules
## Contents
* [Project Directories](#project-directories)
    - [Directory Tree](#directory-tree)
    - [Naming Rules](#naming-rules)
* [Files](#files)
    - [Naming Rules](#naming-rules)
    - [Text Organization](#text-organization)
        + [Text Sizes](#text-sizes)
        + [Indent](#indent)
        + [Braces](#braces)
        + [Declaring Function Prototype](#declaring-function-prototype)
* [Identifiers](#identifiers)
    - [Common Rules for Local Scope Identifers](#common-rules-for-local-scope-identifiers)
    - [Common Rules for Global Scope Identifers](#common-rules-for-global-scope-identifiers)
    - [Type Names](type-names)
* [Error Handling](#error-handling)
    - [Detecting Data Independent Defect](#detecting-data-independent-defect)
    - [Detecting Data Dependent Defect](#detecting-data-dependent-defect)

## Project Directories
### Directory Tree
`Rule`: Each project has its own root directory.<br/>
`Rule`: The project root directory has one or more source directories.<br/>
`Rule`: The project root directory has one or more deliverable directories.<br/>
`Rule`: An application project root directory has a binary deliverable directory.<br/>
`Rule`: An library project root directory has a binary deliverable directory and
an `include` deliverable directory.<br/>
`Rule`: The project root directory can have one or more directories for intermediate
files <br/>

### Naming Rules
`Rule`: Directory names consists of only English alphabet [A-Za-z], digits [0-9],
and underscores '_'.<br/>
`Rule`: A continuous sequence of two or more underscores is not allowed.
&nbsp;&nbsp;&nbsp;&nbsp;`Example which is not allowed`:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;__A_Directory<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A__Directory<br/>
`Rule`: It is not allowed to make two or more directories with names different only
by case variation in a same directory.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;`Example which is not allowed`:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    ProjRoot/A_Second_Level/<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    ProjRoot/a_Second_Level/<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    ProjRoot/A_second_level/<br>

## Files
### Naming Rules
`Rule`: File names consists of only English alphabet [A-Za-z], digits [0-9],
underscores '\_', and periods '.'.<br/>
`Rule`: A continuous sequence consisting of only two or more underscores
and periods is not allowed.
&nbsp;&nbsp;&nbsp;&nbsp;`Example which is not allowed`:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A_File_.c<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A__File.c<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A_File..c<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A_File._text<br/>
`Rule`: It is not allowed to make two or more directories with names different only
by case variation in a same directory.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;`Example which is not allowed`:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    ADirectory/A_File.c/<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    ADirectory/a_File.c/<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    ADirectory/A_file.c/<br>
`Rule`: File extension of c++ source is `cpp` and of c++ header file is `hpp`.
- Header filename without extension is not allowed.
- Source filename extensions, 'cxx' or 'C' are not allowed.

### Text Organization
#### Text Sizes
- Maximum line count: 9999
- Maximum line length: 75 visible characters including white spaces<br/>
Note: It is suitable to A4 portrait layout with 4 digit line numbers and single space separators.

#### Indent
- One indent level is four space characters.
- Indentation is made of only space characters in `c` source and header files.
- Indentation is made of only tab characters in `make` files.

#### Braces
`Rule`: In `c` language, code blocks are enclosed by pairs of braces. An opening brace `{` and a closing brace `}` of a pair must be in a same column.<br/>
`Rule`: The column must be at the first postion of an indent level.<br/>
`Rule`: The column must be in the same indent level of preceding `if`, `for`,
`switch`, `do`, etc.<br/>
`Example`<br/>
```
    // Recommended layout
    for (int i = 0; i < N; i++)
    {
        // some useful operations
    }

    // Not recommended layout
    // due to difficulties of identifying a code block
    for (int i = 0; i < N; i++) {
        // some useful operations
    }
```
#### Declaring Function Prototype
`Rule`: Global scope functions are declared in header files.<br/>
`Rule`: Global scope function declarations are commented by doxygen style comments.<br/>
`Rule`: Global scope function declarations begins from the first column<br/>

## Identifiers
### Common Rules for Local Scope Identifers
#### __Structure of Identifiers__

### Common Rules for Global Scope Identifiers
#### __Project Specific Prefix__

#### __Structure of Identifiers__

#### 

### Global Scope Type Names
#### __`postfix`__

#### __`enum`__

#### __Function Pointer__

#### __Redefining built-in types__

#### __`struct` and `union`__

### Macro Names

### Function Names

### Variable Names

#### Arguments of Functions

#### Arguments of Macros

### Identifiers Derived from Well-known Existing Ones

## Error Handling
### Detecting Data Independent Defect

### Detecting Data Dependent Defect


