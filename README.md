
<p align="center"> <img src="./icon.png" alt="icon" width="100" height="100" /> </p>

# Samurai

Samurai is a simple password generator for the command line. Simple is the magic word, the source is very simple and clean but additionally the generated passwords are human readable, pronouncable and easily typed. Most of the benefits of a long and strong password with less drawbacks. No more 30 character password strings of garbled text, numbers and special characters that only computers can distinguish.

## Getting Started

To get a build of Samurai up and running on your local machine the following tools are required:

* A working installment of GCC
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
-x <int>:	 Set the amount of generated passwords. Defaults to 1.
-l <int>:	 Set the length of the generated passwords. Defaults to 12.
-n <int>:	 Set the amount of numbers in the generated passwords. Defaults to 0.
-c:		 Enable capitalization of the generated passwords.
-s:		 Add a special character to the generated passwords.
```

Good luck!

## Contributors

* **Frederik Christian Slothouber** - *Initial work* - [wollemat](https://github.com/wollemat)
* Icon made by [monkik](https://www.flaticon.com/authors/monkik) from [www.flaticon.com](https://www.flaticon.com)
