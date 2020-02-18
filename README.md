

<p align="center"> <img src="./icon.png" alt="icon" width="100" height="100" /> </p>

# Samurai

Samurai is a simple password generator for the command line. Simple is the magic word, the source is very simple and clean but additionally the generated passwords are human readable, pronouncable and easily typed. No more 30 character password strings of garbled text that only computers can distinguish.

## Getting Started

To get a build of Sorbet up and running on your local machine the following tools are required:

* A working installment of the GCC compiler
* A working installment of CMake
* A working installment of Make


Building is as simple as running the following command in the root of the project:

```
$ cmake . && make
```

## Deployment

Running Samurai is just as easy as building it. Simply run the build executable and receive your generated password.

```
$ samurai
```

By default, Samurai will generate a single password of 12 characters long, not capitalized, without numbers and without special characters. The behavior of Samurai can be altered using a variety of flags:

| Flag | Argument | Description                                        |
|------|----------|----------------------------------------------------|
| -x   | int      | Set the number of passwords that are generated     |
| -l   | int      | Set the length of the generated passwords          |
| -c   | none     | Capitalize the generated passwords                 |
| -s   | none     | Add a special character to the generated passwords |
| -n   | none     | Add numbers to the generated passwords             |
| -h   | none     | Show a usage description                           |


### Examples

```
$ samurai

jariwufebivo

$ samurai -x 3

posafucalyqi
defunoqutiqa
wabajyqudixu

$ samurai -l 20

sumiryjumexusoloduxo

$ samurai -n 3

vakocitaf870

$ samurai -c

Zolacotehefa

$ samurai -s

tybubasefyk!

$ samurai -x 6 -l 12 -c -s -n

Garepuhucuhabywu!053
Pymukydulerosini$180
Qisofykifejyvipo$412
Jujavitydezijyha$521
Kapuqikoweqolyje%883
Cifehytyvehaxobu%992

$ samurai -h

Samurai: Human Readable Password Generator

Usage: samurai [-h] [-x <int>] [-l <int>] [-c] [-s] [-n]

-h:		 Print this help page.
-x <int>:	 Set the amount of generated passwords.
-l <int>:	 Set the length of the generated passwords.
-n <int>:	 Set the amount of numbers in the generated passwords.
-c:		 Enable capitalization of the generated passwords.
-s:		 Add a special character to the generated passwords.
```

Good luck!

## Authors

* **Frederik Christian Slothouber** - *Initial work* - [wollemat](https://github.com/wollemat)
