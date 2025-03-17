# 특수 문자
문자 값에 들어갈 문자로 특수문자를 쓸 수 있습니다.   

특수문자에는 `\'` `\"` `\?'` `\\` `\n` `\t` 등이 있습니다.

`\'`는 작은 따옴표를, `\"`는 큰 따옴표를, `/?`는 물음표를, `\\`는 역슬래시를, `\n`은 줄바꿈을, `\t`는 탭을 의미합니다. 

#### 코드 예시:
```c
int c = '\''; /* '\''는 문자 '에 해당하는 정수 값을 의미합니다 */
```

#### 관련 C89 표준
[3.1.3.4 Character constants](https://port70.net/~nsz/c/c89/c89-draft.html#3.1.3.4)
> **Description**
>
> The double-quote and question-mark ? are representable either by themselves or
> by the escape sequences \" and "? respectively, but the single-quote ' and the backslahs \ shall be represented,
> respectively, by the escape sequences \' and \\.
>
> The octal digits that folow the backslashs in an octal escape sequence ...
>
> The hexadecimal digits that follow the backslash and the letter x in a hexadecimal escape sequence ...
>
> ... if any other escape sequence is encountered, the behavior is undefined.
>
> **Examples**
>
> The construction '\0' is commonly used to represent the null character.

[2.2.2 Character display semantics](https://port70.net/~nsz/c/c89/c89-draft.html#2.2.2)
> Alphabetic escape sequences representing nongraphic characters in the execution character set are intended to produce actions on display devices as
> ... ( "new line" ) Moves the active position to the initial position of the current line.
