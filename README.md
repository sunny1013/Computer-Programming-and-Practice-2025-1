# 문자 값
문자 값은 문자에 해당하는 정수를 나타냅니다.   

`'` `문자` `'` 형태로 씁니다. `문자`는 작은 따옴표 `'`, 역슬래시 `\`, 엔터를 제외하고 쓸 수 있고, 특수문자 문법을 쓸 수도 있습니다. 

각 문자에 해당하는 정수는 컴파일러에서 정합니다. 

문자가 여러개 있을 경우, 한국어 사용 등의 경우에 해당하는 정수도 컴파일러에서 정합니다.  

#### 코드 예시:
```c
int c = 'a'; /* 'a'는 문자 a에 해당하는 정수 값을 의미합니다 */
```

#### 관련 C89 표준
[3.1.3.4 Character constants](https://port70.net/~nsz/c/c89/c89-draft.html#3.1.3.4)
> **Description**
>
> An integer character constant is a sequence of one or more multibyte characters enclosed in single-quotes, as in 'x' or 'ab'.
> ... With a few exceptions detailed later, the elementes of the sequence are any members of the source character set;
> they are mapped in an implementation-defined manner to members of the execution character set.
>
> **Semantics**
>
> An integer character constant has type int.
> The value of an integer character constant containing a single character that maps into a member of the basic execution character set
> is the numerical value of the representation of the mapped character interpreted as an integer.
> The value of an integer character constant containing more than one character, or containing a character or escape sequence
> not represented in the basic execution character set, is implementation-defined. ...

[2.2.1 Character sets](https://port70.net/~nsz/c/c89/c89-draft.html#2.2.1)
> Two sets of characters and their associated collating sequences shall be defined:
> the set in which source files are written, and the set interpreted in the execution environment.
> The value of the members of the execution character set are implementation-defined; ...
>
> In a character constant or string literal, members of the execution character set shall be represented by corresponding members of
> the source character set or by escape sequences consisting of the backslash \ followed by one or more characters.
> A byte with all bits set to 0, called the null character, shall exist in the basic execution character set; ...
>
> Both the basic source and basic execution character sets shall have at least the following members:
> the 26 upper-case letters of the English alphabet
>
> A B C D E F G H I J K L M
>
> N O P Q R S T U V W X Y Z
>
> the 26 lower-case letters of the English alphabet
>
> a b c d e f g h i j k l m
>
> n o p q r s t u v w x y z
>
> the 10 decimal digits
>
> 0 1 2 3 4 5 6 7 8 9
>
> the following 29 graphic characters
>
> ~ " # % & ' ( ) * + , - . / :
> ; < = > ? [ \ ] ^ _ { | } ~
>
> the space character, and control characters representing horizontal tab, vertical tab, and form feed.
>
> ... In source files, there shall be some way of indicating the end of each line of text;
> ... In execution character set, there shall be control characters representing alert, backspace, carriage return, and new line.
> If any other characters are encountered in a source file (except in a preprocessing token ... ), the behavior is undefined.

[3.1.2.5 Types](https://port70.net/~nsz/c/c89/c89-draft.html#3.1.2.5)
> ... If a member of the required source character set enumerated in 2.2.1 is ... guranteed to be positive.
> ... values are treated as ... integers. 
