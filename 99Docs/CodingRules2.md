# Coding Rules
## 1 Contents
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

## 2 Project Directories
### 2.1 Directory Tree
`Rule`: Each project has its own root directory.<br/>
`Rule`: The project root directory has one or more source directories.<br/>
`Rule`: The project root directory has one or more deliverable directories.<br/>
`Rule`: An application project root directory has a binary deliverable directory.<br/>
`Rule`: An library project root directory has a binary deliverable directory and
an `include` deliverable directory.<br/>
`Rule`: The project root directory can have one or more directories for intermediate
files <br/>

### 2.2 Naming Rules
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

## 3 Files
### 3.1 Naming Rules
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

### 3.2 Text Organization
#### 3.2.1 Text Sizes
- Maximum line count: 9999
- Maximum line length: 75 visible characters including white spaces<br/>
Note: It is suitable to A4 portrait layout with 4 digit line numbers and single space separators.

#### 3.2.2 Indent
- One indent level is four space characters.
- Indentation is made of only space characters in `c` source and header files.
- Indentation is made of only tab characters in `make` files.

#### 3.2.3 Braces
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
#### 3.2.4 Declaring Function Prototype
`Rule`: Global scope functions are declared in header files.<br/>
`Rule`: Global scope function declarations are commented by doxygen style comments.<br/>
`Rule`: Global scope function declarations begins from the first column<br/>

## 4 Identifiers
### 4.1 Common Rules for Local Scope Identifers
#### 4.1.1 __Structure of Identifiers__
`Rule`: An identifier consists of single block of words.</br>
`Rule`: The block is made of single English words and/or numbers.</br>
`Rule`: The block with both of upper and lower case letters follow camel format.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;`Example`:`Iso14001Glossaries`, `AnalyzeHumanDna`, `i0`, `i1`, `i`, `x`<br/>
`Rule`: The block without lower case letters is made by concatinating words with underscores.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;`Example`:`ISO14001_GLOSSARIES`, `ANALYZE_HUMAN_DNA`, `I0`, `X`<br/>
`Rule`: The word blocks assigned to constant objects have identifiers without lower case letters. For example, a macro defined constant number has an identifer without lower case letters.<br/>
`Example`
```
#define UNIT_FLOAT  (1.0f)
#define MINUS_64    (-64)
```

### 4.2 Common Rules for Global Scope Identifiers
`Rule`: An identifier consists of two blocks of words combined with single underscore. </br>
`Rule`: In the case of library projects, The first block begins with a project specific prefix
followed by a module name in camel format.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;`Example`: `SLCArray`=[Prefix:`SLC`, Module name: `Array`]<br/>
`Rule`: The second block follows the rule of local scope identifiers.

#### 4.2.2 __Project Specific Prefix__
`Rule`: A project specific prefix consists of upper case letters upto four characters.<br/>
`Rule`: A project specific prefix is described in project `README.md`.
#### 4.2.3 __Structure of Identifiers__

### 4.3 Global Scope Type Names
#### 4.3.1 __Postfix__
Type names must end with one of postfixes.
Postfix | Meaning
--------|-----------
`_t`    | Usual type with real body
`_pt`   | Pointer to variable real body
`_cpt`  | Pointer to constant real body
`_f`    | function pointer
<br/>

#### 4.3.2 __Enumeration__
Identifiers of enum items consis of their type name removing its postfix and their item name.<br/>
`Rule`: The item name consists of one or more English words in upper case letters.<br/>
`Rule`: The words are concatinated with single underscores.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;`Example`: `ISO14001_GLOSSARIES`, `ANALYZE_HUMAN_DNA`
<br/><br/>
`Example of full definition of enumeration`
```
typedef enum
{
    SLCBookComponents_FRONT_COVER,
    SLCBookComponents_TABLE_OF_CONTENTS,
    SLCBookComponents_GLOSSARY,
    SLCBookComponents_PREFACE,
    SLCBookComponents_CHAPTERS,
    SLCBookComponents_INDEX,
    SLCBookComponents_REAR_COVER,
}
SLCBookComponents_t;
```
For example, `SLCBookComponents_FRONT_COVER` consists of two blocks.
The first block, `SLCBookComponents` which made of the type `SLCBookComponents_t` removing the postfix `_t`. The second block `FRONT_COVER` consists of two English
words, `FRONT` and `COVER`.

#### __Function Pointer__

#### __Redefining built-in types__
Focusing to regularity, built-in types are redefined as global scope identifiers.

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


